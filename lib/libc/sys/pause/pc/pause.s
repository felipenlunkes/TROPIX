|*
|****************************************************************
|*								*
|*			pause.s					*
|*								*
|*	Suspende o processo at� a ocorrencia de um sinal	*
|*								*
|*	Vers�o	3.0.0, de 01.01.95				*
|*		3.0.0, de 01.01.95				*
|*								*
|*	M�dulo: pause						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

PAUSE		= 29
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "pause" *******************************
|*
|*	int	pause (void);
|*
|*	Retorna = Erro: -1
|*
	.global	_pause
_pause:
	movl	#PAUSE,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
