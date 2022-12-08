
|*
|****************************************************************
|*								*
|*			getppid.s				*
|*								*
|*	Obtem a identifica��o do pai do processo		*
|*								*
|*	Vers�o	1.0.0, de 15.01.86				*
|*		2.3.0, de 07.09.88				*
|*								*
|*	Modulo: getppid						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*
|*

|*
|*	int
|*	getppid ()
|*
|*	Retorna = identificacao do pai do processo.
|*
	.global	_getppid

GETPPID = 67

_getppid:
	moveq	#GETPPID,d0
	trap	#0
	rts
