|*
|****************************************************************
|*								*
|*			sigchild.s				*
|*								*
|*	Prepara um processo para enviar o signal SIGHLD		*
|*								*
|*	Vers�o	3.0.0, de 14.05.95				*
|*		3.0.0, de 14.05.95				*
|*								*
|*	M�dulo: sigchild					*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

SIGCHILD	= 108
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "sigchild" *******************************
|*
|*	int	sigchild (void);
|*
|*	Retorna = sucesso: >= 0; erro: < 0
|*
	.global	_sigchild
_sigchild:
	movl	#SIGCHILD,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
