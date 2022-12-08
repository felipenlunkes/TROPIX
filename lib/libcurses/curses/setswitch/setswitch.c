/*
 ****************************************************************
 *								*
 *			setswitch.c				*
 *								*
 *	Atribui a fun��o de "switch"				*
 *								*
 *	Vers�o	2.0.0, de 17.08.88				*
 *		3.0.0, de 20.03.95				*
 *								*
 *	M�dulo: setswitch					*
 *		libcurses/curses				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>

#include <stdio.h>
#include <termio.h>
#include <curses.h>
#include <terminfo.h>

#include "../../terminfo/h/defs.h"

#include "../h/term.h"

/*
 ****************************************************************
 *	Atribui a fun��o de "switch"				*
 ****************************************************************
 */
void
setswitch (void (*func) (int, ...))
{
	_curterm->t_switch = func;

}	/* end setswitch */
