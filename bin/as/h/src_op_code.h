/*
 ****************************************************************
 *								*
 *			src_op_code.h				*
 *								*
 *	Estrutura da tabela de c�digos de operadores fonte	*
 *								*
 *	Vers�o	1.0.0, de 17.09.92				*
 *		3.0.6, de 03.09.94				*
 *								*
 *	M�dulo: AS-80386/486/PENTIUM				*
 *		Tradutores					*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****** Elemento da tabela de opcodes fonte *********************
 */
#define	MAX_ADDR	12		/* N�mero m�ximo de endere�os */
#define	MAX_NAME	5		/* N�mero m�ximo de nomes */

typedef	struct
{
	char	o_name[MAX_NAME][SIDSZ+1];

	schar	o_type;			/* Tipo (regular, pseudo, ...) */
	schar 	o_group;		/* No. do grupo da instru��o */
	schar 	o_flags;		/* Indicadores */
	schar	o_pri;			/* Prioridade */

	OPADDR	o_a[MAX_ADDR];		/* Padr�es de endere�amento */

}	SRC_OPCODE;
