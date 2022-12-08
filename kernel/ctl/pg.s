|*
|****************************************************************
|*								*
|*			pg.s					*
|*								*
|*	Fun��es de ger�ncia de p�ginas				*
|*								*
|*	Vers�o	3.0.0, de 30.08.94				*
|*		3.0.0, de 18.01.95				*
|*								*
|*	M�dulo: N�cleo						*
|*		N�CLEO do TROPIX para PC			*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 1999 NCE/UFRJ - tecle "man licen�a"	*
|*								*
|****************************************************************
|*


|*
|****************************************************************
|*	Zera p�ginas						*
|****************************************************************
|*
|*	void	pgclr (pg_t pg_addr, int pg_cnt);
|*
	.globl	_pgclr
_pgclr:
	pushl	r5

	movl	4+4(sp),r5	|* pg_addr
	movl	8+4(sp),r1	|* pg_cnt

	tstl	r1
	jle	9$

	lsll	#PGSHIFT,r5
	lsll	#PGSHIFT-2,r1	|* Lembrar "long"

	clrl	r0
	up
	rep
	stosl
9$:
	popl	r5
	rts

|*
|****************************************************************
|*	Copia p�ginas						*
|****************************************************************
|*
|*	void	pgcpy (pg_t pg_dst, pg_t pg_src, int pg_cnt);
|*
	.globl	_pgcpy
_pgcpy:
	pushl	r5
	pushl	r4

	movl	4+8(sp),r5	|* pg_dst
	movl	8+8(sp),r4	|* pg_src
	movl	12+8(sp),r1	|* pg_cnt

	tstl	r1
	jle	9$

	lsll	#PGSHIFT,r5
	lsll	#PGSHIFT,r4
	lsll	#PGSHIFT-2,r1	|* Lembrar "long"

	cmpl	r4,r5		|* Verifica o sentido da c�pia
	jhi	5$

	up			|* C�pia de baixo para cima 
	jmp	8$
5$:
	down			|* C�pia de cima para baixo
	movl	r1,r0
	decl	r0
	lsll	#2,r0		|* Lembrar "long"
	addl	r0,r4
	addl	r0,r5
8$:
	rep
	movsl
9$:
	popl	r4
	popl	r5
	rts
