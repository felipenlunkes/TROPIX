/*
 ****************************************************************
 *								*
 *			tmpfile.c				*
 *								*
 *	Cria um arquivo tempor�rio				*
 *								*
 *	Vers�o	2.3.0, de 03.03.90				*
 *		3.0.0, de 26.06.95				*
 *								*
 *	M�dulo: tmpfile						*
 *		libc/etc					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/syscall.h>

#include <stdio.h>

/*
 ****************************************************************
 *	Cria um arquivo tempor�rio				*
 ****************************************************************
 */
FILE *
tmpfile (void)
{
	FILE		*fp;
	const char	*filenm;

	filenm = tmpnam (NOSTR);

	if ((fp = fopen (filenm, "w+")) == NOFILE)
		return (NOFILE);

	unlink (filenm);

	return (fp);

}	/* end tmpfile */
