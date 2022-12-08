/*
 ****************************************************************
 *								*
 *			do_quit.c				*
 *								*
 *	Encerra as atividades					*
 *								*
 *	Vers�o	3.0.0, de 28.10.93				*
 *		3.0.5, de 12.02.97				*
 *								*
 *	M�dulo: DOSMP						*
 *		Utilit�rios Sofisticados			*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 		Inspirado no PLDOS de Norival Ribeiro Figueira	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>

#include "../h/common.h"
#include "../h/proto.h"

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void	do_quit_help (void);

/*
 ****************************************************************
 *	Encerra as atividades					*
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

	quit (0);

}	/* end do_quit */

/*
 ****************************************************************
 *	Executa o t�rmino					*
 ****************************************************************
 */
void
quit (int n)
{
	/*
	 *	Escreve a FAT
	 */
   	if (fs_status == FS_MOUNT_RW)
	{
	   /***	put_fat (); ***/
		update_fat32_info ();
	}

	close (dev_fd);

	exit (n);

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
