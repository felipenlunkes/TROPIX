/*
 ****************************************************************
 *								*
 *			lc_vector.c				*
 *								*
 *	Ger�ncia de localiza��o da "libc"			*
 *								*
 *	Vers�o	3.0.0, de 29.01.98				*
 *		3.0.0, de 29.01.98				*
 *								*
 *	M�dulo: lc_vector					*
 *		libc/etc					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <locale.h>

/*
 ****************************************************************
 *	Vetor das linguagens definidas				*
 ****************************************************************
 */
#define	LC_COL	4

entry char	_lc_vector[LC_SIZE][LC_COL] =
{
	{ 'P' },	/* LC_ALL 	Todo o "locale" */
	{ 'P' },	/* LC_COLLATE,	Fun��es "strcoll" e "strxfrm" */
	{ 'P' },	/* LC_CTYPE,	Fun��es de an�lise de caracteres */
	{ 'P' },	/* LC_MONETARY,	Informa��o monet�ria */
	{ 'P' },	/* LC_NUMERIC,	Ponto decimal (e outros) */
	{ 'P' }		/* LC_TIME	Fun��o "strftime" */
};
