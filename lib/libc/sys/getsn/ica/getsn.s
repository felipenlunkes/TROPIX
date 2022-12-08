|*
|****************************************************************
|*								*
|*			getsn.s					*
|*								*
|*	Obtem o n�mero de s�rie da m�quina/sist. oper.		*
|*								*
|*	Vers�o	1.0.0, de 19.06.86				*
|*		2.3.0, de 07.09.88				*
|*								*
|*	Modulo: getsn						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

|*
|*	int
|*	getsn ()
|*
|*	Retorna = n�mero de s�rie
|*
	.global	_getsn
 
GETSN = 101
 
_getsn:
	moveq	#GETSN,d0
	trap	#0
	rts
