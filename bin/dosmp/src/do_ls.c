/*
 ****************************************************************
 *								*
 *			do_ls.c					*
 *								*
 *	Imprime o conte�do de diret�rios			*
 *								*
 *	Vers�o	3.0.0, de 28.10.93				*
 *		3.0.0, de 06.02.96				*
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
 ******	Bloco de informa��es de cada arquivo ********************
 */
typedef struct	info	INFO;

struct	info
{
	char	i_nm[LFN_SZ];	/* Nome de arquivo ou diret�rio */
	int	i_mode;		/* Modo do arquivo ou diret�rio */
	time_t	i_time;		/* Data do arquivo ou diret�rio */
	int	i_cluster;	/* No. do cluster */
	int	i_size;		/* Tamanho do arquivo ou diret�rio */
	INFO	*i_next;	/* Pr�ximo elemento da lista */
};

#define	NOINFO	(INFO *)NULL

entry INFO	ls_filelist,	/* Cabe�a da lista de arquivos */
		ls_dirlist;	/* Cabe�a da lista de diret�rios */

entry INFO	*ls_dirptr;	/* Ponteiro para o diret�rio sendo listado */

/*
 ******	Vari�veis diversas **************************************
 */
entry int	ls_many_files;	/* Mais de um nome dado */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void	ls_proc_file (const char *);
void	ls_list_insert (INFO *, INFO *);
void	ls_show_list (INFO *, int);
long	ls_get_cluster_list_size (int);
void	print_cluster_list (int);
int	dir_ls_function (const DOSSTAT *);
void	do_ls_help (void);

/*
 ****************************************************************
 *	Imprime o conte�do de diret�rios			*
 ****************************************************************
 */
void
do_ls (int argc, const char *argv[])
{
	int		write_dir_nm = 0;
	int		opt;

	/*
	 *	Inicializa��es
	 */
	ls_many_files = 0;

	ls_filelist.i_next	= NOINFO;
	ls_dirlist.i_next	= NOINFO;
	ls_dirptr	  	= NOINFO;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = cmd_getopt (argv, "alH")) >= 0)
	{
		switch (opt)
		{
		    case 'a':			/* Tambem "." e ".." */
			cmd_aflag++;
			break;

		    case 'l':			/* Lista longa */
			cmd_lflag++;
			break;

		    case 'H':			/* Help */
			do_ls_help ();
			return;

		    default:			/* Erro */
			fprintf (stderr, "\n");
			do_ls_help ();
			return;
		}
	}

	/*
	 *	Pequena consist�ncia
	 */
	argc -= cmd_optind;
	argv += cmd_optind;

	if (argc > 1)
		ls_many_files++;

	/*
	 *	Processa os argumentos
	 */
	if (*argv == NOSTR)
	{
		ls_proc_file (".");
	}
	else
	{
		for (/* vazio */; *argv; argv++)
		{
			if (received_intr)
				break;

			ls_proc_file (*argv);
		}
	}

	/*
	 *	Lista os arquivos
	 */
	if (argc > 1)
		write_dir_nm = 1;

	if (ls_filelist.i_next)
		write_dir_nm++;

	ls_show_list (&ls_filelist, 0);

	/*
	 *	Lista os diret�rios; repare que "dir_walk" estende "dirlist"
	 */
	for (ls_dirptr = ls_dirlist.i_next; ls_dirptr != NOINFO; /* abaixo */)
	{
		INFO	*old_ptr;

		if (!received_intr)
		{
			if (write_dir_nm)
			{
				if (write_dir_nm++ > 1)
					printf ("\n");

				printf ("\"%s\":\n", ls_dirptr->i_nm);
			}
		}

		dir_walk (dir_ls_function, ls_dirptr->i_cluster);

		ls_show_list (&ls_filelist, write_dir_nm);

		old_ptr = ls_dirptr; ls_dirptr = ls_dirptr->i_next; free (old_ptr);

	}	/* end for */

}	/* end do_ls */

/*
 ****************************************************************
 *	Processa um nome					*
 ****************************************************************
 */
void
ls_proc_file (const char *filenm)
{
	INFO		*ip;
	DOSSTAT		z;

	if ((ip = malloc (sizeof (INFO))) == NOINFO)
		error ("$Mem�ria esgotada");

	if (dos_stat (filenm, &z) < 0)
	{
		printf
		(	"%s: N�o achei \"%s\" (%s)\n",
			cmd_nm, filenm, strerror (errno)
		);
		free (ip);
		return;
	}

	strcpy (ip->i_nm, last_nm (filenm));
	ip->i_mode = z.z_mode;
	ip->i_cluster = z.z_cluster;

	if (Z_ISDIR (ip->i_mode))
	{
		ls_list_insert (&ls_dirlist, ip);
	}
	else
	{
		ip->i_time = get_dos_file_time (&z.z_d);

		if ((ip->i_size = GET_LONG (z.z_size)) == 0 && Z_ISDIR (z.z_mode))
			ip->i_size = ls_get_cluster_list_size (ip->i_cluster);

		ls_list_insert (&ls_filelist, ip);
	}

}	/* end ls_proc_file */

/*
 ****************************************************************
 *	Insere no ponto correto da lista			*
 ****************************************************************
 */
