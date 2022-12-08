/*
 ****************************************************************
 *								*
 *			cp.c					*
 *								*
 *	Copia arquivos						*
 *								*
 *	Vers�o	1.0.0, de 28.05.86				*
 *		4.2.0, de 01.05.02				*
 *								*
 *	M�dulo: cp						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	4.2.0, de 01.05.02";

#define	elif	else if

entry int	iflag;		/* Interativo */
entry int	fflag;		/* Force */
entry int	vflag;		/* Verbose */
entry int	mflag;		/* Mant�m o estado do arquivo */
entry int	xflag;		/* N�s-�ndice */
entry int	Nflag;		/* Nomes dos pgms no <stdin> */
entry int	dflag;		/* Debug */

entry char	*dirend;	/* Ponteiro para o final do nome do dir. */

const char	**color_vector;	/* Para as cores dos modos */

/*
 ******	Estrutura de LINK ***************************************
 */
typedef struct litem	LITEM;

struct litem
{
	char	*l_dst_nm;	/* Nome do elo (destino) */
	dev_t	l_src_dev;	/* Dispositivo (fonte) */
	ino_t	l_src_ino;	/* No. do Inode (fonte) */
	LITEM	*l_next;	/* o Proximo */
};

entry LITEM	*link_list;		/* Comeco da Lista */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void		help (void);
int		file_copy (const char *, const char *);
int		value_copy (const char *, const char *, STAT *, STAT *, const char *);
int		block_copy (const char *src_nm, const STAT *src_s, const char *dst_nm);
char		*link_proc (const STAT *src_s, const char *dst_nm);

/*
 ****************************************************************
 *	Copia arquivos						*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt, ret = 0;
	const char	*cp;
	char		*pathname = NOSTR;
	const char	*dir_nm;
	STAT		dir_s;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "ifvmxNdH")) != EOF)
	{
		switch (opt)
		{
		    case 'i':			/* Interativo */
			iflag++;
			break;

		    case 'f':			/* Force */
			fflag++;
			break;

		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'm':			/* Mant�m o estado do arquivo */
			mflag++;
			break;

		    case 'x':			/* Elos simb�licos */
			xflag++;
			break;

		    case 'N':			/* Nomes do <stdin> */
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
	 *	Prepara o terminal para consultas
	 */
	if (iflag || !fflag)
	{
		if ((askyesno_stdin = fopen ("/dev/tty", "r")) == NOFILE)
			error ("$*N�o consegui abrir \"/dev/tty\"");

		askyesno_set (1);
	}

	/*
	 *	Processa "modecolor"
	 */
	modecolor (isatty (fileno (stderr)), (void *)NULL, &color_vector);

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
			else
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
		error ("$O arquivo \"%s\" n�o � um diret�rio", dir_nm);

	/*
	 *	Processa os argumentos
	 */
	if   (dirend == NOSTR) 		/* Primeiro caso: "cp a b" */
	{
		ret += file_copy (argv[0], argv[1]);
	}
	elif (!Nflag) 			/* Segundo caso: "cp a b c ... dir" */
	{
		argv[argc-1] = NOSTR;

		for (/* vazio */; *argv; argv++)
		{
			if ((cp = strrchr (*argv, '/')) == NOSTR)
				cp = *argv;
			else
				cp++;

			strcpy (dirend, cp);

			ret += file_copy (*argv, pathname);
		}
	}
	else 				/* Terceiro caso: "cp -N dir" */
	{
		char		*area = alloca (1024);

		while (fngets (area, 1024, stdin) != NOSTR)
		{
			if ((cp = strrchr (area, '/')) == NOSTR)
				cp = area;
			else
				cp++;

			strcpy (dirend, cp);

			ret += file_copy (area, pathname);
		}
	}

	return (ret);

}	/* end main */

/*
 ****************************************************************
 * 	Copia um arquivo					*
 ****************************************************************
 */
