|*
|****************************************************************
|*								*
|*			eventtest.s				*
|*								*
|*	Obt�m o n�mero do �ltimo evento de usu�rio ocorrido	*
|*								*
|*	Vers�o	3.0.0, de 13.08.95				*
|*		3.0.0, de 13.08.95				*
|*								*
|*	M�dulo: eventtest					*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

EVENTTEST	= 112
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "eventtest" ***************************
|*
|*	#include <sys/ipc.h>
|*	#include <sys/syscall.h>
|*
|*	int	eventtest (int eventdescr);
|*
|*	Retorna = Sucesso: N�mero do evento mais recente; Erro: -1
|*
	.global	_eventtest
_eventtest:
	movl	#EVENTTEST,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
