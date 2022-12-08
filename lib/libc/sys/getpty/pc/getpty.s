|*
|****************************************************************
|*								*
|*			getpty.s				*
|*								*
|*	Cria um canal entre processos				*
|*								*
|*	Vers�o	3.0.0, de 05.01.95				*
|*		3.0.0, de 05.01.95				*
|*								*
|*	M�dulo: getpty						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

GETPTY		= 87
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "getpty" *****************************
|*
|*	int	getpty (PTYPAIR *);
|*
|*	Retorna = Sucesso: 0; Erro: -1
|*
	.global	_getpty
_getpty:
	movl	#GETPTY,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
