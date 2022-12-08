|*
|****************************************************************
|*								*
|*			getpgrp.s				*
|*								*
|*	Obtem a identifica��o do grupo de processos		*
|*								*
|*	Vers�o	3.0.0, de 14.08.95				*
|*		3.0.0, de 14.08.95				*
|*								*
|*	M�dulo: getpgrp						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

GETPGRP		= 66
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "getpgrp" *****************************
|*
|*	long	getpgrp (void);
|*
|*	Retorna = identificacao do grupo de processos
|*
	.global	_getpgrp
_getpgrp:
	movl	#GETPGRP,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
