|*
|****************************************************************
|*								*
|*			fix.s					*
|*								*
|*	Pr�logo para programas em "C"				*
|*								*
|*	Vers�o	1.0.0, de 25.11.86				*
|*		3.0.0, de 13.12.94				*
|*								*
|*	M�dulo: fix						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

|*
|****** Convers�o de "double" em "int"	*************************
|*
	.global	___fixdfsi
___fixdfsi:
	clrl	r0
	rts

|*
|****** Convers�o de "double" em "int"	*************************
|*
	.global	___fixunsdfsi
___fixunsdfsi:
	clrl	r0
	rts

|*
|****** Soma valor ao expoente **********************************
|*
	.global	_ldexp
_ldexp:
	fldd	4(sp)
	rts
