|*
|****************************************************************
|*								*
|*			memcmp.s				*
|*								*
|*	Compara duas �reas de mem�ria				*
|*								*
|*	Vers�o	1.0.0, de 09.10.86				*
|*		2.3.1, de 13.04.91				*
|*								*
|*	M�dulo: memcmp						*
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
|*	Compara duas �reas de mem�ria				*
|****************************************************************
|*
|*	int
|*	memcmp (const void *area1, const void *area2, size_t nbytes)
|*
	.global	_memcmp

_memcmp:
	movl	4(sp),a0	|* area1
	movl	8(sp),a1	|* area2

	cmpl	a0,a1		|* Se for a mesma �rea, ...
	jeq	igual

	movl	12(sp),d1	|* nbytes
	jra	teste
loop:
	cmpmb	(a1)+,(a0)+
	jlo	menor
	jhi	maior
teste:
	dbra	d1,loop
	subl	#0x00010000,d1
	jhs	loop
igual:
	moveq	#0,d0
	rts
menor:
	moveq	#-1,d0
	rts
maior:
	moveq	#1,d0
	rts
