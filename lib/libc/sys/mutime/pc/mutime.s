|*
|****************************************************************
|*								*
|*			mutime.s				*
|*								*
|*	Obtem o tempo com microsegundos		 		*
|*								*
|*	Vers�o	3.0.0, de 05.01.95				*
|*		3.0.0, de 05.01.95				*
|*								*
|*	M�dulo: mutime						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

MUTIME		= 102
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "mutime" *******************************
|*
|*	int	mutime (MUTM *mp);
|*
|*	Retorna = Sucesso: 0; Erro: -1
|*
	.global	_mutime
_mutime:
	movl	#MUTIME,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
