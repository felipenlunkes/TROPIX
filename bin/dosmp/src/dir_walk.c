/*
 ****************************************************************
 *								*
 *			dir_walk.c				*
 *								*
 *   Executa um fun��o para todas as entradas de um diret�rio	*
 *								*
 *	Vers�o	3.0.0, de 28.10.93				*
 *		3.0.0, de 26.02.96				*
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
#include <ctype.h>

#include "../h/common.h"
#include "../h/dos.h"
#include "../h/proto.h"

/*
 ******	Prot�tipos de fun��es ***********************************
 */

/*
 ****************************************************************
 *   Executa um fun��o para todas as entradas de um diret�rio	*
 ****************************************************************
 */
int
dir_walk (int (*function) (const DOSSTAT *), int clusno)
{
	int		n;
	DOSFILE		f;
	DOSSTAT		z;

	/*
	 *	Pequena inicializa��o
	 */
	if (dos_open_by_clus (&f, clusno, BIG_SZ) < 0)
		return (-1);

	dos_lfn_init (&z);

	/*
	 *	Percorre o diret�rio
	 */
	while (dos_read (&f, &z.z_d, sizeof (DOSDIR)) > 0)
	{
		if (z.z_name[0] == '\0')
			break;

		if (z.z_name[0] == Z_EMPTY)
			{ dos_lfn_reset (&z); continue; }

		if (Z_ISLFN (z.z_mode))
			{ dos_lfn_add (&z); continue; }

		dos_lfn_get_nm (&z);
		GET_CLUSTER (&z);

		if ((n = (*function) (&z)) < 0)
			return (n);

		dos_lfn_reset (&z);

	}	/* end lendo o diret�rio */

	return (0);

}	/* end dir_walk */
