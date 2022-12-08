|*
|****************************************************************
|*								*
|*			strntcmp.s				*
|*								*
|*	Compara duas cadeias dados comprimento e uma tabela	*
|*								*
|*	Vers�o	1.0.0, de 07.10.86				*
|*		2.3.1, de 15.04.91				*
|*								*
|*	Modulo: strntcmp					*
|*		libc/str					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Multiprocessado		*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

|*
|****************************************************************
|*	Compara duas cadeias dados comprimento e uma tabela	*
|****************************************************************
|*
|*	int
|*	strntcmp (char *s1, char *s2, size_t nbytes, char table[])
|*
	.global	_strntcmp

_strntcmp:
	movl	4(sp),a0	|* s1
	movl	8(sp),a1	|* s2

	moveml	#<a2,d2>,-(sp)	|* Preciso de mais 2 registros

	moveq	#0,d0		|* Zera a parte alta
	moveq	#0,d1

	cmpl	a0,a1		|* Se for a mesma �rea, ... (d0 == 0)
	jeq	exit

	movl	8+12(sp),d2	|* nbytes
	movl	8+16(sp),a2	|* Endere�o da tabela

	jra	teste		|* C�digos de condi��o de nbytes
loop:
	movb	(a0)+,d0	|* Prepara os caracteres
	movb	(a1)+,d1

	movb	0(a2,d0),d0	|* indexa a tabela e compara
	cmpb	0(a2,d1),d0

	jlo	menor
	jhi	maior

	tstb	d1		|* Verifica se chegou num '\0'
teste:
	dbeq	d2,loop
	jeq	desempata
	subl	#0x00010000,d2
	jhs	loop
desempata:
	moveml	(sp)+,#<a2,d2>
	jra	_strncmp	|* desempata pelo ASCII

menor:
	moveq	#-1,d0
	jra	exit
maior:
	moveq	#1,d0
exit:
	moveml	(sp)+,#<a2,d2>
	rts
