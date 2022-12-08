/*
 ****************************************************************
 *								*
 *			scan.h					*
 *								*
 *	Defini��es Usadas Pelo Analisador L�xico		*
 *								*
 *	Vers�o	1.0.0, de 05.08.88				*
 *		4.1.0, de 22.08.01				*
 *								*
 *	M�dulo: CPP						*
 *		Tradutores					*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2001 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Defini��es Gerais					*
 ****************************************************************
 */
#undef	MAJOR
#undef	MINOR

#define elif		else if
#define	EVER		;;
#define	NIL		(-1)
#define	FALSE		0
#define	TRUE		1

#define	MACSZ		32768	/* Tamanho geral para expans�es */

#define	ARGSZ		32

#define	CARG		0x80	/* Argumento normal de macro */
#define	CSTR		0x81	/* Argumento do tipo "# x" */
#define	CGLUE		0x82	/* Argumento do tipo "## x ou x ##" */

/*
 ****************************************************************
 *	Diretivas						*
 ****************************************************************
 */
typedef	enum
{
	IF,				/* Diretiva if */
	ELIF,				/* Diretiva elif */
	ENDIF,				/* Diretiva endif */
	IFDEF,				/* Diretiva ifdef */
	IFNDEF,				/* Diretiva ifndef */
	ELSE,				/* Diretiva else */
	INCLUDE,			/* Diretiva include */
	DEFINE,				/* Diretiva define */
	UNDEF,				/* Diretiva undef */
	LINE,				/* Diretiva line */
	ERROR,				/* Diretiva error */
	PRAGMA				/* Diretiva pragma */

}	DIRECT;

/*
 ****************************************************************
 *	Macros Intr�nsecas					*
 ****************************************************************
 */
typedef	enum
{
	_LINE,
	_FILE,
	_DATE,
	_TIME,
	_DEFINED,
	_STDC

}	BUILTIN;

/*
 ****************************************************************
 *	"Majors" dos Tokens					*
 ****************************************************************
 */
typedef	enum
{
	NOTOKEN,			/* Token Nulo */

	EOFILE,				/* Fim do Arquivo */
	EOL,				/* Fim de Linha */

	ID,				/* Identificador */
	ICTE,				/* Constante Inteira */
	RCTE,				/* Constante Real */
	STR,				/* Cadeia */

	LP,				/* '(' */
	RP,				/* ')' */
	CM,				/* ',' */

	OP,				/* Operadores */

	STROP,				/* '#' */
	GLUEOP				/* '##' */

}	MAJOR;

/*
 ****************************************************************
 *	"Minors" dos Tokens					*
 ****************************************************************
 *
 *	Especifica qual das v�rias alternativas de um Major.
 *	Este valor � retornado em token.l_minor.
 */
typedef	enum
{
	/*
	 *	Minor de Majors sem op��es.
	 */
	N_NULL	=	-1,

	/*
	 *	Minor de Operadores
	 */
	N_OROR,			/* || */
	N_ANDAND,		/* && */
	N_OR,			/* | */
	N_XOR,			/* ^ */
	N_AND,			/* & */
	N_EQ,			/* == */
	N_NE,			/* != */
	N_LT,			/* < */
	N_LE,			/* <= */
	N_GT,			/* > */
	N_GE,			/* >= */
	N_RIGHT,		/* >> */
	N_LEFT,			/* << */
	N_PLUS,			/* + */
	N_MINUS,		/* - */
	N_MUL,			/* * */
	N_DIV,			/* / */
	N_MOD,			/* % */
	N_NOT,			/* ~ */
	N_NEG			/* ! */

}	MINOR;

/*
 ****************************************************************
 *	Estrutura Retornada pelo Analisador L�xico		*
 ****************************************************************
 */
typedef	struct
{
	MAJOR		l_major;	/* Major do Token */
	MINOR		l_minor;	/* Minor do Token */

	const char	*l_begin,	/* Coluna inicial do token na linha */
			*l_end;		/* Coluna final do token na linha */

	long		l_line;		/* Numero da linha do token */

	long		l_ival;		/* Valor Inteiro */

	const char	*l_name;	/* Identificador */
	int		l_nm_len;	/* Comprimento do Identificador */

}	TOKEN;

/*
 ****************************************************************
 *	Vari�veis do Analisador L�xico				*
 ****************************************************************
 */
extern TOKEN		token;		/* Token Atual */

extern const char	*program,	/* O Programa Fonte */
			*endprogram,	/* Fim do Programa */
			*nextp;		/* Pr�ximo Caractere a ser Processado */

extern MAJOR		scan ();	/* O Analisador L�xico */

extern int		lineno,		/* N�mero da Linha Corrente */
			lineout;	/* N�mero da Linha na Sa�da */

extern int		macdef[];	/* Para agilizar o acesso � "symtb" */

extern int		eof_state;	/* O que fazer com EOF: 1 => pula */

/*
 ****************************************************************
 *	Prot�tipos						*
 ****************************************************************
 */
extern MAJOR	getapost (void);
extern MAJOR	getid (void);
extern MAJOR	getnum (const char *);
extern MAJOR	getstr (void);
extern MAJOR	scan (void);
extern int	maccmp (const char *, const char *, MINOR);
