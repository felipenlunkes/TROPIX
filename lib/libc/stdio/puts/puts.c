/*
 ****************************************************************
 *								*
 *			puts.c					*
 *								*
 *	Escreve uma cadeia de caracteres na saida padr�o	*
 *								*
 *	Vers�o	1.0.0, de 18.11.86				*
 *		3.0.0, de 10.07.95				*
 *								*
 *	M�dulo: puts						*
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
 *	Escreve uma cadeia em "stdout"				*
 ****************************************************************
 */
int
puts (register const char *str)
{
	register int	c;

	while ((c = *str++) != '\0')
		putchar (c);

	putchar ('\n');

	if (ferror (stdout))
		return (EOF);

	return (0);

}	/* end puts */
