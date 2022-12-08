|*
|****************************************************************
|*								*
|*			strlen.s				*
|*								*
|*	Obt�m o tamanho de uma cadeia				*
|*								*
|*	Vers�o	1.0.0, de 07.10.86				*
|*		2.3.0, de 05.12.88				*
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
|*	int
|*	strlen (const char *src)
|*
	.global	_strlen

_strlen:
	movl	4(sp),a0
	movl	a0,d0		|* Guarda cad

loop:
	tstb	(a0)+
	jne	loop

	subl	d0,a0		|* Ve a diferenca
	movl	a0,d0
	subql	#1,d0		|* Tira o nulo

	rts
