/*
 ****************************************************************
 *								*
 *			delenv.c				*
 *								*
 *	Remove um valor ao ambiente				*
 *								*
 *	Vers�o	2.3.0, de 01.09.89				*
 *		3.0.0, de 30.05.95				*
 *								*
 *	M�dulo: delenv						*
 *		libc/etc					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdlib.h>
#include <string.h>

/*
 ****************************************************************
 *	Retira uma vari�vel do ambiente				*
 ****************************************************************
 */
int
delenv (register const char *var)
{
	register int		size;
	register const char	**ep, *cp;

	/*
	 *	Verifica se existe um ambiente
	 */
	if (environ == (const char **)NULL)
		return (-1);

	size = strlen (var);

	/*
	 *	Verifica se a vari�vel se encontra no ambiente
	 */
	for (ep = environ; /* abaixo */; ep++)
	{
		if ((cp = *ep) == NOSTR)
			return (-1);

		if (cp[size] == '=' && strncmp (cp, var, size) == 0)
			break;
	}

	/*
	 *	Encontrou: remove
	 */
	while (ep[0] = ep[1])
		 ep++;

	return (0);

}	/* end delenv */
