/*
 ****************************************************************
 *								*
 *			help.c					*
 *								*
 *	Imprime resumos de utiliza��o de comandos		*
 *								*
 *	Vers�o	1.1.0, de 29.08.85				*
 *		3.0.0, de 07.05.97				*
 *								*
 *	M�dulo: help						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	3.0.0, de 07.05.97";

#define	elif	else if

entry int	vflag;		/* Verbose */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		help (void);

/*
 ****************************************************************
 *	Imprime resumos de utiliza��o de comandos		*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt, n;
	long		pid;
	const char	*cmd;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "vH")) != EOF)
	{
		switch (opt)
		{
		    case 'v':			/* Verbose */
			vflag++;
			break;

		    case 'H':			/* Help */
			help ();

		    default:			/* Erro */
			putc ('\n', stderr);
			help ();

		}	/* end switch */

	}	/* end while */

	argv += optind;
   /***	argc -= optind; ***/

	/*
	 *	Imprime o resumo de cada comando
	 */
	for (n = 0; (cmd = argv[n]) != NOSTR; n++)
	{
		if (n > 0)
			putc ('\n', stderr);

		if   ((pid = fork ()) < 0)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui criar um processo (%s)\n",
				pgname, strerror (errno)
			);
			exit (1);
		}
		elif (pid > 0)	/* PAI */
		{
			wait ((int *)NULL);
		}
		else		/* FILHO */
		{
			execlp (cmd, cmd, "-H", NOSTR);

			fprintf
			(	stderr,
				"%s: N�o consegui obter o resumo de \"%s\" (%s)\n",
				pgname, cmd, strerror (errno)
			);
			exit (1);
		}

	}	/* end for */

	return (2);

}	/* end help */

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
		"%s - imprime resumos de utiliza��o de comandos\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s <comando> [<comando> ...]\n",
		pgname, pgversion, pgname
	);

	exit (2);

}	/* end help */
