/*
 ****************************************************************
 *								*
 *			do_lc.c					*
 *								*
 *	Imprime o conte�do de diret�rios			*
 *								*
 *	Vers�o	3.0.0, de 28.10.93				*
 *		3.0.0, de 27.02.96				*
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
#include <sys/stat.h>

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
	int	i_cluster;	/* No. do cluster */
	INFO	*i_next;	/* Pr�ximo elemento da lista */
};

#define	NOINFO	(INFO *)NULL

entry INFO	filelist,	/* Cabe�a da lista de arquivos */
		dirlist;	/* Cabe�a da lista de diret�rios */

entry INFO	*dirptr;	/* Ponteiro para o diret�rio sendo listado */

/*
 ******	Vari�veis diversas **************************************
 */
entry int	many_files;	/* Mais de um nome dado */

entry int	max_file_nm_sz;	/* Tamanho do maior nome */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
void	lc_proc_file (const char *);
void	lc_list_insert (INFO *, INFO *);
void	lc_show_list (INFO *, int);
int	dir_lc_function (const DOSSTAT *);
void	do_lc_help (void);

/*
 ****************************************************************
 *	Imprime o conte�do de diret�rios			*
 ****************************************************************
 */
void
do_lc (int argc, const char *argv[])
{
	int		write_dir_nm = 0;
	int		opt;

	/*
	 *	Inicializa��es
	 */
	many_files = 0;

	filelist.i_next	= NOINFO;
	dirlist.i_next	= NOINFO;
	dirptr  	= NOINFO;

	/*
	 *	Analisa as op��es
	 */
	while ((opt = cmd_getopt (argv, "dH")) >= 0)
	{
		switch (opt)
		{
		    case 'H':			/* Help */
			do_lc_help ();
			return;

		    default:			/* Erro */
			fprintf (stderr, "\n");
			do_lc_help ();
			return;
		}
	}

	/*
	 *	Pequena consist�ncia
	 */
	argc -= cmd_optind;
	argv += cmd_optind;

	if (argc > 1)
		many_files++;

	max_file_nm_sz = 0;

	/*
	 *	Processa os argumentos
	 */
	if (*argv == NOSTR)
	{
		lc_proc_file (".");
	}
	else
	{
		for (/* vazio */; *argv; argv++)
		{
			if (received_intr)
				break;

			lc_proc_file (*argv);
		}
	}

	/*
	 *	Lista os arquivos
	 */
	if (argc > 1)
		write_dir_nm = 1;

	/*
	 *	Lista os diret�rios; repare que "dir_walk" estende "dirlist"
	 */
	for (dirptr = dirlist.i_next; dirptr != NOINFO; /* abaixo */)
	{
		INFO	*old_ptr;

		if (!received_intr)
		{
			if (write_dir_nm)
			{
				if (write_dir_nm++ > 1)
					printf ("\n");

				printf ("\"%s\":\n", dirptr->i_nm);
			}
		}

		dir_walk (dir_lc_function, dirptr->i_cluster);

		lc_show_list (&filelist, write_dir_nm);

		old_ptr = dirptr; dirptr = dirptr->i_next; free (old_ptr);

	}	/* end for */

}	/* end do_lc */

/*
 ****************************************************************
 *	Processa um nome					*
 ****************************************************************
 */
void
lc_proc_file (const char *filenm)
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

	strcpy (ip->i_nm, filenm);
	ip->i_mode = z.z_mode;
	ip->i_cluster = z.z_cluster;

	if (Z_ISDIR (ip->i_mode))
	{
		lc_list_insert (&dirlist, ip);
	}
	else
	{
		if (many_files == 0) printf
		(
			"%s: \"%s\" n�o � um diret�rio\n",
			cmd_nm, filenm
		);

		free (ip);
	}

}	/* end lc_proc_file */

/*
 ****************************************************************
 *	Insere no ponto correto da lista			*
 ****************************************************************
 */
