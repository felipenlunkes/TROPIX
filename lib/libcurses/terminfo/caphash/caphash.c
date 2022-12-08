/*
 ****************************************************************
 *								*
 *			capphash.c				*
 *								*
 *	Acesso �s Capacidades de Terminfo			*
 *								*
 *	Vers�o	1.0.0, de 27.04.87				*
 *		3.0.0, de 21.03.95				*
 *								*
 *	Modulo: caphash						*
 *		libcurses/terminfo				*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <sys/types.h>

#include <stdio.h>
#include <string.h>
#include <terminfo.h>

#include "hash.h"

/*
 ****************************************************************
 *	Vari�veis globais					*
 ****************************************************************
 */
extern CAPHASH	cap_hashtb[];		/* A Tabela Hash */

#ifdef	DEBUG
extern int	dflag;			/* Switch de depura��o */
entry int	ncolision;		/* No. de colis�es */
#endif	DEBUG

/*
 ****************************************************************
 *	Fun��o de "hash"					*
 ****************************************************************
 */
CAPHASH *
caphash (const char *name)
{
	CAPHASH		*hp;
	int		incr;

	hp = &cap_hashtb[strhash (name, strlen (name), CAPHASHSZ)];

	incr = MCAPHASHSZ;

	do
	{
		/*
		 *	Verifica se a Entrada est� vazia
		 */
		if (hp->h_class == C_UNDEF)
			return (hp);

		/*
		 *	A entrada n�o est� vazia; verifica se
		 *	� o ID procurado
		 */
		if (streq (hp->h_id, name))
			return (hp);

		/*
		 *	Houve colis�o: calcula a proxima tentativa
		 */
#ifdef	DEBUG
		if (dflag)
		{
			fprintf (stderr,
			"Capacidades: Colis�o na cap_hashtb entre %-14s e %-14s\n",
			hp->h_id, name);
		}

		ncolision++;
#endif	DEBUG

		if ((hp += incr) >= &cap_hashtb[CAPHASHSZ])
			hp -= CAPHASHSZ;

	}
	while (incr-- > 0);

	/*
	 *	Este trecho n�o deve ser alcancado.
	 */
	fprintf (stderr, "Overflow da Hashtb\n");

	return ((CAPHASH *)NULL);

}	/* end caphash */

#ifdef	PRINT_TABLE
/*
 ****************************************************************
 *	Imprime Tabela de Simbolos.				*
 ****************************************************************
 */
entry void
print_table ()
{
	CAPHASH		*tp;
	static char	id[IDSZ];

	fputs ("\f\n\t Tabela de Capacidades: \n", stdout);
	fputs ("\t ====== == ===========\n\n", stdout);

	fputs ("\t Nome \t Tipo \t\t Ordem \t Posi��o \n", stdout);
	fputs ("\t ---- \t ---- \t\t ----- \t ------- \n", stdout);

	for (tp = cap_hashtb ; tp < &cap_hashtb[CAPHASHSZ] ; tp++)
	{
		if (tp->h_class == C_UNDEF)
			continue;

		idcpy (id, tp->h_id);
		id[IDSZ] = '\0';

		if (tp->h_class == C_BOOLEAN)
			printf ("'%-14s'  Boolean\t  %4d\t  %4d\n",
			id, tp->h_order, tp - cap_hashtb);

		if (tp->h_class == C_NUMBER)
			printf ("'%-14s'  Number\t  %4d\t  %4d\n",
			id, tp->h_order, tp - cap_hashtb);

		if (tp->h_class == C_STRING)
			printf ("'%-14s'  String\t  %4d\t  %4d\n",
			id, tp->h_order, tp - cap_hashtb);
	}

}	/* end print_table */
#endif	PRINT_TABLE
