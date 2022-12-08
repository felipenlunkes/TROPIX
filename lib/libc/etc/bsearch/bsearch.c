/*
 ****************************************************************
 *								*
 *			bsearch.c				*
 *								*
 *	Realiza uma busca bin�ria				*
 *								*
 *	Vers�o	2.3.0, de 05.03.90				*
 *		3.0.0, de 09.06.95				*
 *								*
 *	M�dulo: bsearch						*
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
 *	Vari�veis e defini��es globais				*
 ****************************************************************
 */
#define	EVER		;;
#define	NOTFOUND	(void *)NULL
#define	elif		else if

/*
 ****************************************************************
 *	Realiza uma busca bin�ria				*
 ****************************************************************
 */
void *
bsearch (const void *key, register const void *base, register size_t n,
	size_t size, int (*compar) (const void *, const void *))
{
	register int		i, l, u, c;
	register const void	*vp;

	/*
	 *	Algoritmo B, cap�tulo 6.2.1, Searching, de Knuth
	 */
	l = 0; u = n - 1;

	for (EVER)
	{
		if (u < l)
			return (NOTFOUND);

		i = (l + u) >> 1; vp = base + i * size;

		if   ((c = compar (key, vp)) == 0)
			return ((void *)vp);
		elif (c < 0)
			u = i - 1;
		else
			l = i + 1;

	}	/* end for (EVER) */

}	/* end bsearch */
