/*
 ****************************************************************
 *								*
 *			rewind.c				*
 *								*
 *	Volta o ponteiro de posic�o ao inicio do arquivo	*
 *								*
 *	Vers�o	1.0.0, de 18.11.86				*
 *		3.0.0, de 10.07.95				*
 *								*
 *	M�dulo: rewind						*
 *		libc/stdio					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>
#include <unistd.h>

/*
 ****************************************************************
 *	Volta o ponteiro de posic�o ao inicio do arquivo	*
 ****************************************************************
 */
void
rewind (FILE *fp)
{
	fseek (fp, 0, SEEK_SET);
	clearerr (fp);

}	/* end rewind */
