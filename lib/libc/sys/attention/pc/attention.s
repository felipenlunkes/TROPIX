|*
|****************************************************************
|*								*
|*			attention.s				*
|*								*
|*	Multiplexa��o de entrada s�ncrona			*
|*								*
|*	Vers�o	3.0.0, de 11.05.95				*
|*		3.0.1, de 28.07.97				*
|*								*
|*	M�dulo: attention					*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

ATTENTION	= 119
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "attention" *******************************
|*
|*	int	attention (int n, int vector, int index, int timeout);
|*
|*	extern int	_attention_index;
|*
|*	Retorna = >= 0: �ndice; Erro: -1
|*
	.global	_attention
_attention:
	movl	#ATTENTION,r0
	callgl	#SYS_CALL,0

	movl	r1,__attention_index

	tstl	r2
	jnz	syscall_error

	rts

|*
|*	Retorna o �ndice
|*
	.bss
	.global	__attention_index
__attention_index:
	.long	0
