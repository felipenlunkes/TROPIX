/*
 ****************************************************************
 *								*
 *			do_rmdir.c				*
 *								*
 *	Remove diret�rios					*
 *								*
 *	Vers�o	3.0.0, de 22.11.93				*
 *		3.1.0, de 15.01.99				*
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
void		do_rmdir_help (void);

/*
 ****************************************************************
 *	Remove diret�rios					*
 ****************************************************************
 */
void
do_rmdir (int argc, const char *argv[])
{
	int		opt;

	/*
	 *	Inicializa��es
	 */
	cmd_iflag = 1;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = cmd_getopt (argv, "H")) >= 0)
	{
		switch (opt)
		{
		    case 'H':			/* Help */
			do_rmdir_help ();
			return;

		    default:			/* Erro */
			fprintf (stderr, "\n");
			do_rmdir_help ();
			return;
		}
	}

	/*
	 *	Pequena consist�ncia
	 */
	argc -= cmd_optind;
	argv += cmd_optind;

	if (argc == 0)
		{ do_rmdir_help (); return; }

	/*
	 *	Processa os arquivos
	 */
	for (/* vazio */; *argv; argv++)
	{
		if (received_intr)
			break;

		dos_rmdir (*argv);
	}

}	/* end do_rmdir */

/*
 ****************************************************************
 *	Remove um diret�rio					*
 ****************************************************************
 */
int
dos_rmdir (const char *path)
{
	int			clusno;
   /***	const UNI		*up = &uni; ***/
	DOSSTAT			path_z, z;
	DOSFILE			f;

	/*
	 *	Obt�m o estado do arquivo
	 */
	if (dos_stat (path, &path_z) < 0)
	{
		printf
		(	"%s: N�o consegui obter o estado de \"%s\" (%s)\n",
			cmd_nm, path, strerror (errno)
		);
		return (-1);
	}

	/*
	 *	Verifica se � um diret�rio
	 */
	if (!Z_ISDIR (path_z.z_mode))
	{
		printf
		(	"%s: O arquivo \"%s\" n�o � um diret�rio\n",
			cmd_nm, path
		);
		return (-1);
	}

	if ((clusno = path_z.z_cluster) == uni.u_root_cluster)
	{
		printf
		(	"%s: N�o posso remover a raiz\n",
			cmd_nm
		);
		return (-1);
	}

	if (clusno == cwd_cluster)
	{
		printf
		(	"%s: N�o posso remover o diret�rio corrente\n",
			cmd_nm
		);
		return (-1);
	}

	/*
	 *	Verifica se tem o bit "r" ligado
	 */
	if (path_z.z_mode & Z_RO)
	{
		fprintf
		(	stderr,
			"%s: O diret�rio \"%s\" s� permite leituras - "
			"remove? (n): ",
			cmd_nm, path
		);

		if (askyesno () <= 0)
			return (-1);
	}

	/*
	 *	L� o diret�rio, para verificar que est� vazio
	 */
	if (dos_open_by_clus (&f, clusno, BIG_SZ) < 0)
		return (-1);

	dos_lfn_init (&z);

	while (dos_read (&f, &z.z_d, sizeof (DOSDIR)) > 0)
	{
		if (z.z_name[0] == '\0')
			break;

		if (z.z_name[0] == Z_EMPTY)
			{ dos_lfn_reset (&z); continue; }

		if (Z_ISLFN (z.z_mode))
			{ dos_lfn_add (&z); continue; }

		dos_lfn_get_nm (&z);

		if (streq (z.z_lfn_nm, ".") || streq (z.z_lfn_nm, ".."))
			{ dos_lfn_reset (&z); continue; }

	   /***	GET_CLUSTER (&z); ***/

		printf
		(	"%s: O diret�rio \"%s\" n�o est� vazio\n",
			cmd_nm, path
		);

		return (-1);
	}

	/*
	 *	Remove o arquivo
	 */
	if (dos_unlink (&path_z, 1 /* trunca */) < 0)
		return (-1);

	return (0);

}	/* end dos_rmdir */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
do_rmdir_help (void)
{
	fprintf
	(	stderr,
		"%s - remove diret�rios DOS\n"
		"\nSintaxe:\n"
		"\t%s <diret�rio> ...\n",
		cmd_nm, cmd_nm
	);

}	/* end do_rmdir_help */