void
lc_list_insert (INFO *list, INFO *member)
{
	INFO		*ip;
	const char	*nm;

	if   (list == &dirlist)
	{
		/*
		 *	Se for um diret�rio, insere alfabeticamente,
		 *	mas depois do diret�rio atual
		 */
		if ((ip = dirptr) == NOINFO)
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

}	/* end lc_list_insert */

/*
 ****************************************************************
 *	Lista as informa��es de uma LISTA			*
 ****************************************************************
 */
void
lc_show_list (INFO *list, int write_dir_nm)
{
	INFO		*ip, *nextip;
	int		i = 0, j = 0;
	const char	*cp;
	int		field_sz, precision, no_items;
	char		area[40];

	/*
	 *	Se recebeu interrup��o, ...
	 */
	if (received_intr)
		goto intr_free;

	if (write_dir_nm)
		cp = "  ";
	else
		cp = "";

	/*
	 *	Acerta o visual
	 */
	if (max_file_nm_sz > 16)
		{ field_sz = 37; precision = 35; no_items = 2; }
	else
		{ field_sz = 18; precision = 16; no_items = 4; }

	/*
	 *	Diret�rios
	 */
	for (ip = list->i_next; ip != NOINFO; ip = ip->i_next)
	{
		if (!Z_ISDIR (ip->i_mode))
			continue;

		if (i % no_items == 0)
		{
			if (i == 0)
			{
				printf
				(	"%sDiret�rios:%s",
					cp,
					color_vector[S_IFDIR >> 12]
				);
			}

			printf ("\n%s ", cp);
		}
	
		if (ip->i_mode & Z_HIDDEN)
		{
			sprintf (area, "(%s)", ip->i_nm);
			printf ("%-*.*s ", field_sz, precision, area);
		}
		else
		{
			printf (" %-*.*s", field_sz, precision, ip->i_nm);
		}

		i++;
	}

	if (i > 0)
		{ printf ("\n"); j++; i = 0; }

	/*
	 *	Arquivos regulares
	 */
	for (ip = list->i_next; ip != NOINFO; ip = ip->i_next)
	{
		if (!Z_ISREG (ip->i_mode))
			continue;

		if (i % no_items == 0)
		{
			if (i == 0)
			{
				if (j)
					printf ("\n");

				printf
				(	"%s%sArquivos regulares:%s",
					cp,
					color_vector[MC_DEF],
					color_vector[S_IFREG >> 12]
				);
			}

			printf ("\n%s ", cp);
		}
	
		if (ip->i_mode & Z_HIDDEN)
		{
			sprintf (area, "(%s)", ip->i_nm);
			printf ("%-*.*s ", field_sz, precision, area);
		}
		else
		{
			printf (" %-*.*s", field_sz, precision, ip->i_nm);
		}

		i++;
	}

	if (i > 0)
		{ printf ("\n"); j++; i = 0; }

	/*
	 *	Volumes
	 */
	for (ip = list->i_next; ip != NOINFO; ip = ip->i_next)
	{
		if (!Z_ISVOL (ip->i_mode))
			continue;

		if (i % no_items == 0)
		{
			if (i == 0)
			{
				if (j)
					printf ("\n");

				printf
				(	"%s%sVolumes:%s",
					cp,
					color_vector[MC_DEF],
					color_vector[S_IFBLK >> 12]
				);
			}

			printf ("\n%s ", cp);
		}
	
		if (ip->i_mode & Z_HIDDEN)
		{
			sprintf (area, "(%s)", ip->i_nm);
			printf ("%-*.*s ", field_sz, precision, area);
		}
		else
		{
			printf (" %-*.*s", field_sz, precision, ip->i_nm);
		}

		i++;
	}

	printf ("%s", color_vector[MC_DEF]);

	if (i > 0)
		printf ("\n");

	/*
	 *	Libera a mem�ria
	 */
    intr_free:
	for (ip = list->i_next; ip != NOINFO; ip = nextip)
	{
		nextip = ip->i_next;
		free (ip);
	}

	list->i_next = NOINFO;		/* Esvazia a LISTA */

}	/* end lc_show_list */

/*
 ****************************************************************
 *	Fun��o executada para cada diret�rio lido		*
 ****************************************************************
 */
int
dir_lc_function (const DOSSTAT *zp)
{
	INFO	 	*ip;
	const char	*nm = zp->z_lfn_nm;
	int		sz;

	if (received_intr)
		return (-1);

	if (streq (nm, ".") || streq (nm, ".."))
		return (0);

	/*
	 *	Limita o tamanho do nome a 32/35 caracteres
	 */
	if ((sz = strlen (nm)) > 35)
		{ strcpy ((char *)nm + 32, "..."); sz = 35; }

	if (sz > max_file_nm_sz)
		max_file_nm_sz = sz;

	if ((ip = malloc (sizeof (INFO))) == NOINFO)
		error ("$Mem�ria esgotada");

	strcpy (ip->i_nm, nm);

	ip->i_mode = zp->z_mode;
	ip->i_cluster = zp->z_cluster;

	lc_list_insert (&filelist, ip);

	return (0);

}	/* end dir_lc_function */

/*
 ****************************************************************
 *	Resumo de utiliza��o do programa			*
 ****************************************************************
 */
void
do_lc_help (void)
{
	fprintf
	(	stderr,
		"%s - imprime o conte�do de diret�rios\n"
		"\nSintaxe:\n"
		"\t%s [<diret�rio> ...]\n",
		cmd_nm, cmd_nm
	);

	fprintf
	(	stderr,
		"\nObs.: Se n�o for dado nenhum <diret�rio> "
			"ser� considerado o diret�rio corrente\n"
	);

}	/* end do_lc_help */
