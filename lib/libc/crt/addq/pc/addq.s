|*
|****************************************************************
|*								*
|*			qadd.s					*
|*								*
|*	Soma de 64 bits						*
|*								*
|*	Vers�o	4.4.0, de 29.10.02				*
|*		4.4.0, de 29.10.02				*
|*								*
|*	M�dulo: qadd						*
|*		libc/crt					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

|*
|******	Soma de 64 bits *****************************************
|*
|*	long long  ___adddi3 (long long a, long long b);
|*
	.text
	.global	___adddi3
___adddi3:
	movl	12(sp),r0
	addl	4(sp),r0

	movl	16(sp),r2
	adcl	8(sp),r2

	rts
