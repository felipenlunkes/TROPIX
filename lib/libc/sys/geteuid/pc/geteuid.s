|*
|****************************************************************
|*								*
|*			geteuid.s				*
|*								*
|*	Obtem a identificacao efetiva do usuario		*
|*								*
|*	Vers�o	3.0.0, de 07.01.95				*
|*		3.0.0, de 07.01.95				*
|*								*
|*	M�dulo: geteuid						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

GETUID		= 24
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "geteuid" *******************************
|*
|*	int	geteuid (void);
|*
|*	Retorna = Identifica��o efetiva do usu�rio.
|*
	.global	_geteuid
_geteuid:
	movl	#GETUID,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	movl	r1,r0
	rts
