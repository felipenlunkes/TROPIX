/*
 ****************************************************************
 *								*
 *			fngets.c				*
 *								*
 *	Le uma linha de um arquivo (sem o <nl>)			*
 *								*
 *	Vers�o	1.0.0, de 17.11.86				*
 *		3.0.0, de 08.07.95				*
 *								*
 *	M�dulo: fngets						*
 *		libc/stdio					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>

/*
 ****************************************************************
 *	Le uma linha de um arquivo				*
 ****************************************************************
 */
char *
fngets (char *str, register int n, register FILE *fp)
{
	register char	*cp = str;
	register int	c = 0;

	while (--n > 0 && (c = getc (fp)) >= 0)
	{
		if (c == '\n')
			break;

		*cp++ = c;
	}

	if (cp == str && c < 0)
		return ((char *)NULL);

	*cp = '\0';

	return (str);

}	/* end fngets */
