|*
|****************************************************************
|*								*
|*			streq.s					*
|*								*
|*	Testa a igualdade de cadeias				*
|*								*
|*	Vers�o	1.0.0, de 20.10.86				*
|*		2.3.0, de 05.12.88				*
|*								*
|*	M�dulo: streq						*
|*		libc/str					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

|*
|****************************************************************
|*	Testa a igualdade de cadeias				*
|****************************************************************
|*
|*	int
|*	streq (const char *src, const char *dst)
|*
|*	devolve  1 se src � igual a dst, ou 0, caso contrario
|*
	.global	_streq

_streq:
	movl	4(sp),a0
	movl	8(sp),a1

	cmpl	a0,a1		|* s�o uma mesma cadeia
	jeq	igual
loop:
	movb	(a0)+,d0
	cmpb	(a1)+,d0
	jne	dif

	tstb	d0
	jne	loop
igual:
	moveq	#1,d0
	rts
dif:
	moveq	#0,d0
	rts
