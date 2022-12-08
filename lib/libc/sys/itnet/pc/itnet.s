|*
|****************************************************************
|*								*
|*			itnet.s					*
|*								*
|*	Executa uma fun��o da INTERNET				*
|*								*
|*	Vers�o	3.0.0, de 11.05.95				*
|*		3.0.0, de 11.05.95				*
|*								*
|*	M�dulo: itnet						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

ITNET		= 124
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "itnet" *******************************
|*
|*	int	itnet (int fd, int cmd, int arg1, int arg2)
|*
|*	Retorna = Sucesso: >= 0; Erro: -1
|*
	.global	_itnet
_itnet:
	movl	#ITNET,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
