/*
 ****************************************************************
 *								*
 *			parm.h					*
 *								*
 *	Defini��es para a compila��o e execu��o das		*
 *	capacidades de cadeias de caracteres com par�metros	*
 *								*
 *	Vers�o	1.0.0, de 07.05.87				*
 *		3.0.0, de 22.03.95				*
 *								*
 *	Modulo: parm						*
 *		libcurses/terminfo				*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ******	Linguagem Fonte *****************************************
 */
#define	S_SPECIAL	'%'

/*
 *	Instru��es de sa�da formatada
 */
#define	SO_CHAR		'c'
#define	SO_DEC		'd'
#define	SO_OCTAL	'o'
#define	SO_HEX		'x'
#define	SO_CHEX		'X'

/*
 *	Instru��es de "push"
 */
#define	SP_PARM		'p'
#define	SP_CHAR1	'\''
#define	SP_CHAR2	'\''
#define	SP_DEC1		'{'
#define	SP_DEC2		'}'

/*
 *	Instru��es aritm�ticas
 */
#define	SA_ADD		'+'
#define	SA_MUL		'*'
#define	SA_SUB		'-'
#define	SA_DIV		'/'
#define	SA_MOD		'm'

/*
 *	Outras instru��es
 */
#define	S_INC		'i'

/*
 ******	Linguagem objeto ****************************************
 */
#define	T_END		0
#define	T_NULL		1
#define	T_NORMAL	2
#define	T_SPECIAL	3

/*
 *	Instru��es de sa�da formatada
 */
#define	TO_CHAR		4
#define	TO_DEC		5
#define	TO_OCTAL	6
#define	TO_HEX		7
#define	TO_CHEX		8

/*
 *	Instru��es de "push"
 */
#define	TP_PARM		9
#define	TP_CHAR		10
#define	TP_DEC		11

/*
 *	Instru��es aritm�ticas
 */
#define	TA_ADD		12
#define	TA_MUL		13
#define	TA_SUB		14
#define	TA_DIV		15
#define	TA_MOD		16

/*
 *	Outras instru��es
 */
#define	T_INC		17

/*
 ******	Outras defini��es ***************************************
 */
#define	PARMSZ	255

extern char	*_parmerror;	/* Mensagem de Erro */
extern char	*_parmptr;	/* Local do Erro */
extern char	*_parmrtn;	/* �rea[PARMSZ] para retorno das Fun��es */
