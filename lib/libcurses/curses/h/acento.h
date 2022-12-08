/*
 ****************************************************************
 *								*
 *			acento.h				*
 *								*
 *	Defini��o de acentos					*
 *								*
 *	Vers�o	2.0.0, de 15.03.88				*
 *		3.0.0, de 22.03.95				*
 *								*
 *	Modulo: acento.h					*
 *		libcurses/curses				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ******	Defini��o de acentos ************************************
 */
typedef	struct
{
	int	a_fonte;	/* Fonte: pares */
	int	a_destino;	/* Destino: resultado da conversao */

}	ACENTO;

#define	OR(a, b)	((a << 8) | b)

#define		isaccent(c)	(c == ',' || c == ':' || c == '\'' ||	\
					c == '`' || c == '^' ||		\
					c == '~' || c == '=')
