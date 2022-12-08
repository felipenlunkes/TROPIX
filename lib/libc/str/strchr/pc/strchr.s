|*
|****************************************************************
|*								*
|*			strchr.s				*
|*								*
|*	Indica a primeira ocorr�ncia de um caractere		*
|*								*
|*	Vers�o	3.0.0, de 22.12.94				*
|*		3.0.6, de 23.03.97				*
|*								*
|*	M�dulo: strchr						*
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
|*	Indica a primeira ocorr�ncia de um caractere		*
|****************************************************************
|*
|*	char *
|*	strchr (const char *str, int carac)
|*
	.globl	_strchr
_strchr:
	link	#0
	pushl	r5

	movl	8(fp),r5	|* "str"
	movb	12(fp),r0	|* "carac"

	up

	tstb	r0		|* Verifica se "carac" � NULO
	jne	1$

|*
|*	Caso de "carac" NULO
|*
	movl	#-1,r1		|* Maior valor poss�vel para o contador

	repne			|* Procura o final da cadeia
	scasb

	jmp	7$

|*
|*	Caso de "carac" N�O NULO
|*
1$:
	cmpb	#0,(r5)
	jne	3$

	clrl	r0		|* N�o achou
	jmp	9$
3$:
	scasb			|* Procura o caracter
	jne	1$
7$:
	movl	r5,r0		|* Achou
	decl	r0
9$:
	popl	r5
	unlk
	rts
