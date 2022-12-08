/*
 ****************************************************************
 *								*
 *			statetostr.c				*
 *								*
 *	Devolve o nome de um estado				*
 *								*
 *	Vers�o	1.0.0, de 29.05.97				*
 *		1.0.1, de 28.03.98				*
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

#include <xti.h>

static char	*stname[] =
{
	"T_UNINIT",	/* N�o inicializado */
	"T_UNBND",	/* "unbound" */
	"T_IDLE",	/* Inerte */
	"T_OUTCON",	/* Enviando pedido de conex�o */
	"T_INCON",	/* Recebendo pedido de conex�o */
	"T_DATAXFER",	/* Transferindo dados */
	"T_OUTREL",	/* Enviando pedido de desconex�o */
	"T_INREL"	/* Recebendo pedido de desconex�o */
};

char *
statetostr (T_STATE state)
{
	if (state < T_UNINIT || state > T_INREL)
		return ("ESTADO INV�LIDO");

	return (stname[state]);

}	/* end statetostr */
