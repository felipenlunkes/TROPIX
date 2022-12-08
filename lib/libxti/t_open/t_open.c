/*
 ****************************************************************
 *								*
 *			t_open.c				*
 *								*
 *	Abre um meio de comunica��o internet			*
 *								*
 *	Vers�o	2.3.0, de 08.08.91				*
 *		3.0.0, de 10.05.95				*
 *								*
 *	M�dulo: t_open						*
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
#include <sys/syscall.h>
#include <sys/itnet.h>

#include <stat.h>
#include <xti.h>

/*
 ****************************************************************
 *	Abre um meio de comunica��o internet			*
 ****************************************************************
 */
int
t_open (const char *dev_nm, int oflag, T_INFO *ip)
{
	int		fd;

	if ((fd = open (dev_nm, oflag)) < 0)
		return (-1);

	if (ip != (T_INFO *)NULL && t_getinfo (fd, ip) < 0)
		return (-1);

	return (fd);

}	/* end t_open */
