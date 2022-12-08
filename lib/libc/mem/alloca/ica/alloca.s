|*
|****************************************************************
|*								*
|*			alloca.s				*
|*								*
|*	Aloca uma �rea na pilha de execu��o			*
|*								*
|*	Vers�o	2.3.0, de 26.10.89				*
|*		2.3.1, de 26.12.90				*
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
	movl	(sp),a0		|* Guarda o endere�o de retorno

	movl	4(sp),d0	|* d0 = Tamanho arredondado
	addql	#3,d0
	andw	#~3,d0

	subl	d0,sp 		|* sp = come�o da �rea - 4
	addql	#4,sp		|* Fun��o que chamou retira mais 4 bytes

	movl	sp,d0		|* d0 = come�o da �rea
	addql	#4,d0

	movl	d0,a1		|* For�a a aloca��o
	tstw	(a1)

	jmp	(a0)		|* Retorna
