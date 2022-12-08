/*
 ****************************************************************
 *								*
 *			cmp.c					*
 *								*
 *	Compara pares de arquivos				*
 *								*
 *	Vers�o	1.0.0, de 02.04.86				*
 *		4.6.0, de 27.08.04				*
 *								*
 *	M�dulo: cmp						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2004 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#include <a.out.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	4.6.0, de 27.08.04";

#define	elif	else if

#define QUICKSZ (4 * 1024)	/* Para a op��o "-q" */

entry char	*dirend;	/* Ponteiro para o final do nome do dir. */

entry int	lflag;		/* Lista as linhas diferentes */
entry int	pflag;		/* Aceita prefixos como iguais */
entry int	qflag;		/* Compara��o r�pida */
entry int	sflag;		/* Silencioso */
entry int	xflag;		/* Compara os n�s-�ndice */
entry int	Nflag;		/* Nomes dos pgms no "stdin" */
entry int	dflag;		/* Debug */

const char	**color_vector;	/* Para as cores dos modos */

const char	*error_color_str;
const char	*warn_color_str;
const char	*def_color_str;

/*
 ******	Prot�tipos de fun��es ***********************************
 */
int	compare (const char *, const char *);
int	preludium (int, const char **, STAT *, FILE **);
int	isobj (const char *, FILE *);
int	linecompare (const char *, const char *, FILE *, FILE *, int);
int	quickcompare (const char *, const char *, FILE *, FILE *, STAT *, STAT *);
void	help (void);

/*
 ****************************************************************
 *	Move (troca o nome de) arquivos				*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt, ret = 0;
	const char	*cp;
	const char	*dir_nm;
	char		*pathname = NOSTR;
	STAT		dir_s;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "lpqsxNdH")) != EOF)
	{
		switch (opt)
		{
		    case 'l':			/* Lista linhas diferentes */
			lflag++;
			break;

		    case 'p':			/* Aceita prefixo como correto */
			pflag++;
			break;

		    case 'q':			/* Compara��o r�pida */
			qflag++;
			break;

		    case 's':			/* Silencioso */
			sflag++;
			break;

		    case 'x':			/* Compara os elos simb�licos */
			xflag++;
			break;

		    case 'N':			/* Nomes do "stdin" */
			Nflag++;
			break;

		    case 'd':			/* Debug */
			dflag++;
			break;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			putc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	argv += optind;
	argc -= optind;

	if (argc < 1)
		help ();

	/*
	 *	Verifica compatibilidades
	 */
	if (sflag)
		lflag = 0;

	if (qflag && (lflag|pflag))
		help ();

	/*
	 *	Processa "modecolor"
	 */
	modecolor (isatty (fileno (stderr)), (void *)NULL, &color_vector);

	error_color_str = color_vector[MC_ERR];
	warn_color_str  = color_vector[MC_WARN];
	def_color_str   = color_vector[MC_DEF];

	/*
	 *	Examina se o �ltimo argumento � um diret�rio
	 */
	if (stat ((dir_nm = argv[argc-1]), &dir_s) >= 0 && S_ISDIR (dir_s.st_mode))
	{
		pathname = alloca (1024);

		strcpy (pathname, dir_nm); strcat (pathname, "/");
		dirend = strrchr (pathname, '/') + 1;

		if (dirend [-2] == '/')
			dirend--;

		if (xflag && lstat (dir_nm, &dir_s) >= 0 && S_ISLNK (dir_s.st_mode))
		{
			if   (argc == 2)		/* Tenta fazer algo de �til */
				dirend = NOSTR;
#if (0)	/*******************************************************/
			elif (!sflag)
				error ("Cuidado: \"%s\" � um elo simb�lico", dir_nm);
#endif	/*******************************************************/

		}
	}

	/*
	 *	Analisa o Nflag
	 */
	if   (argc == 1)
		Nflag++;
	elif (Nflag)
		error ("Os argumentos sup�rfluos ser�o ignorados");

	if ((Nflag || argc > 2)  &&  dirend == NOSTR)
		error ("$%sO arquivo \"%s\" n�o � um diret�rio%s", error_color_str, dir_nm, def_color_str);

	/*
	 *	Processa os argumentos
	 */
	if   (dirend == NOSTR)			/* Primeiro caso: "cmp a b" */
	{
		ret += compare (argv[0], argv[1]);
	}
	elif (!Nflag)				/* Segundo caso: "cmp a b c ... dir" */
	{
		argv[argc-1] = NOSTR;

		for (/* vazio */; *argv; argv++)
		{
			if ((cp = strrchr (*argv, '/')) == NOSTR)
				cp = *argv;
			else
				cp++;

			strcpy (dirend, cp);

			ret += compare (*argv, pathname);
		}
	}
	else					/* Terceiro caso: "cmp -N dir" */
	{
		char		*area = alloca (1024);

		while (fngets (area, 1024, stdin) != NOSTR)
		{
			if ((cp = strrchr (area, '/')) == NOSTR)
				cp = area;
			else
				cp++;

			strcpy (dirend, cp);

			ret += compare (area, pathname);
		}
	}

	return (ret);

}	/* end main */

