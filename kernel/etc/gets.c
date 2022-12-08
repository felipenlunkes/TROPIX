/*
 ****************************************************************
 *								*
 *			gets.c					*
 *								*
 *	L� (e edita) uma linha do teclado			*
 *								*
 *	Vers�o	3.0.0, de 05.07.94				*
 *		3.0.0, de 07.02.95				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 1999 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#include "../h/common.h"

#include "../h/proto.h"
#include "../h/extern.h"

/*
 ****************************************************************
 *	Defini��es globais					*
 ****************************************************************
 */

/*
 ******	Tabela de Acentos ***************************************
 */
typedef struct
{
	ushort	a_fonte;	/* Fonte: pares */
	ushort	a_destino;	/* Destino: resultado da conversao */

}	ACENTO;

#define	OR(a, b)	((a << 8) | b)

#define IS_ACCENT(c)	(c == '\'' || c == ',' || c == '~' ||	\
				c == '^' || c == '`' || c == ':')

entry int	esc_char = 0;	/* Primeira parte de poss�vel acento */

extern const ACENTO acento[];	/* Tabela de acentos */

/*
 ****************************************************************
 *	L� (e edita) uma linha do teclado			*
 ****************************************************************
 */
char *
gets (register char *cp)
{
	int		c;
	char		*old_cp = cp;
	ushort		or_c;
	const ACENTO	*ap;

 	/*
 	 *	L� os caracteres
 	 */
	for (EVER)
	{
		/*
		 *	Obt�m um caractere
		 */
	    again:
		c = getchar ();

		/*
		 *	Tratamento dos ACENTOS
		 */
		if (esc_char)
		{
			or_c = OR (esc_char, c);	esc_char = 0;

			if   (c == '\\')
				continue;

			/*
			 *	Procura o acento dado
			 */
			for (ap = acento; ap->a_fonte; ap++)
			{
				if (ap->a_fonte == or_c)
				{
					c = ap->a_destino; 	cp[-1] = c;
					putchar ('\b');		putchar (c);
					goto again;
				}
			}

			/*
			 *	Se n�o achou na tabela, continua normalmente
			 */
		}

		/*
		 *	Verifica se terminou a linha
		 */
		if (c == '\n' || c == '\r')
		{
			*cp++ = '\0'; 	putchar ('\n');
			return (old_cp);
		}

		/*
		 *	Processa erase
		 */
		if (c == '\b' || c == 0x7F /* DEL */)
		{
			if (cp <= old_cp)
				continue;

			cp--;
			putchar ('\b'); putchar (' '); putchar ('\b');
			continue;
		}

		/*
		 *	Processa os acentos
		 */
		if (IS_ACCENT (c))
			esc_char = c;

		/*
		 *	Guarda e ecoa o caracter
		 */
		*cp++ = c;

		putchar (c);

	}	/* end for EVER */

}	/* end gets */
