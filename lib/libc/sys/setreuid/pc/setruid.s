|*
|****************************************************************
|*								*
|*			setruid.s				*
|*								*
|*	Atribui o RUID do processo				*
|*								*
|*	Vers�o	3.0.0, de 20.08.95				*
|*		3.0.0, de 20.08.95				*
|*								*
|*	M�dulo: setruid						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

SETREUID	 = 73
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "setruid" ****************************
|*
|*	int	setruid (int ruid);
|*
|*	Retorna = Sucesso: 0; Erro: -1
|*
	.global	_setruid
_setruid:
	movl	4(sp),r0	|* Salva o RUID
	pushl	#-1		|* O EID == -1 (n�o muda)
	pushl	r0		|* Prepara o RUID
	pushl	r0		|* Coloca um endere�o de retorno fict�cio

	movl	#SETREUID,r0
	callgl	#SYS_CALL,0

	popl	r1		|* Retira o endere�o de retorno fict�cio
	popl	r1		|* Retira o RUID
	popl	r1		|* Retira o -1

	tstl	r2
	jnz	syscall_error

	rts
