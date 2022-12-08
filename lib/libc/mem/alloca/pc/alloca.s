|*
|****************************************************************
|*								*
|*			alloca.s				*
|*								*
|*	Aloca uma �rea na pilha de execu��o			*
|*								*
|*	Vers�o	3.0.0, de 29.01.95				*
|*		3.0.0, de 29.01.95				*
|*								*
|*	Modulo: alloca						*
|*		libc/mem					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

|*
|*	void *
|*	alloca (size)
|*	size_t	size;
|* 
|*	Retorno: Sucesso: Endere�o da �rea (!=0); Erro: 0
|* 
	.global	_alloca
_alloca:
	movl	(sp),r1		|* Guarda o endere�o de retorno

	movl	4(sp),r0	|* r0 = Tamanho arredondado
	addl	#3,r0
	andb	#~3,r0

	subl	r0,sp 		|* sp = come�o da �rea - 4
	addl	#4,sp		|* Fun��o que chamou retira mais 4 bytes

	movl	sp,r0		|* r0 = come�o da �rea
	addl	#4,r0

	cmpb	#0,(r0)		|* For�a a aloca��o

	jmp	r1		|* Retorna
