/*
 ****************************************************************
 *								*
 *			sub.c					*
 *								*
 *	Substitui��es						*
 *								*
 *	Vers�o	2.0.0, de 17.08.88				*
 *		3.0.0, de 23.03.95				*
 *								*
 *	M�dulo: EX/VI						*
 *		Editores de texto				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>
#include <stdlib.h>

#include "../h/global.h"
#include "../h/text.h"
#include "../h/commands.h"
#include "../h/extern.h"
#include "../h/proto.h"

/*
 ****************************************************************
 *	Compila��o de uma substitui��o				*
 ****************************************************************
 */
void
sub_compile (const char *string /* fonte */, REPL *repl /* objeto */)
{
	const char	*cp;	/* Character pointer */
	char		*tp;	/* Text pointer */
	char		**sp;	/* Specials pointer */

	sp = repl->r_specials; tp = repl->r_text;

	for (cp = string; *cp; cp++)
	{
		switch (*cp)
		{
			/*
			 *	Comandos Especiais
			 */
		    case '&':
		    case '\n':
			*tp++ = '\0';
			*sp++ = tp;
			*tp++ = *cp;
			break;

		    case '\\':
			if (cp[1] != '\0')
				cp++;
		    default:
			*tp++ = *cp;
			break;
		}

	}	/* end (percorrendo "string") */

	*sp = tp;
	*tp++ = '\0';
	*tp = '\0';

}	/* end sub_compile */

/*
 ****************************************************************
 *	Executa uma substitui��o				*
 ****************************************************************
 */
char *
sub_execute (BASE *base, char *start, char *End, REPL *repl)
{
	/*
	 *	base:
	 *	start:	Primeiro caractere da substitui��o
	 *	End:	Primeiro caractere ap�s a substitui��o
	 *	repl:	Substitui��o
	 */

	char		*lp;	/* Line Pointer */
	char		*cp;	/* Character Pointer */
	char		*tp;	/* Replacement Text Pointer */
	char		**sp;	/* Special Commands Pointer */
	char		*next;	/* Pr�ximo caractere ap�s a substitui��o */
	int		room;	/* Espaco disponivel */

	/*
	 *	Copia o in�cio da linha
	 */
	lp = temp_buffer;
	cp = base->ch;

	if ((room = LSIZE - (start - cp)) < 0)
		return (NOSTR);

	while (cp < start)
		*lp++ = *cp++;

	/*
	 *	Insere o texto da substitui��o
	 */
	sp = repl->r_specials;
	tp = repl->r_text;

	for (EVER)	/*  Percorre repl->r_text */
	{
		/*
		 *	Copia at� um comando especial
		 */
		if ((room -= *sp - tp) < 0)
			return (NOSTR);

		while (*lp++ = *tp++)
			/* vazio */;
		lp--;

		/*
		 *	Verifica se repl->r_text j� foi percorrido
		 */
		if (*tp == '\0')
			break;

		/*
		 *	Executa o comando especial
		 */
		switch (*tp)
		{
			/*
			 *	Copia a parte removida na substitui��o
			 */
		    case '&':
			if ((room -= End - start) < 0)
				return (NOSTR);

			cp = start;

			while (cp < End)
				*lp++ = *cp++;
			break;

			/*
			 *	Divide a linha em duas
			 */
		    case '\n':
			*lp = '\0';

			if (!txt_insert (base->ant, temp_buffer))
				return (NOSTR);

			lp = temp_buffer;
			room = LSIZE;
			break;

		    default:
			printf ("Special pointer inesperado: '%c' \n", *tp);
			break;

		}	/* switch **sp */

		tp++; sp++;
	}

	/*
	 *	Copia o final da linha ap�s a parte substituida
	 */
	next = lp;
	cp = End;

	while (room-- > 0 && (*lp++ = *cp++))
		/* vazio */;

	if (room == 0)
		return (NOSTR);

	/*
	 *	Aloca uma nova base->ch
	 */
	if ((cp = malloc (lp - temp_buffer)) == NOSTR)
		return (NOSTR);

	free (base->ch); base->ch = cp;

	/*
	 *	Copia a nova linha para a nova base->ch
	 */
	lp = temp_buffer;

	while (*cp++ = *lp++)
		/* vazio */;

	next = base->ch + (next - temp_buffer);

	return (next);

}	/* end sub_execute */
