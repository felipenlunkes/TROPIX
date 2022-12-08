/*
 ****************************************************************
 *								*
 *			re.c					*
 *								*
 *	Express�es regulares					*
 *								*
 *	Vers�o	2.0.0, de 17.08.88				*
 *		3.0.0, de 30.04.97				*
 *								*
 *	M�dulo: EX/VI						*
 *		Editores de texto				*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../h/global.h"
#include "../h/extern.h"
#include "../h/proto.h"

/*
 ****************************************************************
 *	Vari�veis globais					*
 ****************************************************************
 */
entry char	*_end_match;	/* Primeiro caracter na linha ap�s a express�o */

/*
 ****************************************************************
 *	Tipos de elementos do aut�mato				*
 ****************************************************************
 */
#define  C_UNIQUE	0x01		/* Caracter Normal */
#define  C_SET		0x02		/* Um conjunto de caracteres */
#define  C_ANY		0x03		/* Qualquer caracter */
#define  E_BEGIN	0x04		/* In�cio de uma Express�o */
#define  E_END		0x05		/* Fim de uma Express�o */
#define  E_TABLE	0x06		/* In�cio de uma tabela C_SET */

#define  ELEM(c)	(c & 0x0F)

/*
 ****************************************************************
 *	Atributos para os elementos do aut�mato			*
 ****************************************************************
 */
#define  A_FIRST	0x10	/* Ocorrencia do elemento no in�cio */
#define  A_LAST		0x20	/*			  no fim */
#define  A_REPEAT	0x40	/* Repeti��o zero ou mais vezes */
#define  A_RANGE	0x80	/* Repeti��o entre limites */

#define  ATRIB(c)	((c) & 0xF0)

/*
 ****************************************************************
 *	Conjuntos de caracteres					*
 ****************************************************************
 */
#define  TBSIZE		(128)
#define  MASK(n)	(1 << (n-1))

#define  INCLUDE(ch, bit)	(set_table[ch] |= MASK(bit))
#define  EXCLUDE(ch, bit)	(set_table[ch] &= ~MASK(bit))
#define  PRESENT(ch, mask)	((set_table[ch] & mask) != 0)

/*
 ******	Prot�tipos de fun��es ***********************************
 */
static bool	 match (char *, char *, char *, int);

/*
 ****************************************************************
 *	Compila uma express�o regular em um aut�mato finito	*
 ****************************************************************
 */