/*
 ****************************************************************
 *	Compara um par de arquivos				*
 ****************************************************************
 */
int
compare (const char *old_nm, const char *new_nm)
{
	int		ret;
	STAT		old_s, new_s;
	FILE		*old_fp, *new_fp;
	int		objeto;

	if (dflag)
		fprintf (stderr, "=> compare (%s, %s)\n", old_nm, new_nm);
 
	/*
	 *	Analisa os arquivos
	 */
	if (ret = preludium (0, &old_nm, &old_s, &old_fp))
		return (ret);

	if (ret = preludium (1, &new_nm, &new_s, &new_fp))
		{ fclose (old_fp); return (ret); }

	/*
	 *	Verifica se se trata na realidade, do mesmo arquivo
	 */
	if (old_s.st_dev == new_s.st_dev && old_s.st_ino == new_s.st_ino)
	{
		if (!sflag) fprintf
		(	stderr,
		 	"\"%s\" e \"%s\" %ss�o o mesmo arquivo%s\n",
			old_nm, new_nm, warn_color_str, def_color_str
		);

		fclose (old_fp); fclose (new_fp); return (0);
	}

	/*
	 *	Compara os conte�do dos arquivos (modo normal)
	 */
	if (!xflag)
	{
		objeto = isobj (old_nm, old_fp) || isobj (new_nm, new_fp);

		if (qflag)
			ret = quickcompare (old_nm, new_nm, old_fp, new_fp, &old_s, &new_s);
		else
			ret = linecompare (old_nm, new_nm, old_fp, new_fp, objeto);
	
		fclose (old_fp); fclose (new_fp);
		return (ret);
	}

	/*
	 *	Compara os n�s-�ndice (especiais ou elos simb�licos)
	 */
	fclose (old_fp); fclose (new_fp);

	if ((old_s.st_mode & S_IFMT) != (new_s.st_mode & S_IFMT))
	{
		if (!sflag) fprintf
		(	stderr,
		 	"\"%s\" e \"%s\" %ss�o tipos diferentes de arquivo%s (%c :: %c)\n",
			old_nm, new_nm, error_color_str, def_color_str,
			modetostr (old_s.st_mode)[0], modetostr (new_s.st_mode)[0]
		);

		return (1);
	}

	/*
	 *	Elos simb�licos	 ou especiais
	 */
	if   (S_ISLNK (old_s.st_mode))			/* Elos simb�licos */
	{
		char		*old_symlink_nm, *new_symlink_nm;

		old_symlink_nm = alloca (old_s.st_size + 1);

		if (readlink (old_nm, old_symlink_nm, old_s.st_size + 1) < 0)
		{
			if (!sflag) error
			(	"*%sN�o consegui ler o conte�do do elo simb�lico%s \"%s\"",
				error_color_str, def_color_str, old_nm
			);

			return (1);
		}

		new_symlink_nm = alloca (new_s.st_size + 1);

		if (readlink (new_nm, new_symlink_nm, new_s.st_size + 1) < 0)
		{
			if (!sflag) error
			(	"*%sN�o consegui ler o conte�do do elo simb�lico%s \"%s\"",
				error_color_str, def_color_str, new_nm
			);

			return (1);
		}

		if (!streq (old_symlink_nm, new_symlink_nm))
		{
			if (!sflag) fprintf
			(	stderr,
				"%sOs conte�dos dos elos simb�licos s�o diferentes%s: \"%s\" :: \"%s\"\n",
				error_color_str, def_color_str, old_symlink_nm, new_symlink_nm
			);

			return (1);
		}

	}
	elif (old_s.st_rdev != new_s.st_rdev)		/* Especiais */
	{
		if (!sflag) fprintf
		(	stderr,
			"\"%s\" e \"%s\" %ss�o dispositivos diferentes%s: (%d/%d :: %d/%d)\n",
			old_nm, new_nm, error_color_str, def_color_str,
			MAJOR (old_s.st_rdev), MINOR (old_s.st_rdev),
			MAJOR (new_s.st_rdev), MINOR (new_s.st_rdev)
		);

		return (1);
	}

	/*
	 *	S�o iguais
	 */
	if (dirend  &&  !sflag)
		putc ('\n', stderr);

	return (0);

}	/* end compare */

