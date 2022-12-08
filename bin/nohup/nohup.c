/*
 ****************************************************************
 *								*
 *			nohup.c					*
 *								*
 *	Executa um comando imune ao sinal SIGHUP		*
 *								*
 *	Vers�o	3.2.0, de 13.05.99				*
 *		3.2.3, de 15.04.00				*
 *								*
 *	M�dulo: nohup						*
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
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o:	3.2.3, de 15.04.00";

#define	NOHUP_STR "nohup.out"

#define	elif	else if

#define STR(x)	# x
#define XSTR(x)	STR (x)

#define	STDOUT	1
#define	STDERR	2

entry int	vflag;		/* Verbose */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		help (void);

/*
 ****************************************************************
 *	Executa um comando imune ao sinal SIGHUP		*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt;

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
	 *	Se n�o foram dados argumentos, ...
	 */
	if (argv[0] == NOSTR)
		return (0);

	/*
	 *	Ignora o sinal SIGHUP
	 */
	if (signal (SIGHUP, SIG_IGN) == SIG_ERR)
		error ("$*N�o consegui ignorar o sinal SIGHUP");

	/*
	 *	Redireciona as sa�das padr�es e de erro
	 */
	if (isatty (STDOUT) || isatty (STDERR))
	{
		char		*out_str;
		const char	*home_str;
		int		fd, r;

		if ((fd = open (NOHUP_STR, O_WRONLY|O_CREAT|O_APPEND)) < 0)
		{
			if ((home_str = getenv ("HOME")) == NOSTR)
				error ("$*N�o consegui abrir/criar " NOHUP_STR);

			out_str = alloca (strlen (home_str) + sizeof (NOHUP_STR) + 2);

			strcpy (out_str, home_str);
			strcat (out_str, "/");
			strcat (out_str, NOHUP_STR);

			if ((fd = open (out_str, O_WRONLY|O_CREAT|O_APPEND)) < 0)
				error ("$*N�o consegui abrir/criar \"%s\"", out_str);
		}

		if (isatty (STDOUT))
		{
			close (STDOUT);

			if ((r = dup2 (fd, STDOUT)) != STDOUT)
				error ("$*N�o consegui duplicar o descritor de arquivos (%d)", r);
		}

		if (isatty (STDERR))
		{
			close (STDERR);

			if ((r = dup2 (fd, STDERR)) != STDERR)
				error ("$*N�o consegui duplicar o descritor de arquivos (%d)", r);
		}


	}

	/*
	 *	Executa o comando dado
	 */
	execvp (argv[0], &argv[0]);

	error ("*N�o consegui executar \"%s\"", argv[0]);

	return (2);

}	/* end nohup */

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
		"%s - executa um comando imune ao sinal SIGHUP\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s <comando> [<op��es>] [<argumentos>]\n",
		pgname, pgversion, pgname
	);

	exit (2);

}	/* end help */
