|*
|****************************************************************
|*								*
|*			_exit.s					*
|*								*
|*	Termina um processo sem atualizar os "buffers"		*
|*								*
|*	Vers�o	1.0.0, de 12.01.86				*
|*		2.3.0, de 05.09.88				*
|*								*
|*	Modulo: _exit						*
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
|*	void
|*	_exit (status)
|*	int status;
|*
|*	Retorno: N�o h�
|*
	.global	__exit
 
EXIT = 1

__exit:
	moveq	#EXIT,d0
	movl	4(sp),a0
	trap	#0
