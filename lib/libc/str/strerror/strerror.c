/*
 ****************************************************************
 *								*
 *			strerror.c				*
 *								*
 *	Obtem uma mensagem de erro do KERNEL			*
 *								*
 *	Vers�o	1.0.0, de 30.10.86				*
 *		3.0.0, de 08.08.95				*
 *								*
 *	M�dulo: strerror					*
 *		libc/etc 					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/kcntl.h>
#include <sys/syscall.h>

#include <stdlib.h>
#include <errno.h>

/*
 ****************************************************************
 *	Obtem a mensagem de erro				*
 ****************************************************************
 */
char *
strerror (int err)
{
	static char	*cp;

	if (cp == NOSTR && (cp = malloc (80)) == NOSTR)
		return ("N�o consegui obter a mensagem de erro");

	if (kcntl (K_ERRTOSTR, err, cp) < 0)
		return ("N�o consegui obter a mensagem de erro");

	return (cp);

}	/* end strerror */
