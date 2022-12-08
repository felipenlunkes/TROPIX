|*
|****************************************************************
|*								*
|*			sema.s					*
|*								*
|*	Obt�m sem�foros para o usu�rio				*
|*								*
|*	Vers�o	1.0.0, de 29.10.90				*
|*		2.3.0, de 29.10.90				*
|*								*
|*	Modulo: sema						*
|*		libc/sys					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|* 		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

|*
|*	#include <sys/types.h>
|*	#include <sys/usync.h>
|*
|*	int
|*	semactl (UEVENTCTLFUNC func, int fd, int arg1, int arg2)
|*
|*	func = US_ALLOC: arg1 = no. de sem�foros
|*	Retorna = Sucesso: 0; Erro: -1
|*
|*	func = US_GET:   arg1 = id. do sem�foro
|*			 arg2 = valor inicial
|*	Retorna = Sucesso: Descritor do sem�foro; Erro: -1
|*
	.global	_semactl, _errno
 
SEMACTL = 113

_semactl:
	movl	d2,-(sp)

	moveq	#SEMACTL,d0
	movl	8(sp),a0
	movl	12(sp),d1
	movl	16(sp),a1
	movl	20(sp),d2

	trap	#0
	jcc	1$

	movl	d0,_errno
	moveq	#-1,d0
1$:
	movl	(sp)+,d2
	rts

|*
|*	int
|*	semalock (int semadescr)
|*
|*	Retorna = Sucesso: No. de recursos ainda dispon�veis; Erro: -1
|*
	.global	_semalock, _errno
 
SEMALOCK = 114

_semalock:
	moveq	#SEMALOCK,d0
	movl	4(sp),a0

	trap	#0
	jcc	1$

	movl	d0,_errno
	moveq	#-1,d0
1$:
	rts

|*
|*	int
|*	semafree (int semadescr)
|*
|*	Retorna = Sucesso: No. de recursos dispon�veis; Erro: -1
|*
	.global	_semafree, _errno
 
SEMAFREE = 115

_semafree:
	moveq	#SEMAFREE,d0
	movl	4(sp),a0

	trap	#0
	jcc	1$

	movl	d0,_errno
	moveq	#-1,d0
1$:
	rts

|*
|*	int
|*	sematestl (int eventdescr)
|*
|*	Retorna = Sucesso: No. de recusos dispon�veis; Erro: -1
|*
	.global	_sematestl, _errno
 
SEMATESTL = 116

_sematestl:
	moveq	#SEMATESTL,d0
	movl	4(sp),a0

	trap	#0
	jcc	1$

	movl	d0,_errno
	moveq	#-1,d0
1$:
	rts

