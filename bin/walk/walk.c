/*
 ****************************************************************
 *								*
 *			walk.c					*
 *								*
 * 	Caminha em �rvores do sistema de arquivos		*
 *								*
 *	Vers�o	1.0.0, de 28.09.86				*
 *		4.2.0, de 25.04.02				*
 *								*
 *	M�dulo: walk						*
 *		Utilit�rios b�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ftw.h>
#include <fcntl.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	4.2.0, de 25.04.02";

#define	EVER	;;
#define	elif	else if
#define STR(x)	# x
#define XSTR(x)	STR (x)

#define	NPAT	20	/* No. maximo de Padr�es */

/*
 ******	Vari�veis globais ***************************************
 */
entry int	rflag;		/* Arquivos regulares */
entry int	dflag;		/* Diret�rios  */
entry int	bflag;		/* Arquivos especiais de blocos */
entry int	cflag;		/* Arquivos especiais de caracteres */
entry int	lflag;		/* Elos simb�licos */
entry int	fflag;		/* FIFOs  */
entry int	mflag;		/* Prefixo */
entry int	Lflag;		/* Evite LINKS flag */
entry int	dotflag;	/* N�o ignora ".old" ... */
entry int	Nflag;		/* Nomes dos pgms no <stdin> */
entry int	vflag;		/* Verbose */

const char	**color_vector;	/* Para as cores dos modos */

/*
 ******	Os padr�es **********************************************
 */
entry const char *inc_pat[NPAT+1];	/* Os Padr�es de inclus�o */
entry int	inc_pati;

entry const char *exc_pat[NPAT+1];	/* Os Padr�es de exclus�o */
entry int	exc_pati;

/*
 ******	Prot�tipos de fun��es ***********************************
 */
int		accept (const char *, STAT *, int);
void		put_s_option (void);
int		put_p_option (char *, const char *[], int *);
int		pattern_accept (const char *);
void		process (const char *, STAT *);
int		proclink (STAT *);
void		help (void);

/*
 ****************************************************************
 *	Estruturas						*
 ****************************************************************
 */
typedef struct litem	LITEM;

struct litem
{
	dev_t	l_dev;		/* Dispositivo */
	ino_t	l_ino;		/* No. do Inode */
	LITEM	*l_next;	/* o Proximo */
};

entry LITEM	*linklist;	/* Comeco da Lista */

/*
 ****************************************************************
 * 	Caminha em �rvores do sistema de arquivos		*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "rdbclfamL.Nsp:P:vH")) != EOF)
	{
		switch (opt)
		{
		    case 'r':		/* Arquivos regulares */
			rflag++;
			continue;

		    case 'd':		/* Diret�rios */
			dflag++;
			continue;

		    case 'b':		/* Especial de blocos */
			bflag++;
			continue;

		    case 'c':		/* Especial de caracteres */
			cflag++;
			continue;

		    case 'l':		/* Elos Simb�licos */
			lflag++;
			continue;

		    case 'f':		/* FIFOs */
			fflag++;
			continue;

		    case 'a':		/* Todos tipos */
			rflag++;
			dflag++;
			bflag++;
			cflag++;
			fflag++;
			continue;

		    case 'm':			/* Prefixo */
			mflag++;
			break;

		    case 'L':			/* evite LINKS */
			Lflag++;
			break;

		    case '.':			/* N�o ignora ".old" ... */
			dotflag++;
			break;

		    case 'N':			/* Nomes do <stdin> */
			Nflag++;
			break;

		    case 's':			/* Padr�es = 	*.[cshryv] e */
			put_s_option ();
			break;

		    case 'p':		/* Padr�es de inclus�o */
			put_p_option ((char *)optarg, inc_pat, &inc_pati);
			break;

		    case 'P':		/* Padr�es de exclus�o */
			put_p_option ((char *)optarg, exc_pat, &exc_pati);
			break;

		    case 'v':		/* verbose flag */
			vflag++;
			continue;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			fputc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */ 

	/*
	 *	Ajustes
	 */
	argv += optind;

	if (rflag + dflag + bflag + cflag + lflag + fflag == 0)
		{ rflag++; bflag++; cflag++; lflag++; fflag++; }

	/*
	 *	Processa "modecolor"
	 */
	modecolor (isatty (fileno (stdout)), (void *)NULL, &color_vector);

	/*
	 *	Analisa o Nflag
	 */
	if (Nflag && *argv != NOSTR)
		{ error ("Os argumentos sup�rfluos ser�o ignorados"); *argv = NOSTR; }

	/*
	 *	Procura os argumentos
	 */
	if (*argv == NOSTR) 		/* N�o foram dados argumentos: l� do "stdin" */
	{
		char		*area = alloca (1024);

		while (fngets (area, 1024, stdin) != NOSTR)
			ftw (area, accept);
	}
	else 				/* Foram dados argumentos */
	{
		for (/* vazio */; *argv; argv++)
			ftw (*argv, accept);
	}

	return (0);

}	/* end walk */

