/*
 ****************************************************************
 *								*
 *			error.h					*
 *								*
 *	Defini��es Acerca de Mensagens de Erro			*
 *								*
 *	Vers�o	1.0.0, de 05.08.88				*
 *		4.6.0, de 27.08.04				*
 *								*
 *	M�dulo: CPP						*
 *		Tradutores					*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2004 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ******	Tipo de Erro ********************************************
 */
typedef	enum
{
	ADVR,			/* Advert�ncia */
	ERRO,			/* Erro */
	COMP			/* Erro do Preprocessador */

}	ERRTYPE;

/*
 ******	Tipo de Marca *******************************************
 */
typedef	enum
{
	NOMARK,			/* Sem indica��o do local do erro */
	TOKMARK,		/* Marca no Token Atual */
	MYMARK			/* S�o fornecidas as posi��es da marca */

}	MARKTYPE;

extern	int	nerrors;	/* N�mero de Erros Encontrados */

/*
 ****** Vari�veis globais ***************************************
 */
extern const char	**color_vector; /* Para as cores dos modos */

/*
 ******	Prot�tipos de fun��es ***********************************
 */
extern void		err_msg (ERRTYPE, MARKTYPE, const char *, ...);
extern void		putmark (MARKTYPE, const char *, const char *);
