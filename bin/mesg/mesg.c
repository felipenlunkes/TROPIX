/*
 ****************************************************************
 *								*
 *			mesg.c					*
 *								*
 *	Habilita ou desabilita a recep��o de mensagens		*
 *								*
 *	Vers�o	1.0.0, de 30.05.86				*
 *		3.0.0, de 23.05.97				*
 *								*
 *	M�dulo: mesg						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <stat.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	3.0.0, de 23.05.97";

#define	elif	else if

entry int	exit_code = 0;	/* C�digo de retorno */

entry int	vflag;		/* Verbose */
entry int	nflag;		/* Desabilita */
entry int	sflag;		/* Habilita */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		help (void);

/*
 ****************************************************************
 *	Habilita ou desabilita a recep��o de mensagens		*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	register int	opt;
	register char	*tty_nm;
	STAT		s;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "nNsSyYvH")) != EOF)
	{
		switch (opt)
		{
		    case 'n':			/* Desabilita */
		    case 'N':
			if (sflag)
				help ();
			nflag++;
			break;

		    case 's':			/* Habilita */
		    case 'S':
		    case 'y':
		    case 'Y':
			if (nflag)
				help ();
			sflag++;
			break;

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
	argc -= optind;

	/*
	 *	Obt�m o estado do terminal
	 */
	if ((tty_nm = ttyname (2 /* == STDERR */)) == NOSTR)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui obter o nome do terminal (%s)\n",
			pgname, strerror (errno)
		);
		exit (2);
	}

	if (stat (tty_nm, &s) < 0)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui obter o estado do terminal \"%s\" (%s)\n",
			pgname, tty_nm, strerror (errno)
		);
		exit (2);
	}

	/*
	 *	Imprime o estado atual
	 */
	if (nflag + sflag == 0)
	{
		if (s.st_mode & S_IWOTH)
		{
			fprintf (stderr, "Recep��o habilitada\n");
		   /***	exit_code = 0; ***/
		}
		else
		{
			fprintf (stderr, "Recep��o desabilitada\n");
			exit_code = 1;
		}
	}

	/*
	 *	Altera o estado
	 */
	if   (nflag)
	{
		exit_code = 1;

		if (chmod (tty_nm, s.st_mode & ~(S_IWGRP|S_IWOTH)) < 0)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui mudar o estado do terminal \"%s\" (%s)\n",
				pgname, tty_nm, strerror (errno)
			);
			exit_code = 2;
		}
	}
	elif (sflag)
	{
	   /***	exit_code = 0; ***/

		if (chmod (tty_nm, s.st_mode|S_IWGRP|S_IWOTH) < 0)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui mudar o estado do terminal \"%s\" (%s)\n",
				pgname, tty_nm, strerror (errno)
			);
			exit_code = 2;
		}
	}

	return (exit_code);

}	/* end mesg */

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
		"%s - habilita ou desabilita a recep��o de mensagens\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-nNsSyY]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-n (N)      : Desabilita a recep��o\n"
		"\t-s (S, y, Y): Habilita a recep��o\n"
		"\nObs.:\tSem op��es, imprime o estado atual\n"
	);

	exit (2);

}	/* end help */
