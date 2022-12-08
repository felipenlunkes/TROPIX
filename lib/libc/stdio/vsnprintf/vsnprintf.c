/*
 ****************************************************************
 *								*
 *			vsnprintf.c				*
 *								*
 *   Converte e formata uma cadeia com lista vari�vel de args	*
 *								*
 *	Vers�o	4.2.0, de 26.09.01				*
 *		4.2.0, de 26.09.01				*
 *								*
 *	M�dulo: printf						*
 *		libc/stdio					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2001 NCE/UFRJ - tecle "man licen�a"	*
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
int	_doprnt (const char *, va_list, FILE *);

/*
 ****************************************************************
 *	Escreve na string "str"					*
 ****************************************************************
 */
int
vsnprintf (char *str, size_t size, const char *fmt, va_list args)
{
	int		n;
	FILE		_strbuf;

	_strbuf._flag = _IOWRITE|_IOSTRG;
	_strbuf._ptr = str;
	_strbuf._bend = str + size - 1;
	_strbuf._lend = 0;

	n = _doprnt (fmt, args, &_strbuf);

	_strbuf._bend++; putc ('\0', &_strbuf);

	return (_strbuf._ptr - str - 1);

}	/* end vsprintf */
