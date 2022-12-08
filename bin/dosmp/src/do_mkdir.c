/*
 ****************************************************************
 *								*
 *			do_mkdir.c				*
 *								*
 *	Cria um diret�rio					*
 *								*
 *	Vers�o	3.0.0, de 28.10.93				*
 *		3.0.0, de 01.03.96				*
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
#include <string.h>
#include <time.h>
#include <errno.h>

#include "../h/common.h"
#include "../h/dos.h"
#include "../h/proto.h"

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void	do_mkdir_help (void);

/*
 ****************************************************************
 *	Cria um diret�rio					*
 ****************************************************************
 */
void
do_mkdir (int argc, const char *argv[])
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
			do_mkdir_help ();
			return;

		    default:			/* Erro */
			fprintf (stderr, "\n");
			do_mkdir_help ();
			return;
		}
	}

	/*
	 *	Pequena consist�ncia
	 */
	argc -= cmd_optind;
	argv += cmd_optind;

	if (argc == 0)
		{ do_mkdir_help (); return; }

	/*
	 *	Cria os diversos diret�rios
	 */
	for (/* vazio */; *argv; argv++)
	{
		if (received_intr)
			break;

		dos_mkdir (*argv);
	}

}	/* end do_mkdir */

/*
 ****************************************************************
 *	Cria um diret�rio					*
 ****************************************************************
 */
int
dos_mkdir (const char *nm)
{
	const char	*cp;
	const UNI	*up = &uni;
	char		par_nm[BLSZ];
	const char	*son_nm;
	DOSSTAT		par_z, son_z;
	int		par_clusno, son_clusno;
	int		dot_dot_clusno;

	/*
	 *	Obt�m o nome do diret�rio pai
	 */
	if   ((cp = strrchr (nm, '/')) == NOSTR)
		{ strcpy (par_nm, "."); son_nm = nm; }
	elif (cp == nm)
		{ strcpy (par_nm, "/"); son_nm = cp + 1; }
	else
		{ strcpy (par_nm, nm); par_nm[cp - nm] = '\0'; son_nm = cp + 1; }

	/*
	 *	Analisa o diret�rio pai
	 */
	if (dos_stat (par_nm, &par_z) < 0)
	{
		printf
		(	"%s: O diret�rio pai \"%s\" j� deve existir (%s)\n",
			cmd_nm, par_nm, strerror (errno)
		);
		return (-1);
	}

	if (!Z_ISDIR (par_z.z_mode))
	{
		printf
		(	"%s: O arquivo \"%s\" n�o � um diret�rio\n",
			cmd_nm, par_nm
		);
		return (-1);
	}

	/*
	 *	Lembrar da idiosincrasia da FAT32
	 */
	if ((par_clusno = par_z.z_cluster) == up->u_root_cluster)
		dot_dot_clusno = 0;
	else
		dot_dot_clusno = par_clusno;

	/*
	 *	Verifica se por acaso o diret�rio filho j� existe
	 */
	if (dos_fstat (son_nm, par_clusno, &son_z) >= 0)
	{
		printf
		(	"%s: O arquivo \"%s\" j� existe\n",
			cmd_nm, son_nm
		);
		return (-1);
	}

	/*
	 *	Agora, aloca um CLUSTER para o diret�rio FILHO 
	 */
	if ((son_clusno = get_new_cluster (0)) < 0)
	{
		printf
		(	"%s: N�o consegui obter um cluster para o diret�rio (%s)\n",
			cmd_nm, strerror (errno)
		);
		return (-1);
	}

	cluster_block_clr (son_clusno);

	/*
	 *	Prepara a entrada "." do filho
	 */
	clr_dir_ent (&son_z.z_d);

	put_str_with_blanks (".", son_z.z_name, sizeof (son_z.z_name));
	put_str_with_blanks ("",  son_z.z_ext,  sizeof (son_z.z_ext));
	son_z.z_mode = Z_DIR;
	put_dos_file_time (time ((time_t *)NULL), &son_z.z_d);
	PUT_CLUSTER (son_clusno, &son_z);
   /*** son_z.z_size = 0; ***/

	son_z.z_blkno  = FIRST_BLK (son_clusno);
	son_z.z_offset = 0;

	dos_dir_write (&son_z);

	/*
	 *	Prepara a entrada ".." do filho
	 */
	clr_dir_ent (&son_z.z_d);

	put_str_with_blanks ("..", son_z.z_name, sizeof (son_z.z_name));
   	put_str_with_blanks ("",  son_z.z_ext,  sizeof (son_z.z_ext));
	son_z.z_mode = Z_DIR;
	put_dos_file_time (time ((time_t *)NULL), &son_z.z_d);
	PUT_CLUSTER (dot_dot_clusno, &son_z);
   /*** son_z.z_size = 0; ***/

   /***	son_z.z_blkno  = FIRST_BLK (son_clusno); ***/
	son_z.z_offset = sizeof (DOSDIR);

	dos_dir_write (&son_z);

	/*
	 *	Prepara a entrada do pai para o filho
	 */
   /***	put_dos_file_nm (son_nm, &par_z.z_d); ***/
	par_z.z_mode = Z_DIR;
	put_dos_file_time (time ((time_t *)NULL), &par_z.z_d);
	PUT_CLUSTER (son_clusno, &par_z);
   /*** par_z.z_size = 0; ***/

	par_z.z_lfn_clusno = par_clusno;
	par_z.z_lfn_nm = (char *)son_nm;

	dos_lfn_dir_put (&par_z);

	return (0);

}	/* end dos_mkdir */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
do_mkdir_help (void)
{
	fprintf
	(	stderr,
		"%s - cria diret�rios DOS\n"
		"\nSintaxe:\n"
		"\t%s <diret�rio> ...\n",
		cmd_nm, cmd_nm
	);

}	/* end do_mkdir_help */
