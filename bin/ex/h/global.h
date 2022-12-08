/*
 ****************************************************************
 *								*
 *			global.h				*
 *								*
 *	Defini��es globais					*
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

#define	H_GLOBAL	/* Para declarar as fun��es */

/*
 ******	Tipos fundamentais **************************************
 */
typedef	enum	{ false, true } bool;

#define	EVER	;;
#define	elif	else if

/*
 ******	Limites m�ximos de caracteres para: *********************
 */
#define  LSIZE	512		/* Linha do texto */
#define  NSIZE	 64		/* Nome de arquivo */
#define  RSIZE	128		/* Cadeia para Substitui��o */

/*
 ******	Manipula��o de Indicadores ******************************
 */
#define	check(f,m)	(((f)&(m)) == (m))	/* Verifica��o */
#define	set(f,m)	((f) |=  (m))		/* Ligando */
#define	reset(f,m)	((f) &= ~(m))		/* Desligando */
