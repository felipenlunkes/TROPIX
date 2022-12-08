|*
|****************************************************************
|*								*
|*			shmem.s					*
|*								*
|*	Obt�m regi�es de mem�ria compartilhada para o usu�rio	*
|*								*
|*	Vers�o	3.0.0, de 21.08.95				*
|*		3.1.5, de 05.12.98				*
|*								*
|*	M�dulo: shmem						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

SHMEM		= 117
SYS_CALL	= { 6 * 8 + 3 }

|*
|******	Chamada ao sistema "shmem" ******************************
|*
|*	#include <sys/syscall.h>
|*	#include <sys/unistd.h>
|*
|*	int	shmem (int fd, int size);
|*
|*	Retorna = Sucesso: Endere�o virtual da regi�o; Erro: -1
|*
	.global	_shmem
_shmem:
	movl	#SHMEM,r0
	callgl	#SYS_CALL,0

	tstl	r2
	jnz	syscall_error

	rts
