/*
 ****************************************************************
 *								*
 *			scan.h					*
 *								*
 *	Defini��es para o uso do "scanner"			*
 *								*
 *	Vers�o	2.0.0, de 17.08.88				*
 *		3.0.1, de 30.04.97				*
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

#define	H_SCAN		/* Para declarar as fun��es */

/*
 ******	Tipo "token" ********************************************
 */
typedef	struct
{
	char	*t_begin;
	char	*t_end;

}	TOKEN;

/*
 ******	Tipo da marca de erro ***********************************
 */
typedef	enum { NOMARK, SHORTMARK, LONGMARK }	ERROR;
