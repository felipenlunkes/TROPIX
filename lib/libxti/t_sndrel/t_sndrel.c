/*
 ****************************************************************
 *								*
 *			t_sndrel.c				*
 *								*
 *	Inicia a desconex�o TCP					*
 *								*
 *	Vers�o	2.3.0, de 29.08.91				*
 *		3.0.0, de 10.05.95				*
 *								*
 *	M�dulo: t_sndrel					*
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
 *	Inicia a desconex�o TCP					*
 ****************************************************************
 */
int
t_sndrel (int fd)
{
#ifdef	PC
	return (itnet (fd, I_SNDREL));
#else
	return (ioctl (fd, I_SNDREL));
#endif	PC

}	/* end t_sndrel */
