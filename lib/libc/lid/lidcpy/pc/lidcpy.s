|*
|****************************************************************
|*								*
|*			lidcpy.s				*
|*								*
|*	Copia identificadores longos				*
|*								*
|*	Vers�o	1.0.0, de 27.10.86				*
|*		3.0.0, de 09.04.95				*
|*								*
|*	M�dulo: lidcpy						*
|*		libc/lid					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

|*
|****************************************************************
|*	Copia identificadores longos				*
|****************************************************************
|*
|*	int	lidcpy (idp_t id1, const idp_t id2);
|*
	.global	_lidcpy
_lidcpy:
	pushl	r5
	pushl	r4

	movl	12(sp),r5	|* "lid1"
	movl	16(sp),r4	|* "lid2"
	movl	#8,r1		|* 8 longos
	movl	r5,r0		|* O resultado � "lid1"

	up
	rep
	movsl

	popl	r4
	popl	r5
	rts
