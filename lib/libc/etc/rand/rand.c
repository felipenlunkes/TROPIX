/*
 ****************************************************************
 *								*
 *			rand.c					*
 *								*
 *	Fun��o simples para a gera��o de nos. aleatorios	*
 *								*
 *	Vers�o	1.0.0, de 15.10.86				*
 *		3.0.0, de 19.06.95				*
 *								*
 *	M�dulo: rand						*
 *		libc/etc					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdlib.h>

/*
 ****************************************************************
 *	Defini��es globais					*
 ****************************************************************
 */
static long	seed = 1;

/*
 ****************************************************************
 *	Rotina para inicializa��o do gerador			*
 ****************************************************************
 */
void
srand (long a)
{
	seed = a;

}	/* end srand */

/*
 ****************************************************************
 *	Rotina para gera��o dos nos. aleatorios			*
 ****************************************************************
 */
long
rand (void)
{
	seed = getrand (seed); return (seed & 0x7FFFFFFF);

}	/* end rand */
