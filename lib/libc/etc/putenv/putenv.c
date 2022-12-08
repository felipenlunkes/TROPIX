/*
 ****************************************************************
 *								*
 *			putenv.c				*
 *								*
 *	Modifica ou acresenta um valor ao ambiente		*
 *								*
 *	Vers�o	1.0.0, de 28.10.86				*
 *		3.0.0, de 30.05.95				*
 *								*
 *	M�dulo: putenv						*
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
 *	Vari�veis e defini��es globais				*
 ****************************************************************
 */
#undef	DEBUG

#ifdef	DEBUG
#define	ENV_SZ_INC	3	/* Incremento do tamanho do ambiente */
#else
#define	ENV_SZ_INC	50	/* Incremento do tamanho do ambiente */
#endif	DEBUG

#define	elif	else if

static int	environ_sz;	/* Tamanho atual do ambiente criado */

static const char **environ_copy; /* C�pia do "environ" para cheque */

/*
 ****************************************************************
 *	Modifica ou acrescenta uma vari�vel ao ambiente		*
 ****************************************************************
 */
int
putenv (register const char *str)
{
	register int		sz;
	register const char	**ep, *cp;

	/*
	 *	Verifica se cadeia � da forma var=valor
	 */
	if ((cp = strchr (str, '=')) == NOSTR)
		return (-1);

	sz = cp - str + 1;	/* Incorpora o "=" */

	/*
	 *	Verifica se j� existe um ambiente
	 */
	if (environ == (const char **)NULL)
	{
#ifdef	DEBUG
		printf ("Criando o primeiro ambiente\n");
#endif	DEBUG
		if ((ep = malloc ((ENV_SZ_INC + 1) * sizeof (char *))) == NOVOID)
			return (-1);

		environ_sz   = ENV_SZ_INC;
		environ_copy = environ = ep;

		*ep++ = str; *ep = NOSTR;

		return (0);
	}

	/*
	 *	Verifica se a vari�vel j� se encontra no ambiente (NOSSO ou n�o)
	 */
	for (ep = environ; *ep != NOSTR; ep++)
	{
		if (strncmp (*ep, str, sz) == 0)
			{ *ep = str; return (0); }
	}

	/*
	 *	N�O est� no ambiente - verifica se o ambiente j� � o NOSSO
	 */
	if (environ != environ_copy || environ_sz == 0)
	{
#ifdef	DEBUG
		printf ("Copiando o ambiente original\n");
#endif	DEBUG
		sz = ep - environ;	/* Espa�o original */

		if ((ep = malloc ((sz + ENV_SZ_INC + 1) * sizeof (char *))) == NOVOID)
			return (-1);

		memmove (ep, environ, sz * sizeof (char *));

		environ_sz   = sz + ENV_SZ_INC;
		environ_copy = environ = ep;

		ep += sz; *ep++ = str; *ep = NOSTR;

		return (0);
	}

	/*
	 *	N�O est� no NOSSO ambiente - verifica se tem espa�o para colocar
	 */
	if (ep >= environ + environ_sz)
	{
#ifdef	DEBUG
		printf ("Aumentando o ambiente pr�prio\n");
#endif	DEBUG
		sz = ep - environ;	/* Espa�o original */

		if ((ep = realloc (environ, (environ_sz + ENV_SZ_INC + 1) * sizeof (char *))) == NOVOID)
			return (-1);

		environ_sz  += ENV_SZ_INC;
		environ_copy = environ = ep;

		ep += sz;
	}
#ifdef	DEBUG
	else
	{
		printf ("Coube no ambiente pr�prio\n");
	}
#endif	DEBUG

	*ep++ = str; *ep = NOSTR;

	return (0);

}	/* end putenv */
