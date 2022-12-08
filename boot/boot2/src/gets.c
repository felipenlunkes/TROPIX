/*
 ****************************************************************
 *								*
 *			gets.c					*
 *								*
 *	L� (e edita) uma linha do teclado			*
 *								*
 *	Vers�o	3.0.0, de 05.07.94				*
 *		3.0.7, de 14.03.97				*
 *								*
 *	M�dulo: Boot2						*
 *		N�CLEO do TROPIX para PC			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 1994 NCE/UFRJ - tecle "man licen�a"	*
 *								*
 ****************************************************************
 */

#include <common.h>

#include "../h/common.h"
#include "../h/extern.h"
#include "../h/proto.h"

/*
 ****************************************************************
 *	Defini��es globais					*
 ****************************************************************
 */
#define	CTL_Q	0x11

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
gets (char *cp)
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

		if (c == CTL_Q)
			goto again;

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
			putchar ('\b');	putchar (' ');	putchar ('\b');
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

/*
 ****************************************************************
 *	Tabela de Acentos					*
 ****************************************************************
 */
const ACENTO	acento[] =
{
	OR ('~', 'A'),	0xC3,	/*  � */
	OR ('~', 'a'),	0xE3,	/*  � */
	OR ('~', 'O'),	0xD5,	/*  � */
	OR ('~', 'o'),	0xF5,	/*  � */
	OR (',', 'C'),	0xC7,	/*  � */
	OR (',', 'c'),	0xE7,	/*  � */
	OR (',', 'z'),	0xDF,	/* sz */
	OR ('\'','A'),	0xC1,	/*  � */
	OR ('\'','a'),	0xE1,	/*  � */
	OR ('\'','E'),	0xC9,	/*  � */
	OR ('\'','e'),	0xE9,	/*  � */
	OR ('\'','I'),	0xCD,	/*  � */
	OR ('\'','i'),	0xED,	/*  � */
	OR ('\'','O'),	0xD3,	/*  � */
	OR ('\'','o'),	0xF3,	/*  � */
	OR ('\'','U'),	0xDA,	/*  � */
	OR ('\'','u'),	0xFA,	/*  � */
	OR ('^', 'A'),	0xC2,	/*  � */
	OR ('^', 'a'),	0xE2,	/*  � */
	OR ('^', 'E'),	0xCA,	/*  � */
	OR ('^', 'e'),	0xEA,	/*  � */
	OR ('^', 'I'),	0xCE,	/* ^I */
	OR ('^', 'i'),	0xEE,	/* ^i */
	OR ('^', 'O'),	0xD4,	/*  � */
	OR ('^', 'o'),	0xF4,	/*  � */
	OR ('^', 'U'),	0xDB,	/* ^U */
	OR ('^', 'u'),	0xFB,	/* ^u */
	OR ('`', 'A'),	0xC0,	/*  � */
	OR ('`', 'a'),	0xE0,	/*  � */
	OR ('`', 'E'),	0xC8,	/* `E */
	OR ('`', 'e'),	0xE8,	/* `e */
	OR ('`', 'I'),	0xCC,	/* `I */
	OR ('`', 'i'),	0xEC,	/* `i */
	OR ('`', 'O'),	0xD2,	/* `O */
	OR ('`', 'o'),	0xF2,	/* `o */
	OR ('`', 'U'),	0xD9,	/* `U */
	OR ('`', 'u'),	0xF9,	/* `u */
	OR (':', 'A'),	0xC4,	/* :A */
	OR (':', 'a'),	0xE4,	/* :a */
	OR (':', 'E'),	0xCB,	/* :E */
	OR (':', 'e'),	0xEB,	/* :e */
	OR (':', 'I'),	0xCF,	/* :I */
	OR (':', 'i'),	0xEF,	/* :i */
	OR (':', 'O'),	0xD6,	/* :O */
	OR (':', 'o'),	0xF6,	/* :o */
	OR (':', 'U'),	0xDC,	/*  � */
	OR (':', 'u'),	0xFC,	/*  � */
	0,		0
};
