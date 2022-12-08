/*
 ****************************************************************
 *								*
 *			src/add.c				*
 *								*
 *	Reconhecimento e Avalia��o de Endere�os			*
 *								*
 *	Vers�o	1.0.0, de 04.11.86				*
 *		3.0.0, de 27.05.97				*
 *								*
 *	Modulo: ED						*
 *		Editores de Texto				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>
#include <ctype.h>

#include "../h/ed.h"
#include "../h/scan.h"
#include "../h/proto.h"
#include "../h/extern.h"

/*
 ****************************************************************
 *	Condi��es no Reconhecimento e Avalia��o de Endere�os	*
 ****************************************************************
 */
#define  S_INIT		000	/* Estado Inicial */
#define  S_BASE		001	/* Endere�o base j� fornecido */
#define  S_PLUS		002	/* Existe um '+' pendente */
#define  S_MINUS	004	/* Existe um '-' pendente */

/*
 ****************************************************************
 *	Reconhecimento e Avalia��o de Endere�os			*
 ****************************************************************
 */
BASE *
get_address (BASE *current)
{
	int		state;
	BASE		*add = NOBASE;	/* Linha enderecada */
	char		*bp;		/* In�cio do Endere�o em Line */
	char		mark;
	int		count;
	bool		advanced;
	char		*string;
	bool		found = false;

	error_msg = NULL;

	state = S_INIT;
	advanced = false;

	while (isspace (*nextp))
		nextp++;

	bp = nextp;

	while (*nextp) switch (*nextp++)
	{
	    case '.':
		if (state & S_BASE)
			goto s_error;

		add = current;
		state |= S_BASE;
		continue;

	    case '$':
		if (state & S_BASE)
			goto s_error;

		add = Root->ant;
		state |= S_BASE;
		continue;

	    case '\'':
		if (state & S_BASE)
			goto s_error;

		if ((mark = get_lower ()) == '\0')
			return (NOBASE);

		state |= S_BASE;

		if ((add = mrk_base (mark)) == NOBASE)
			goto m_error;

		continue;

	    case '1':
	    case '2':
	    case '3':
	    case '4':
	    case '5':
	    case '6':
	    case '7':
	    case '8':
	    case '9':
		count = *--nextp - '0';

		while (isdigit (*++nextp))
		{
			count = count * 10 + *nextp - '0';

			if (count < 0)
				goto c_error;
		}

		advanced = true;

		if ((state & S_BASE) == 0)
		{
			if ((add = txt_base (count)) == NOBASE)
				goto o_error;

			state |= S_BASE;
		}
		elif (state & S_MINUS)
		{
			if ((add = txt_advance (add, -count)) == NOBASE)
				goto o_error;

			state &= ~S_MINUS;
		}
		else
		{
			if ((add = txt_advance (add, count)) == NOBASE)
				goto o_error;

			state &= ~S_PLUS;
		}

		advanced = false;
		continue;

	    case '/':
		if ((state & S_BASE) == 0)
		{
			add = current;
			state |= S_BASE;
		}
		elif (state & S_MINUS)
		{
			if (add == Root)
				goto o_error;

			add = add->ant;
			state &= ~S_MINUS;
		}
		elif (state & S_PLUS)
		{
			if (add == Root->ant)
				goto o_error;

			add = add->pos;
			state &= ~S_PLUS;
		}

		if ((string = get_string ('/')) == NULL)
			return (NOBASE);

		if (*string == '\0')
		{
			if (Search[0] == '\0')
				goto e_error;
		}
		elif (!re_compile (string, Search))
		{
			return (NOBASE);
		}

		current = add;

		for (add = current->pos; add != current; add = add->pos)
		{
			if (found = (re_execute (Search, add->ch, add->ch)) != NULL)
				break;
		}

		if (!found)
			goto n_error;

		continue;

	    case '?':
		if ((state & S_BASE) == 0)
		{
			add = current;
			state |= S_BASE;
		}
		elif (state & S_MINUS)
		{
			if (add == Root)
				goto o_error;

			add = add->ant;
			state &= ~S_MINUS;
		}
		elif (state & S_PLUS)
		{
			if (add == Root->ant)
				goto o_error;

			add = add->pos;
			state &= ~S_PLUS;
		}

		if ((string = get_string ('?')) == NULL)
			return (NOBASE);

		if (*string == '\0')
		{
			if (Search[0] == '\0')
				goto e_error;
		}
		elif (!re_compile (string, Search))
		{
			return (NOBASE);
		}

		current = add;

		for (add = current->ant; add != current; add = add->ant)
		{
			if (found = (re_execute (Search, add->ch, add->ch)) != NULL)
				break;
		}

		if (!found)
			goto n_error;

		continue;

	    case '-':
		if ((state & S_BASE) == 0)
		{
			add = current;
			state |= S_BASE | S_MINUS;
		}
		elif (state & S_PLUS)
		{
			add = add->pos;
			state &= ~S_PLUS;
			state |= S_MINUS;
		}
		elif (state & S_MINUS)
		{
			if (add == Root)
				goto o_error;

			add = add->ant;
		}
		else
		{
			state |= S_MINUS;
		}

		continue;

	    case '+':
		if ((state & S_BASE) == 0)
		{
			add = current;
			state |= S_BASE | S_PLUS;
		}
		elif (state & S_MINUS)
		{
			add = add->ant;
			state &= ~S_MINUS;
			state |= S_PLUS;
		}
		elif (state & S_PLUS)
		{
			if (add == Root->ant)
				goto o_error;

			add = add->pos;
		}
		else
		{
			state |= S_PLUS;
		}

		continue;

	    case ' ':
	    case '\t':
		continue;

	    default:
		nextp--;
		advanced = true;
		goto end;
	}

    end:
	if ((state & S_BASE) == 0)
		return (NOBASE);

	/*
	 *	Processamento de '+' ou '-' pendentes
	 */
	if (state & S_MINUS)
	{
		if (add == Root)
			goto o_error;

		add = add->ant;
		state &= ~S_MINUS;
	}
	elif (state & S_PLUS)
	{
		if (add == Root->ant)
			goto o_error;

		add = add->pos;
		state &= ~S_PLUS;
	}

	token.t_begin = bp;
	token.t_end = (advanced) ? nextp - 1 : nextp;
	return (add);

	/*
	 *	Tratamento de Erros
	 */
    c_error:
	token.t_begin = bp;
	token.t_end = nextp;
	error_msg = "Numero grande demais";
	return (NOBASE);

    e_error:
	token.t_begin = nextp - 2;
	token.t_end = nextp - 1;
	error_msg = "Express�o regular para busca indefinida";
	return (NOBASE);

    m_error:
	error_msg = "Marca n�o definida";
	return (NOBASE);

    n_error:
	error_msg = "Express�o regular n�o encontrada";
	return (NOBASE);

    o_error:
	token.t_begin = bp;
	token.t_end = (advanced) ? nextp - 1 : nextp;
	error_msg = "Endere�o inexistente";
	return (NOBASE);

    s_error:
	token.t_begin = nextp;
	token.t_end = nextp;
	error_msg = "Erro de sintaxe";
	return (NOBASE);

}	/* end get_addresses */