int
file_copy (const char *src_nm, const char *dst_nm)
{
	STAT		src_s, dst_s;
	char		*link_nm;
	int		code, save_errno;

	if (dflag)
		fprintf (stderr, "=> file_copy (%s, %s)\n", src_nm, dst_nm);

	/*
	 *	Obt�m o estado da fonte
	 */
	src_s.st_mode = 0;

	if (xflag)
		code = lstat (src_nm, &src_s);
	else
		code = stat (src_nm, &src_s);

	save_errno = errno;

	/*
	 *	Se necess�rio, pede confirma��o do usu�rio
	 */
	if (iflag || (vflag && dirend != NOSTR))
	{
		fprintf
		(	stderr,
			"%s%s%s",
			color_vector[(src_s.st_mode & S_IFMT) >> 12],
			src_nm,
			color_vector[MC_DEF]
		);
	}

	if   (iflag)
	{
		if (code >= 0)
		{
			fprintf (stderr, "? (n): ");

			if (askyesno () <= 0)
				return (0);
		}
		else
		{
			fprintf (stderr, ":\n");
		}
	}
	elif (vflag && dirend != NOSTR)
	{
		fprintf (stderr, ":\n");
	}

	if (code < 0)
	{
		errno = save_errno;

		error ("*N�o consegui obter o estado de \"%s\"", src_nm);
		return (1);
	}

	if (S_ISDIR (src_s.st_mode))
	{
		error ("\"%s\" � um diret�rio", src_nm);
		return (1);
	}

	/*
	 *	Verifica se � um elo f�sico a um arquivo anterior
	 */
	link_nm = link_proc (&src_s, dst_nm);

	/*
	 *	Examina o nome novo
	 */
	if (lstat (dst_nm, &dst_s) >= 0)
	{
		if (S_ISDIR (dst_s.st_mode))
		{
			error ("\"%s\" j� existe e � um diret�rio", dst_nm);
			return (1);
		}

		if (src_s.st_dev == dst_s.st_dev && src_s.st_ino == dst_s.st_ino)
		{
			error ("\"%s\" j� existe e � o mesmo arquivo do que \"%s\"", dst_nm, src_nm);
			return (1);
		}

		if (!fflag)
		{
			fprintf
			(	stderr,
				"%s: \"%s\" j� existe. Apaga/reescreve? (n): ",
				pgname, dst_nm
			);

			if (askyesno () <= 0)
				return (1);
		}

		/* Tenta usar "creat" para aproveitar o dono, modo, ... */

		if (!S_ISREG (src_s.st_mode) || !S_ISREG (dst_s.st_mode) || link_nm != NOSTR)
		{
			if (unlink (dst_nm) < 0)
			{
				error ("*N�o consigo remover \"%s\"", dst_nm);
				return (1);
			}
		}

	}	/* end if (j� existe o dst_nm) */ 

	/*
	 *	Copia o conte�do ou n�-�ndice do arquivo
	 */
	if (value_copy (src_nm, dst_nm, &src_s, &dst_s, link_nm) != 0)
		return (1);

	return (0);

}	/* end file_copy */
 
/*
 ****************************************************************
 *	Copia os blocos (ou o n�-�ndice) do arquivo		*
 ****************************************************************
 */
int
value_copy (const char *src_nm, const char *dst_nm, STAT *src_s, STAT *dst_s, const char *link_nm)
{
	char		*symlink_nm;

	if (dflag)
		fprintf (stderr, "=> value_copy (%s, %s)\n", src_nm, dst_nm);

	/*
	 *	Verifica se � um elo f�sico a um arquivo anterior
	 */
	if (link_nm != NOSTR)
	{
		if (dflag)
			fprintf (stderr, "=> LINK (%s, %s)\n", link_nm, dst_nm);

		if (link (link_nm, dst_nm) < 0)
		{
			error ("*N�o consegui criar o elo f�sico para \"%s\"", dst_nm);
			return (1);
		}

		return (0);
	}

	/*
	 *	Copia o conte�do ou o n�-�ndice
	 */
	if (!xflag)
	{
		if (block_copy (src_nm, src_s, dst_nm) != 0)
			return (1);
	}
	else switch (src_s->st_mode & S_IFMT)
	{
		/*
		 ****** Arquivo regular: Copia bloco a bloco ****
		 */
	    case S_IFREG:
		if (block_copy (src_nm, src_s, dst_nm) != 0)
			return (1);

		break;

		/*
		 ****** Arquivo especial: Recria ****************
		 */
	    case S_IFBLK:
	    case S_IFCHR:
	    case S_IFIFO:
		if (mknod (dst_nm, src_s->st_mode, src_s->st_rdev) < 0)
		{
			error ("*N�o consegui criar \"%s\"", dst_nm);
			return (1);
		}

		break;

		/*
		 ****** Elo simb�lico ***************************
		 */
	    case S_IFLNK:
		symlink_nm = alloca (src_s->st_size + 1);

		if (readlink (src_nm, symlink_nm, src_s->st_size + 1) < 0)
		{
			error ("*N�o consegui obter o conte�do do elo simb�lico de \"%s\"", src_nm);
			return (1);
		}

		if (symlink (symlink_nm, dst_nm) < 0)
		{
			error ("*N�o consegui criar o elo simb�lico \"%s\"", dst_nm);
			return (1);
		}

		return (0);

	    default:
		error ("Tipo %d do arquivo \"%s\" inv�lido", (src_s->st_mode & S_IFMT) >> 12, src_nm);
		return (1);

	}	/* end switch */

	/*
	 *	Tenta igualar o estado do arquivo
	 */
	if (!mflag)
		return (0);

	if (stat (dst_nm, dst_s) < 0)
	{
		error ("*N�o consegui obter o estado de \"%s\"", dst_nm);
		return (1);
	}

	if ((src_s->st_mode & ~S_IFMT) != (dst_s->st_mode & ~S_IFMT))
	{
		if (chmod (dst_nm, src_s->st_mode & ~S_IFMT) < 0) 
		{
			error ("*N�o consegui restaurar a prote��o de \"%s\"", dst_nm);
			return (1);
		}
	}

	if (utime (dst_nm, &src_s->st_atime) < 0)
	{
		error ("*N�o consegui restaurar os tempos de \"%s\"", dst_nm);
		return (1);
	}

	if (src_s->st_uid != dst_s->st_uid || src_s->st_gid != dst_s->st_gid)
	{
		if (chown (dst_nm, src_s->st_uid, src_s->st_gid) < 0) 
		{
			error ("*N�o consegui restaurar o dono/grupo de \"%s\"", dst_nm);
			return (1);
		}
	}

	return (0);

}	/* end value_copy */

