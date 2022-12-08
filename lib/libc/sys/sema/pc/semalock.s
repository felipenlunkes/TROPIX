|*
|****************************************************************
|*								*
|*			semalock.s				*
|*								*
|*	Controle de sem�foros do usu�rio			*
|*								*
|*	Vers�o	3.0.0, de 13.08.95				*
|*		3.0.0, de 13.08.95				*
|*								*
|*	M�dulo: semalock					*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

SEMALOCK	= 114
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "semalock" ***************************
|*
|*	#include <sys/syscall.h>
|*	#include <unistd.h>
|*
|*	int	semalock (int semadescr);
|*
|*	Retorna = Sucesso: >= 0; Erro: -1
|*
	.global	_semalock
_semalock:
	movl	#SEMALOCK,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
