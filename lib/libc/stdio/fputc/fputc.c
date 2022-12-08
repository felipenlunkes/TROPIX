/*
 ****************************************************************
 *								*
 *			fputc.c					*
 *								*
 *	Escreve o caracter c em um arquivo (funcao)		*
 *								*
 *	Vers�o	1.0.0, de 18.11.86				*
 *		3.0.0, de 09.07.95				*
 *								*
 *	M�dulo: fputc						*
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
 *	Escreve um caractere em um arquivo			*
 ****************************************************************
 */
int
fputc (int c, FILE *fp)
{
	return (putc (c, fp));

}	/* end fputc */
