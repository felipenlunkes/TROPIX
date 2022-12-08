/*
 ****************************************************************
 *								*
 *			quit.c					*
 *								*
 *	Gerenciador de contas					*
 *								*
 *	Vers�o	1.5.0, de 04.06.84				*
 *		3.0.0, de 30.07.97				*
 *								*
 *	M�dulo: edusr						*
 *		Utilit�rios B�sicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>

#include "../h/edusr.h"

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void	do_quit_help (void);

/*
 ****************************************************************
 *	Encerra o editor					*
 ****************************************************************
 */
void
do_quit (int argc, const char *argv[])
{
	int		opt;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = cmd_getopt (argv, "H")) >= 0)
	{
		switch (opt)
		{
		    case 'H':			/* Help */
			do_quit_help ();
			return;

		    default:			/* Erro */
			fprintf (stderr, "\n");
			do_quit_help ();
			return;
		}
	}

	/*
	 *	Pequena consist�ncia
	 */
	argc -= cmd_optind;
	argv += cmd_optind;

	if (argc != 0)
		{ do_quit_help (); return; }

	quit ();

}	/* end do_quit */

/*
 ****************************************************************
 *	Termina a edi��o					*
 ****************************************************************
 */
void
quit (void)
{
	unlink (lock_file_nm);

	exit (exit_code);

}	/* end quit */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
do_quit_help (void)
{
	fprintf
	(	stderr,
		"%s - termina a execu��o de \"%s\"\n"
		"\nSintaxe:\n"
		"\t%s\n",
		cmd_nm, pgname, cmd_nm
	);

}	/* end do_quit_help */
