/*
 ****************************************************************
 *								*
 *			ttyslot.c				*
 *								*
 *	Obt�m o no. da linha do arquivo "/etc/initab"		*
 *								*
 *	Vers�o	1.0.0, de 10.09.86				*
 *		3.0.0, de 27.06.95				*
 *								*
 *	M�dulo: ttyslot						*
 *		libc/etc					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 ****************************************************************
 *	Obt�m o no. da linha do arquivo "/etc/initab"		*
 ****************************************************************
 */
int
ttyslot (const char *name)
{
	register FILE		*fp;
	register const char	*lp;
	register int 		i;
	char			line[40];	

	if ((fp = fopen ("/etc/initab", "r")) == NOFILE)
		return (-1);

	for (i = 0; fgets (line, sizeof (line), fp) != NOSTR; i++)
	{
		strfield (line,  ':'); lp =  strfield (NOSTR, ':');

		if (streq (lp, name))
			{ fclose (fp); return (i); }
	}

	fclose (fp); return (-2);

}	/* end ttyslot */
