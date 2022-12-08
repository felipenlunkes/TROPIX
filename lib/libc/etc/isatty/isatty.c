/*
 ****************************************************************
 *								*
 *			isatty.c				*
 *								*
 *	Verifica se o arquivo � um terminal			*
 *								*
 *	Vers�o	1.0.0, de 05.09.86				*
 *		3.0.0, de 19.12.94				*
 *								*
 *	M�dulo:	isatty 						*
 *		libc/etc					*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>

#include <stdlib.h>
#include <termio.h>

/*
 ****************************************************************
 *	Verifica se � um terminal				*
 ****************************************************************
 */
int
isatty (int fd)
{
	if (ioctl (fd, TCISATTY, 0) < 0)
		return (0);

	return (1);

}	/* isatty */
