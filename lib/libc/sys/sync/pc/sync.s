|*
|****************************************************************
|*								*
|*			sync.s					*
|*								*
|*	Atualiza o conte�do do disco				*
|*								*
|*	Vers�o	3.0.0, de 06.01.95				*
|*		3.0.0, de 06.01.95				*
|*								*
|*	M�dulo: sync						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

SYNC		= 36
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "sync" *******************************
|*
|*	int	sync (void);
|*
|*	Retorna = Sucesso: 0; Erro: -1
|*
	.global	_sync
_sync:
	movl	#SYNC,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
