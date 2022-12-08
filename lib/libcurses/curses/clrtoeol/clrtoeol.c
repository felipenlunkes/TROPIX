/*
 ****************************************************************
 *								*
 *			clrtoeol.c				*
 *								*
 *	Escreve espa�os at� o final da linha ou janela		*
 *								*
 *	Vers�o	2.0.0, de 20.04.88				*
 *		3.0.0, de 08.03.95				*
 *								*
 *	M�dulo: clrtoeol					*
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
 *	Escreve espa�os at� o final da janela			*
 ****************************************************************
 */
void
wclrtobot (register WINDOW *win)
{
	register chtype	*cp, *endp;
	register int	l, c;
	register int	b;

	/*
	 *	Inicializa��es
	 */
	b = check (win->w_flags, W_BOX) ? 1: 0;
	l = win->w_curl;
	c = win->w_curc;

	/*
	 *	Escreve brancos e marca o vetor de altera��es
	 */
	while (l <= win->w_maxl - b)
	{
		cp = &win->w_text[l][c];
		endp = &win->w_text[l][win->w_maxc - b];

		while (cp <= endp)
			*cp++ = ' ';

		win->w_changed[l] = 1;

		l++; c = b;
	}

}	/* end wclrtobot */

/*
 ****************************************************************
 *	Escreve espa�os at� o final da linha corrente		*
 ****************************************************************
 */
void
wclrtoeol (register WINDOW *win)
{
	register chtype	*cp, *endp;
	register int	b;

	/*
	 *	Pontos inicial e final
	 */
	b = check (win->w_flags, W_BOX) ? 1: 0;
	cp = &win->w_text[win->w_curl][win->w_curc];
	endp = &win->w_text[win->w_curl][win->w_maxc - b];

	/*
	 *	Escreve espa�os
	 */
	while (cp <= endp)
		*cp++ = ' ';

	/*
	 *	Marca o vetor de altera��es
	 */
	win->w_changed[win->w_curl] = 1;

}	/* end wclrtoeol */