/*
 ****************************************************************
 *	Copia os blocos						*
 ****************************************************************
 */
int
block_copy (const char *src_nm, const STAT *src_s, const char *dst_nm)
{
	int		fdin, fdout;
	char		area[BL4SZ];
	int		count;

	if ((fdout = creat (dst_nm, src_s->st_mode)) < 0)
	{
		error ("*N�o consegui criar o arquivo \"%s\"", dst_nm);
		return (1);
	}

	if ((fdin = open (src_nm, O_RDONLY)) < 0)
	{
		error ("*N�o consegui abrir o arquivo \"%s\"", src_nm);
		close (fdout);
		return (1);
	}

	while ((count = read (fdin, area, sizeof (area))) > 0)
	{
		if (write (fdout, area, count) != count)
		{
			error ("*Erro de escrita em \"%s\"", dst_nm);
			close (fdin);
			close (fdout);
			return (1);
		}
	}

	close (fdin);
	close (fdout);

	if (count < 0)
	{
		error ("*Erro de leitura em \"%s\"", src_nm);
		return (1);
	}

	return (0);

}	/* end block_copy */

/*
 ****************************************************************
 *	Processa elos f�sicos 					*
 ****************************************************************
 */
char *
link_proc (const STAT *src_s, const char *dst_nm)
{
	LITEM		*lp;

	/*
	 *	Se tem apenas 1 elo f�sico, nada precisa ser feito
	 */
	if (src_s->st_nlink == 1)
		return (NOSTR);

	/*
	 *	Verifica se um outro nome j� foi visto
	 */
	for (lp = link_list; lp != (LITEM *)NULL; lp = lp->l_next)
	{
		if (lp->l_src_dev == src_s->st_dev && lp->l_src_ino == src_s->st_ino)
			return (lp->l_dst_nm);
	}

	/*
	 *	� o primeiro da s�rie: insere na lista
	 */
	if   ((lp = malloc (sizeof (LITEM))) == (LITEM *)NULL)
	{
		error ("N�o obtive mem�ria para item de elo f�sico");
	}
	elif ((lp->l_dst_nm = strdup (dst_nm)) == NOSTR)
	{
		error ("N�o obtive mem�ria para item de elo f�sico");
	}
	else
	{
		lp->l_src_dev = src_s->st_dev;
		lp->l_src_ino = src_s->st_ino;

		lp->l_next = link_list;
		link_list = lp;
	}

	return (NOSTR);

}	/* end link_proc */

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
		"%s - copia arquivos\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-ifvmx] <arquivo1> <arquivo2>\n"
		"\t%s [-ifvmx] <arquivo1> [<arquivo2> ...] <diret�rio>\n"
		"\t%s [-ifvmx] [-N] <diret�rio>\n",
		pgname, pgversion,
		pgname,	pgname,	pgname
	);

	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-i: Pede a confirma��o para cada <arquivo> a copiar\n"
		"\t-f: Os <arquivo>s destino existentes s�o removidos silenciosamente\n"
		"\t-v: Lista o nome dos <arquivo>s copiados\n"
		"\t-m: Copia o dono, grupo, prote��o e datas do <arquivo>\n"
		"\t-x: Copia o n�-�ndice ao inv�s do conte�do\n"
		"\t-N: L� os nomes dos <arquivo>s de \"stdin\"\n"
		"\t    Esta op��o � impl�cita se for dado apenas o <diret�rio>\n"
	);

	exit (2);

}	/* end help */