void
ls_list_insert (INFO *list, INFO *member)
{
	INFO		*ip;
	const char	*nm;

	if   (list == &ls_dirlist)
	{
		/*
		 *	Se for um diret�rio, insere alfabeticamente,
		 *	mas depois do diret�rio atual
		 */
		if ((ip = ls_dirptr) == NOINFO)
			ip = list;

		nm = member->i_nm;

		for (/* vazio */; ip->i_next != NOINFO; ip = ip->i_next)
		{
			if (strcmp (nm, ip->i_next->i_nm) <= 0)
				break;
		}
	}
	else
	{
		/*
		 *	Insere alfabeticamente
		 */
		nm = member->i_nm;
	
		for (ip = list; ip->i_next != NOINFO; ip = ip->i_next)
		{
			if (strcmp (nm, ip->i_next->i_nm) <= 0)
				break;
		}
	}

	member->i_next = ip->i_next;
	ip->i_next = member;

}	/* end ls_list_insert */

/*
 ****************************************************************
 *	Lista as informa��es de uma LISTA			*
 ****************************************************************
 */
void
ls_show_list (INFO *list, int write_dir_nm)
{
	const UNI	*up = &uni;
	INFO		*ip, *nextip;
	const char	*cp;

	if (write_dir_nm)
		cp = "  ";
	else
		cp = "";

	for (ip = list->i_next; ip != NOINFO; ip = ip->i_next)
	{
		if (received_intr)
			break;

		if (cmd_lflag == 2)
		{
			printf ("%7d, ", ip->i_cluster);
			printf ("%7d ", FIRST_BLK (ip->i_cluster));
		}

		if (cmd_lflag)
		{
			printf ("%c ",  file_type_edit (ip->i_mode));
			printf ("%s ",  file_mode_edit (ip->i_mode));
			printf ("%9d ", ip->i_size);
			print_time (ip->i_time);
		}

		printf ("%s", color_vector[file_color_convert (ip->i_mode)]);

		if (ip->i_mode & Z_HIDDEN)
			printf (" (%s)\n", ip->i_nm);
		else
			printf ("  %s\n", ip->i_nm);

		printf ("%s", color_vector[MC_DEF]);

		if (cmd_lflag > 2)
			print_cluster_list (ip->i_cluster);
	}

	/*
	 *	Libera a mem�ria
	 */
	for (ip = list->i_next; ip != NOINFO; ip = nextip)
	{
		nextip = ip->i_next;
		free (ip);
	}

	list->i_next = NOINFO;		/* Esvazia a LISTA */

}	/* end ls_show_list */

/*
 ****************************************************************
 *	Obt�m o tamanho a partir da lista de CLUSTERs		*
 ****************************************************************
 */
long
ls_get_cluster_list_size (int cluster)
{
	long		sz;
	const UNI	*up = &uni;

	for (sz = 0; /* abaixo */; cluster = get_fat_value (cluster))
	{
		if (C_ISFREE (cluster) || C_ISBAD_OR_EOF (cluster))
			break;

		sz += CLUSZ;
	}

	return (sz);

}	/* end ls_get_cluster_list_size */

/*
 ****************************************************************
 *	Imprime a lista de CLUSTERs				*
 ****************************************************************
 */
void
print_cluster_list (int cluster)
{
	printf ("[");

	for (/* vazio */; /* abaixo */; cluster = get_fat_value (cluster))
	{
		if (C_ISFREE (cluster) || C_ISBAD_OR_EOF (cluster))
			break;

		printf ("%d ", cluster);
	}
	
	printf ("]\n");

}	/* end print_cluster_list */

/*
 ****************************************************************
 *	Fun��o executada para cada diret�rio lido		*
 ****************************************************************
 */
int
dir_ls_function (const DOSSTAT *zp)
{
	INFO 		*ip;
	const char	*nm = zp->z_lfn_nm;

	if (received_intr)
		return (-1);

	if (!cmd_aflag && (streq (nm, ".") || streq (nm, "..")))
		return (0);

	if ((ip = malloc (sizeof (INFO))) == NOINFO)
		error ("$Mem�ria esgotada");

	strcpy (ip->i_nm, nm);

	ip->i_mode	= zp->z_mode;
	ip->i_time	= get_dos_file_time (&zp->z_d);
	ip->i_cluster	= zp->z_cluster;

	if ((ip->i_size = GET_LONG (zp->z_size)) == 0 && Z_ISDIR (zp->z_mode))
		ip->i_size = ls_get_cluster_list_size (ip->i_cluster);

	ls_list_insert (&ls_filelist, ip);

	return (0);

}	/* end dir_ls_function */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
do_ls_help (void)
{
	fprintf
	(	stderr,
		"%s - lista caracter�sticas de arquivos\n"
		"\nSintaxe:\n"
		"\t%s [-al] <arquivo> ...\n",
		cmd_nm, cmd_nm
	);

	fprintf
	(	stderr,
		"\nOp��es:"
		"\t-a: Lista tamb�m \".\" e \"..\"\n"
		"\t-l: Listagem longa\n"
		"\nObs.: Se n�o for dado nenhum <arquivo> "
			"ser� considerado o diret�rio corrente\n"
	);

}	/* end do_ls_help */
