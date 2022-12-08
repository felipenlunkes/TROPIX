|*
|****************************************************************
|*								*
|*			memccpy.s				*
|*								*
|*	Copia uma �rea at� encontrar um caractere		*
|*								*
|*	Vers�o	1.0.0, de 17.10.86				*
|*		2.3.1, de 14.04.91				*
|*								*
|*	M�dulo: memccpy						*
|*		libc/mem					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

|*
|****************************************************************
|*	Copia uma �rea at� encontrar um caractere		*
|****************************************************************
|*
|*	void *
|*	memccpy (void *dst, void *src, int carac, size_t nbytes)
|*
|*	dst   - �rea destino 
|*	src   - �rea origem
|*	carac - caractere
|*
	.globl	_memccpy

_memccpy:
	movl	4(sp),a1	|* dst
	movl	8(sp),a0	|* src
	movb	3+12(sp),d0	|* carac em d0
	movl	16(sp),d1	|* nbytes
	jeq	n�o_achou
	jra	teste
loop:
	movb	(a0)+,(a1)
	cmpb	(a1)+,d0
teste:
	dbeq	d1,loop		|* sai se achou ou nbytes
	jeq	achou
	subl	#0x00010000,d1
	jhs	loop
n�o_achou:
	moveq	#0,d0		|* N�o achou
	rts
achou:
	movl	a1,d0		|* retorna onde achou + 1
	rts