/*
 ****************************************************************
 *	Identifica, obt�m o estado e abre arquivos		*
 ****************************************************************
 */
int
preludium (int index, const char **file_nm, STAT *sp, FILE **fp)
{
	int		code, save_errno;

	/*
	 *	Obt�m o estado do arquivo
	 */
	*fp = NOFILE; sp->st_mode = 0;

	if   (streq (*file_nm, "-"))
	{
		*fp = stdin; *file_nm = "\"stdin\"";

		code = fstat (fileno (*fp), sp);
	}
	elif (xflag)
	{
		code = lstat (*file_nm, sp);
	}
	else
	{
		code = stat (*file_nm, sp);
	}

	save_errno = errno;

	/*
	 *	Imprime o nome do arquivo, se for o caso
	 */
	if (index == 0 && dirend != NOSTR && !sflag)
	{
		fprintf
		(	stderr,
			"%s%s%s:\t",
			color_vector[(sp->st_mode & S_IFMT) >> 12],
			*file_nm,
			color_vector[MC_DEF]
		);

		fflush (stderr);
	}

	if (code < 0)
	{
		errno = save_errno;

		if (!sflag) fprintf
		(	stderr,
		 	"%sN�o consegui obter o estado de%s \"%s\" (%s)\n",
			error_color_str, def_color_str, *file_nm, strerror (errno)
		);

		return (2);
	}

	/*
	 *	Verifica se � um diret�rio
	 */
	if (S_ISDIR (sp->st_mode))
	{
		if (!sflag) fprintf
		(	stderr,
			"\"%s\" %s� um diret�rio%s\n",
			*file_nm, error_color_str, def_color_str
		);

		return (2);
	}

	/*
	 *	Trata os arquivos especiais
	 */
	if (xflag)
		{ *fp = NOFILE; return (0); }

	/*
	 *	Abre os arquivos restantes
	 */
	if (*fp != NOFILE || (*fp = fopen (*file_nm, "r")) != NOFILE)
		return (0);

	if (!sflag) fprintf
	(	stderr,
		"%sN�o consegui abrir%s \"%s\" (%s)\n",
		error_color_str, def_color_str,	*file_nm, strerror (errno)
	);

	return (2);

}	/* end preludium */