/*
 ****************************************************************
 *	Processa um nome 					*
 ****************************************************************
 */
int
accept (const char *file_nm, STAT *sp, int status)
{
	if   (status == FTW_NS)
	{
		error ("*N�o consegui obter o estado de \"%s\"", file_nm);
		return (0);
	}
	elif (status == FTW_DNR)
	{
		error ("*N�o consegui percorrer \"%s\"", file_nm);
	}

	/*
	 *	Seleciona os tipos de arquivos
	 */
	switch (sp->st_mode & S_IFMT)
	{
	    case S_IFREG:
		if (!rflag)
			return (0);
		break;

	    case S_IFDIR:	/* Diret�rios ".old": pula toda sub�rvore */
		if (!dotflag)
		{
			if (patmatch (file_nm, ".!.*") || patmatch (file_nm, "*/.!.*"))
				return (1);
		}

		if (!dflag)
			return (0);
		break;

	    case S_IFIFO:
		if (!fflag)
			return (0);
		break;

	    case S_IFBLK:
		if (!bflag)
			return (0);
		break;

	    case S_IFCHR:
		if (!cflag)
			return (0);
		break;

	    case S_IFLNK:
		if (!lflag)
			return (0);
		break;

	    default:
		error ("Tipo inv�lido de arquivo: \"%s\"", file_nm);
		return (0);

	}	/* end switch */


	/*
	 *	Analisa os padr�es
	 */
	if (pattern_accept (file_nm))
		process (file_nm, sp);

	return (0);

}	/* end accept */

/*
 ****************************************************************
 *	Executa a op��o "-s" (padr�es de "C")			*
 ****************************************************************
 */
void
put_s_option (void)
{
	put_p_option ("*.[cshryv]", inc_pat, &inc_pati);
	put_p_option ("*[Mm]akefile", inc_pat, &inc_pati);

}	/* end put_s_option */

/*
 ****************************************************************
 *	Executa a op��o "-p" (outros padr�es)			*
 ****************************************************************
 */
int
put_p_option (char *cp, const char *pat_vec[], int *pati_ptr)
{
	char		c;

	for (EVER)
	{
		while ((c = *cp) == ' ' || c == '\t' )
			cp++;

		if (c == '\0')
			return (0);

		if (*pati_ptr >= NPAT)
		{
			printf
			(	"%s: No momento somente aceitamos "
				XSTR (NPAT) " padr�es\n\n",
				pgname
			);
			help ();
		}

		pat_vec[(*pati_ptr)++] = cp++;

		while ((c = *cp) != '\0' && c != ' ' && c != '\t')
			cp++;

		if (c == '\0')
			return (0);

		*cp++ = '\0';

	}	/* end for (EVER) */

}	/* end put_p_option */

/*
 ****************************************************************
 *	Verifica se o nome do arquivo satisfaz um dos padr�es	*
 ****************************************************************
 */
