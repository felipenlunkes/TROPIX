|*
|****************************************************************
|*								*
|*			setjmp.s				*
|*								*
|*	"Goto" N�o local					*
|*								*
|*	Vers�o	1.0.0, de 11.11.86				*
|*		2.3.0, de 25.11.88				*
|*								*
|*	M�dulo: setjmp						*
|*		libc/etc					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

 
|*
|****************************************************************
|*	Prepara o Desvio					*
|****************************************************************
|*
	.globl	_setjmp
 
_setjmp:
	movl	4(sp),a0

	movl	(sp),(a0)
	moveml	#<a2-a7,d2-d7>,4(a0)

	clrl	d0
	rts

|*
|****************************************************************
|*	Desvia							*
|****************************************************************
|*
	.globl	_longjmp
 
_longjmp:
	movl	4(sp),a0

	movl	8(sp),d0
	jne	1$

	moveq	#1,d0
1$:
	moveml	4(a0),#<a2-a7,d2-d7>

	movl	(a0),(sp)
	rts
