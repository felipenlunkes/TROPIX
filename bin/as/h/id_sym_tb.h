/*
 ****************************************************************
 *								*
 *			id_sym_tb.h				*
 *								*
 *	Estrutura da tabela de s�mbolos				*
 *								*
 *	Vers�o	1.0.0, de 28.01.86				*
 *		3.0.6, de 04.09.94				*
 *								*
 *	M�dulo: AS-68000/10/20/30				*
 *		Tradutores					*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Multiprocessado		*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****** Defini��es gerais **************************************
 */
#define	NOSYMTB		(SYMTB *)NULL

#define	LABSZ		30

/*
 ****** Elemento da tabela de s�mbolos **************************
 */
/*** typedef	struct symbol	SYMTB; ***/

struct symbol
{
	SYMTB		*s_next;	/* Pr�xima defini��o */
	SYMTB		*s_def;		/* Pr�xima defini��o */
	short		s_line;		/* Linha em que foi definido */
	short		s_index;	/* N�mero do Simbolo */
	double		s_rval;		/* Valor Real */
	SYMTB		*s_link;	/* Lista de colis�o */
	SYM		s;		/* S�mbolo */
};

/*
 ****** Tipo da busca *******************************************
 */

/*** typedef enum sdef	SDEF; ***/

enum sdef { S_DEFINE, S_SEARCH };

/*
 ****** Tipos De Simbolos (usados somente pelo assembler) *******
 */
#define	CONST	0x05		/* Pseudo-se��o ".const" */
#define	ERR	0x0A		/* Erro em Express�o */
#define	REAL	0x0B		/* Express�o tem valor Real */

/*
 ****** Vetor auxiliar para alinhamento dos r�tulos *************
 */
extern SYMTB	*labtb[], **labp;