int
pattern_accept (const char *file_nm)
{
	const char	**pp;

	/*
	 *	Testa em primeiro lugar os pontos
	 */
	if (!dotflag)
	{
		if (patmatch (file_nm, ".!.*") || patmatch (file_nm, "*/.!.*"))
			return (0);
	}

	/*
	 *	Agora testa os padr�es de inclus�o
	 */
	if ((pp = inc_pat)[0] != NOSTR)
	{
		for (/* vazio */; /* vazio */; pp++)
		{
			if (*pp == NOSTR)
				return (0);

			if (patmatch (file_nm, *pp))
				break;
		}
	}

	/*
	 *	Finalmente testa os padr�es de exclus�o
	 */
	if ((pp = exc_pat)[0] != NOSTR)
	{
		for (/* vazio */; *pp != NOSTR; pp++)
		{
			if (patmatch (file_nm, *pp))
				return (0);
		}
	}

	return (1);

}	/* end pattern_accept */

/*
 ****************************************************************
 *	Processa O arquivo					*
 ****************************************************************
 */
void
process (const char *file_nm, STAT *sp)
{

	if (Lflag)
	{
		if (proclink (sp) > 0)
			return;
	}

	if (mflag)
	{
		printf ("%c  ", *(modetostr (sp->st_mode)));

		if (S_ISREG (sp->st_mode))
			printf ("%7d  ", sp->st_size);
		else
			printf ("         ");
	}

	printf
	(	"%s%s%s\n",
		color_vector[(sp->st_mode & S_IFMT) >> 12],
		file_nm,
		color_vector[MC_DEF]
	);

}	/* end process */

/*
 ****************************************************************
 *	Processa LINKs						*
 ****************************************************************
 */
int
proclink (STAT *sp)
{
	LITEM		*lp;

	if (sp->st_nlink == 1)
		return (0);

	for (lp = linklist; lp != (LITEM *)NULL; lp = lp->l_next)
	{
		if (lp->l_dev == sp->st_dev && lp->l_ino == sp->st_ino)
			return (1);
	}

	if ((lp = malloc (sizeof (LITEM))) == (LITEM *)NULL)
	{
		error ("N�o obtive mem�ria para item de elo f�sico");
	}
	else
	{
		lp->l_dev = sp->st_dev;
		lp->l_ino = sp->st_ino;

		lp->l_next = linklist;
		linklist = lp;
	}

	return (0);

}	/* end proclink */

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
	 	"%s - caminha em �rvores do sistema de arquivos\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [rdbclfamL.N] [<�rvore> ...]\n\n"
		"\tValores de <PAD>: [-s] [-p \"<p>\"] [-P \"<P>\"]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t--: Sem nenhuma das op��es \"-rdbclfa\" lista todos os tipos "
			"\n\t    de arquivos exceto diret�rios\n"
		"\t-r: Lista arquivos regulares\n"
		"\t-d: Lista diret�rios\n"
		"\t-b: Lista arquivos especiais de bloco (estruturados)\n"
		"\t-c: Lista arquivos especiais de caracteres (n�o estruturados)\n"
		"\t-l: Lista elos simb�licos\n"
		"\t-f: Lista FIFOs\n"
		"\t-a: Lista todos os tipos de arquivos (equivalente a \"-rdbcf\")\n"
		"\t-m: Imprime um prefixo com o tipo do arquivo e seu tamanho\n"
	);
	fprintf
	(	stderr,
		"\t-L: N�o repete arquivos com mais de um elo f�sico\n"
		"\t-.: Lista tamb�m arquivos ocultos (\".old\" ...)\n"
		"\t-N: L� os nomes das <�rvore>s de \"stdin\"\n"
		"\t    Esta op��o � impl�cita se n�o forem dados <�rvore>s\n"
		"\t-s: Adiciona os padr�es dos fontes em \"C\"\n"
		"\t-p: Seleciona arquivos atrav�s dos padr�es <p> de inclus�o\n"
		"\t-P: Seleciona arquivos atrav�s dos padr�es <P> de exclus�o\n"
	);
	exit (2);

}	/* end help */
