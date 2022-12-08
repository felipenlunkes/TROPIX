/*
 ****************************************************************
 *								*
 *			emptydir.c				*
 *								*
 * 	Gera os nomes dos diret�rios vazios (para remo��o)	*
 *								*
 *	Vers�o	3.1.0, de 14.01.99				*
 *		4.2.0, de 08.05.02				*
 *								*
 *	M�dulo: emptydir					*
 *		Utilit�rios experimentais			*
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
#include <dirent.h>
#include <ftw.h>
#include <fcntl.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	4.2.0, de 08.05.02";

#define	EVER	;;
#define	elif	else if
#define STR(x)	# x
#define XSTR(x)	STR (x)

/*
 ******	Vari�veis globais ***************************************
 */
entry int	gflag;		/* Gera o garfield */
entry int	vflag;		/* Verbose */
entry int	Nflag;		/* Nomes dos pgms no <stdin> */

entry int	n_dirs;		/* No. total de diret�rios vazios */

/*
 ****** Garfield ************************************************
 */
const char	garfield[] = "garfield";
entry FILE	*gfp;

/*
 ******	Prot�tipos de fun��es ***********************************
 */
int		accept (const char *, STAT *, int);
void		dir_read (const char *, STAT *);
void		help (void);

/*
 ****************************************************************
 * 	Gera os nomes dos diret�rios vazios (para remo��o)	*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "gvNH")) != EOF)
	{
		switch (opt)
		{
		    case 'g':			/* garfield */
			gflag++;
			continue;

		    case 'v':			/* verbose flag */
			vflag++;
			continue;

		    case 'N':			/* Nomes do <stdin> */
			Nflag++;
			break;

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
   /***	argc -= optind; ***/
	argv += optind;

	/*
	 *	Prepara o "garfield"
	 */
	if (gflag && (gfp = fopen (garfield, "w")) == NOFILE)
		error ("$*N�o consegui abrir \"%s\"", garfield);

	/*
	 *	Analisa o Nflag
	 */
	if (Nflag && *argv != NOSTR)
	{
		error ("Os argumentos sup�rfluos ser�o ignorados");
		*argv = NOSTR;
	}

	/*
	 *	Procura os argumentos
	 */
	if (*argv == NOSTR) 		 /* N�o foram dados argumentos: l� do "stdin" */
	{
		char		*area = alloca (1024);

		while (fngets (area, 1024, stdin) != NOSTR)
		{
			ftw (area, accept);
		}
	}
	else 				 /* Foram dados argumentos */
	{
		for (/* vazio */; *argv; argv++)
		{
			ftw (*argv, accept);
		}
	}

	/*
	 *	Imprime o total
	 */
	if (!vflag)
		return (0);

	if (n_dirs == 0)
		error ("N�o foram encontrados diret�rios vazios");
	else
		error ("Foram encontrados %d diret�rios vazios", n_dirs);

	return (0);

}	/* end emptydir */

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
	 *	S� interessam diret�rios
	 */
	if ((sp->st_mode & S_IFMT) == S_IFDIR)
		dir_read (file_nm, sp);

	return (0);

}	/* end accept */

/*
 ****************************************************************
 *	Le um diret�rio						*
 ****************************************************************
 */
void
dir_read (const char *dir_nm, STAT *sp)
{
	DIR		*dir_fp;
	const DIRENT	*dp;

	/*
	 *	Abre o diret�rio
	 */
	if ((dir_fp = opendir (dir_nm)) == NODIR)
	{
		error ("*N�o consegui abrir \"%s\"", dir_nm);
		return;
	}

	/*
	 *	Le o diret�rio
	 */
	while ((dp = readdir (dir_fp)) != NODIRENT)
	{
		if (streq (dp->d_name, ".") || streq (dp->d_name, ".."))
			continue;

		/* N�o est� vazio */

		closedir (dir_fp); return;

	}	/* end while (fread) */

	/*
	 *	Est� vazio
	 */
	closedir (dir_fp);

	n_dirs++;

	if (gflag)
		fprintf (gfp, "%s\n", dir_nm);
	else
		printf ("%s\n", dir_nm);

}	/* end dir_read */

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
		"%s - gera os nomes dos diret�rios vazios\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-gvN] [<�rvore> ...]\n\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-g: Gera o arquivo \"garfield\"\n"
		"\t-v: Verboso\n"
		"\t-N: L� os nomes das <�rvore>s de \"stdin\"\n"
	);
	exit (2);

}	/* end help */
