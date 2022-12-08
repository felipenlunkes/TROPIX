/*
 ****************************************************************
 *								*
 *			titpag.c				*
 *								*
 *	Trata "title page".					*
 *								*
 *	Vers�o	2.0.0, de 11.05.86				*
 *		3.0.0, de 07.07.97				*
 *								*
 *	Rotinas:						*
 *		titpag						*
 *								*
 *	Modulo: SROFF						*
 *		Utilitarios Basicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>
#include <stdlib.h>

#include "../h/sroff.h"
#include "../h/proto.h"

/*
 ****************************************************************
 *	Trata o comando "title page" (.tl).			*
 ****************************************************************
 */
void
titpag (void)
{
	if (linhaescrita != 0)
		trtpag (-1);

	if (pagcorr >= 1)
		pagcorr--;

	tp = TRUE;
	attampag ();

}	/* end titpag */
