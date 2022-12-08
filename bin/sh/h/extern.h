/*
 ****************************************************************
 *								*
 *			extern.h				*
 *								*
 *	Vari�veis Globais					*
 *								*
 *	Vers�o	3.2.2, de 16.09.99				*
 *		4.5.0, de 10.10.03				*
 *								*
 *	M�dulo: SHELL						*
 *		Interpretador de Comandos			*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2003 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ******	Em "src/exec.c" *****************************************
 */
extern	int		sonsignaled;

extern	int		last_bg_pid,	/* PID do �ltimo cmd em background */
			last_cmd_code;	/* Valor de retorno do �ltimo comando */

/*
 ******	Em "src/hist.c" *****************************************
 */
extern	int		hist_max;	/* Tamanho m�ximo do hist�rico */
extern	char		HISTMAX[];	/* Cadeia contendo o tam. m�ximo */
extern	int		last_cmd;	/* N�mero do �ltimo comando */

/*
 ******	Em "src/parse.c" ****************************************
 */
extern	int		in_command;	/* Analisando um comando */
extern	int		nesting;	/* N�vel de aninhamento */

/*
 ******	Em "src/scan.c" *****************************************
 */
extern	TOKEN		token;		/* Token corrente */

extern	char		*linebuf,
			*line;

extern	int		nline;
extern	int		lineprinted;
extern	int		line_read;	/* A linha j� foi lida */

/*
 ******	Em "src/sh.c" *******************************************
 */
extern	const char	pgversion[];	/* Vers�o do Programa */

extern	int		exit_code;	/* C�digo de retorno */

extern	int		dflag,		/* Sai com Control-D */
			quick_exit,	/* Termina se der erro em comando */
			rewriting,	/* Verifica a reescrita */
			vflag;		/* Verboso */

extern	int		script,		/* Executando arquivo de comandos */
			interact;	/* Interativa */

extern	int		my_pid,		/* PID da Shell */
			user_id;	/* UID */

extern	int		max_fd;		/* N�mero m�ximo de FD's */

extern	int		npospar;	/* N�mero de Par�metros Posicionais */
extern	const char	*pospar[];	/* Par�metros Posicionais */

extern	int		ignore_signals;		/* Ignora INT, QUIT e TERM */
extern	const char	*trap[];		/* Comandos associados ao sinais */
extern	void		(*sig[]) (int, ...);	/* Estados antigos dos sinais */

extern	char		*current_wd;	/* Nome do diret�rio corrente */
