/*
 ****************************************************************
 *								*
 *			buffer.c				*
 *								*
 *	Manipula��o de "buffers"				*
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
#include <string.h>
#include <ctype.h>

#include "../h/global.h"
#include "../h/text.h"
#include "../h/obj.h"
#include "../h/extern.h"
#include "../h/proto.h"

/*
 ****************************************************************
 *	Buffers							*
 ****************************************************************
 */
typedef	struct
{
	BASE	*b_list;
	int	b_type;		/* Veja abaixo */

}	BUFFER;

#define		B_NULL		0
#define		B_INTEGRAL	1
#define		B_PARTIAL	2

static BUFFER	Buffers[30];
static BUFFER	*bufp = &Buffers[0];

/*
 ******	Prot�tipos de fun��es ***********************************
 */
static BUFFER	*map (int);
static void	add (char *, BASE *, int);

/*
 ****************************************************************
 *	Acrescenta uma lista a um buffer			*
 ****************************************************************
 */
bool
buf_lput (BASE *first, BASE *last, int buf)
{
	BASE		*from, *to;
	BASE		*list, *tail = NOBASE;	/* CUIDADO */
	bool		again;

	if (Debug)
	{
		fprintf (stderr, "buf_lput: \"%s\" em '%c'\n", first->ch, buf);
		fprintf (stderr, "    last: \"%s\" em '%c'\n", last->ch, buf);
	}

	/*
	 *	Renova��o do buffer
	 */
	if (buf != '\0')
	{
		bufp = map (buf);

		/*
		 *	Buffers nomeados com mai�sculas n�o s�o renovados
		 */
		if (!isupper (buf))
		{
			if (bufp->b_list != NOBASE)
				txt_free (bufp->b_list, bufp->b_list->ant);

			bufp->b_list = NOBASE;
		}
	}

	if (bufp->b_list == NOBASE)
		bufp->b_type = B_INTEGRAL;

	/*
	 *	Copia a lista
	 */
	list = NOBASE;

	for (from = first, again = true; again; from = from->pos)
	{
		again = from != last;

		if ((to = malloc (sizeof (BASE))) == NOBASE)
			goto No_mem;

		if (list == NOBASE)
			tail = list = to;

		if ((to->ch = malloc (strlen (from->ch) +1)) == NOSTR)
			goto No_mem;

		strcpy (to->ch, from->ch);

		tail->pos = to;
		to->ant = tail;

		tail = to;

	}	/* for from = first up to last */

	/*
	 *	Acrescenta a lista ao buffer
	 */
	if (bufp->b_list == NOBASE)
	{
		bufp->b_list = list;
		tail->pos = list;
		list->ant = tail;
	}
	else
	{
		tail->pos = bufp->b_list;
		list->ant = bufp->b_list->ant;

		list->ant->pos = list;
		tail->pos->ant = tail;
	}

	return (true);

	/*
	 *	Se faltar mem�ria libera list e retorna false
	 */
    No_mem:
	if (to != NOBASE)
		free (to);

	if (list != NOBASE)
		txt_free (list, tail);

	return (false);

}	/* end buf_lput */

/*
 ****************************************************************
 *	Acrescenta uma cadeia a um buffer			*
 ****************************************************************
 */
