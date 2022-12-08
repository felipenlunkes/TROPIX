/*
 ****************************************************************
 *								*
 *			tee.c					*
 *								*
 *	Copia a entrada padr�o para diversos arquivos e		*
 *	para a saida padr�o					*
 *								*
 *	Vers�o	1.0.0, de 10.08.89				*
 *		3.0.0, de 12.07.97				*
 *								*
 *	M�dulo: tee						*
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
#include <signal.h>	
#include <fcntl.h>	
#include <errno.h>	

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	3.0.0, de 12.07.97";

#define	O_MODE(f) (f ? O_WRONLY|O_CREAT|O_APPEND : O_WRONLY|O_CREAT|O_TRUNC)

entry int	aflag;		/* Append */
entry int	vflag;		/* Verbose */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void		help (void);

/*
 ****************************************************************
 *	Programa de duplicar a entrada padr�o			*
 ****************************************************************
 */
int
main (int argc, register const char *argv[])
{
	register int		opt, n, i;
	register int		*fd;
	int			nfiles;
	int			ret = 0;
	char			buf[BUFSIZ];

	/*
	 *	Analisa as op��es
	 */
	while ((opt = getopt (argc, argv, "aivH")) != EOF)
	{
		switch (opt)
		{
		    case 'a':			/* Append */
			aflag++;
			break;

		    case 'i':			/* Ignore interrupts */
			signal (SIGHUP,  SIG_IGN);
			signal (SIGINT,  SIG_IGN);
			signal (SIGQUIT, SIG_IGN);
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
	 *	Aloca �rea para os "file descriptors"
	 */
	nfiles = argc + 1;

	fd = alloca (nfiles * sizeof (int));
	
	argv--;		/* argv[0] == stdout */
	fd[0] = 1;

	/*
	 *	Abre todos os arquivos dados
	 */
	for (i = 1; argv[i]; i++)
	{
		if ((fd[i] = open (argv[i], O_MODE (aflag), 0666)) < 0)
		{
			fprintf 
			(	stderr,
				"%s: N�o consegui abrir \"%s\" (%s)\n",
				pgname, argv[i], strerror (errno)
			);
			ret++;
		}
	}

	if (ret)
		exit (ret);

	/*
	 *	L� da entrada padr�o e copia em todas as sa�das
	 */
	while ((n = read (0, buf, BUFSIZ)) > 0)
	{
		for (i = 0; i < nfiles; i++)
		{
			if (write (fd[i], buf, n) != n)
			{
				fprintf 
				(	stderr,
					"%s: Erro de escrita no arquivo \"%s\" (%s)\n",
					pgname, i == 0 ? "stdout" : argv[i], strerror (errno)
				);
				exit (1);
			}
		}
	}

	if (n < 0)
	{
		fprintf 
		(	stderr,
			"%s: Erro na leitura da entrada padr�o (%s)\n",
			pgname, strerror (errno)
		);
		ret++;
	}

	/*
	 *	Fecha todos os arquivos
	 */
	for (i = 1; argv[i]; i++)
		close (fd[i]);

	return (ret);

}	/* end tee */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
help ()
{
	fprintf
	(	stderr,
		"%s - copia a entrada padr�o para diversos arquivos e "
		 "a saida padr�o\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [-ai] [<arquivo> ...]\n",
		pgname, pgversion, pgname
	);
	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-a: adiciona ao final dos arquivos ao inv�s de "
			"reescreve-los\n"
		"\t-i: Ignora interrup��es\n"
	);

	exit (2);

}	/* end help */
