|*
|****************************************************************
|*								*
|*			strlen.s				*
|*								*
|*	Obt�m o tamanho de uma cadeia				*
|*								*
|*	Vers�o	3.0.0, de 19.12.94				*
|*		3.0.0, de 19.12.94				*
|*								*
|*	M�dulo: strlen						*
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
|*	Obt�m o tamanho de uma cadeia				*
|****************************************************************
|*
|*	int 	strlen (const char *src);
|*
	.global	_strlen
_strlen:
	link	#0
	pushl	r5

	movl	8(fp),r5	|* "src"
	movl	#-1,r1		|* Maior valor poss�vel para o contador
	clrl	r0		|* Valor = 0

	up			|* Testa a cadeia
	repne
	scasb

	subl	8(fp),r5	|* Faz o c�lculo do tamanho
	movl	r5,r0
	decl	r0

	popl	r5
	unlk
	rts
