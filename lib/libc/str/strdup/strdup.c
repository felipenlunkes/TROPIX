/*
 ****************************************************************
 *								*
 *			strdup.c				*
 *								*
 *	Copia uma cadeia					*
 *								*
 *	Vers�o	1.0.0, de 26.22.86				*
 *		3.0.0, de 12.12.97				*
 *								*
 *	M�dulo: strdup						*
 *		libc/str					*
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
 *	Copia um Cadeia						*
 ****************************************************************
 */
char *
strdup (register const char *str)
{
	register char	*cp;

	if (str == NOSTR)
		return (NOSTR);

	if ((cp = malloc (strlen (str) + 1)) != NOSTR)
		strcpy (cp, str);

	return (cp);

}	/* end strdup */
