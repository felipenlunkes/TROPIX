/*
 ****************************************************************
 *								*
 *			main.c					*
 *								*
 *	Editor de textos orientado por linhas			*
 *								*
 *	Vers�o	1.0.0, de 24.10.86				*
 *		3.0.0, de 27.04.97				*
 *								*
 *	M�dulo: ED						*
 *		Editores de Texto				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

#include "../h/ed.h"
#include "../h/txtio.h"
#include "../h/proto.h"
#include "../h/extern.h"

/*
 ****************************************************************
 *	Vari�veis e Defini��es globais				*
 ****************************************************************
 */
const char	pgversion[] =  "Vers�o: 3.0.0, de 26.04.97";

entry int	vflag;		/* Verbose */

/*
 ******	Vari�veis globais ***************************************
 */
entry TEXT	Text;		/* Informa��es sobre o Texto em edi��o */
entry BASE	*Root;		/* In�cio da Lista com o Texto em edi��o */
entry BASE	*Current;	/* Posi��o Corrente */
entry AUTO	Search;		/* Express�o Regular p/ Busca */

entry bool	Interactive;		/* Edi��o no terminal */
entry bool	Interruption = false;	/* Houve uma interrup��o */
entry char	temp_buffer[LSIZE];	/* Buffer temporario para uso geral */

/*
 ****** Prot�tipos de fun��es ***********************************
 */
void		on_signal (int, ...);
void		help (void);

/*
 ****************************************************************
 *	Editor de textos orientado por linhas			*
 ****************************************************************
 */
int
main (int argc, const char *argv[])
{
	int		opt;

	/*
	 *	Pequena inicializa��o
	 */
	signal (SIGINT, on_signal);
	Interactive = isatty (fileno (stdin));

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
	 *	Inicializa��o do Texto
	 */
	if (argv[0] != NULL)
		c_edit (argv[0]);
	else
		c_edit ("");

	Current = Root;

	for (EVER)
	{
		if (Interruption)
		{
			puts ("\nInterrup��o");
			Interruption = false;
		}

		if (Interactive)
		{
			putchar (':');
			putchar (' ');
			fflush (stdout);
		}

		if (read_command ())
			command ();
		elif (!Interactive)
			c_quit ();
	}

}	/* end ed */

/*
 ****************************************************************
 *	Tratamento de Interrup��es				*
 ****************************************************************
 */
void
on_signal (int signo, ...)
{
	signal (SIGINT, on_signal);

	Interruption = true;

}	/* end on_signal */

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
		"%s - editor de textos orientado por linhas\n"
		"\n%s\n"
		"\nSintaxe:\n"
		"\t%s [<arquivo>]\n",
		pgname, pgversion, pgname
	);

	exit (2);

}	/* end help */
