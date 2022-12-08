|*
|****************************************************************
|*								*
|*			memchr.s				*
|*								*
|*	Procura um caractere em uma �rea			*
|*								*
|*	Vers�o	3.0.0, de 06.07.95				*
|*		3.0.0, de 06.07.95				*
|*								*
|*	M�dulo: memchr						*
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
|*	Procura um caractere em uma �rea			*
|****************************************************************
|*
|*	void	*memchr (void *str, int c, size_t count);
|*
	.global	_memchr
_memchr:
	link	#0
	pushl	r5

	movl	8(fp),r5	|* "str"
	movb	12(fp),r0	|* "c"
	movl	16(fp),r1	|* "count"

	up			|* C�pia de baixo para cima 
1$:
	scasb
   |*** cmpb	(r5)+,r0

	jeq	8$

	decl	r1
	jnz	1$

	clrl	r0		|* N�o achou
	jmp	9$
8$:
	movl	r5,r0		|* Achou
	decl	r0
9$:
	popl	r5
	unlk
	rts
