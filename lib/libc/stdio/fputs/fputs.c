/*
 ****************************************************************
 *								*
 *			fputs.c					*
 *								*
 *	Escreve uma cadeia de caracteres em um arquivo		*
 *								*
 *	Vers�o	1.0.0, de 18.11.86				*
 *		3.0.0, de 03.01.95				*
 *								*
 *	M�dulo: fputs						*
 *		libc/stdio					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>

/*
 ****************************************************************
 *	Escreve uma cadeia de caracteres			*
 ****************************************************************
 */
int
fputs (register const char *str, register FILE *fp)
{
	register int	c;

	while ((c = *str++) != '\0')
		putc (c, fp);

	if (ferror (fp))
		return (EOF);

	return (0);

}	/* end fputs */
