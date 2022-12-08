/*
 ****************************************************************
 *								*
 *			move.c					*
 *								*
 *	Altera a posi��o corrente de uma janela			*
 *								*
 *	Vers�o	2.0.0, de 22.03.88				*
 *		3.0.0, de 10.03.95				*
 *								*
 *	M�dulo: move						*
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
 *	Altera a posi��o corrente de uma janela			*
 ****************************************************************
 */
int
wmove (register WINDOW *win, register int l, register int c)
{
	register int	b;

	/*
	 *	Verifica consist�ncia dos argumentos
	 */
	b = check (win->w_flags, W_BOX) ? 1 : 0;

	if (l < 0 || l > win->w_maxl - b)
		return (ERR);

	if (c < 0 || c > win->w_maxc - b)
		return (ERR);

	/*
	 *	Se esta janela tem contorno, ele � respeitado
	 */
	if (check (win->w_flags, W_BOX))
	{
		if   (l == 0)
			l++;
		elif (l == win->w_maxl)
			l--;

		if   (c == 0)
			c++;
		elif (c == win->w_maxc)
			c--;
	}

	win->w_curl = l;
	win->w_curc = c;

	return (OK);

}	/* end wmove */
