/*
 ****************************************************************
 *								*
 *			common.h				*
 *								*
 *	Defini��es universais					*
 *								*
 *	Vers�o	1.0.0, de 19.09.92				*
 *		3.0.0, de 22.04.94				*
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
 ******	Macros �teis ********************************************
 */
#define	NULL	0
#define	NIL	(-1)
#define	NOSTR	(char *)NULL
#define	NOVOID	(void *)NULL

#define	elif	else if

#define	EVER	;;
#define STR(x)	# x
#define XSTR(x)	STR (x)

#undef	MAJOR
#undef	MINOR

#define	TESTPHASE	/* Verifica a igualdade dos r�tulos nos 2 passos */

/*
 ******	As diversas estruturas **********************************
 */
typedef	struct estack	ESTACK;
typedef	struct exp	EXP;
typedef	struct symbol	SYMTB;
typedef	struct opaddr	OPADDR;
typedef	struct instr	OPCODE;
typedef	struct opnd	OPND;
typedef	struct token	TOKEN;
typedef	enum errtype	ERRTYPE;
typedef	enum marktype	MARKTYPE;
typedef enum sdef	SDEF;
typedef	enum major	MAJOR;
typedef	struct lnotb	LNOTB;
typedef struct db	DBTB;
