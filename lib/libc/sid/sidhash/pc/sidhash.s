|*
|****************************************************************
|*								*
|*			sidhash.s				*
|*								*
|*	Calcula um n�mero hash para um identificador longo	*
|*								*
|*	Vers�o	1.0.0, de 17.10.86				*
|*		3.0.0, de 04.07.95				*
|*								*
|*	M�dulo: sidhash						*
|*		libc/sid					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

|*
|****************************************************************
|*	Calcula um n�mero hash para um identificador longo	*
|****************************************************************
|*
|*	int
|*	sidhash (idp_t id, int size)
|*
	.global	_sidhash
_sidhash:
	movl	4(sp),r1	|* Endere�o de sid

	movl	 0(r1),r0	|* Out�rio dos 2 longos 
	eorl	 4(r1),r0

BIG_ENDIAN = 0
.if	BIG_ENDIAN
	xchgb	r0,h0		|* Usa "big endian"
	rorl	#16,r0
	xchgb	r0,h0
.endif	BIG_ENDIAN

	clrl	r2
	divul	8(sp),r0
	movl	r2,r0

	rts
