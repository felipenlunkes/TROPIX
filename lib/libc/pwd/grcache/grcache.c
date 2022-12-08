/*
 ****************************************************************
 *								*
 *			grcache.c				*
 *								*
 *	Obten��o r�pida do nome do grupo, dado o GID		*
 *								*
 *	Vers�o	1.0.0, de 29.10.86				*
 *		3.0.0, de 07.07.95				*
 *								*
 *	M�dulo: grcache						*
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
#include <grp.h>

/*
 ****************************************************************
 *	Vari�veis e estruturas globais				*
 ****************************************************************
 */
typedef struct gidname	GIDN;

struct gidname
{
	char	c_name[16];	/* Nome da Conta */
	int	c_gid;		/* No. da Conta */
	GIDN 	*c_next;	/* Proximo da Lista */
};

static GIDN	lista;		/* Inicio da Lista */

#define	NOGIDN	(GIDN *)NULL

/*
 ****************************************************************
 *	Obten��o r�pida do nome do grupo, dado o GID		*
 ****************************************************************
 */
char *
grcache (int gid)
{
	const GROUP	*gr;
	GIDN		*ap, *up;

	for (ap = &lista, up = ap->c_next; up != NOGIDN; ap = up, up = up->c_next)
	{ 
		if (up->c_gid != gid)
			continue;

		/* Achou no cache: p�e no in�cio */

		if (ap != &lista)
			{ ap->c_next = up->c_next; up->c_next = lista.c_next; lista.c_next = up; }

		return (up->c_name);
	} 

	/*
	 *	Nao achou no cache
	 */
	if ((gr = getgrgid (gid)) == NOGROUP)
		return (NOSTR);

	if ((up = malloc (sizeof (GIDN))) == NOGIDN)
		{ fprintf (stderr, "grcache: Mem�ria esgotada\n"); return (gr->gr_name); }

	/*
	 *	Insere o elemento na lista
	 */
	strcpy (up->c_name, gr->gr_name); up->c_gid = gr->gr_gid;

	up->c_next = lista.c_next; lista.c_next = up;

	return (up->c_name);

}	/* end grcache */
