/*
 ****************************************************************
 *								*
 *			pwcache.c				*
 *								*
 *	Obten��o r�pida do nome do usu�rio, dado o UID		*
 *								*
 *	Vers�o	1.0.0, de 07.10.86				*
 *		3.0.0, de 07.07.95				*
 *								*
 *	M�dulo: pwcache						*
 *		libc/pwd					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>

/*
 ****************************************************************
 *	Vari�veis e estruturas globais				*
 ****************************************************************
 */
typedef struct uidname	UIDN;

struct uidname
{
	char	c_name[16];		/* Nome da Conta */
	int	c_uid;		/* No. da Conta */
	UIDN 	*c_next;	/* Proximo da Lista */
};

static UIDN	lista;		/* Inicio da Lista */

#define	NOUIDN	(UIDN *)NULL

/*
 ****************************************************************
 *	Obten��o r�pida do nome do usu�rio, dado o UID		*
 ****************************************************************
 */
char *
pwcache (int uid)
{
	const PASSWD	*pw;
	UIDN		*up, *ap;

	for (ap = &lista, up = ap->c_next; up != NOUIDN; ap = up, up = up->c_next)
	{ 
		if (up->c_uid != uid)
			continue;

		/* Achou no cache: p�e no in�cio */

		if (ap != &lista)
			{ ap->c_next = up->c_next; up->c_next = lista.c_next; lista.c_next = up; }

		return (up->c_name);
	} 

	/*
	 *	N�o achou no cache
	 */
	if ((pw = getpwuid (uid)) == NOPASSWD)
		return (NOSTR);

	if ((up = malloc (sizeof (UIDN))) == NOUIDN)
		{ fprintf (stderr, "pwcache: Mem�ria esgotada\n"); return (pw->pw_name); }

	/*
	 *	Insere o elemento na lista
	 */
	strcpy (up->c_name, pw->pw_name); up->c_uid = pw->pw_uid;

	up->c_next = lista.c_next; lista.c_next = up;

	return (up->c_name);

}	/* end pwcache */
