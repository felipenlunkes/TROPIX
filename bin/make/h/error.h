/*
 ****************************************************************
 *								*
 *			error.h					*
 *								*
 *	Defini��es relativas �s mensagens de erro		*
 *								*
 *	Vers�o	3.0.0, de 29.03.96				*
 *								*
 *	M�dulo: Make: Construtor de Programas			*
 *		Interpretador de Comandos			*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Tipos de erro						*
 ****************************************************************
 */
typedef	enum
{
	WARNING,	/* Advert�ncia */
	ERROR,		/* Erro */
	INTERNAL_ERROR	/* Erro interno do programa */

}	ERRTYPE;

/*
 ****************************************************************
 *	Tipo de indica��o do erro				*
 ****************************************************************
 */
typedef	enum
{
	NOMARK,		/* Sem indica��o do local do erro */
	GIVENMARK,	/* Indicador com as posi��es dadas em "set_mark" */
	TOKMARK,	/* Indicador com a extens�o do token corrente */
	SHORTMARK	/* Indicador de um caractere ('^') */

}	MARKTYPE;

/*
 ****************************************************************
 *	Estrutura de uma faixa					*
 ****************************************************************
 */
struct	range
{
	char	*r_begin,	/* Posi��o inicial da faixa */
		*r_end,		/* Posi��o final   da faixa */
		*r_line;	/* Posi��o do in�cio da linha onde
				   come�a a faixa */
	int	r_nline;	/* N�mero da linha onde come�a a faixa */
};
