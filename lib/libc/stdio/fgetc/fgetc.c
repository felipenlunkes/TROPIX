/*
 ****************************************************************
 *								*
 *			fgetc.c					*
 *								*
 *	Le de um arquivo de entrada (fun��o)			*
 *								*
 *	Vers�o	1.0.0, de 18.11.86				*
 *		3.0.0, de 08.07.95				*
 *								*
 *	M�dulo: fgetc						*
 *		libc/stdio					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include	<stdio.h>

/*
 ****************************************************************
 *	L� um caractere de um arquivo				*
 ****************************************************************
 */
int
fgetc (FILE *fp)
{
	return (getc (fp));

}	/* end fgetc   */
