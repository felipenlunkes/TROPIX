/*
 ****************************************************************
 *								*
 *			aux/waitpid.c				*
 *								*
 *	Simula��o provis�ria da "system call" waitpid (BSD)	*
 *								*
 *	Vers�o	1.0.0, de 27.07.97				*
 *		4.2.0, de 26.09.01				*
 *								*
 *	M�dulo: programs/Xserver				*
 *		X Windows - Servidor				*
 *		Baseado no software hom�nimo do XFree86		*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright (c) 2001 TROPIX Technologies Ltd.	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>
#include <sys/syscall.h>

#define	EVER	;;

/*
 ****************************************************************
 *	Aguarda dados em diversos descritores			*
 ****************************************************************
 */
int
waitpid (int pid, int *status, int notused)
{
	for (EVER)
	{
		if (wait (status) == pid)
			return (pid);
	}

}	/* end waitpid */
