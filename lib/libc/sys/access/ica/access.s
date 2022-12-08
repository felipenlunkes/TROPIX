|*
|****************************************************************
|*								*
|*			access.s				*
|*								*
|*	Informa sobre a permiss�o de acesso a um arquivo	*
|*								*
|*	Vers�o	1.0.0, de 05.01.87				*
|*		2.3.0, de 02.09.88				*
|*								*
|*	M�dulo: access						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*


|*
|*	ret = access (path, mode)
|*	char	*path;
|*	int	mode;
|*
|*	ret =  0 => Acesso � permitido
|*	ret = -1 => Nao � permitido,  ver errno.
|*
	.global	_access, _errno
 
ACCESS = 33

_access:
	moveq	#ACCESS,d0
	movl	4(sp),a0
	movl	8(sp),d1

	trap	#0
	jcc	1$

	movl	d0,_errno
	moveq	#-1,d0
1$:
	rts