bool
re_compile (const char *expression, char **automata)
{
	const char	*ep;	/* aponta caracter corrente */
	char		*cp;	/* aponta c�digo corrente */
	char		*cq;	/* aponta ultimo c�digo */
	char		*cs;	/* aponta in�cio do c�digo da exp. atual */
	char			*code;	/* Area para o c�digo gerado */

	int		ch;

	int		size;	/* tamanho necessario p/ o c�digo */
	int		ntabs;	/* No. de tabelas C_SET */
	int		nbits;	/* No. de bits C_SET ainda disponiveis */

	int		nsets;
	char		*set_table;

	/*
	 ******	Calcula o tamanho necessario para o c�digo gerado
	 */
	size = 3;	/* E_BEGIN, E_END, '\0' */
	ntabs = 0;
	nbits = 0;

	for (ep = &expression[0]; *ep; ep++)
	{
#ifdef	DEBUG
		printf ("caracter: '%c'\n", *ep); fflush (stdout);
#endif	DEBUG
		switch (*ep)
		{
		    case '\\':
			ep++;
			goto case_default;

		    case '^':
			if (ep > expression)
				goto case_default;
			break;

		    case '$':
			if (ep[1] != '\0')
				goto case_default;
			break;

		    case '[':
			if (nbits == 0)
			{
				ntabs++;
				nbits = 8;
			}

			nbits--; size += 2;

			while (*ep && *ep != ']' && ep[-1] != '\\')
				ep++;

			if (*ep == '\0')
			{
				error_msg = "Falta ']'\n";
				return (false);
			}
			break;

		    case '.':
			size += 1;
			break;

		    case '*':
			if (ep == expression)
				goto case_default;
			break;

		    case '+':
			if (ep == expression)
				size += 2;
			else
				goto case_default;
			break;

		    case_default:
		    default:
			size += 2;
			break;

		}	/* switch (*ep) */

#ifdef	DEBUG
		printf ("Size:%d, Nbits:%d, Ntabs:%d\n\n", size, nbits, ntabs);
		fflush (stdout);
#endif

	}	/* for (*ep) */

	size += TBSIZE * ntabs;

	/*
	 *	Verifica o tamanho do c�digo
	 */
	if ((*automata = realloc (*automata, size + 1)) == NOSTR)
	{
		error_msg = "Express�o regular longa demais";
		return (false);
	}

	code = *automata;

	/*
	 ******	Compila��o **************************************
	 */
	nsets = 0;
	set_table = NOSTR;

	cs = &code[0];

	/*
	 *	Coloca as tabelas no in�cio do c�digo
	 */
	while (ntabs -- > 0)
	{
		*cs = E_TABLE;

		if (set_table == NOSTR)
			set_table = cs +1;

		for (cp = cs +1; cp < cs + TBSIZE +1; cp++)
			*cp = 0;

		cs += TBSIZE +1;
	}

	/*
	 *	Inicia a gera��o do aut�mato
	 */
	*cs = E_BEGIN;
	cq = NOSTR;	/* cq == NOSTR => in�cio de uma express�o */
	cp = cs +1;

	/*
	 *	Percorre a express�o regular e gera seu aut�mato correspondente
	 */
	for (ep = &expression[0]; *ep; ep++)
	{
#ifdef	DEBUG
		printf ("caracter: '%c'\n", *ep); fflush (stdout);
#endif
		switch (*ep)
		{
		    case '\\':
			cq = cp;
			*cp++ = C_UNIQUE;
			*cp++ = *++ep;
			break;

		    case '^':
			if (cq == NOSTR)
				*cs |= A_FIRST;
			else
				goto case_normal;
			break;

		    case '$':
			if (ep[1] == '\0')
				*cs |= A_LAST;
			else
				goto case_normal;
			break;

		    case '[':
			cq = cp;

			if (nsets == 8)
			{
				set_table += TBSIZE +1;
				nsets = 1;
			}
			else
			{
				nsets++;
			}

			if (ep[1] == '^')
				goto case_neg;

			while (*++ep != ']')
			{
				if (*ep != '\\' && ep[1] == '-' && *(ep+2) >= *ep && *(ep+2) != ']')
				{
					for (ch = *ep; ch <= *(ep+2); ch++)
						INCLUDE (ch, nsets);
					ep += 2;
				}
				else
				{
					if (*ep == '\\')
						ep++;

					INCLUDE (*ep, nsets);
				}
			}

			*cp++ = C_SET;
			*cp++ = MASK (nsets);
			break;

		    case_neg:
			for (ch = 0; ch <= 127; ch++)
				INCLUDE (ch, nsets);

			ep++;

			while (*++ep != ']')
			{
				if (*ep != '\\' && ep[1] == '-' && *(ep+2) >= *ep && *(ep+2) != ']')
				{
					for (ch = *ep; ch <= *(ep+2); ch++)
						EXCLUDE (ch, nsets);

					ep += 2;
				}
				else
				{
					if (*ep == '\\')
						ep++;

					EXCLUDE (*ep, nsets);
				}
			}

			*cp++ = C_SET;
			*cp++ = MASK (nsets);
			break;

		    case '.':
			cq = cp;
			*cp++ = C_ANY;
			break;

		    case '*':
			if (cq != NOSTR && (ATRIB(*cq) & A_REPEAT) == 0)
				*cq |= A_REPEAT;
			else
				goto case_normal;
			break;

		    case '+':
			if (cq != NOSTR && (ATRIB(*cq) & A_REPEAT) == 0)
			{
				*cp++ = ELEM(*cq) | A_REPEAT;

				if (ELEM(*cq) == C_ANY)
				{
					cq = cp -1;
				}
				else
				{
					*cp++ = *(cq+1);
					cq = cp -2;
				}
			}
			else
			{
				goto case_normal;
			}
			break;

		case_normal:
		    default:
			cq = cp;
			*cp++ = C_UNIQUE;
			*cp++ = *ep;
			break;

		}	/* switch (*ep) */

	}	/* for (*ep) */

	*cp++ = E_END;
	*cp = '\0';

	return (true);

}	/* end re_compile */

/*
 ****************************************************************
 *  Executa o aut�mato correspondente a uma express�o regular	*
 ****************************************************************
 */
