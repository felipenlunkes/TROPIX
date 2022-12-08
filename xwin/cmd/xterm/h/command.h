/*
 ****************************************************************
 *								*
 *			h/command.h				*
 *								*
 *	Defini��es relativas ao m�dulo "command.c"		*
 *								*
 *	Vers�o	3.0.0, de 17.09.97				*
 *		4.8.0, de 18.03.05				*
 *								*
 *	M�dulo: programs/xterm					*
 *		X Windows - Clientes				*
 *		Baseado no software hom�nimo do XFree86		*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright (c) 2005 TROPIX Technologies Ltd.	*
 * 								*
 ****************************************************************
 */

#define menuBar_esc	10
#define scrollBar_esc	30

extern	int		exec_command (const char *[]);
extern	void		main_loop (void);
extern	void		stty_resize (void);
extern	void		cmd_printf (const char *, ...);
extern	void		cmd_write (const char *, unsigned int);
extern	FILE		*popen_printer (void);
extern	int		pclose_printer (FILE *);
