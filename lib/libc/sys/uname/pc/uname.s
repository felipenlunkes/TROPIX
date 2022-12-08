|*
|****************************************************************
|*								*
|*			uname.s					*
|*								*
|*	Obtem a identifica��o do sistema			*
|*								*
|*	Vers�o	3.0.0, de 22.12.94				*
|*		3.0.0, de 22.12.94				*
|*								*
|*	M�dulo: uname						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

UNAME		= 71
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "uname" *******************************
|*
|*	int	uname (UTSNAME *name)
|*
|*	Retorna = Sucesso: 0; Erro: -1
|*
	.global	_uname
_uname:
	movl	#UNAME,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
