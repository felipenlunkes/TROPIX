/*
 ****************************************************************
 *								*
 *			scan.h					*
 *								*
 *	Defini��es relativas � an�lise l�xica			*
 *								*
 *	Vers�o	3.2.2, de 16.09.99				*
 *								*
 *	M�dulo: SHELL						*
 *		Interpretador de Comandos			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#ifdef	MAJOR		/* Evita conflitos com <sys/common.h> */
#undef	MAJOR
#endif	MAJOR

#define	VAR_SYMBOL	24
#define	CMD_SYMBOL	25

/*
 ****************************************************************
 *	Majors dos Tokens 					*
 ****************************************************************
 */
typedef	enum
{
	EOT,		/* Final de texto */
	EOL,		/* Final da linha */

	STRING,		/* Cadeia */
	DEFVAR,		/* Defini��o de vari�vel */
	PROG,		/* Comando de programa��o */

	REDIREC,	/* Redirecionamento */

	/*
	 *	Aten��o: a ordem dos conectores n�o pode ser alterada.
	 */
	BG,		/* & */
	SM,		/* ; */
	AND,		/* && */
	OR,		/* || */
	PIPE,		/* | */

	SMSM,		/* ;; */

	LP,		/* ( */
	RP,		/* ) */
	LC,		/* { */
	RC		/* } */

}	MAJOR;

/*
 ****************************************************************
 *	Estrutura de sa�da do Analisador L�xico			*
 ****************************************************************
 */
typedef	struct
{
	MAJOR	t_major;	/* Major do Token */

	int	t_nline;	/* N�mero da linha do token */

	char	*t_begin,	/* Coluna inicial do token na linha */
		*t_end;		/* Coluna final   do token na linha */

	char	*t_sval;	/* Se t_major == STRING */

	PROGID	t_progid;	/* Se t_major == PROG */

}	TOKEN;

/*
 ****************************************************************
 *	Vari�veis do Analisador L�xico				*
 ****************************************************************
 */
extern	TOKEN		token;
extern	FILE		*input_file;
extern	char		*lineread;
