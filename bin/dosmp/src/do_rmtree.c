/*
 ****************************************************************
 *								*
 *			do_rmtree.c				*
 *								*
 *	Remove �rvores DOS					*
 *								*
 *	Vers�o	3.0.0, de 23.11.93				*
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
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../h/common.h"
#include "../h/dos.h"
#include "../h/proto.h"

/*
 ******	Vari�veis globais ***************************************
 */
entry int	first;		/* Primeiro nome escrito */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
int		recursive_dir_rm (const char *, DOSSTAT *);
int		file_rm (const char *, DOSSTAT *);
int		dir_rm (const char *, DOSSTAT *);
void		do_rmtree_help (void);

/*
 ****************************************************************
 *	Remove �rvores DOS					*
 ****************************************************************
 */
void
do_rmtree (int argc, const char *argv[])
{
	const char	*tree;
	int		opt;
	DOSSTAT		old_z;

	/*
	 *	Inicializa��es
	 */
	first = 1;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = cmd_getopt (argv, "fvH")) >= 0)
	{
		switch (opt)
		{
		    case 'f':			/* For�a */
			cmd_fflag++;
			break;

		    case 'v':			/* Verboso */
			cmd_vflag++;
			break;

		    case 'H':			/* Help */
			do_rmtree_help ();
			return;

		    default:			/* Erro */
			fprintf (stderr, "\n");
			do_rmtree_help ();
			return;
		}
	}

	/*
	 *	Pequena consist�ncia
	 */
	argc -= cmd_optind;
	argv += cmd_optind;

	if (argc != 1)
		{ do_rmtree_help (); return; }

	/*
	 *	Obt�m o estado do diret�rio fonte
	 */
	tree = path_can ((char *)argv[0]);

	if (dos_stat (tree, &old_z) < 0)
	{
		printf
		(	"%s: N�o consegui obter o estado de \"%s\" (%s)\n",
			cmd_nm, tree, strerror (errno)
		);
		return;
	}

	if (!Z_ISDIR (old_z.z_mode))
	{
		printf
		(	"%s: O arquivo DOS \"%s\" n�o � um diret�rio\n",
			cmd_nm, tree
		);
		return;
	}

	/*
	 *	Come�a a remover
	 */
	recursive_dir_rm (tree, &old_z);

}	/* end do_rmtree */

/*
 ****************************************************************
 *	Percorre a arvore					*
 ****************************************************************
 */
int
recursive_dir_rm (const char *dir_nm, DOSSTAT *zp)
{
	char		*son_nm;
	int		r, files_not_removed = 0;
	int		sz;
	DOSSTAT		son_z, z;
	DOSFILE		f;

	/*
	 *	Verifica se veio uma interrup��o
	 */
	if (received_intr)
		return (-1);

	/*
	 *	Pula uma linha, se for o caso
	 */
	if (cmd_vflag || !cmd_fflag)
	{
		if (!first)
			fputc ('\n', stdout);
		else
			first = 0;
	}

	/*
	 *	Verifica o modo de funcionamento
	 */
	if   (!cmd_fflag)
	{
		fprintf (stderr, "Diret�rio \"%s\", entra? (n): ", dir_nm);

		if (askyesno () <= 0)
			return (1);
	}
	elif (cmd_vflag)
	{
		printf ("Diret�rio \"%s\":\n", dir_nm);
	}

	/*
	 *	Abre o diret�rio e verifica se por acaso n�o �
	 *	o diret�rio corrente ou a raiz
	 */
	if (dos_open (&f, zp) < 0)
		return (1);

	if   (f.f_o_clusno == cwd_cluster)
	{
		printf
		(	"%s: N�o posso remover o diret�rio corrente \"%s\"\n",
			cmd_nm, dir_nm
		);
		return (1);
	}
	elif (f.f_o_clusno == 0)
	{
		printf
		(	"%s: N�o posso remover a raiz\"%s\"\n",
			cmd_nm, dir_nm
		);
		return (1);
	}

	/*
	 *	Le o diret�rio, removendo os arquivos regulares e volumes
	 */
	dos_lfn_init (&z);

	while (dos_read (&f, &z.z_d, sizeof (DOSDIR)) > 0)
	{
		if (received_intr)
			return (-1);

		if (z.z_name[0] == '\0')
			break;

		if (z.z_name[0] == Z_EMPTY)
			{ dos_lfn_reset (&z); continue; }

		if (Z_ISLFN (z.z_mode))
			{ dos_lfn_add (&z); continue; }

		dos_lfn_get_nm (&z);

		if (streq (z.z_lfn_nm, ".") || streq (z.z_lfn_nm, ".."))
			{ dos_lfn_reset (&z); continue; }

		/*
		 *	Comp�e o nome
		 */
		GET_CLUSTER (&z);

		sz = strlen (dir_nm) + strlen (z.z_lfn_nm) + 2;

		son_nm = alloca (sz);

		strcpy (son_nm, dir_nm);
		strcat (son_nm, "/");
		strcat (son_nm, z.z_lfn_nm);

		if (strncmp (son_nm, "./", 2) == 0)
			son_nm += 2;

		if (dos_stat (son_nm, &son_z) < 0)
		{
			printf
			(	"%s: N�o consegui obter o estado de \"%s\" (%s)\n",
				cmd_nm, son_nm, strerror (errno)
			);
			files_not_removed++;
			{ dos_lfn_reset (&z); continue; }
		}

		/*
		 *	Verifica se � um arquivo regular ou volume
		 */
		if (!Z_ISDIR (son_z.z_mode))
		{
			if (file_rm (son_nm, &son_z) < 0)
				files_not_removed++;
		}

		dos_lfn_reset (&z);

	}	/* end while (lendo o diret�rio) */

	/*
	 *	Rel� o diret�rio, removendo os diret�rio
	 */
	dos_rewind (&f); dos_lfn_init (&z);

	while (dos_read (&f, &z.z_d, sizeof (DOSDIR)) > 0)
	{
		GET_CLUSTER (&z);

		if (z.z_name[0] == '\0')
			break;

		if (z.z_name[0] == Z_EMPTY)
			{ dos_lfn_reset (&z); continue; }

		if (Z_ISLFN (z.z_mode))
			{ dos_lfn_add (&z); continue; }

		dos_lfn_get_nm (&z);

		if (streq (z.z_lfn_nm, ".") || streq (z.z_lfn_nm, ".."))
			{ dos_lfn_reset (&z); continue; }

		/*
		 *	Comp�e o nome
		 */
		sz = strlen (dir_nm) + strlen (z.z_lfn_nm) + 2;

		son_nm = alloca (sz);

		strcpy (son_nm, dir_nm);
		strcat (son_nm, "/");
		strcat (son_nm, z.z_lfn_nm);

		if (strncmp (son_nm, "./", 2) == 0)
			son_nm += 2;

		if (dos_stat (son_nm, &son_z) < 0)
		{
			printf
			(	"%s: N�o consegui obter o estado de \"%s\" (%s)\n",
				cmd_nm, son_nm, strerror (errno)
			);
			files_not_removed++;
			{ dos_lfn_reset (&z); continue; }
		}

		/*
		 *	Verifica se � um diret�rio
		 */
		if (Z_ISDIR (son_z.z_mode))
		{
			if ((r = recursive_dir_rm (son_nm, &son_z)) < 0)
				return (-1);

			files_not_removed += r;
		}

		dos_lfn_reset (&z);

	}	/* end while (lendo o diret�rio) */

	/*
	 *	Remove o diret�rio (se ficou vazio)
	 */
	if (files_not_removed == 0)
	{
		if (dir_rm (dir_nm, zp) < 0)
			files_not_removed++;
	}

	return (files_not_removed);

}	/* end recursive_dir_rm */

