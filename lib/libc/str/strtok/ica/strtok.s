|*
|****************************************************************
|*								*
|*			strtok.s				*
|*								*
|*	Extra��o de tokens em uma cadeia			*
|*								*
|*	Vers�o	1.0.0, de 16.10.86				*
|*		2.3.0, de 05.12.88				*
|*								*
|*	M�dulo: strtok						*
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
|*	Extra��o de tokens em uma cadeia			*
|****************************************************************
|*
|*	char *
|*	strtok (char *cad, const char *sep)
|*
|*	cad - cadeia com os tokens 
|*	sep - cadeia com os separadores de tokens
|*
	.globl	_strtok

_strtok:
	movl	8(sp),d1	|* sep
	movl	4(sp),d0	|* cad
	movl	d0,a0		|* codigos de condi��o
	jne	loop1

	movl	prox,a0		|* resto de cad
	cmpl	#0,a0
	jeq	fim

loop1:
	movl	d1,a1		|* sep
	movb	(a0)+,d0	|* carac.de cad em d0
	jeq	fim		|* fim de cadeia

loop2:
	cmpb	(a1),d0
	jeq	loop1		|* � separador
	tstb	(a1)+
	jne	loop2		|* n�o � fim dos separadores

	movl	a0,4(sp)	|* guarda inicio do token + 1

loop3:
	movl	d1,a1		|* sep
	movb	(a0)+,d0	|* carac. de cad em d0
	jeq	sai0		|* fim de cadeia
	
loop4:
	cmpb	(a1),d0
	jeq	sai		|* � separador
	tstb	(a1)+
	jne	loop4		|* n�o � fim dos separadores
	jra	loop3		|* faz parte do token

sai0:
	movl	#0,prox		|* cad chegou ao fim
	jra	cont

sai:
	movb	#0,-(a0)	|* poe o nulo
	addql	#1,a0
	movl	a0,prox		|* prepara proxima chamada

cont:
	movl	4(sp),d0
	subql	#1,d0		|* retorna o ender. do token
	rts

fim:
	moveq	#0,d0		|* cad chegou ao fim
	movl	d0,prox		|* n�o tem proximo
	rts

	.data
prox:	.long	0
