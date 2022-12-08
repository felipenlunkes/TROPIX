/*
 ****************************************************************
 *								*
 *			str.c					*
 *								*
 *	Manipula��o de cadeias de caracteres			*
 *								*
 *	Vers�o	2.0.0, de 17.08.88				*
 *		3.0.0, de 30.04.97				*
 *								*
 *	M�dulo: EX/VI						*
 *		Editores de texto				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <ctype.h>

#include "../h/global.h"
#include "../h/extern.h"
#include "../h/proto.h"

/*
 ****************************************************************
 *	Coluna ocupada pelo caracter *(linha + n)		*
 ****************************************************************
 */
int	
str_coln (int n, char *linha)
{
	int		i;
	char		*pf;

	i = 0;

	for (pf = linha + n; *linha && linha <= pf; ++linha)
	{
		if (isgraph (*linha) || *linha == ' ')
			i++;
		else
			i = (*linha == '\t') ? (i & ~7) + 8 : i + 2;
	}

	return ((*pf) ? i - 1 : i);

}	/* end str_coln  */

/*
 ************************************************************************
 *	Ordem do caracter cuja coluna � mais pr�xima de desejo		*
 ************************************************************************
 */
int
str_try (int desejo /* coluna */, char *linha)
{
	int		col;
	char		*pch;

	col = 0; desejo++;

	for (pch = linha; *pch; ++pch)
	{
		if (isgraph(*pch) || *pch == ' ')
			col++;
		else
			col = (*pch == '\t') ? (col & ~7) + 8 : col + 2;

		if (col >= desejo)
			break;
	}

	if (col > desejo && pch > linha)
		return (pch - linha -1);
	else
		return (pch - linha);

}	/* end str_try */

/*
 ****************************************************************
 *	Primeiro caracter n�o branco nlinhas ap�s base		*
 ****************************************************************
 */
int	
str_nonwhite (char *linha)
{
	char		*l;

	for (l = linha; *l && isspace(*l); ++l)
		/* vazio */;

	return (l - linha);

}	/* end str_nonwhite */