/*
 ****************************************************************
 *	Remove arquivos						*
 ****************************************************************
 */
int
file_rm (const char *filenm, DOSSTAT *zp)
{
	/*
	 *	Verifica o modo de funcionamento
	 */
	if   (!cmd_fflag)
	{
		fprintf (stderr, "    %s? (n): ", last_nm (filenm));

		if (askyesno () <= 0)
			return (-1);
	}
	elif (cmd_vflag)
	{	
		printf ("    %s:\n", last_nm (filenm));
	}

	/*
	 *	Verifica se tem o bit "r" ligado
	 */
	if (zp->z_mode & Z_RO)
	{
		fprintf
		(	stderr, "%s: O arquivo \"%s\" s� permite leituras - "
			"remove? (n): ",
			cmd_nm, filenm
		);

		if (askyesno () <= 0)
			return (-1);
	}

	/*
	 *	Remove o arquivo
	 */
	if (dos_unlink (zp, 1 /* trunca */) < 0)
	{
		printf
		(	"%s: N�o consegui remover \"%s\" (%s)\n",
			cmd_nm, filenm, strerror (errno)
		);
		return (-1);
	}

	return (0);

}	/* end file_rm */

/*
 ****************************************************************
 *	Remove um diret�rio					*
 ****************************************************************
 */
int
dir_rm (const char *dir_nm, DOSSTAT *zp)
{
	/*
	 *	Verifica o modo de funcionamento
	 */
	if   (!cmd_fflag)
	{
		fprintf (stderr, "\nDiret�rio \"%s\", apaga? (n): ", dir_nm);

		if (askyesno () <= 0)
			return (-1);
	}
	elif (cmd_vflag)
	{	
		printf ("\nRemovendo o diret�rio \"%s\"\n", dir_nm);
	}

	/*
	 *	remove o diret�rio
	 */
	if (dos_rmdir (dir_nm) < 0)
	{
		/* As mensagens j� foram dadas */
		return (-1);
	}

	return (0);

}	/* end dir_rm */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
do_rmtree_help (void)
{
	fprintf
	(	stderr,
		"%s - remove uma �rvore DOS\n"
		"\nSintaxe:\n"
		"\t%s [-fv] <�rvore>\n",
		cmd_nm, cmd_nm
	);

	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-f: Remove os arquivos/diret�rios sem pedir confirma��o "
			"do usu�rio\n"
		"\t-v: Lista os arquivos/diret�rios sendo removidos\n"
	);

}	/* end do_rmtree_help */
