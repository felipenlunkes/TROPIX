|*
|****************************************************************
|*								*
|*			spy.s					*
|*								*
|*	Chama a rotina de instrumenta��o do n�cleo		*
|*								*
|*	Vers�o	3.0.0, de 05.01.95				*
|*		3.0.0, de 05.01.95				*
|*								*
|*	M�dulo: spy						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

SPY		= 100
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "spy" *******************************
|*
|*	int	spy (void);
|*
|*	Retorna = Sucesso: 0; Erro: -1
|*
	.global	_spy
_spy:
	movl	#SPY,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
