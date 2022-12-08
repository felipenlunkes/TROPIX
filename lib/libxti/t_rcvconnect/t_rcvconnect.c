/*
 ****************************************************************
 *								*
 *			t_rcvconnect.c				*
 *								*
 *	Recebe a confirma��o de um pedido de conex�o		*
 *								*
 *	Vers�o	2.3.0, de 04.11.91				*
 *		3.0.0, de 10.05.95				*
 *								*
 *	M�dulo: t_rcvconnect					*
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
 *	Recebe a confirma��o de um pedido de conex�o		*
 ****************************************************************
 */
int
t_rcvconnect (int fd, T_CALL *call)
{
#ifdef	PC
	return (itnet (fd, I_RCVCONNECT, call));
#else
	return (ioctl (fd, I_RCVCONNECT, call));
#endif	PC

}	/* end t_rcvconnect */
