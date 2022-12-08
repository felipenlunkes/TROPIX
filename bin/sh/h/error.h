/*
 ****************************************************************
 *								*
 *			error.h					*
 *								*
 *	Defini��es acerca de mensagens de erro			*
 *								*
 *	Vers�o	3.2.3, de 03.01.00				*
 *		4.4.0, de 10.12.02				*
 *								*
 *	M�dulo: SHELL						*
 *		Interpretador de Comandos			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Tipo da marca de indica��o do erro			*
 ****************************************************************
 */
typedef	enum
{
	SHORTMARK,	/* Indicador de 1 Caractere ('^') */
	LONGMARK	/* Indicador de v�rios caracteres ('|/////|') */

}	MARKTYPE;

/*
 ****************************************************************
 *	Prot�tipos de Fun��es					*
 ****************************************************************
 */
void	sherror (MARKTYPE, const char *, ...);
