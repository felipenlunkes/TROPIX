|*
|****************************************************************
|*								*
|*			cmpsq.s					*
|*								*
|*	Compara��o com sinal de 64 bits				*
|*								*
|*	Vers�o	4.4.0, de 31.10.02				*
|*		4.4.0, de 31.10.02				*
|*								*
|*	M�dulo: cmpsq						*
|*		libc/crt					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2002 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

|*
|******	Compara��o com sinal de 64 bits	*************************
|*
|*	int _cmpsq (long long a, long long b);
|*
	.text
	.global	___cmpdi2
___cmpdi2:
	movl	#1,r0

	movl	16(sp),r2
	cmpl	8(sp),r2
	jle	2$
1$:
	decl	r0			|* A parte � maior
	rts
2$:
	jeq	5$			|* Desvia se a parte alta � igual
3$:
	incl	r0			|* A parte � menor
	rts
5$:
	movl	12(sp),r2		|* As partes altas s�o iguais
	cmpl	4(sp),r2		|* Compara as partes baixas
	jne	6$
	rts				|* Igual: retorna com 1
6$:
	jhi	1$			|* A parte � maior
	jmp	3$			|* A parte � menor
