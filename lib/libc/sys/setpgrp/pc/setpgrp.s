|*
|****************************************************************
|*								*
|*			setpgrp.s				*
|*								*
|*	Torna o processo um l�der de um grupo de processos	*
|*								*
|*	Vers�o	3.0.0, de 09.02.95				*
|*		3.0.0, de 09.02.95				*
|*								*
|*	M�dulo: setpgrp						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

SETPGRP		= 69
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "setpgrp" ****************************
|*
|*	int	setpgrp (void);
|*
|*	Retorna = ID do grupo
|*
	.global	_setpgrp
_setpgrp:
	movl	#SETPGRP,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
