|*
|****************************************************************
|*								*
|*			umask.s					*
|*								*
|*	Obtem e modifica a mascara de cria��o de arquivos	*
|*								*
|*	Vers�o	3.0.0, de 05.01.95				*
|*		3.0.0, de 05.01.95				*
|*								*
|*	M�dulo: umask						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

UMASK		= 60
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "umask" ******************************
|*
|*	int	umask (int cmask);
|*
|*	Retorna = Sucesso: Valor antigo da mascara
|*
	.global	_umask
_umask:
	movl	#UMASK,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
