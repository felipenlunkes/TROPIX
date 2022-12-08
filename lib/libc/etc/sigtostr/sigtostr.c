/*
 ****************************************************************
 *								*
 *			sigtostr.c				*
 *								*
 *	Obt�m a descri��o simb�lica de um sinal			*
 *								*
 *	Vers�o	1.0.0, de 17.10.86				*
 *		4.4.0, de 18.11.02				*
 *								*
 *	M�dulo:	sigtostr 					*
 *		libc/etc					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include <signal.h>

/*
 ****************************************************************
 *	Tabela dos sinais					*
 ****************************************************************
 */
static const char * const sigstr[] =
{
    /* 0 */	"SIGNULL: Sinal NULO",
    /* 1 */	"SIGHUP:  Hangup",
    /* 2 */	"SIGINT:  Interrup��o",
    /* 3 */	"SIGQUIT: Quit",
    /* 4 */	"SIGILL:  Instru��o inv�lida",
    /* 5 */	"SIGTRAP: Trace ou breakpoint",
    /* 6 */	"SIGIOT:  Exce��o IOT",
    /* 7 */	"SIGEMT:  Exce��o EMT",
    /* 8 */	"SIGFPE:  Exce��o de ponto flutuante",
    /* 9 */	"SIGKILL: KILL, t�rmino inevit�vel",
    /* 10 */	"SIGBUS:  Bus error",
    /* 11 */	"SIGSEGV: Viola��o de segmenta��o",
    /* 12 */	"SIGSYS:  Erro nos argumentos de uma chamada ao sistema",
    /* 13 */	"SIGPIPE: Escrita em \"pipe\" sem leitor",
    /* 14 */	"SIGALRM: Alarme de rel�gio",
    /* 15 */	"SIGTERM: Sinal normal de t�rmino",
    /* 16 */	"SIGADR:  Erro de endere�amento",
    /* 17 */	"SIGDVZ:  Divis�o por ZERO",
    /* 18 */	"SIGCHK:  Instru��o \"check\"",
    /* 19 */	"SIGTRPV: Instru��o \"trapv\"",
    /* 20 */	"SIGVIOL: Viola��o de privil�gio",
    /* 21 */	"SIGCHLD: T�rmino de um filho",
    /* 22 */	"SIGABRT: Chamado ao sistema \"abort\"",
    /* 23 */	"SIGUSR1: Sinal reservado para o usu�rio",
    /* 24 */	"SIGUSR2: Sinal reservado para o usu�rio",
    /* 25 */	"SIGWINCH: Mudan�a do tamanho da janela"
};

/*
 ****************************************************************
 *	Ponto de entrada da fun��o				*
 ****************************************************************
 */
const char *
sigtostr (int signum)
{
	if (signum >= 0 && signum <= NSIG)
		return (sigstr[signum]);

	return ("Sinal desconhecido");

}	/* end sigtostr */
