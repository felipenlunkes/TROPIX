/*
 ****************************************************************
 *								*
 *			op_code.h				*
 *								*
 *	Estrutura da tabela de c�digos de operadores		*
 *								*
 *	Vers�o	1.0.00, de 17.09.92				*
 *		3.0.10, de 13.04.95				*
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


#define	NOFLAG		0	/* Nenhum indicador */

/*
 ******* Indicadores dos OPCODEs ********************************
 */
#define	IQ		0x01	/* Valor do operando imediato j� no passo 1 */
#define	NOSKIP		0x02	/* N�o pule mesmo dentro de ".if" falso */

/*
 ******* Indicadores dos endere�os ******************************
 */
#define	WP		0x01	/* Deve acrescentar 0x66 se 16 bits */
#define	LP		0x02	/* Deve acrescentar 0x66 se 32 bits */
#define	getOPND3	0x04	/* Obt�m o terceiro operando */
#define	WAITP		0x08	/* Deve 0x9B (wait para flutuante) */

/*
 ****** Tipos de Instru��es *************************************
 */
#define	I_REGULAR	0	/* Instru��o Regular */
#define	I_ANOMALOUS	1	/* Instru��o An�mala */
#define	I_PSEUDO	2	/* Pseudo-instru��o */
#define	I_PREFIX	3	/* Prefixo */
#define	I_FLOAT		4	/* Ponto Flutuante */

/*
 ******* Entrada da tabela de instrucoes ************************
 */
/*** typedef	struct instr	OPCODE; ***/

struct	instr
{
	char	o_name[SIDSZ+1];	/* Nome da instru��o */

	schar	o_type;			/* Tipo (regular, pseudo, ...) */
	schar	o_group;		/* N�mero do grupo da instru��o */
	short	o_flags;		/* Indicadores da instru��o */

	OPADDR	*o_begin;		/* Primeiro e �ltimo endere�amentos */
	OPADDR	*o_end;
	OPCODE	*o_link;		/* Cadeia de colis�es */
};

#define	NOOPCODE (OPCODE *)NULL

/*
 ******* Estrutura de um Padr�o: opcode + endere�amento *********
 */
/*** typedef	struct opaddr	OPADDR; ***/

struct opaddr
{
	char	o_opcode;	/* Codigo da instru��o */
	char	o_opexten;	/* Extens�o do opcode */
	char	o_group;	/* N�mero do grupo do endere�amento */
	char	o_flags;	/* Indicadores do endere�amento */

	ulong	o_opnd1;	/* Os dois operandos */
	ulong	o_opnd2;
};

#define	NOOPADDR (OPADDR *)NULL
