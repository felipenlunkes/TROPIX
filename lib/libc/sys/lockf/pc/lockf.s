|*
|****************************************************************
|*								*
|*			lockf.s					*
|*								*
|*	Gerencia LOCKs em regi�es de arquivos			*
|*								*
|*	Vers�o	3.0.0, de 16.08.95				*
|*		3.0.0, de 16.08.95				*
|*								*
|*	M�dulo: lockf						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

LOCKF	 	= 56
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "lockf" ******************************
|*
|*	int	lockf (int fd, int mode, int size);
|*
|*	Retorna = Sucesso: 0; Erro: -1
|*
	.global	_lockf
_lockf:
	movl	#LOCKF,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
