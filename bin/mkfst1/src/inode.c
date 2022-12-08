/*
 ****************************************************************
 *								*
 *			inode.c					*
 *								*
 *	Gerencia dos INODES					*
 *								*
 *	Vers�o	4.3.0, de 05.07.02				*
 *		4.3.0, de 05.07.02				*
 *								*
 *	M�dulo: mkfst1						*
 *		Utilit�rios especiais				*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/common.h>
#include <sys/sync.h>
#include <sys/stat.h>
#include <sys/t1.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../h/mkfst1.h"

/*
 ****************************************************************
 *	Vari�veis locais					*
 ****************************************************************
 */
entry daddr_t	inode_bno;	/* No. do bloco dos INODEs */

entry T1DINO	inode_block[T1_INOinBL4];

/*
 ****************************************************************
 *	Aloca um INODE						*
 ****************************************************************
 */
T1DINO *
ialloc (void)
{
	T1DINO		*ip;

	/*
	 *	Verifica se j� tem um bloco de INODEs
	 */
	if (inode_bno == 0)
	{
		inode_bno = get_empty_block (T1_MAP_INODE_EMPTY);

		memsetl (inode_block, 0, sizeof (inode_block) / sizeof (long));

		for (ip = inode_block; ip < &inode_block[T1_INOinBL4]; ip++)
			ip->n_magic = T1_SBMAGIC;
	}

	/*
	 *	Procura um INODE vago
	 */
	for (ip = inode_block; /* abaixo */; ip++)
	{
		if (ip >= &inode_block[T1_INOinBL4])
			error ("$INODEs esgotados");

		if (ip->n_mode == 0)
			break;
	}

	sb.s_busy_ino++;

	return (ip);

}	/* end ialloc */
