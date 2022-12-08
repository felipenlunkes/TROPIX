/*
 ****************************************************************
 *								*
 *			qsort.c					*
 *								*
 *	Fun��o de ordena��o usando "quicksort"			*
 *								*
 *	Vers�o	1.0.0, de 22.09.86				*
 *		3.0.0, de 23.06.95				*
 *								*
 *	M�dulo: qsort						*
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
 *	Defini��es e vari�veis globais				*
 ****************************************************************
 */
#define elif	else if

static int 	global_size;	/* Tamanho do registro */

static int	(*global_comp) (const void *, const void *);

/*
 ******	Prot�tipos de fun��es ***********************************
 */
static void	sort (void *, void *);
static void	troca (char *, char *);

/*
 ****************************************************************
 *	Fun��o Principal					*
 ****************************************************************
 */
void
qsort (void *base, size_t nel, size_t size, int (*comp) (const void *, const void *))
{
	if (nel < 2)
		return;

	global_size = size;
	global_comp = comp;

	sort (base, base + size * (nel - 1));

}	/* end qsort */

/*
 ****************************************************************
 *	Fun��o recursiva usando o algoritmo "quicksort"		*
 ****************************************************************
 */
static void
sort (void *e, void *d)
{
	register void 	*i, *j;
	register void	*p;
	register int	size, (*comp) (const void *, const void *);

	comp = global_comp;
	size = global_size;

	i = e;
	j = d;
	p = ((((d - e) / size) >> 1) * size  + e);

	do
	{
		while ((*comp) (i, p) < 0)
			i += size;

		while ((*comp) (p, j) < 0)
			j -= size;

		if (i <= j)
		{
			if (i < j)
			{
				troca (i, j);

				if   (p == i)
					p = j;
				elif (p == j)
					p = i;
			}

			i += size;
			j -= size;
		}

	}
	while (i <= j);

	/*
	 *	Mantem a stack com tamanho m�nimo
	 */
	if (j - e < d - i)
	{
		/*
		 *	Examina se a recus�o vale a pena
		 */
		if (e == j - size)
		{
			/*
			 *	Se a diferenca � 1, compara logo
			 */
			if ((*comp) (e, j) > 0)
				troca (e, j);
		}
		else
		{
			/*
			 *	Caso contrario chama recursivamente
			 */	
			if (e < j)
				sort (e, j);
		}

		if (i == d - size)
		{
			if ((*comp) (i, d) > 0)
				troca (i, d);
		}
		else
		{
			if (i < d)
				sort (i, d);
		}
	}
	else
	{
		if (i == d - size)
		{
			if ((*comp) (i, d) > 0)
				troca (i, d);
		}
		else
		{
			if (i < d)
				sort (i, d);
		}

		if (e == j - size)
		{
			if ((*comp) (e, j) > 0)
				troca (e, j);
		}
		else
		{
			if (e < j)
				sort (e, j);
		}
	}

}	/* end sort */

/*
 ****************************************************************
 *	Fun��o para intercambiar dois registros			*
 ****************************************************************
 */
static void
troca (register char *i, register char *j)
{
	register int	k, size;
	register char	temp;

	k = 0; size = global_size;

	while (k++ < size)
	{
		temp  = *i;
		*i++  = *j;
		*j++  = temp;
	}

}	/* end troca */
