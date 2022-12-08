/*
 ****************************************************************
 *								*
 *			data.c					*
 *								*
 *	Defini��o das vari�veis globais de "curses"		*
 *								*
 *	Vers�o	2.0.0, de 15.03.88				*
 *		3.0.0, de 02.11.95				*
 *								*
 *	M�dulo: data						*
 *		libcurses/curses				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>

#include <termio.h>
#include <stdio.h>
#include <curses.h>
#include <terminfo.h>

#include "../../terminfo/h/defs.h"

#include "../h/term.h"
#include "../h/acento.h"
#include "../h/local.h"

/*
 ****************************************************************
 *	Dimens�es do terminal					*
 ****************************************************************
 */
entry int	LINES = 0;
entry int	COLS = 0;

/*
 ****************************************************************
 *	Janela padr�o						*
 ****************************************************************
 */
entry WINDOW	*stdwin = NOWINDOW;

/*
 ****************************************************************
 *	Caracteres semi-gr�ficos				*
 ****************************************************************
 */
entry chtype	ACS_ULCORNER = 0,
		ACS_LLCORNER = 0,
		ACS_URCORNER = 0,
		ACS_LRCORNER = 0,
		ACS_RTEE = 0,
		ACS_LTEE = 0,
		ACS_BTEE = 0,
		ACS_TTEE = 0,
		ACS_HLINE = 0,
		ACS_VLINE = 0,
		ACS_PLUS = 0,
		ACS_S1 = 0,
		ACS_S9 = 0,
		ACS_DIAMOND = 0,
		ACS_CKBOARD = 0,
		ACS_DEGREE = 0,
		ACS_PLMINUS = 0,
		ACS_BULLET = 0,
		ACS_LARROW = 0,
		ACS_RARROW = 0,
		ACS_DARROW = 0,
		ACS_UARROW = 0,
		ACS_BOARD = 0,
		ACS_LANTERN = 0,
		ACS_BLOCK = 0;

/*
 ****************************************************************
 *	Lista de terminais (interna)				*
 ****************************************************************
 */
entry TERM	*_firstterm = NOTERM;	/* Terminal 0 */
entry TERM	*_curterm = NOTERM;	/* Terminal Corrente */

/*
 ****************************************************************
 *	Pool de janelas	(interno)				*
 ****************************************************************
 */
entry WINDOW	*_windows;

/*
 ****************************************************************
 *	Tabela de acentos (interno)				*
 ****************************************************************
 */
entry const ACENTO	Acentos[] =
{
	OR ('~', 'A'),	0xC3,	/* � */
	OR ('~', 'a'),	0xE3,	/* � */
	OR ('~', 'O'),	0xD5,	/* � */
	OR ('~', 'o'),	0xF5,	/* � */
	OR (',', 'C'),	0xC7,	/* � */
	OR (',', 'c'),	0xE7,	/* � */
	OR (',', 'z'),	0xDF,	/* � */
	OR ('\'','A'),	0xC1,	/* � */
	OR ('\'','a'),	0xE1,	/* � */
	OR ('\'','E'),	0xC9,	/* � */
	OR ('\'','e'),	0xE9,	/* � */
	OR ('\'','I'),	0xCD,	/* � */
	OR ('\'','i'),	0xED,	/* � */
	OR ('\'','O'),	0xD3,	/* � */
	OR ('\'','o'),	0xF3,	/* � */
	OR ('\'','U'),	0xDA,	/* � */
	OR ('\'','u'),	0xFA,	/* � */
#if (0)	/*******************************************************/
	OR ('\'','C'),	0xC7,	/* � */
	OR ('\'','c'),	0xE7,	/* � */
	OR ('\'','z'),	0xDF,	/* � */
#endif	/*******************************************************/
	OR ('^', 'A'),	0xC2,	/* � */
	OR ('^', 'a'),	0xE2,	/* � */
	OR ('^', 'E'),	0xCA,	/* � */
	OR ('^', 'e'),	0xEA,	/* � */
	OR ('^', 'I'),	0xCE,	/* � */
	OR ('^', 'i'),	0xEE,	/* � */
	OR ('^', 'O'),	0xD4,	/* � */
	OR ('^', 'o'),	0xF4,	/* � */
	OR ('^', 'U'),	0xDB,	/* � */
	OR ('^', 'u'),	0xFB,	/* � */
	OR ('`', 'A'),	0xC0,	/* � */
	OR ('`', 'a'),	0xE0,	/* � */
	OR ('`', 'E'),	0xC8,	/* � */
	OR ('`', 'e'),	0xE8,	/* � */
	OR ('`', 'I'),	0xCC,	/* � */
	OR ('`', 'i'),	0xEC,	/* � */
	OR ('`', 'O'),	0xD2,	/* � */
	OR ('`', 'o'),	0xF2,	/* � */
	OR ('`', 'U'),	0xD9,	/* � */
	OR ('`', 'u'),	0xF9,	/* � */
	OR (':', 'A'),	0xC4,	/* � */
	OR (':', 'a'),	0xE4,	/* � */
	OR (':', 'E'),	0xCB,	/* � */
	OR (':', 'e'),	0xEB,	/* � */
	OR (':', 'I'),	0xCF,	/* � */
	OR (':', 'i'),	0xEF,	/* � */
	OR (':', 'O'),	0xD6,	/* � */
	OR (':', 'o'),	0xF6,	/* � */
	OR (':', 'U'),	0xDC,	/* � */
	OR (':', 'u'),	0xFC,	/* � */
#if (0)	/*******************************************************/
	OR ('=', 'a'),	0xAA,	/* � */
	OR ('=', 'o'),	0xBA,	/* � */
#endif	/*******************************************************/
	0,		0
};
