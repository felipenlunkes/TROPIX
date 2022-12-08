/*
 ****************************************************************
 *								*
 *			do_walk.c				*
 *								*
 *	Percorre uma �rvore DOS					*
 *								*
 *	Vers�o	3.0.0, de 28.10.93				*
 *		3.0.0, de 10.06.95				*
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
int	walk_function (const char *, DOSSTAT *, int);
void	do_walk_help (void);

/*
 ****************************************************************
 *	Percorre uma �rvore DOS					*
 ****************************************************************
 */
void
do_walk (int argc, const char *argv[])
{
	int		opt;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = cmd_getopt (argv, "lH")) >= 0)
	{
		switch (opt)
		{
		    case 'l':			/* Longo */
			cmd_lflag++;
			break;

		    case 'H':			/* Help */
			do_walk_help ();
			return;

		    default:			/* Erro */
			fprintf (stderr, "\n");
			do_walk_help ();
			return;
		}
	}

	/*
	 *	Pequena consist�ncia
	 */
	argc -= cmd_optind;
	argv += cmd_optind;

	/*
	 *	Percorre as �rvores dadas
	 */
	if (argc == 0)
	{
		dos_ftw (".", walk_function);
	}
	else for (/* vazio */; *argv; argv++)
	{
		if (received_intr)
			break;

		dos_ftw (*argv, walk_function);
	}

}	/* end do_walk */

/*
 ****************************************************************
 *	Fun��o chamada por "ftw"				*
 ****************************************************************
 */
int
walk_function (const char *nm, DOSSTAT *zp, int status)
{
	if (status == DOS_FTW_NS)
	{
		printf
		(	"%s: N�o encontrei o arquivo \"%s\" (%s)\n",
			cmd_nm, nm, strerror (errno)
		);
		return (-1);
	}

	if (cmd_lflag > 1)
		printf ("%6d,%6d  ", zp->z_blkno, zp->z_offset);

	printf ("%c  ", file_type_edit (zp->z_mode));

	if (Z_ISREG (zp->z_mode))
		printf ("%9d  ", GET_LONG (zp->z_size));
	else
		printf ("           ");

	if (cmd_lflag)
	{

		printf ("%4d  ", zp->z_cluster);

		printf ("(%d)\t", status); 
	}

	printf ("%s", color_vector[file_color_convert (zp->z_mode)]);

	if (zp->z_mode & Z_HIDDEN)
		printf ("(%s)\n", nm);
	else
		printf (" %s\n", nm);

	printf ("%s", color_vector[MC_DEF]);

	return (0);

}	/* end walk_function */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
do_walk_help (void)
{
	fprintf
	(	stderr,
		"%s - percorre �rvores DOS\n"
		"\nSintaxe:\n"
		"\t%s [-l] [<�rvore> ...]\n",
		cmd_nm, cmd_nm
	);

	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-l: Listagem longa\n"
		"\nObs.:\tSe n�o for dada nenhuma <�rvore>, � percorrido "
			"o diret�rio corrente\n"
	);

}	/* end do_walk_help */
