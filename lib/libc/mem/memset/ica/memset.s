|*
|****************************************************************
|*								*
|*			memset.s				*
|*								*
|*	Preenche uma �rea com um caractere			*
|*								*
|*	Vers�o	1.0.0, de 17.10.86				*
|*		2.3.1, de 13.04.91				*
|*								*
|*	Modulo: memset						*
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
|*	Preenche uma �rea com um caractere			*
|****************************************************************
|*
|*	void *
|*	memchr (void *area, int carac, size_t nbytes)
|*
|*	area   - �rea de memoria 
|*	carac  - caractere a ser escrito
|*	nbytes - tamanho da �rea
|*
	.global	_memset

_memset:
	movl	4(sp),a0	|* �rea
	movb	3+8(sp),d0	|* carac em d0
	movl	12(sp),d1	|* nbytes
	jra	teste
loop:
	movb	d0,(a0)+
teste:
	dbra	d1,loop		|* sai se terminou
	subl	#0x00010000,d1
	jhs	loop
sai:
	movl	4(sp),d0	|* retorna �rea
	rts
