|*
|****************************************************************
|*								*
|*			strrchr.s				*
|*								*
|*	Obt�m a �ltima ocorr�ncia de um caractere		*
|*								*
|*	Vers�o	1.0.0, de 17.10.86				*
|*		2.3.0, de 05.12.88				*
|*								*
|*	M�dulo: strrchr						*
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
|*	Obt�m a �ltima ocorr�ncia de um caractere		*
|****************************************************************
|*
|*	char *
|*	strrchr (const char *cad, int carac)
|*
|*	cad   - cadeia 
|*	carac - caractere a ser pesquisado
|*
	.global	_strrchr

_strrchr:
	movl	4(sp),a0	|* cad
	movb	3+8(sp),d1	|* carac em d1

	moveq	#0,d0		|* prepara retorno

loop:
	cmpb	(a0),d1
	jeq	achou		|* achou igual

	tstb	(a0)+
	jne	loop		|* n�o � fim de cad

	rts

achou:
	movl	a0,d0		|* guarda onde achou

	tstb	(a0)+		|* se n�o era nulo continua
	jne	loop

	rts
