/*
 ****************************************************************
 *								*
 *		hw/os-support/tropix/time.c			*
 *								*
 *	Suspende a execu��o por um tempo em micro-segundos	*
 *								*
 *	Vers�o	1.0.0, de 04.03.97				*
 *		4.2.0, de 28.09.01				*
 *								*
 *	M�dulo: xc/lib/aux					*
 *		X Windows - Bibliotecas				*
 *		Baseado no software hom�nimo do XFree86		*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2001 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include "Xos.h"

/*
 ****************************************************************
 *	Suspende a execu��o do processo				*
 ****************************************************************
 */
void
xf86usleep (int delay)
{
	usleep (delay);

}	/* end xf86usleep */

/*
 ****************************************************************
 *	Obt�m o tempo corrente					*
 ****************************************************************
 */
void
xf86getsecs(long * secs, long * usecs)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	*secs = tv.tv_sec;
	*usecs= tv.tv_usec;

	return;
}
