|*
|****************************************************************
|*								*
|*			gettzmin.s				*
|*								*
|*	Obt�m o fuso hor�rio, em minutos 			*
|*								*
|*	Vers�o	3.1.0, de 23.10.98				*
|*		3.1.0, de 23.10.98				*
|*								*
|*	M�dulo: gettzmin					*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

GETTZMIN	= 78
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "gettzmin" ***************************
|*
|*	int	gettzmin (void);
|*
|*	Obt�m o fuso hor�rio, em minutos
|*
	.global	_gettzmin
_gettzmin:
	movl	#GETTZMIN,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
