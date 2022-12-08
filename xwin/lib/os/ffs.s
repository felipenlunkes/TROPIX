|*
|****************************************************************
|*								*
|*			ffs.s					*
|*								*
|*	Retorna o �ndice do primeiro bit n�o nulo		*
|*								*
|*	Vers�o	1.0.0, de 04.03.97				*
|*								*
|*	M�dulo: xc/lib/aux					*
|*		X Windows - Bibliotecas				*
|*		Baseado no software hom�nimo do XFree86		*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright (c) 1997 TROPIX Technologies Ltd.	*
|* 								*
|****************************************************************
|*
	.text
	.global	_ffs
|*
|*	ffs determina o �ndice do primeiro bit ligado no argumento
|*	fornecido. Os bits s�o numerados a partir de 1, do menos
|*	para o mais significativo.
|*
_ffs:
	bsfl	4(sp),r0
	jz	1$
	incl	r0		|* a numera��o come�a de 1
	ret

1$:	clrl	r0		|* o valor dado � nulo
	ret
