|*
|****************************************************************
|*								*
|*			div.s					*
|*								*
|*	Calcula o quociente e resto de uma divis�o inteira	*
|*								*
|*	Vers�o	3.0.0, de 27.6.95				*
|*		3.0.0, de 27.6.95				*
|*								*
|*	M�dulo: crt/div						*
|*		libc						*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*


|*
|******	Calcula o quociente e resto *****************************
|*/
	.text
	.global	_div, _ldiv
_div:
_ldiv:
	movl	4(sp),r0
	extlq
	divsl	8(sp)
	rts
