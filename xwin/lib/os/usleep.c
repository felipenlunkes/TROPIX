/*
 ****************************************************************
 *								*
 *			usleep.c				*
 *								*
 *	Suspende a execu��o por um tempo em micro-segundos	*
 *								*
 *	Vers�o	1.0.0, de 04.03.97				*
 *		4.0.0, de 06.07.00				*
 *								*
 *	M�dulo: xc/lib/aux					*
 *		X Windows - Bibliotecas				*
 *		Baseado no software hom�nimo do XFree86		*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/common.h>
#include <sys/scb.h>
#include <sys/syscall.h>

#include <stdlib.h>


/*
 ******	Vari�veis globais ***************************************
 */
entry long	DELAY_value;	/* Constante para 1 micro segundo */
extern void	DELAY (long);	/* Fun��o para esperar */

/*
 ****************************************************************
 *	Suspende a execu��o do processo				*
 ****************************************************************
 */
void
usleep (int delay)
{
	if (DELAY_value == 0)
	{
		SCB	*sp;

		sp = alloca (sizeof (SCB));

		getscb (sp);

		DELAY_value = sp->y_DELAY_value;
	}

	DELAY (delay);

}	/* end usleep */
