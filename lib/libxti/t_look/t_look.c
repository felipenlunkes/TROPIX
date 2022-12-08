/*
 ****************************************************************
 *								*
 *			t_look.c				*
 *								*
 *	Obt�m os eventos ocorridos				*
 *								*
 *	Vers�o	2.3.0, de 30.09.91				*
 *		3.0.0, de 10.05.95				*
 *								*
 *	M�dulo: t_look						*
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
 *	Obt�m os eventos ocorridos				*
 ****************************************************************
 */
int
t_look (int fd)
{
#ifdef	PC
	return (itnet (fd, I_LOOK));
#else
	return (ioctl (fd, I_LOOK));
#endif	PC

}	/* end t_look */
