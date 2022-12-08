/*
 ****************************************************************
 *								*
 *			sprintf.c				*
 *								*
 *	Converte e formata uma cadeia				*
 *								*
 *	Vers�o	1.0.0, de 14.11.86				*
 *		3.0.0, de 10.07.95				*
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
sprintf (char *str, const char *fmt, ...)
{
	FILE		_strbuf;
	int		n;

	_strbuf._flag = _IOWRITE|_IOSTRG;
	_strbuf._ptr  = str;
	_strbuf._bend = _EOMEM;

	n = _doprnt (fmt, va_first (fmt), &_strbuf);

	putc ('\0', &_strbuf);

	return (n);

}	/* end sprintf */
