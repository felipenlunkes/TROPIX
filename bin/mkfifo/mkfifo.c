/*
 ****************************************************************
 *								*
 *			mkfifo.c				*
 *								*
 *	Cria FIFOs 						*
 *								*
 *	Vers�o	1.0.0, de 05.02.86				*
 *		3.0.0, de 31.10.90				*
 *								*
 *	M�dulo: mkfifo						*
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

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		help (void);

/*
 ****************************************************************
 *	Cria FIFOs 						*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	register int	opt;

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
	argc -= optind;

	/*
	 *	Cria os FIFOs
	 */
	for (/* vazio */; *argv; argv++)
	{
		if (mknod (*argv, S_IFIFO|S_IWRITE|S_IREAD, 0) < 0)
		{
			fprintf
			(	stderr,
				"%s: N�o consegui criar \"%s\" (%s)\n",
				pgname, *argv, strerror (errno)
			);
			exit_code++;
		}

	}	/* end for */

	return (exit_code);

}	/* end mkfifo */

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
		"%s - cria FIFOs\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s <fifo> ...\n",
		pgname, pgversion, pgname
	);

	exit (2);

}	/* end help */
