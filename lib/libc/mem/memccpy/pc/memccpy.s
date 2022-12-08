|*
|****************************************************************
|*								*
|*			memccpy.s				*
|*								*
|*	Copia uma �rea de memoria at� um caratere dado		*
|*								*
|*	Vers�o	3.0.0, de 06.07.95				*
|*		3.0.0, de 06.07.95				*
|*								*
|*	M�dulo: memccpy						*
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
|*	Copia uma �rea de memoria at� um caratere dado		*
|****************************************************************
|*
|*	void	*memccpy (void *dst, const void *src, int c, size_t count);
|*
	.global	_memccpy
_memccpy:
	link	#0
	pushl	r5
	pushl	r4

	movl	8(fp),r5	|* "dst"
	movl	12(fp),r4	|* "src"
	movb	16(fp),r2	|* "c"
	movl	20(fp),r1	|* "count"

	up			|* C�pia de baixo para cima 
1$:
	cmpb	(r4),r2
	movsb
   |*** movb	(r4)+,(r5)+

	jeq	8$

	decl	r1
	jnz	1$

	clrl	r0		|* N�o achou
	jmp	9$
8$:
	movl	r5,r0
9$:
	popl	r4
	popl	r5
	unlk
	rts
