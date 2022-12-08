/*
 ****************************************************************
 *								*
 *			insch.c					*
 *								*
 *	Insere um caractere em uma janela			*
 *								*
 *	Vers�o	2.0.0, de 20.04.88				*
 *		3.0.0, de 10.03.95				*
 *								*
 *	M�dulo: insch						*
 *		libcurses/curses				*
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
#include <curses.h>

#include "../../terminfo/h/defs.h"

/*
 ****************************************************************
 *	Insere um caractere em uma janela			*
 ****************************************************************
 */
int
winsch (register WINDOW	*win, register chtype ch)
{
	register chtype	*source, *first, *dest;
	register chtype	chtext, chattr;
	register int	b;
	chtype		*rest = (chtype *)NULL;
	int		size = 0;

	chtext = ch & A_CHARTEXT; chattr = ch & A_ATTRIBUTES;

	b = check (win->w_flags, W_BOX) ? 1 : 0;

	/*
	 *	Processamento de caracteres especiais
	 *	------------- -- ---------- ---------
	 */
	if (!check (win->w_flags, A_REAL))
	{
		/*
		 *	Fora do modo real
		 */
		if (chtext == '\t')
		{
			/*
			 *	Tabula��o: insere espa�os
			 */
			register int	i, e;

			i = win->w_curc;

			for (e = ((i + b) & (~7)) + 8 + b ; i < e ; i++)
			{
				if (winsch (win, ' ' | chattr) == ERR)
					return (ERR);
			}

			return (OK);
		}
		elif (!isgraph (chtext) && chtext != ' ' && chtext != '\n')
		{
			/*
			 *	Caracteres de Controle: escreve na forma "^X"
			 */
			if (winsch (win, '^' | chattr) == ERR)
				return (ERR);

			if (winsch (win, (chtext + '@') | chattr) == ERR)
				return (ERR);

			return (OK);
		}
	}

	/*
	 *	Final de linha
	 */
	if (chtext == '\n')
	{
		/*
		 *	Guarda o restante da linha
		 */
		size = (win->w_maxc - win->w_curc + 1 - b) * sizeof (chtype);
		rest = malloc (size);

		memmove (rest, &win->w_text[win->w_curl][win->w_curc], size);

		/*
		 *	Limpa o restante da linha
		 */
		wclrtoeol (win);
			
		goto nextline;
	}

	/*
	 *	Processamento de caracteres normais:
	 *	------------- -- ---------- -------
	 *	Verifica a posi��o corrente
	 */
	if (win->w_curc >= win->w_maxc - b || win->w_curl > win->w_maxl - b)
		return (ERR);

	/*
	 *	Abre espa�o para o caractere: 
	 *		os caracteres � direita s�o deslocados
	 *		para a direita de uma posi��o.
	 */
	first = &win->w_text[win->w_curl][win->w_curc];
	source = &win->w_text[win->w_curl][win->w_maxc - 1 - b];
	dest = source + 1;

	while (source >= first)
		*dest-- = *source--;

	/*
	 *	Copia o caractere para a posi��o corrente.
	 */
	win->w_text[win->w_curl][win->w_curc] = ch;

	/*
	 *	Marca o vetor de altera��es
	 */
	win->w_changed[win->w_curl] = 1;

	/*
	 *	Incrementa a posi��o corrente.
	 *	Se a janela tem contorno, respeitamo-lo
	 */
	if (win->w_curc < win->w_maxc - b)
	{
		/*
		 *	Basta incrementar a Coluna
		 */
		win->w_curc++;
	}
	else
	{
		/*
		 *	�ltima coluna: verifica "wrapping"
		 */
		if (!check (win->w_flags, A_WRAP))
			return (ERR);
	    nextline:
		if (win->w_curl < win->w_maxl - b)
		{
			/*
			 *	Avan�a criando a pr�xima linha
			 */
			win->w_curl++;
			win->w_curc = b;

			winsertln (win);
		}
		elif (win->w_flags & A_SCROLL)
		{
			/*
			 *	Avan�a rolando a janela
			 */
			wscroll (win, 1);
			win->w_curc = b;
		}

		/*
		 *	Copia o restante da linha anterior
		 */
		if (rest != (chtype *)NULL)
		{
			memmove (&win->w_text[win->w_curl][win->w_curc], rest, size);
			free (rest);
		}
	}

	return (OK);

}	/* end winsch */
