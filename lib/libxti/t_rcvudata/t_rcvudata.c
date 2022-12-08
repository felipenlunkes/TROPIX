/*
 ****************************************************************
 *								*
 *			t_rcvudata.c				*
 *								*
 *	Recebe um datagrama do usu�rio (UDP)			*
 *								*
 *	Vers�o	2.3.0, de 10.08.91				*
 *		3.0.0, de 10.05.95				*
 *								*
 *	M�dulo: t_rcvudata					*
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
 *	Recebe um datagrama do usu�rio (UDP)			*
 ****************************************************************
 */
int
t_rcvudata (int fd, T_UNITDATA *unitdata, int *flags)
{
#ifdef	PC
	return (itnet (fd, I_RCVUDATA, unitdata, flags));
#else
	return (ioctl (fd, I_RCVUDATA, &unitdata));
#endif	PC

}	/* end t_rcvudata */
