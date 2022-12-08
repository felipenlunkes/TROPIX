/*
 ****************************************************************
 *								*
 *			sym.h					*
 *								*
 *	Estrutura da Tabela de S�mbolos				*
 *								*
 *	Vers�o	3.2.2, de 16.09.99				*
 *		3.2.3, de 17.01.00				*
 *								*
 *	M�dulo: SHELL						*
 *		Interpretador de Comandos			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Informa��es sobre s�mbolos				*
 ****************************************************************
 */
#define	NOSYMP		(SYM *)0

/*
 ****	Tipos de s�mbolos  **************************************
 */
typedef enum
{
	S_UNDEF,		/* Tipo indefinido */
	S_VAR,			/* Vari�vel do ambiente */
	S_FUNC,			/* Comando intr�nseco */
	S_PROG			/* Comando de programa��o */

}	STYPE;

/*
 ******	Valores para "s_flags" **********************************
 */
#define	V_ALL		0
#define	V_EXPORT	1
#define	V_READONLY	2
#define	V_PERMANENT	4

/*
 ******	Valores para "s_funcid" *********************************
 */
typedef	enum
{
	F_NOFUNC,

	F_CD,			/* "cd" */
	F_COLON,		/* ":" */
	F_DOT,			/* "." */

	F_EDIT_HIST,		/* "eh" (fun��es do hist�rico deve ficar juntas */
	F_EXEC_HIST,		/* "xh" */
	F_GRAPHIC_HIST,		/* "gh" */
	F_SHOW_HIST,		/* "h" */

	F_EXEC,			/* "exec" */
	F_EXIT,			/* "exit" */
	F_EXPORT,		/* "export" */
	F_EVAL,			/* "eval" */
	F_FALSE,		/* "false" */
	F_LOGIN,		/* "login" */
	F_LOGOUT,		/* "logout" */
	F_READ,			/* "read" */
	F_READONLY,		/* "readonly" */
	F_REHASH,		/* "rehash" */
	F_RETURN,		/* "return" */
	F_SET,			/* "set" */
	F_SHID,			/* "shid" */
	F_SHIFT,		/* "shift" */
	F_SPY,			/* "spy" */
	F_TIMES,		/* "times" */
	F_TRAP,			/* "trap" */
	F_TRUE,			/* "true" */
	F_UMASK,		/* "umask" */
	F_UNSET,		/* "unset" */
	F_WAIT			/* "wait" */

}	FUNCID;

/*
 ******	Valores para "s_progid" *********************************
 */
typedef	enum
{
	P_NOPROG,

	P_BREAK,		/* "break" */
	P_CASE,			/* "case" */
	P_CONTINUE,		/* "continue" */
	P_DO,			/* "do" */
	P_DONE,			/* "done" */
	P_ELIF,			/* "elif" */
	P_ELSE,			/* "else" */
	P_ESAC,			/* "esac" */
	P_FI,			/* "fi" */
	P_FOR,			/* "for" */
	P_IF,			/* "fi" */
	P_IN,			/* "in" */
	P_THEN,			/* "then" */
	P_TIME,			/* "time" */
	P_UNTIL,		/* "until" */
	P_WHILE,		/* "while" */
	P_ENDOPT		/* ";;" */

}	PROGID;

/*
 ******	Estrutura de informa��es sobre s�mbolos *****************
 */
typedef	struct sym	SYM;

struct	sym
{
	STYPE		s_type;		/* Tipo */
	char		s_name[32];	/* Identificador */

	int		s_union;	/* Pode ser: FUNCID, PROGID ou int */

	char		*s_value;	/* Valor da vari�vel */

	SYM		*s_next,	/* Pr�xima vari�vel */
			*s_prev;	/* Vari�vel anterior */

	SYM		*s_hnext;	/* Pr�ximo na cadeia de colis�es */
};

/*
 ******	Algumas abreviaturas ************************************
 */
#define	s_flags		s_union
#define	s_funcid	s_union
#define	s_progid	s_union

/*
 ****************************************************************
 *	A tabela hash						*
 ****************************************************************
 */
extern	SYM		*hashtb[];
extern	const int	hashsz;

/*
 ****************************************************************
 *	Vari�veis Importantes					*
 ****************************************************************
 */
extern	SYM	*home_sp,		/* Ponteiro para vari�vel HOME */
		*ps1_sp,		/* Ponteiro para vari�vel PS1 */
		*ps2_sp,		/* Ponteiro para vari�vel PS2 */
		*current_prompt,	/* Prompt corrente */
		*hist_sp,		/* Ponteiro para vari�vel HIST */
		*path_sp;		/* Ponteiro para vari�vel PATH */

/*
 ****************************************************************
 *	Fun��es relacionadas � Manipula��o da Tabela		*
 ****************************************************************
 */
extern	void	init_var_list (void);
extern	SYM	*define_variable_from_string (char *);
extern	SYM	*define_variable (const char *, const char *, int);
extern	int	set_variable_flag (const char *, int);
extern	SYM	*search_sym (const char *);
extern	SYM	*put_sym (const char *);
extern	int	delete_variable (const char *);
extern	void	show_variables (FILE *, int);
extern	int	show_environment (FILE *);
