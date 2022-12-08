/*
 ****************************************************************
 *								*
 *			malloc.c				*
 *								*
 *	Aloca��o de mem�ria					*
 *								*
 *	Vers�o	4.0.0, de 26.07.01				*
 *		4.0.0, de 26.07.01				*
 *								*
 *	M�dulo: Boot2						*
 *		N�CLEO do TROPIX para PC			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2001 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#include <common.h>

#include "../h/common.h"
#include "../h/extern.h"

/*
 ****************************************************************
 *	Defini��es Globais					*
 ****************************************************************
 */
entry void	*malloc_mem0;

/*
 ****************************************************************
 *	Aloca��o de pequenas �reas de mem�ria			*
 ****************************************************************
 */
void *
malloc_byte (int size)
{
	void		*mem;

	/*
	 *	Arredonda
	 */
	size += 3; size &= ~3;

	/*
	 *	Subtrai o tamanho pedido
	 */
	mem = malloc_mem0;

	malloc_mem0 += size;

	return (mem);

}	/* end malloc_byte */

/*
 ****************************************************************
 *	Libera��o de uma �rea					*
 ****************************************************************
 */
void
free_byte (void *area)
{
}	/* end free_byte */