int
re_execute (char *expr, char *line, char *start)
{
	/*
	 *	expr:	/* Aut�mato da Express�o Regular
	 *	line:	/* Linha de Texto p/ execu��o do Aut�mato
	 *	start:	/* In�cio da execu��o em line
	 */
	bool		again;
	char		*set_table;
	int		nsets;
	bool		first,
			last;

	bool		common_case;
	char		first_char;

	/*
	 *	Se ainda n�o foi dada uma cadeia de busca, ...
	 */
	if (expr == NOSTR)
		return (-1);

	/*
	 *	Avan�a as tabelas
	 */
	if (ELEM (*expr) == E_TABLE)
	{
		set_table = expr +1;
		expr = expr + TBSIZE + 1;

		while (ELEM(*expr) == E_TABLE)
			expr += TBSIZE + 1;

		nsets = 8;
	}
	else
	{
		set_table = NOSTR;
		nsets = 0;
	}

	/*
	 *	Pequena verifica��o do formato do aut�mato
	 */
	if (ELEM (*expr) != E_BEGIN)
	{
		error_msg = "Aut�mato invalido\n";
		return (-1);
	}

	/*
	 *	Atributos exclusivos da express�o m�e
	 */
	first = ATRIB (*expr) & A_FIRST;
	last =  ATRIB (*expr) & A_LAST;

	/*
	 *	Express�o no in�cio da linha
	 */
	if (first)
	{
		if (start != line)
			return (-1);

		if (match (expr, line, set_table, nsets))
		{
			if (!last || *_end_match == '\0')
				return (start - line);
		}

		return (-1);
	}

	/*
	 *	Otimiza��o
	 */
	common_case = ELEM (*(expr+1)) == C_UNIQUE
			&& (ATRIB (*(expr+1)) & A_REPEAT) == 0;

	first_char = common_case ? *(expr+2) : '\0';

	/*
	 *	Percorre line, a partir de start, at� que o
	 *	aut�mato possa ser executado ou que line termine
	 */
	for (again = true; again; start++)
	{
		again = *start != '\0';

		/*
		 *	Otimiza��o:
		 */
		if (common_case)
		{
			if ((start = strchr (start, first_char)) == NOSTR)
				return (-1);
		}

		/*
		 *	Tenta executar o Aut�mato
		 */
		if (match (expr, start, set_table, nsets))
		{
			if (!last || *_end_match == '\0')
				return (start - line);
		}
	}

	return (-1);

}	/* end re_execute */

/*
 ****************************************************************
 *	Verifica a continua��o da execu��o do aut�mato		*
 ****************************************************************
 */
static bool	
match (char *ep, char *lp, char *set_table, int nsets)
{
	/*
	 *	ep: Aut�mato
	 *	lp: Linha de Texto
	 */

	char		ch;
	char		*bp;

	/*
	 *	Executa (recursivamente) o Aut�mato a partir de start
	 */
	for (/* vazio */; *ep; ep++) switch (*ep)
	{
	    case E_BEGIN:
	    case E_BEGIN | A_FIRST:
	    case E_BEGIN | A_FIRST | A_LAST:
	    case E_BEGIN | A_LAST:
		break;

	    case E_END:
		break;

	    case C_UNIQUE:
		if (*lp == *++ep)
			lp++;
		else
			return (false);
		break;

	    case C_UNIQUE | A_REPEAT:
		ch = *++ep;
		bp = lp;

		while (*lp == ch)
			lp++;

		goto case_repeat;

	    case C_SET:
		if (--nsets < 0)
		{
			set_table += TBSIZE +1;
			nsets = 7;
		}

		ch = *++ep;

		if (PRESENT(*lp, ch))
			lp++;
		else
			return (false);
		break;

	    case C_SET | A_REPEAT:
		if (--nsets < 0)
		{
			set_table += TBSIZE +1;
			nsets = 7;
		}

		ch = *++ep;
		bp = lp;

		while (PRESENT (*lp, ch))
			lp++;

		goto case_repeat;

	    case C_ANY:
		if (*lp)
			lp++;
		else
			return (false);
		break;

	    case C_ANY | A_REPEAT:
		bp = lp;

		while (*lp)
			lp++;

		goto case_repeat;

	    case_repeat:
		ep++;

		for (/* vazio */; lp >= bp; lp--)
		{
			if (match (ep, lp, set_table, nsets))
				return (true);
		}

		return (false);

	    default:
		error_msg = "match: Aut�mato invalido\n";
		return (false);

	}	/* for (*ep)  switch (*ep) */

	/*
	 *	O Aut�mato executou completamente
	 *	Indica o final da execu��o em _end_match
	 */
	_end_match = lp;
	return (true);

}	/* end match */
