/*
 ****************************************************************
 *								*
 *			t_bind.c				*
 *								*
 *	Associa um "port" a uma comunica��o			*
 *								*
 *	Vers�o	2.3.0, de 08.08.91				*
 *		3.0.0, de 10.05.95				*
 *								*
 *	M�dulo: t_bind						*
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
 *	Associa um "port" a uma comunica��o			*
 ****************************************************************
 */
int
t_bind (int fd, const T_BIND *req, T_BIND *ret)
{
#ifdef	PC
	return (itnet (fd, I_BIND, req, ret));
#else
	return (ioctl (fd, I_BIND, &req));
#endif	PC

}	/* end t_bind */
