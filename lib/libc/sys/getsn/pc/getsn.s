|*
|****************************************************************
|*								*
|*			getsn.s					*
|*								*
|*	Obtem o n�mero de s�rie da m�quina			*
|*								*
|*	Vers�o	3.0.0, de 03.02.95				*
|*		3.0.0, de 14.08.95				*
|*								*
|*	M�dulo: getsn						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

GETSN		= 101
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "getsn" ******************************
|*
|*	int	getsn (void);
|*
|*	Retorna = Sucesso: o n�mero de s�rie; Erro: -1
|*
	.global	_getsn
_getsn:
	movl	#GETSN,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