/*
 ****************************************************************
 *	Testa se o arquivo � objeto				*
 ****************************************************************
 */
int
isobj (const char *file_nm, FILE *fp)
{
	HEADER		h;
	int		n;

	if (streq (file_nm, "\"stdin\""))
		return (0); 

	n = fread (&h, sizeof (h), 1, fp);

	rewind (fp);

	if (n == 1 && (h.h_magic == FMAGIC || h.h_magic == NMAGIC || h.h_magic == SMAGIC))
		return (1);
	
	return (0);

}	/* end isobj */

/*
 ****************************************************************
 *	Compara dois arquivos					*
 ****************************************************************
 */
int
linecompare (const char *old_nm, const char *new_nm, FILE *old_fp, FILE *new_fp, int objeto)
{
	int		oldc, newc;
	char		*oldcp, *newcp;
	long		nc = 1;
	long		nl = 1;
	char		oldline[BLSZ+1], newline[BLSZ+1];

	/*
	 *	Percorre os dois arquivos
	 */
	for
	(	oldcp = oldline, newcp = newline, newc = '\0';
		(oldc = getc (old_fp)) != EOF && (newc = getc (new_fp)) != EOF;
		nc++
	)
	{
		/*
		 *	Guarda caracteres
		 */
		if (lflag  &&  !objeto  &&  oldcp < (oldline + BLSZ))
		{
			if (oldc != '\n')
				*oldcp++ = oldc;
			if (newc != '\n')
				*newcp++ = newc;
		}

		/*
		 *	Testa se os caracteres s�o diferentes
		 */
		if (oldc != newc)
		{
			/*
			 *	Indica o local da diferen�a
			 */
			if (!sflag) fprintf
			(	stderr,
			 	"\"%s\" e \"%s\" %sdiferem na linha %d, caracter %d%s\n",
				old_nm, new_nm, error_color_str, nl, nc, def_color_str
			);
			
			/*
			 *	Lista as linhas diferentes
			 */
			if (lflag  &&  !objeto)
			{
				if (oldc != '\n')
				{
					while ((oldc = getc (old_fp)) != '\n')
					{
						if (oldcp >= (oldline + BLSZ))
							break;

						*oldcp++ = oldc;
					}
				}

				*oldcp = '\0';

				fprintf (stderr, "%s:	%s\n", old_nm, oldline);

				if (newc != '\n')
				{
					while ((newc = getc (new_fp)) != '\n')
					{
						if (newcp >= (newline + BLSZ))
							break;
						*newcp++ = newc;
					}
				}

				*newcp = '\0';

				fprintf (stderr, "%s:	%s\n", new_nm, newline);
			}

			return (1);

		}	/* end	if (oldc != newc) */

		if (oldc == '\n')
			{ nl++; oldcp = oldline; newcp = newline; }

	}	/* end lendo as linhas dos arquivos */

	/*
	 *	Verifica se houve erros
	 */
	if (ferror (old_fp))
	{
		error
		(	"*%sErro de leitura em%s \"%s\"",
			error_color_str, def_color_str, old_nm
		);

		return (1);
	}

	if (ferror (new_fp))
	{
		error
		(	"*%sErro de leitura em%s \"%s\"",
			error_color_str, def_color_str, new_nm
		);

		return (1);
	}

	/*
	 *	Verifica se um dos arquivos terminou antes do outro
	 */
	if (newc == EOF)
	{
		if (nc == 1)
		{
			if (!sflag) fprintf
			(	stderr,
				"\"%s\" %s� um arquivo vazio%s\n",
				new_nm, warn_color_str, def_color_str
			);

			return (1);
		}
		elif (!pflag)
		{
			if (!sflag) fprintf
			(	stderr,
				"%sO arquivo \"%s\" � um prefixo de \"%s\"%s\n",
				warn_color_str, new_nm, old_nm, def_color_str
			);

			return (1);
		}

		return (0);
	}

	if (oldc == EOF  &&  getc (new_fp) != EOF)
	{
		if (nc == 1)
		{
			if (!sflag) fprintf
			(	stderr,
				"\"%s\" %s� um arquivo vazio%s\n",
				old_nm, warn_color_str, def_color_str
			);

			return (1);
		}
		elif (!pflag)
		{
			if (!sflag) fprintf
			(	stderr,
				"%sO arquivo \"%s\" � um prefixo de \"%s\"%s\n",
				warn_color_str, old_nm, new_nm, def_color_str
			);

			return (1);
		}

		return (0);
	}

	/*
	 *	S�o iguais
	 */
	if (dirend  &&  !sflag)
		putc ('\n', stderr);

	return (0);

}	/* end linecompare */

