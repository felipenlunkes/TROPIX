/*
 ****************************************************************
 *								*
 *			setmove.c				*
 *								*
 *	Atribui a fun��o de "move"				*
 *								*
 *	Vers�o	2.2.0, de 31.08.89				*
 *		3.0.0, de 20.03.95				*
 *								*
 *	M�dulo: setmove						*
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

/*
 ****************************************************************
 *	Atribui a fun��o de "move"				*
 ****************************************************************
 */
void
setmove (WINDOW *win, void (*func) ())
{
	win->w_move = func;

}	/* end setmove */
