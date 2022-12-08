/*
 ****************************************************************
 *								*
 *			mem_alloc.c				*
 *								*
 *	Aloca��o dinamica de mem�ria				*
 *								*
 *	Vers�o	4.0.0, de 23.08.00				*
 *		4.0.0, de 23.08.00				*
 *								*
 *	M�dulo: MAIL						*
 *		Utilit�rios de comunica��o			*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>

/*
 ****************************************************************
 *	Defini��es e vari�veis globais				*
 ****************************************************************
 */
#define	INCR		4192	/* Tamanho Basico para aloca��o */

#define	elif	else if

#define	ROUND(x) ((x + 3) & ~3)	/* Arredondamento do tamanho */

entry void	*mem0,		/* Ponteiros para a �rea dispon�vel */
		*mem1,
		*mem2;

/*
 ****************************************************************
 *	Aloca��o de Mem�ria					*
 ****************************************************************
 */
void *
mem_alloc (int size)
{
	void		*addr, *status;

	size = ROUND (size);

	/*
	 *	Verifica se h� espa�o
	 */
	while (mem1 + size > mem2)
	{
		if   ((int)(status = sbrk (INCR)) == -1)
		{
			error (NOSTR);
		}
		elif (mem0 == NOVOID)
		{
			mem0 = mem1 = status;	/* Primeira vez */
		}
		elif (status != mem2)
		{
			error ("$mem_alloc: Recebi �rea N�O adjacente");
		}

		mem2 = status + INCR;
	}

	/*
	 *	Acerta os indicadores
	 */
	addr = mem1; mem1 += size;

	return (addr);

}	/* end mem_alloc */

/*
 ****************************************************************
 *	Devolve um trecho n�o usado de mem�ria			*
 ****************************************************************
 */
void
mem_free (void	*a)
{
	a = (void *)ROUND ((int)a);

	if (a >= mem0 && a <= mem1)
		{ mem1 = a; return; }

	error ("mem_free: Devolu��o inv�lida de mem�ria: %P\n", a);

}	/* end mem_free */
