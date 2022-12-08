/*
 ****************************************************************
 *								*
 *			getstr.c				*
 *								*
 *	Le uma linha de texto do teclado			*
 *								*
 *	Vers�o	2.0.0, de 14.04.88				*
 *		3.0.0, de 10.03.95				*
 *								*
 *	M�dulo: getstr						*
 *		libcurses/curses				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>
#include <curses.h>

#include "../../terminfo/h/defs.h"

/*
 ****************************************************************
 *	Le uma linha de texto do teclado			*
 ****************************************************************
 */
int
wgetstr (register WINDOW *win, register char *str)
{
	register int	ch;

	/*
	 *	O <nl> n�o � copiado
	 */
	while ((ch = wgetch (win)) != '\n')
	{
		if (ch == ERR || ch == EOT || ch == EOL)
			break;

		*str++ = ch;
	}

	*str = '\0';

	return ((ch == '\n') ? OK : ch);

}	/* end wgetstr */
