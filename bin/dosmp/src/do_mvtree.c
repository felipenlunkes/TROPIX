/*
 ****************************************************************
 *								*
 *			do_mvtree.c				*
 *								*
 *	Move (troca o nome) de diret�rios DOS			*
 *								*
 *	Vers�o	3.0.0, de 22.11.93				*
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
void		simple_mvtree (const char *, const char *);
int		is_ancest (const char *, int, const char *, int);
void		do_mvtree_help (void);

/*
 ****************************************************************
 *	Move (troca o nome) de diret�rios DOS			*
 ****************************************************************
 */
void
do_mvtree (int argc, const char *argv[])
{
	char		*cp;
	const char	*nm;
	int		opt;
	int		old_clusno;
	int		old_par_clusno, new_par_clusno;
	const char	*old_path, *new_path;
	const char	*new_par_path;
	DOSSTAT		old_z, new_z, old_par_z;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = cmd_getopt (argv, "ifvH")) >= 0)
	{
		switch (opt)
		{
		    case 'H':			/* Help */
			do_mvtree_help ();
			return;

		    default:			/* Erro */
			fprintf (stderr, "\n");
			do_mvtree_help ();
			return;
		}
	}

	/*
	 *	Pequena consist�ncia
	 */
	argc -= cmd_optind;
	argv += cmd_optind;

	if (argc != 2)
		{ do_mvtree_help (); return; }

	/*
	 *	Normaliza os caminhos
	 */
	old_path = path_can ((char *)argv[0]);
	new_path = path_can ((char *)argv[1]);

	/*
	 *	Analisa o "old"
	 */
	if ((dos_stat (old_path, &old_z)) < 0)
	{
		printf
		(	"%s: N�o consegui obter o estado de \"%s\" (%s)\n",
			cmd_nm, old_path, strerror (errno)
		);
		return;
	}

	old_clusno = old_z.z_cluster;

	if (!Z_ISDIR (old_z.z_mode))
	{
		fprintf
		(	stderr,
			"%s: \"%s\" n�o � um diret�rio\n",
			cmd_nm, old_path
		);
		return;
	}

	/*
	 *	Analisa o �ltimo componente do caminho do <diret�rio fonte>
	 */
	nm = last_nm (old_path);

	if (streq (nm, ".")  ||  streq (nm, "..") || old_clusno == 0)
	{
		fprintf
		(	stderr,
			"%s: N�o posso trocar o nome de \"%s\"\n",
			cmd_nm, old_path
		);
		return;
	}

	/*
	 *	Analisa o "new"
	 */
	if ((dos_stat (new_path, &new_z)) >= 0)		/* O "new" j� existe */
	{
		if (!Z_ISDIR (new_z.z_mode))
		{
			fprintf
			(	stderr,
				"%s: \"%s\" j� existe e n�o � diret�rio\n",
				cmd_nm, new_path
			);
			return;
		}

		new_par_clusno = new_z.z_cluster;

		if (new_par_clusno == old_clusno)
		{
			fprintf
			(	stderr,
				"%s: Os dois nomes referem-se ao mesmo diret�rio\n",
				cmd_nm
			);
			return;
		}

		/*
		 *	Comp�e o nome novo
		 */
	   /***	nm = last_nm (old_path)); ***/

		cp = alloca (strlen (new_path) + strlen (nm) + 2);

		strcpy (cp, new_path);

		if (strcmp (cp, "/"))
			strcat (cp, "/");

		strcat (cp, nm);

		new_path = cp;

		if ((dos_stat (new_path, &new_z)) >= 0)
		{
			fprintf
			(	stderr,
				"%s: \"%s\" j� existe\n",
				cmd_nm, new_path
			);
			return;
		}
	}
	else		/* O "new" ainda n�o existe */
	{
		if   ((cp = strrchr (new_path, '/')) == NOSTR)
			new_par_path = ".";
		elif (cp == new_path)
			{ new_par_path = "/"; cp = NOSTR; }
		else
			{ new_par_path = new_path; *cp = '\0'; }

		if ((dos_stat (new_par_path, &new_z)) < 0)
		{
			printf
			(	"%s: N�o consegui obter o estado de \"%s\" (%s)\n",
				cmd_nm, new_par_path, strerror (errno)
			);
			return;
		}

		new_par_clusno = new_z.z_cluster;

		if (cp != NOSTR)
			*cp = '/';
	}

	/*
	 *	Verifica se o nome composto ficou igual
	 */
	if (streq (old_path, new_path))
	{
		printf ("%s: <fonte> == <destino> ?\n", cmd_nm);
		return;
	}

	/*
	 *	Analisa o pai do <diret�rio fonte>
	 */
	if (dos_fstat ("..",  old_clusno, &old_par_z) < 0)
	{
		fprintf
		(	stderr,
			"%s: N�o consegui obter o estado do pai de \"%s\" (%s)\n",
			cmd_nm, old_path, strerror (errno)
		);
		return;
	}

	old_par_clusno = old_par_z.z_cluster;

	/*
	 *	Se o pai n�o � o mesmo, ...
	 */
	if (new_par_clusno != old_par_clusno)
	{
		if (is_ancest (old_path, old_clusno, new_path, new_par_clusno))
			return;
	}

	/*
	 *	Cria/apaga os nomes do "diret�rio"
	 */
	if (dos_link (&old_z, new_path) < 0)
	{
		printf
		(	"%s: N�o consegui criar o link de \"%s\" para \"%s\" (%s)\n",
			cmd_nm, old_path, new_path, strerror (errno)
		);
		return;
	}

	dos_unlink (&old_z, 0 /* Sem truncar */);

	/*
	 *	Se o pai n�o � o mesmo, atualiza a entrada ".."
	 */
	if (new_par_clusno != old_par_clusno)
	{
		PUT_CLUSTER (new_par_clusno, &old_par_z);
		dos_dir_write (&old_par_z);
	}

}	/* end do_mvtree */

/*
 ****************************************************************
 * 	Checa se o diret�rio antigo � ancestral do novo		*	
 ****************************************************************
 */
int
is_ancest (const char *old_path, int old_clusno, const char *new_path, int new_par_clusno)
{
	int		clusno = new_par_clusno;
	DOSSTAT		z;

	while (clusno != 0)
	{
		if (dos_fstat ("..", clusno, &z) < 0)
		{
			printf
			(	"%s: N�o consegui obter o estado de um "
				"ancestral de \"%s\"\n",
				cmd_nm, new_path	
			);
			return (1);
		}

		if ((clusno = z.z_cluster) == old_clusno)
		{
			fprintf
			(	stderr,
				"%s: \"%s\" � ancestral de \"%s\"\n",
				cmd_nm, old_path, new_path
			);
			return (1);
		}

	}	/* end while (subindo na �rvore) */

	return (0);

}	/* end is_ancest */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
do_mvtree_help (void)
{
	fprintf
	(	stderr,
		"%s - move (troca o nome) de diret�rios DOS\n"
		"\nSintaxe:\n"
		"\t%s <diret�rio1> <diret�rio2>\n",
		cmd_nm, cmd_nm
	);

}	/* end do_mvtree_help */