void
buf_sput (const char *line, int start, int End, int buf)
{
	BASE		*base;

	/*
	 *	Renova��o do buffer
	 */
	if (buf)
	{
		bufp = map (buf);

		if (!isupper (buf))
		{
			if (bufp->b_list != NOBASE)
				txt_free (bufp->b_list, bufp->b_list->ant);

			bufp->b_list = NOBASE;
		}
	}
	if (bufp->b_list == NOBASE)
		bufp->b_type = B_PARTIAL;

	/*
	 *	Acrescenta a cadeia em uma nova base
	 */
	base = malloc (sizeof (BASE));

	if (bufp->b_list == NOBASE)
	{
		bufp->b_list = base;
		base->ant = base;
		base->pos = base;
	}
	else
	{
		base->ant = bufp->b_list->ant;
		base->pos = bufp->b_list;

		base->ant->pos = base;
		base->pos->ant = base;
	}

	base->ch = malloc (End - start + 2);
	strncpy (base->ch, &line[start], End - start + 1);
	base->ch[End - start + 1] = '\0';

	if (Debug)
	{
		fprintf (stderr, "buf_sput: \"%s\" em '%c'\n", base->ch,  buf);
		fprintf (stderr, "buf_sput: de '%c' at� '%c'\n", line[start], line[End]);
	}

}	/* end buf_sput */

/*
 ****************************************************************
 *	C�pia de um buffer para o texto				*
 ****************************************************************
 */
bool
buf_get (BASE *base, int order, bool forward, int buf)
{
	int		btype;
	BASE		*list;

	if (Debug)
		fprintf (stderr, "buf_get: do buffer '%c'\n", buf);

	bufp = map (buf);
	btype = bufp->b_type;
	list = bufp->b_list;

	/*
	 *	Verifica se o buffer est� vazio
	 */
	if (list == NOBASE)
		return (false);

	/*
	 *	Verifica se as linhas s�o completas
	 */
	if (btype == B_INTEGRAL)
	{
		/*
		 *	O buffer cont�m linhas completas
		 */
		if (forward)
			txt_copy (list, list->ant, base);
		else
			txt_copy (list, list->ant, base->ant);
	}
	elif (btype == B_PARTIAL)
	{
		/*
		 *	Buffer n�o cont�m linhas completas
		 */
		char	*right;
		BASE	*posterior;

		if (!forward)
			order--;

		/*
		 *	Apenas parte de uma linha
		 */
		if (list->ant == list)
		{
			if (base->ch[order])
				add (list->ch, base, order + 1);
			else
				add (list->ch, base, order);

			return (true);
		}

		/*
		 *	Guarda restante da linha (� direita)
		 */
		right = malloc (strlen (base->ch) - order + 1);
		strcpy (right, base->ch + order + 1);

		/*
		 *	Acrescenta primeira parte
		 */
		base->ch[order + 1] = '\0';
		add (list->ch, base, order + 1);

		/*
		 *	Acrescenta linhas intermedi�rias
		 */
		posterior = base->pos;
		txt_copy (list->pos, list->ant, base);

		/*
		 *	Recoloca o restante da linha
		 */
		add (right, posterior->ant, strlen (posterior->ant->ch));
		free (right);
	}
	else
	{
		fprintf (stderr, "buf_get: btype: %d\n", btype);
	}

	return (true);

}	/* end buf_get */

/*
 ****************************************************************
 *	Mapeamento nome -> buffer				*
 ****************************************************************
 */
static BUFFER *
map (int name)
{
	/*
	 *	Letras min�sculas
	 *
	 *	Letras mai�sculas
	 *	
	 *	!	�ltima remo��o
	 *
	 *	?	�ltima inser��o
	 */

	if (islower (name))
		return (&Buffers [name - 'a' + 2]);
	elif (isupper (name))
		return (&Buffers [name - 'A' + 2]);
	elif (name == '?')		/* Destinado � �ltima remo��o */
		return (&Buffers[1]);
	else				/* '!': Destinado � �ltima inser��o */
		return (&Buffers[0]);

}	/* end map */

/*
 ****************************************************************
 *	Acr�scimo de caracteres a uma linha do texto		*
 ****************************************************************
 */
static void
add (char *str, BASE *base, int start)
{
	memmove (temp_buffer, base->ch, start);
	strcpy (temp_buffer + start, str);
	strcat (temp_buffer, &base->ch[start]);
	base->ch = (char *)realloc (base->ch, strlen (temp_buffer) + 1);
	strcpy (base->ch, temp_buffer);

}	/* end add */
