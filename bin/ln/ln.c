/*
 ****************************************************************
 *								*
 *			ln.c					*
 *								*
 *	Cria elos f�sicos ou simb�licos para arquivos		*
 *								*
 *	Vers�o	1.0.0, de 28.05.86				*
 *		4.2.0, de 08.05.02				*
 *								*
 *	M�dulo: ln						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] = "Vers�o:	4.2.0, de 10.04.02";

#define	elif	else if

entry int	iflag;		/* Interativo */
entry int	fflag;		/* Force */
entry int	sflag;		/* Simb�lico */
entry int	vflag;		/* Verbose */
entry int	Nflag;		/* Nomes dos pgms no <stdin> */
entry int	dflag;		/* Debug */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void		help (void);
int		mklink (const char *, const char *);

/*
 ****************************************************************
 *	Cria elos f�sicos ou simb�licos para arquivos		*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt, ret = 0;
	const char	*cp;
	char		pathname[512];
	char		*dirend = NOSTR;
	const char	*dirnm;
	STAT		s;

	/*
	 *	Analisa as op��es.
	 */
	while ((opt = getopt (argc, argv, "sifvNdH")) != EOF)
	{
		switch (opt)
		{
		    case 's':			/* Simb�lico */
			sflag++;
			break;

		    case 'i':			/* Interativo */
			iflag++;
			break;

		    case 'f':			/* Force */
			fflag++;
			break;

		    case 'v':			/* Verbose */
			vflag++;
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

	/*
	 *	Prepara o terminal para consultas
	 */
	if (iflag || !fflag)
	{
		if ((askyesno_stdin = fopen ("/dev/tty", "r")) == NOFILE)
			error ("$*N�o consegui abrir \"/dev/tty\"");
	}

	/*
	 *	Analisa o Nflag e a sintaxe
	 */
	if (Nflag)
	{
		if (argc != 1)
			help ();
	}
	else
	{
		if (argc < 2)
			help ();
	}

	/*
	 *	Examina se o �ltimo argumento � um diret�rio
	 */
	if (stat ((dirnm = argv[argc-1]), &s) >= 0 && S_ISDIR (s.st_mode))
	{
		strcpy (pathname, dirnm);
		strcat (pathname, "/");
		dirend = strrchr (pathname, '/') + 1;
	}

	/*
	 *	Se foram dados mais de dois arquivos,
	 *	o �ltimo deve ser um diret�rio
	 */
	if ((Nflag || argc > 2)  &&  dirend == NOSTR)
	{
		error ("O arquivo \"%s\" n�o � um diret�rio\n", dirnm);
		help ();
	}

	/*
	 *	Processa os argumentos
	 */
	if   (dirend == NOSTR) 		/* Primeiro caso: "ln a b" */
	{
		ret += mklink (argv[0], argv[1]);
	}
	elif (!Nflag) 			/* Segundo caso: "ln a b c ... dir" */
	{
		argv[argc-1] = NOSTR;

		for (/* vazio */; *argv; argv++)
		{
			if ((cp = strrchr (*argv, '/')) == NOSTR)
				cp = *argv;
			else
				cp++;

			strcpy (dirend, cp);

			ret += mklink (*argv, pathname);
		}
	}
	else				/* Terceiro caso: "ln -N dir" */
	{
		char		*area = alloca (1024);

		while (fngets (area, 1024, stdin) != NOSTR)
		{
			if ((cp = strrchr (area, '/')) == NOSTR)
				cp = area;
			else
				cp++;

			strcpy (dirend, cp);

			ret += mklink (area, pathname);
		}
	}

	return (ret);

}	/* end main */

/*
 ****************************************************************
 * 	Cria um elo f�sico ou simb�lico				*
 ****************************************************************
 */
int
mklink (const char *oldnm, const char *newnm)
{
	STAT		olds, news;
	int		ret;

	if (dflag)
		fprintf (stderr, "=> mklink (%s, %s)\n", oldnm, newnm);

	/*
	 *	Se necess�rio, pede confirma��o do usuario
	 */
	if (iflag)
	{
		fprintf (stderr, "%s: ", oldnm);

		if (askyesno () <= 0)
			return (0);
	}

	if (!sflag)
	{
		if (lstat (oldnm, &olds) < 0)
		{
			error ("*N�o consegui obter o estado de \"%s\"", oldnm);
			return (1);
		}

		if (S_ISDIR (olds.st_mode))
		{
			error ("\"%s\" � um diret�rio", oldnm);
			return (1);
		}
	}

	/*
	 *	Examina o nome novo
	 */
	if (lstat (newnm, &news) >= 0)
	{
		if (S_ISDIR (news.st_mode))
		{
			error ("\"%s\" j� existe e � um diret�rio", newnm);
			return (1);
		}

		if (!sflag && olds.st_dev == news.st_dev && olds.st_ino == news.st_ino)
		{
			error ("\"%s\" j� existe e � o mesmo arquivo do que \"%s\"", newnm, oldnm);
			return (0);
		}

		if (!fflag)
		{
			fprintf
			(	stderr,
				"%s: \"%s\" j� existe. Apaga? (n): ",
				pgname, newnm
			);

			if (askyesno () <= 0)
				return (1);
		}

		if (unlink (newnm) < 0)
		{
			error ("*N�o consigo remover \"%s\"", newnm);
			return (1);
		}

	}	/* end if (j� existe o newnm) */ 

	/*
	 *	Cria o nome novo
	 */
	if (!sflag)
		ret = link (oldnm, newnm);
	else
		ret = symlink (oldnm, newnm);

	if (ret < 0)
	{
		error ("*N�o consigo criar o novo elo para \"%s\"", newnm);
		return (1);

	}

	if (vflag  &&  !iflag)
		fprintf (stdout, "%s:\n", oldnm);

	return (0);

}	/* end mklink */
 
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
		"%s - cria elos f�sicos ou simb�licos para arquivos\n"
		"\n%s\n",
		pgname,	pgversion
	);
	fprintf
	(	stderr,
		"\nSintaxe:\n"
		"\t%s [-sifv] <arquivo1> <arquivo2>\n"
		"\t%s [-sifv] <arquivo1> [<arquivo2> ...] <diret�rio>\n"
		"\t%s [-sifv] -N <diret�rio>\n",
		pgname,	pgname,	pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-s: Cria um elo simb�lico ao inv�s de f�sico\n"
		"\t-i: Pede a confirma��o para cada elo a criar\n"
		"\t-f: Os arquivos destino existentes s�o removidos "
			"silenciosamente\n"
		"\t-v: Lista o nome dos elos criados\n"
		"\t-N: L� os nomes dos arquivos de \"stdin\"\n"
	);

	exit (2);

}	/* end help */
