/*
 ****************************************************************
 *								*
 *			t_getaddr.c				*
 *								*
 *	Obt�m os endere�os local e remoto			*
 *								*
 *	Vers�o	2.3.0, de 27.11.92				*
 *		3.0.0, de 10.05.95				*
 *								*
 *	M�dulo: t_getaddr					*
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
 *	Obt�m os endere�os local e remoto			*
 ****************************************************************
 */
int
t_getaddr (int fd, INADDR *addr)
{
#ifdef	PC
	return (itnet (fd, I_GETADDR, addr));
#else
	return (ioctl (fd, I_GETADDR, addr));
#endif	PC

}	/* end t_getaddr */
