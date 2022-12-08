/*
 ****************************************************************
 *								*
 *			perror.c				*
 *								*
 *	Imprime uma mensagem de erro do KERNEL			*
 *								*
 *	Vers�o	1.0.0, de 29.10.86				*
 *		3.0.0, de 23.06.95				*
 *								*
 *	M�dulo: libc/etc					*
 *		Biblioteca padrao				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/syscall.h>
#include <sys/kcntl.h>

#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
 ****************************************************************
 *	Vari�veis e defini��es globais				*
 ****************************************************************
 */
#define	elif	else if

/*
 ****************************************************************
 *	Imprime a mensagem de �rro				*
 ****************************************************************
 */
void
perror (const char *pgname)
{
	static char	*cp;
	register int 	n;

	if   (cp == NOSTR && (cp = malloc (80)) == NOSTR)
		cp = "N�o consegui obter a mensagem de erro";
	elif (kcntl (K_ERRTOSTR, errno, cp) < 0)
		cp = "N�o consegui obter a mensagem de erro";

	if (pgname != NOSTR && (n = strlen (pgname)) > 0)
	{
		write (2, pgname, n);
		write (2, ": ", 2);
	}

	write (2, cp, strlen (cp));
	write (2, "\n", 1);

}	/* end perror */
