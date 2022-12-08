/*
 ****************************************************************
 *								*
 *			getctlch.c				*
 *								*
 *	Obt�m caracteres de controle				*
 *								*
 *	Vers�o	2.1.0, de 14.02.89				*
 *		3.0.0, de 10.03.95				*
 *								*
 *	M�dulo: getctlch					*
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
 *	Vari�veis externas					*
 ****************************************************************
 */
extern	TERM	*_curterm;	/* Terminal correntemente em uso */

/*
 ****************************************************************
 *	Defini��es locais					*
 ****************************************************************
 */
#define	DEL	0xFF
#define	ESC	0x1B

/*
 ****************************************************************
 *	Obt�m caracteres de controle				*
 ****************************************************************
 */
int
getctlch (int ctlname)
{
	register const TERMIO	*tp;

	tp = &_curterm->t_termio;

	switch (ctlname)
	{
	    case C_INTR:
		return (tp->t_intr);

	    case C_QUIT:
		return (tp->t_quit);

	    case C_SWITCH:
		return (tp->t_swtch);

	    case C_ERASE:
		return (tp->t_erase);

	    case C_AERASE:
		return (tp->t_aerase);

	    case C_WORD:
		return (tp->t_word);

	    case C_KILL:
		return (tp->t_kill);

	    case C_RETYPE:
		return (tp->t_retype);

	    case C_EOF:
		return (tp->t_eof);

	}	/* end switch */

	return (-1);

}	/* end getctlch */
