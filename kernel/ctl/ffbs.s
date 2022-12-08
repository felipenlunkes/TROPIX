|*
|****************************************************************
|*								*
|*			ffbs.s					*
|*								*
|*	Retorna o �ndice do primeiro bit n�o nulo		*
|*								*
|*	Vers�o	1.0.0, de 04.03.97				*
|*		3.2.3, de 19.12.99				*
|*								*
|*	M�dulo: N�cleo						*
|*		N�CLEO do TROPIX para PC			*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 1999 NCE/UFRJ - tecle "man licen�a"	*
|*								*
|****************************************************************
|*

|*
|*	"ffbs" determina o �ndice do primeiro bit ligado no argumento
|*	fornecido. Os bits s�o numerados a partir de 0, do menos
|*	para o mais significativo. Se n�o houver nenhum, retorna -1
|*
	.text
	.global	_ffbs
_ffbs:
	bsfl	4(sp),r0
	jz	bad
	ret
bad:
	clrl	r0		|* O valor dado � nulo
	decl	r0		|* Retorna -1
	ret

|*
|****************************************************************
|*	Calcula o "log2", usando a instru��o "bsfl"		*
|****************************************************************
|*
	.text
	.global	_log2
_log2:
	bsfl	4(sp),r0
	jz	bad

	movl	#1,r2
	movl	r0,r1
	lsll	r1,r2
	cmpl	r2,4(sp)
	jne	bad

	ret
