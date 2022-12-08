/*
 ****************************************************************
 *								*
 *			<sys/kcntl.h>				*
 *								*
 *	Controle dos Processos e Threads			*
 *								*
 *	Vers�o	1.0.0, de 03.07.91				*
 *		3.2.0, de 06.05.99				*
 *								*
 *	M�dulo: N�cleo						*
 *		N�CLEO do TROPIX para PC			*
 *		/usr/include/sys				*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 * 		Copyright � 1999 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

/*
 ****************************************************************
 *	Comandos do PCNTL					*
 ****************************************************************
 */
typedef enum
{
	P_PMUTIMES = 1,		/* Obt�m tempos estimados de proc. paralelo */
	P_GETSTKRGSZ,		/* Obt�m o tamanho da regi�o de stack */
	P_SETSTKRGSZ,		/* Aumenta o tamanho da regi�o de stack */	
	P_GETPRI,		/* Obt�m a prioridade moment�nea do processo */
	P_SETPRI,		/* Altera a prioridade moment�nea do processo */
	P_SETRTPROC,		/* Transforma o proc. em proc. de tempo real */
	P_SETFPREGADDR,		/* Indica o end. de usu. dos regs fp de soft */
	P_ENABLE_USER_IO,	/* Permite o usu�rio ler/escrever nas portas */
	P_DISABLE_USER_IO,	/* Impede o usu�rio de ler/escrever nas portas */
	P_GET_PHYS_ADDR		/* Obt�m um endere�o f�sico */

}	PENUM;
