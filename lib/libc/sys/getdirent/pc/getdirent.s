|*
|****************************************************************
|*								*
|*			getdirent.s				*
|*								*
|*	L� de um diret�rio com um formato independente		*
|*								*
|*	Vers�o	4.0.0, de 02.08.01				*
|*		4.8.0, de 05.11.05				*
|*								*
|*	M�dulo: getdirent					*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2005 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

GETDIRENT	= 80
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "getdirent" **************************
|*
|*	int	getdirent (int fd, void *area, int count, int *eof);
|*
|*	Retorna = Sucesso: bytes lidos (>= 0); Erro: -1
|*
	.global	_getdirent
_getdirent:
	movl	#GETDIRENT,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
