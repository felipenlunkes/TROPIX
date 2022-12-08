/*
 ****************************************************************
 *								*
 *			extern.h				*
 *								*
 *	Declara��o de vari�veis					*
 *								*
 *	Vers�o	3.0.0, de 29.04.97				*
 *		3.0.1, de 30.04.97				*
 *								*
 *	M�dulo: EX/VI						*
 *		Editores de texto				*
 *		Categoria D					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ******	Vari�veis globais ***************************************
 */
extern const char	pgversion[];

extern char		Line[];
extern char		dos_mode;	/* Modo DOS (<cr><nl>) */
extern char		*nextp;
extern char		*Search;	/* Aut�mato para Busca */
extern char		*Esearch;	/* Express�o regular para Busca */
extern bool		Interruption;	/* Houve uma interrup��o */
extern char		*System;	/* �ltimo comando para o Shell */
extern bool		Verbose;
extern bool		Mdebug;
extern bool		Debug;
extern const char	*error_msg;	/* Mensagens de Erro */
extern char		temp_buffer[];	/* Buffer tempor�rio para uso geral */
extern char		Message[80];	/* Mensagem pendente */

extern char		*_end_match;	/* Primeiro caracter na linha ap�s a express�o */

extern char		*M_txtio;	/* Mensagem correspondente a TXTIO */
extern const char	int_tab[];
extern const char	obj_tab[];
extern bool		Redo;		/* Repetindo a �ltima Edi��o */
extern int		LINES, COLS;	/* N�mero de linhas/colunas */

#ifdef	H_SCAN
extern TOKEN		token;
#endif	H_SCAN

#ifdef	H_CURSES
extern WINDOW		*Win;		/* Janela onde ocorre a edi��o */
#endif	H_CURSES

#ifdef	H_TEXT
extern TEXT		*Text;		/* Texto em Edi��o */
#endif	H_TEXT

#ifdef	H_COMMANDS
extern COMM		*Comm;		/* Informa��es sobre o Texto em edi��o */
#endif	H_COMMANDS

#ifdef	H_VISUAL
extern VIEW		*View;		/* Estado da Edi��o Visual */
#endif	H_VISUAL
