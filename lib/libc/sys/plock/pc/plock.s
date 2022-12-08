|*
|****************************************************************
|*								*
|*			plock.s					*
|*								*
|*	Mantem/libera um processo na mem�ria interna		*
|*								*
|*	Vers�o	3.0.0, de 18.08.95				*
|*		3.0.0, de 18.08.95				*
|*								*
|*	M�dulo: plock						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

PLOCK		= 97
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "plock" ******************************
|*
|*	int	plock (int flag);
|*
|*	Retorna = Sucesso: 0; Erro: -1
|*
	.global	_plock
_plock:
	movl	#PLOCK,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