/*
 ****************************************************************
 *	Compara��o r�pida de dois arquivos			*
 ****************************************************************
 */
int
quickcompare (const char *old_nm, const char *new_nm, FILE *old_fp, FILE *new_fp, STAT *old_s, STAT *new_s)
{
	char		old_area[QUICKSZ], new_area[QUICKSZ];
	int		old_fd,	new_fd;
	int		count;

	/*
	 *	Compara o tamanho
	 */
	if (old_s->st_size != new_s->st_size)
	{
		if (!sflag) fprintf
		(	stderr,
		 	"\"%s\" e \"%s\" %st�m tamanhos diferentes%s: %d :: %d\n",
			old_nm, new_nm, error_color_str, def_color_str, old_s->st_size, new_s->st_size
		);

		return (1);
	}

	/*
	 *	Compara o come�o do arquivo
	 */
	old_fd = fileno (old_fp); new_fd = fileno (new_fp);

	lseek (old_fd, 0, SEEK_SET);
	lseek (new_fd, 0, SEEK_SET);

	if (old_s->st_size >= QUICKSZ)
		count = QUICKSZ;
	else
		count = old_s->st_size;

	if (read (old_fd, old_area, count) != count)
	{
		error
		(	"*%sErro de leitura em%s \"%s\"",
			error_color_str, def_color_str, old_nm
		);

		return (1);
	}

	if (read (new_fd, new_area, count) != count)
	{
		error
		(	"*%sErro de leitura em%s \"%s\"",
			error_color_str, def_color_str, new_nm
		);

		return (1);
	}

	if (!memeq (old_area, new_area, count))
	{
		if (!sflag) fprintf
		(	stderr,
		 	"%sOs arquivos \"%s\" e \"%s\" s�o diferentes nos %d primeiros bytes%s\n",
			error_color_str, old_nm, new_nm, count, def_color_str
		);

		return (1);
	}

	/*
	 *	S�o iguais
	 */
	if (dirend  &&  !sflag)
		putc ('\n', stderr);

	return (0);

}	/* end quickcompare */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
help (void)
{
	fprintf
	(	stderr,
		"%s - compara pares de arquivos\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-lpqsx] <arquivo1> <arquivo2>\n"
		"\t%s [-lpqsx] <arquivo1> [<arquivo2> ...] <diret�rio>\n"
		"\t%s [-lpqsx] [-N] <diret�rio>\n",
		pgname, pgversion, pgname, pgname, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-l: Lista a primeira linha diferente entre os dois arquivos\n"
		"\t-p: Considera como iguais pares de arquivos quando um for o "
			"prefixo\n\t    do outro\n"
		"\t-q: Compara apenas os 4 KB primeiros bytes\n"
		"\t-s: Funcionamento silencioso\n"
		"\t-x: Compara os n�s-�ndices ao inv�s do conte�do\n"
		"\t-N: L� os nomes dos <arquivo>s de \"stdin\"\n"
		"\t    Esta op��o � impl�cita se for dado apenas o <diret�rio>\n"
	);
	exit (2);

}	/* end help */
