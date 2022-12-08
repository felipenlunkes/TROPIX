|*
|****************************************************************
|*								*
|*			boot.s					*
|*								*
|*	Reinicializa o computador				*
|*								*
|*	Vers�o	3.0.0, de 01.09.97				*
|*		3.0.0, de 01.09.97				*
|*								*
|*	M�dulo: boot						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

BOOT		= 77
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "boot" *******************************
|*
|*	int	boot (void);
|*
|*	Reinicializa o computador; s� retorna em caso de erro
|*
	.global	_boot
_boot:
	movl	#BOOT,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
