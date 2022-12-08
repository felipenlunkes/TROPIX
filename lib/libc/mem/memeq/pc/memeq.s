|*
|****************************************************************
|*								*
|*			memeq.s					*
|*								*
|*	Compara �reas de memoria				*
|*								*
|*	Vers�o	3.0.0, de 07.04.95				*
|*		3.0.0, de 07.07.95				*
|*								*
|*	M�dulo: memeq						*
|*		libc/mem					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

|*
|****************************************************************
|*	Compara �reas de memoria				*
|****************************************************************
|*
|*	int	memeq (const void *dst, const void *src, size_t count);
|*
	.global	_memeq
_memeq:
	link	#0
	pushl	r5
	pushl	r4

	movl	8(fp),r5	|* "dst"
	movl	12(fp),r4	|* "src"
	movl	16(fp),r1	|* "count"

	clrl	r0		|* Por enquanto, n�o � igual

	up			|* Compara��o de baixo para cima 
	lsrl	#2,r1
	repe
	cmpsl

	jne	9$

	movl	16(fp),r1	|* Compara os 3 bytes restantes
	andl	#3,r1
	repe
	cmpsb

	jne	9$
	incl	r0		|* � igual
9$:
	popl	r4
	popl	r5
	unlk
	rts
