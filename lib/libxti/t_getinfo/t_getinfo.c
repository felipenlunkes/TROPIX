/*
 ****************************************************************
 *								*
 *			t_getinfo.c				*
 *								*
 *	Obt�m informa��es sobre o protocolo 			*
 *								*
 *	Vers�o	2.3.0, de 04.11.91				*
 *		3.0.0, de 10.05.95				*
 *								*
 *	M�dulo: t_getinfo					*
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
 *	Obt�m informa��es sobre o protocolo 			*
 ****************************************************************
 */
int
t_getinfo (int fd, T_INFO *info)
{
#ifdef	PC
	return (itnet (fd, I_GETINFO, info));
#else
	return (ioctl (fd, I_GETINFO, info));
#endif	PC

}	/* end t_getinfo */
