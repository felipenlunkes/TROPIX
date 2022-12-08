|*
|****************************************************************
|*								*
|*			setpgrp.s				*
|*								*
|*	Torna o processo um l�der de um grupo de processos	*
|*								*
|*	Vers�o	1.0.0, de 22.01.87				*
|*		2.3.0, de 09.09.88				*
|*								*
|*	Modulo: setpgrp						*
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
|*	setpgrp ()
|*
|*	Retorna = ID do grupo
|*
	.global	_setpgrp

SETPGRP = 69

_setpgrp:
	moveq	#SETPGRP,d0
	trap	#0
	rts
