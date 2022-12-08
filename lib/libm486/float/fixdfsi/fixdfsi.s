|*
|****************************************************************
|*								*
|*			fixdfsi.s				*
|*								*
|*	Obt�m a parte inteira de um n�mero flutuante		*
|*								*
|*	Vers�o	3.0.0, de 14.07.95				*
|*		3.0.0, de 14.07.95				*
|*								*
|*	M�dulo: fixdfsi						*
|*		/lib/libm486					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

|*
|****************************************************************
|*	Converte um n�mero flutuante em inteiro			*
|****************************************************************
|*
|*	int	__fixdfsi (double a);
|*
	.global	___fixdfsi
___fixdfsi:
	fldd	4(sp)
	fistpl	-4(sp)		|* ou "fistl" ?
	movl	-4(sp),r0
	rts
