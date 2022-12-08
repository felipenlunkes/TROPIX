/*
 ****************************************************************
 *								*
 *			t_sync.c				*
 *								*
 *	Sincroniza a biblioteca de transporte			*
 *								*
 *	Vers�o	2.3.0, de 04.11.91				*
 *		3.0.0, de 10.05.95				*
 *								*
 *	M�dulo: t_sync						*
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

#include <xti.h>

/*
 ****************************************************************
 *	Sincroniza a biblioteca de transporte			*
 ****************************************************************
 */
int
t_sync (int fd)
{
#ifdef	PC
	return (itnet (fd, I_SYNC));
#else
	return (ioctl (fd, I_SYNC));
#endif	PC

}	/* end t_sync */
