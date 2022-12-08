|*
|****************************************************************
|*								*
|*			lidclr.s				*
|*								*
|*	Zera um identificador longo				*
|*								*
|*	Vers�o	2.1.0, de 20.01.87				*
|*								*
|*	Rotinas:						*
|*		lidclr						*
|*								*
|*	M�dulo: lidclr						*
|*		libc/lid					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

|*
|****************************************************************
|*	Zera um Identificador longo				*
|****************************************************************
|*
|*	idp_t
|*	lidclr (lid)
|*	idp_t	lid;
|*
	.global	_lidclr

_lidclr:
	movl	4(sp),a0	|* lid
	movl	a0,d0

	clrl	(a0)+		|* Zera os 32 bytes
	clrl	(a0)+
	clrl	(a0)+
	clrl	(a0)+

	clrl	(a0)+
	clrl	(a0)+
	clrl	(a0)+
	clrl	(a0)

	rts
