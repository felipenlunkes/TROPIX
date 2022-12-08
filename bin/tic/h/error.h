/*
 ****************************************************************
 *								*
 *			error.h					*
 *								*
 *	Compilador de Descricoes de Terminais			*
 *								*
 *	Vers�o 2.0.0, de 21.04.87				*
 *	       3.0.0, de 12.07.97				*
 *								*
 *	Modulo: tic/tac						*
 *		Utilitarios Basicos				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Tipo de Erro						*
 ****************************************************************
 */
typedef	enum
{
	ADVR,		/* Advertencia */
	ERRO,		/* Erro */
	COMP,		/* Erro do compilador */
	FATAL		/* Erro Fatal: Interrompe a Compila��o */

}	ERRTYPE;

/*
 ****************************************************************
 *	Tipo de Ponteiro					*
 ****************************************************************
 */
typedef	enum
{
	NOMARK,		/* Sem indicacao do local do erro */
	SMARK,	/* Indicador de 1 Caractere ('^') */
	LMARK	/* Indicador de Varios Caracteres ('|/////|') */

}	MARKTYPE;

/*
 ******	Prot�tipos de fun��es ***********************************
 */
extern void	tic_error (ERRTYPE, MARKTYPE, const char *, const char *);
