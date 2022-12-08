|*
|****************************************************************
|*								*
|*			exit.s					*
|*								*
|*	Termina um programa com atualiza��o dos "buffers"	*
|*								*
|*	Vers�o	1.0.0, de 12.01.86				*
|*		2.3.0, de 05.09.88				*
|*								*
|*	Modulo: exit						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

|*
|*	void
|*	exit (status)
|*	int status;
|*
|*	Retorno = N�o h�
|*

	.global	_exit, __cleanup

EXIT = 1

_exit:
	jsr	__cleanup

	moveq	#EXIT,d0
	movl	4(sp),a0
	trap	#0
