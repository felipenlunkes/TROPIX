/*
 ****************************************************************
 *								*
 *			delch.c					*
 *								*
 *	Remo��o de um caractere de uma janela			*
 *								*
 *	Vers�o	2.0.0, de 20.04.88				*
 *		3.0.0, de 08.03.95				*
 *								*
 *	M�dulo: delch						*
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
 *	Remove um caractere de uma janela			*
 ****************************************************************
 */
void
wdelch (register WINDOW *win)
{
	register const chtype	*source;
	register chtype		*dest, *end;

	/*
	 *	Remove o caractere: 
	 *		os caracteres � esquerda s�o deslocados
	 *		para a direita de uma posi��o.
	 */
	source = &win->w_text[win->w_curl][win->w_curc + 1];

	if (win->w_flags & W_BOX)
		end = &win->w_text[win->w_curl][win->w_maxc - 1];
	else
		end = &win->w_text[win->w_curl][win->w_maxc];

	dest = &win->w_text[win->w_curl][win->w_curc];

	while (source <= end)
		*dest++ = *source++;

	/*
	 *	A �ltima posi��o da linha corrente � preenchida com espa�o
	 */
	*end = (chtype)' ';

	/*
	 *	Marca o vetor de altera��es
	 */
	win->w_changed[win->w_curl] = 1;

}	/* end wdelch */
