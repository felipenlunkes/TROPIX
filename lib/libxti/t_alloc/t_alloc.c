/*
 ****************************************************************
 *								*
 *			t_alloc.c				*
 *								*
 *	Aloca mem�ria para estruturas (N�O IMPLEMENTADA)	*
 *								*
 *	Vers�o	2.3.0, de 12.11.91				*
 *		3.0.0, de 10.05.95				*
 *								*
 *	M�dulo: t_alloc						*
 *		libxti 						*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 * 		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/common.h>
#include <sys/sync.h>
#include <sys/itnet.h>
#include <sys/syscall.h>

#include <errno.h>
#include <xti.h>

/*
 ****************************************************************
 *	Aloca mem�ria para estruturas (N�O IMPLEMENTADA)	*
 ****************************************************************
 */
void *
t_alloc (int fd, T_ALLOC_ENUM struct_type, int fields)
{
	errno = TNOTSUPPORT;

	return ((void *)NULL);

}	/* end t_alloc */
