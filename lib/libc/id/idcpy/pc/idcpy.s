|*
|****************************************************************
|*								*
|*			idcpy.s					*
|*								*
|*	Copia identificadores					*
|*								*
|*	Vers�o	1.0.0, de 27.10.86				*
|*		3.0.0, de 09.01.95				*
|*								*
|*	M�dulo: idcpy						*
|*		libc/id						*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

|*
|****************************************************************
|*	Copia identificadores					*
|****************************************************************
|*
|*	idp_t	idcpy (idp_t id1, const idp_t id2);
|*
	.global	_idcpy
_idcpy:
	pushl	r5
	pushl	r4

	movl	12(sp),r5	|* "id1"
	movl	16(sp),r4	|* "id2"
	movl	#4,r1		|* 4 longos
	movl	r5,r0		|* O resultado � "id1"

	up
	rep
	movsl

	popl	r4
	popl	r5
	rts
