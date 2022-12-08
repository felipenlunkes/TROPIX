/*
 ****************************************************************
 *								*
 *			t_getstate.c				*
 *								*
 *	Obt�m o estado corrente					*
 *								*
 *	Vers�o	2.3.0, de 04.11.91				*
 *		3.0.0, de 10.05.95				*
 *								*
 *	M�dulo: t_getstate					*
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
 *	Obt�m o estado corrente					*
 ****************************************************************
 */
int
t_getstate (int fd)
{
#ifdef	PC
	return (itnet (fd, I_GETSTATE));
#else
	return (ioctl (fd, I_GETSTATE));
#endif	PC

}	/* end t_getstate */
