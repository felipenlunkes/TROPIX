/*
 ****************************************************************
 *								*
 *			index.c					*
 *								*
 *	Velharia						*
 *								*
 *	Vers�o	1.0.0, de 28.03.98				*
 *								*
 *	M�dulo: xc/lib/aux					*
 *		X Windows - Bibliotecas				*
 *		Baseado no software hom�nimo do XFree86		*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright (c) 1998 TROPIX Technologies Ltd.	*
 * 								*
 ****************************************************************
 */

#include <string.h>

char *
index (char *str, char c)
{
	return (strchr (str, c));

}	/* end index */
