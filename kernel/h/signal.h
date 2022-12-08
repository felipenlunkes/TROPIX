/*
 ****************************************************************
 *								*
 *			<signal.h>				*
 *								*
 *	Signal handling						*
 *								*
 *	Vers�o	2.3.0, de 02.10.89				*
 *		4.4.0, de 28.11.02				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *		/usr/include/sys				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Defini��o de tipos					*
 ****************************************************************
 */
typedef int	sig_atomic_t;	/* Tipo indivis�vel */

/*
 ****************************************************************
 *	Constantes 						*
 ****************************************************************
 */
#define SIG_DFL	(void (*) (int, ...))0	/* A��o normal (cancela o processo) */
#define SIG_IGN	(void (*) (int, ...))1	/* Ignora o sinal */
#define SIG_ERR	(void (*) (int, ...))-1	/* Erro */

/*
 ****************************************************************
 *	Sinais							*
 ****************************************************************
 */
typedef enum
{
	SIGNULL,	/* Sem sinal */
	SIGHUP,		/* Hangup */
	SIGINT,		/* Interrupt (^C) */
	SIGQUIT,	/* Quit (FS) */
	SIGILL,		/* Instru��o Invalida */
	SIGTRAP,	/* Trace ou breakpoint */
	SIGIOT,		/* I/O Trap */
	SIGEMT,		/* Emulation Trap */
	SIGFPE,		/* Exce��o de ponto flutuante */
	SIGKILL,	/* Kill, morte inevitavel */
	SIGBUS,		/* Bus error */
	SIGSEGV,	/* Viola��o de segmenta��o (da gerencia de memoria) */
	SIGSYS,		/* Erro nos argumentos de um System Call */
	SIGPIPE,	/* Escrita em Pipe sem leitor */
	SIGALRM,	/* Alarm de Relogio */
	SIGTERM,	/* Sinal normal do Comando "Kill" */
	SIGADR,		/* Erro de Enderecamento */
	SIGDVZ,		/* Divisao por zero */
	SIGCHK,		/* Instru��o "check" */
	SIGTRPV,	/* Instru��o "trapv" */
	SIGVIOL,	/* Viola��o de Privilegio */
	SIGCHLD, 	/* Termino de um Filho */
	SIGABRT,	/* Syscall ABORT */
	SIGUSR1,	/* Sinal Reservado para o usuario (1) */
	SIGUSR2,	/* Sinal Reservado para o usuario (2) */
	SIGWINCH,	/* Mudan�a de tamanho da janela */

	SIG_LAST

}	SIG_ENUM;

#define	NSIG	(SIG_LAST-1)	/* NSIG < 32 */

/*
 ****************************************************************
 *	Prot�tipos das fun��es					*
 ****************************************************************
 */
extern void		(*signal (int, void (*) (int, ...))) (int, ...);
extern int		raise (int);
extern const char	*sigtostr (int);
