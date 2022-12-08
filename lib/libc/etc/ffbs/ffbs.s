|*
|****************************************************************
|*								*
|*			ffbs.s					*
|*								*
|*	Retorna o �ndice do primeiro bit n�o nulo		*
|*								*
|*	Vers�o	3.2.3, de 14.12.99				*
|*		3.2.3, de 26.12.99				*
|*								*
|*	M�dulo: ffbs						*
|*		lib/etc						*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 1999 NCE/UFRJ - tecle "man licen�a"	*
|*								*
|****************************************************************
|*

|*
|*	int ffbs (unsigned long value);
|*
|*	"ffbs" determina o �ndice do primeiro bit ligado no argumento
|*	fornecido. Os bits s�o numerados a partir de 0, do menos
|*	para o mais significativo. Se n�o houver bit algum, retorna -1
|*
	.text
	.global	_ffbs
_ffbs:
	bsfl	4(sp),r0
	jz	1$
	ret
1$:
	clrl	r0		|* O valor dado � nulo
	decl	r0		|* Retorna -1
	ret
