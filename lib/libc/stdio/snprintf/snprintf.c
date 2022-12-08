/*
 ****************************************************************
 *								*
 *			snprintf.c				*
 *								*
 *	Converte e formata uma cadeia				*
 *								*
 *	Vers�o	3.2.3, de 28.10.99				*
 *		3.2.3, de 28.10.99				*
 *								*
 *	M�dulo: printf						*
 *		libc/stdio					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdarg.h>
#include <stdio.h>

/*
 ****************************************************************
 *	Vari�veis e defini��es globais				*
 ****************************************************************
 */
#define	_EOMEM	(char *)EOF

/*
 ******	Prot�tipos de fun��es ***********************************
 */
int	_doprnt (const char *, const char *, FILE *);

/*
 ****************************************************************
 *	Escreve na string "str"					*
 ****************************************************************
 */
int
snprintf (char *str, size_t size, const char *fmt, ...)
{
	FILE		_strbuf;

	_strbuf._flag = _IOWRITE|_IOSTRG;
	_strbuf._ptr  = str;
	_strbuf._bend = str + size - 1;
	_strbuf._lend = 0;

	_doprnt (fmt, va_first (fmt), &_strbuf);

	_strbuf._bend++; putc ('\0', &_strbuf);

	return (_strbuf._ptr - str - 1);

}	/* end snprintf */
