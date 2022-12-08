/*
 ****************************************************************
 *								*
 *			atof.c					*
 *								*
 *	Converte uma cadeia de caracteres representando		*
 *	um n�mero de ponto flutuante no formato interno		*
 *								*
 *	Vers�o	2.0.0, de 11.08.86				*
 *		3.0.0, de 08.07.95				*
 *								*
 *	M�dulo: strtod						*
 *		libc/stdio					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <stdlib.h>

/*
 ****************************************************************
 *	Converte n�meros de ponto flutuante			*
 ****************************************************************
 */
double
atof (const char *cp)
{
	return (strtod (cp, (const char **)0));

}	/* end atof */
