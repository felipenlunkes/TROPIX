|*
|****************************************************************
|*								*
|*			strtok.s				*
|*								*
|*	Extra��o de "tokens" de uma cadeia			*
|*								*
|*	Vers�o	1.0.0, de 16.10.86				*
|*		3.0.0, de 08.02.94				*
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
|*	Extra��o de "tokens" de uma cadeia			*
|****************************************************************
|*
|*	char	*strtok (char *str, const char *sep)
|*
|*	str - cadeia com os tokens 
|*	sep - cadeia com os separadores de tokens
|*
	.globl	_strtok
_strtok:
	link	#0
	pushl	r5
	pushl	r4

	movl	8(fp),r4	|* "str"
   |***	movl	12(fp),r5	|* "sep"
	up			|* Sempre para cima

	tstl	r4		|* Verifica se � uma cadeia nova
	jne	1$

	movl	next_str,r4	|* � uma cadeia antiga
	tstl	r4
	jeq	no_token

|*
|******	Procura o in�cio do TOKEN *******************************
|*
1$:
	movl	12(fp),r5	|* Ponteiro para a cadeia de separadores

	lodsb			|* Pega um caractere de "str"
   |***	movb	(r4)+,r0
	tstb	r0
	jeq	no_token	|* fim de "str"
2$:
	cmpb	#0,(r5)		|* Testa o final dos separadores
	jeq	4$
	scasb			|* Compara o caractere com o separador
   |***	cmpb	r0,(r5)+
	jeq	1$		|* Se for separador, ...
	jmp	2$
4$:
	movl	r4,8(fp)	|* Guarda inicio do token + 1

|*
|******	Procura o final do TOKEN ********************************
|*
5$:
	movl	12(fp),r5	|* Ponteiro para a cadeia de separadores

	lodsb			|* Pega um caractere de "str"
   |***	movb	(r4)+,r0
	tstb	r0
	jne	6$

	clrl	next_str	|* Fim de "str": n�o tem proximo
	jmp	8$
6$:
	cmpb	#0,(r5)		|* Testa o final dos separadores
	jeq	5$
	scasb			|* Compara o caractere com o separador
   |***	cmpb	r0,(r5)+
	jne	6$		|* N�o � este separador

|*
|****** Achou o final do TOKEN **********************************
|*
	movl	r4,next_str	|* Prepara para a pr�xima chamada

	decl	r4		|* Marca o final do TOKEN
	clrb	(r4)
8$:
	movl	8(fp),r0	|* Retorna o in�cio do TOKEN
	decl	r0

	jmp	return

no_token:
	clrl	r0		|* "str" chegou ao fim
	movl	r0,next_str	|* N�o tem continua��o
return:
	popl	r4
	popl	r5
	unlk
	rts

|*
|******	�reas e dados *******************************************
|*
	.data
next_str:
	.long	0		|* Come�o do resto da cadeia
