/*
 ****************************************************************
 *								*
 *			scanw.c					*
 *								*
 *	Leitura formatada do teclado 				*
 *								*
 *	Vers�o	2.0.0, de 14.04.88				*
 *		3.0.0, de 20.03.95				*
 *								*
 *	M�dulo: scanw						*
 *		libcurses/curses				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <curses.h>

#include "../../terminfo/h/defs.h"

/*
 ******	Prot�tipos de fun��es ***********************************
 */
extern int	_doscan (FILE *, const char *, void *);

/*
 ****************************************************************
 *	Formata��o em uma janela				*
 ****************************************************************
 */
int
wscanw (WINDOW *win, const char *fmt, ...)
{
	va_list		args;
	FILE		_strbuf;
	int		r;
	char		str[256];

	va_start (args, fmt);

	wgetstr (win, str);

	_strbuf._flag = _IOREAD|_IOSTRG;
	_strbuf._ptr  = str;
	_strbuf._base = str;
	_strbuf._bend = strend (str);

	r = _doscan (&_strbuf, fmt, args);

	va_end (args);

	return (r);

}	/* end wscanw */

/*
 ****************************************************************
 *	Formata��o na janela padr�o				*
 ****************************************************************
 */
int
scanw (const char *fmt, ...)
{
	va_list		args;
	FILE		_strbuf;
	int		r;
	char		str[256];

	va_start (args, fmt);

	wgetstr (stdwin, str);

	_strbuf._flag = _IOREAD|_IOSTRG;
	_strbuf._ptr  = str;
	_strbuf._base = str;
	_strbuf._bend = strend (str);

	r = _doscan (&_strbuf, fmt, args);

	va_end (args);

	return (r);

}	/* end wscanw */
