/*
 ****************************************************************
 *								*
 *			mkdir.c					*
 *								*
 *	Cria diret�rios						*
 *								*
 *	Vers�o	1.0.0, de 08.04.86				*
 *		4.2.0, de 10 05.02				*
 *								*
 *	M�dulo: mkdir						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	4.2.0, de 10.05.02";

#define	elif	else if

#define		MODO	0777	/* Modo do diret�rio criado */

entry int	fflag;		/* Cria os subdiret�rios */
entry int	vflag;		/* Verbose */
entry int	dflag;		/* Debug */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
int		ver_dir (char *);
void		help (void);

/*
 ****************************************************************
 *	Cria diret�rios						*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt, exit_code = 0;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "fvdH")) != EOF)
	{
		switch (opt)
		{
		    case 'f':			/* Cria os subdiret�rios */
			fflag++;
			break;

		    case 'v':			/* Verbose */
			vflag++;
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
	 *	Verifica uso correto do programa
	 */
	if (argc < 1)
		help ();

	/*
	 *	Cria os diret�rios
	 */
	for (/* vazio */; *argv != NOSTR; argv++)
	{
		if (fflag && ver_dir ((char *)*argv) < 0)
			{ exit_code++; continue; }

		if (mkdir (*argv, MODO) < 0)
		{
			error ("*N�o consegui criar o diret�rio \"%s\"", *argv);
			exit_code++;
		}
	}

	return (exit_code);

}	/* end main */

/*
 ****************************************************************
 *	Cria os diret�rios intermedi�rios faltando		*
 ****************************************************************
 */
int
ver_dir (char *file_nm)
{
	char		*cp;

	for (cp = file_nm + 1; *cp != '\0'; cp++)
	{
		if (*cp == '/')
		{
			*cp = '\0';

			if (access (file_nm, F_OK) < 0 && mkdir (file_nm, MODO) < 0)
			{
				error ("*N�o consegui criar o diret�rio \"%s\"", file_nm);

				*cp = '/'; return (-1);
			}

			*cp = '/';
		}
	}

	return (0);

}	/* end ver_dir */

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
		"%s - cria diret�rios\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-f] <diret�rio> ...\n",
		pgname, pgversion, pgname
	);

	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-f: Cria os diret�rios intermedi�rios (se necess�rio)\n"
	);

	exit (2);

}	/* end help */
