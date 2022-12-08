|*
|****************************************************************
|*								*
|*			mem.s					*
|*								*
|*	Fun��es de aloca��o, c�pia e atribui��o de mem�ria	*
|*								*
|*	Vers�o	3.0.0, de 03.07.94				*
|*		4.8.0, de 29.09.05				*
|*								*
|*	M�dulo: N�cleo						*
|*		N�CLEO do TROPIX para PC			*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2005 NCE/UFRJ - tecle "man licen�a"	*
|*								*
|****************************************************************
|*


|*
|****************************************************************
|*	Aloca uma �rea na pilha					*
|****************************************************************
|*
|*	void *alloca (size_t size);
|* 
	.global	_alloca
_alloca:
	movl	(sp),r1		|* Guarda o endere�o de retorno

	movl	4(sp),r0	|* r0 = Tamanho arredondado
	addl	#3,r0
	andb	#~3,r0

	subl	r0,sp 		|* sp = come�o da �rea - 4
	addl	#4,sp		|* Fun��o que chamou retira mais 4 bytes

	movl	sp,r0		|* r0 = come�o da �rea
	addl	#4,r0

|***	cmpb	#0,(r0)		|* For�a a aloca��o

	jmp	r1		|* Retorna

|*
|****************************************************************
|*	Fun��o de atribui��o de �reas de mem�ria (char)		*
|****************************************************************
|*
|*	void	memset (void *dst, char c, int count);
|*
	.global	_memset
_memset:
	link	#0
	pushl	r5

	movl	8(fp),r5	|* "dst"
	movl	12(fp),r0	|* "c"
	movl	16(fp),r1	|* "count"

	up
	rep
	stosb

	popl	r5
	unlk
	rts

|*
|****************************************************************
|*	Fun��o de atribui��o de �reas de mem�ria (short)	*
|****************************************************************
|*
|*	memsetw (short *dst, short w, int word_count);
|*
	.global	_memsetw
_memsetw:
	link	#0
	pushl	r5

	movl	8(fp),r5	|* "dst"
	movl	12(fp),r0	|* "w"
	movl	16(fp),r1	|* "count"

	up			|* Baixo para cima 
	rep
	stosw

	popl	r5
	unlk
	rts

|*
|****************************************************************
|*	Fun��o de atribui��o de �reas de mem�ria (long)		*
|****************************************************************
|*
|*	memsetl (long *dst, long l, int long_count);
|*
	.global	_memsetl
_memsetl:
	link	#0
	pushl	r5

	movl	8(fp),r5	|* "dst"
	movl	12(fp),r0	|* "l"
	movl	16(fp),r1	|* "count"

	up			|* Baixo para cima 
	rep
	stosl

	popl	r5
	unlk
	rts

|*
|****************************************************************
|*	Zera uma entrada de uma �rea ou estrutura		*
|****************************************************************
|*
|*	void	memclr (void *dst, int count);
|*
	.global	_memclr
_memclr:
	link	#0
	pushl	r5

	movl	8(fp),r5	|* "dst"
	movl	12(fp),r1	|* "count"
	clrl	r0		|* Valor = 0

	up			|* Atribui inicialmente longos
	lsrl	#2,r1
	rep
	stosl

	movl	12(fp),r1	|* Atribui os 3 bytes restantes
	andl	#3,r1
	rep
	stosb

	popl	r5
	unlk
	rts

.if 0	|*******************************************************|
|*
|****************************************************************
|*	Verifica se uma �rea est� zerada			*
|****************************************************************
|*
|*	int	memtst (void *dst, int count);
|*
	.global	_memtst
_memtst:
	link	#0
	pushl	r5

	movl	8(fp),r5	|* "dst"
	movl	12(fp),r1	|* "count"
	clrl	r0		|* Valor = 0

	up			|* Testa inicialmente longos
	lsrl	#2,r1
	repe
	scasl

	jne	3$

	movl	12(fp),r1	|* Testa os 3 bytes restantes
	andl	#3,r1
	repe
	scasb

	jeq	5$
3$:
	movl	#-1,r0
	jmp	9$
5$:
	clrl	r0
9$:
	popl	r5
	unlk
	rts
.endif	|*******************************************************|

|*
|****************************************************************
|*	Compara �reas de memoria				*
|****************************************************************
|*
|*	int	memeq (const void *dst, const void *src, size_t count);
|*
	.global	_memeq
_memeq:
	link	#0
	pushl	r5
	pushl	r4

	movl	8(fp),r5	|* "dst"
	movl	12(fp),r4	|* "src"
	movl	16(fp),r1	|* "count"

	clrl	r0		|* Por enquanto, n�o � igual

	up			|* Compara��o de baixo para cima 
	lsrl	#2,r1
	repe
	cmpsl

	jne	9$

	movl	16(fp),r1	|* Compara os 3 bytes restantes
	andl	#3,r1
	repe
	cmpsb

	jne	9$
	incl	r0		|* � igual
9$:
	popl	r4
	popl	r5
	unlk
	rts

|*
|****************************************************************
|*	Compara �reas de memoria sem considerar as caixas	*
|****************************************************************
|*
|*	int	memnocaseeq (const void *dst, const void *src, size_t count);
|*
	.global	_memnocaseeq
_memnocaseeq:
	link	#0
	pushl	r5
	pushl	r4
	pushl	r3

	movl	8(fp),r5		|* "dst"
	movl	12(fp),r4		|* "src"
	movl	16(fp),r1		|* "count"
	movl	#_uppertolower,r3	|* "tb"

	cmpl	r4,r5		|* Se for a mesmas cadeia, ...
	jeq	7$

	clrl	r0		|* Zera a parte alta
	clrl	r2

	up			|* De baixo para cima 
2$:
	lodsb			|* Obt�m os caracteres
   |***	movb	(r4)+,r0
   	movb	(r5),r2
	incl	r5
   |***	movb	(r5)+,r2

	movb	(r3,r0),r0	|* Compara um caractere
	cmpb	(r3,r2),r0
	jne	8$

	decl	r1
	jne	2$
7$:
	clrl	r0		|* "str2" == "str2" =>	retorna 1
	incl	r0
	jmp	9$

8$:
	clrl	r0		|* "str2" != "str2" =>	retorna 0
9$:
	popl	r3
	popl	r4
	popl	r5
	unlk
	rts
