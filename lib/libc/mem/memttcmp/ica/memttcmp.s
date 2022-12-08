|*
|****************************************************************
|*								*
|*			memttcmp.s				*
|*								*
|*	Compara duas �reas de mem�ria dadas duas tabelas	*
|*								*
|*	Vers�o	1.0.0, de 07.10.86				*
|*		2.3.1, de 13.04.91				*
|*								*
|*	Modulo: memttcmp					*
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
|*	Compara duas �reas de mem�ria dadas duas tabelas	*
|****************************************************************
|*
|*	int
|*	memttcmp (const void *area1, const void *area2, size_t nbytes,
|*				char table[], char tabled[])
|*
	.global	_memttcmp

_memttcmp:
	moveml	#<a2,d2>,-(sp)	|* Preciso de mais 2 registros
desempate:
	movl	8+4(sp),a0	|* area1
	movl	8+8(sp),a1	|* area2

	cmpl	a0,a1		|* Se for a mesma �rea, ...
	jeq	igual

	moveq	#0,d0		|* Zera a parte alta
	moveq	#0,d1

	movl	8+12(sp),d2	|* nbytes
	movl	8+16(sp),a2	|* Endere�o da tabela

	jra	teste
loop:
	movb	(a0)+,d0	|* Prepara os caracteres
	movb	(a1)+,d1

	movb	0(a2,d0),d0	|* indexa a tabela e compara
	cmpb	0(a2,d1),d0

	jlo	menor
	jhi	maior
teste:
	dbra	d2,loop
	subl	#0x00010000,d2
	jhs	loop
fim:
	movl	8+20(sp),d0	|* Desempata com a segunda tabela
	clrl	8+20(sp)

	movl	d0,8+16(sp) 	|* Se n�o tem tabela de desempate, � igual
	jne	desempate
igual:
	moveq	#0,d0
	jra	exit
menor:
	moveq	#-1,d0
	jra	exit
maior:
	moveq	#1,d0
exit:
	moveml	(sp)+,#<a2,d2>
	rts
