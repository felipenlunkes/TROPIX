/*
 ****************************************************************
 *								*
 *			do_clri.c				*
 *								*
 *	Remove entradas de diret�rio (modo de p�nico)		*
 *								*
 *	Vers�o	3.0.0, de 30.11.93				*
 *		3.0.0, de 03.03.95				*
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../h/common.h"
#include "../h/dos.h"
#include "../h/proto.h"

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void		simple_clri (const char *);
void		do_clri_help (void);

/*
 ****************************************************************
 *	Remove entradas de diret�rio (modo de p�nico)		*
 ****************************************************************
 */
void
do_clri (int argc, const char *argv[])
{
	int		opt;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = cmd_getopt (argv, "vH")) >= 0)
	{
		switch (opt)
		{
		    case 'v':			/* Verboso */
			cmd_vflag++;
			break;

		    case 'H':			/* Help */
			do_clri_help ();
			return;

		    default:			/* Erro */
			fprintf (stderr, "\n");
			do_clri_help ();
			return;
		}
	}

	/*
	 *	Pequena consist�ncia
	 */
	argc -= cmd_optind;
	argv += cmd_optind;

	if (argc == 0)
		{ do_clri_help (); return; }

	/*
	 *	Processa os arquivos
	 */
	for (/* vazio */; *argv; argv++)
	{
		if (received_intr)
			break;

		simple_clri (*argv);
	}

}	/* end do_clri */

/*
 ****************************************************************
 *	Move um arquivo						*
 ****************************************************************
 */
void
simple_clri (const char *path)
{
	DOSSTAT		z;

	/*
	 *	Obt�m o estado do arquivo
	 */
	if (dos_stat (path, &z) < 0)
	{
		printf
		(	"%s: N�o consegui obter o estado de \"%s\" (%s)\n",
			cmd_nm, path, strerror (errno)
		);
		return;
	}

	/*
	 *	Pede confirma��o do usuario
	 */
	fprintf (stderr, "%s (cluster %d)? (n) : ", path, z.z_cluster);

	if (askyesno () <= 0)
		return;

	/*
	 *	Zera a entrada
	 */
	dos_lfn_dir_clr (&z);

}	/* end simple_clri */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
do_clri_help (void)
{
	fprintf
	(	stderr,
		"%s - remove entradas de diret�rio DOS (modo de P�NICO)\n"
		"\nSintaxe:\n"
		"\t%s <arquivo> ...\n",
		cmd_nm, cmd_nm
	);

}	/* end do_clri_help */
