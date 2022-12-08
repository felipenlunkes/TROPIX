/*
 ****************************************************************
 *								*
 *			expr.h					*
 *								*
 *	Defini��es Acerca de Express�es				*
 *								*
 *	Vers�o	1.0.0, de 26.02.86				*
 *		3.0.0, de 26.02.94				*
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
 ******	Pilha de opera��es **************************************
 */
#define	ESTACKSZ	20		/* Profundidade Maxima da Stack */

/*** typedef	struct estack	ESTACK; ***/

struct estack
{
	long	e_value;		/* Operando */
	MINOR	e_opr;			/* Operador */
	short	e_type;			/* Tipo do Operando */
	short	e_prec;			/* Precedencia do Operador */
	SYMTB	*e_ref;			/* Operando � identificador */
};

/*
 ******	Estrutura de uma express�o ******************************
 */

/*** typedef	struct exp	EXP; ***/

struct exp
{
	char	*ex_begin;		/* Inicio da Express�o */
	char	*ex_end;		/* Fim da Express�o */
	long	ex_value;		/* Valor da Express�o */
	short	ex_type;		/* Tipo da Express�o */
	short	ex_nopnd;		/* N�mero de Operandos */
	SYMTB	*ex_ref;		/* Referencia a um Label (para SDI) */
	double	ex_rval;		/* Valor Real */
};

/*
 ******	M�scara sint�tica  **************************************
 */
#define	E_END		0x01		/* Fim da Express�o */
#define	E_LC		0x02		/* Abre-chave */
#define	E_RC		0x04		/* Fecha-chave */
#define	E_OPND		0x08		/* Operando */
#define	E_OPR		0x10		/* Operador */
#define	E_UNOPR		0x20		/* Operador Unario */
