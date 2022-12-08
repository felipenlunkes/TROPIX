|*
|****************************************************************
|*								*
|*			inout.s					*
|*								*
|*	Interface para ler/escrever de uma porta		*
|*								*
|*	Vers�o	1.0.0, de 02.01.98				*
|*								*
|*	M�dulo: hw/os/inout.s					*
|*		X-Windows - Servidor				*
|*		Baseado no Software Hom�nimo do XFree86		*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright (c) 1995 TROPIX Technologies Ltd.	*
|*								*
|****************************************************************
|*
	.seg32
	.text
|*
|****************************************************************
|*	L� um byte de uma porta					*
|****************************************************************
|*
|*	int
|*	inb (int portno);
|*
	.text
	.global	_inb

_inb:
	movl	4(sp),r2	|* No. do port
	clrl	r0
	inb	r2,r0		|* L� o byte
	rts
|*
|****************************************************************
|*	Escreve um byte em uma porta				*
|****************************************************************
|*
|*	void
|*	outb (int portno, int val);
|*
	.global	_outb

_outb:
	movl	4(sp),r2	|* No. do port
	movl	8(sp),r0	|* Valor
	outb	r0,r2		|* Escreve o byte
	rts
|*
|****************************************************************
|*	L� um "word" de uma porta				*
|****************************************************************
|*
|*	int
|*	inw (int portno);
|*
	.global	_inw
_inw:
	movl	4(sp),r2	|* No. do port
	clrl	r0
	inw	r2,r0		|* L� o short

	rts
|*
|****************************************************************
|*	Escreve um "word" em uma porta				*
|****************************************************************
|*
|*	void
|*	outw (int portno, int val);
|*
	.global	_outw
_outw:
	movl	4(sp),r2	|* No. do port
	movl	8(sp),r0	|* Valor
	outw	r0,r2		|* Escreve o short
	rts
|*
|****************************************************************
|*	L� um "long" de uma porta				*
|****************************************************************
|*
|*	long
|*	inl (int portno);
|*
	.global	_inl
_inl:
	movl	4(sp),r2	|* No. do port
	inl	r2,r0		|* L� o long
	rts
|*
|****************************************************************
|*	Escreve um "long" em uma porta				*
|****************************************************************
|*
|*	void
|*	outl (int portno, long val);
|*
	.global	_outl
_outl:
	movl	4(sp),r2	|* No. do port
	movl	8(sp),r0	|* Valor
	outl	r0,r2		|* Escreve o long
	rts
|*
|****************************************************************
|*	Habilita/Desabilita interrup��es			*
|****************************************************************
|*
|*	void
|*	xf86EnableInterrupts (void);
|*
|*	Bool
|*	xf86DisableInterrupts (void);
|*
|*	.global	_xf86EnableInterrupts, _xf86DisableInterrupts
|*
|*_xf86EnableInterrupts:
|*	enint
|*	rts
|*
|*_xf86DisableInterrupts:
|*	disint
|*	movl	#1,r0		|* Retorna "TRUE" (n�o sei para qu�)
|*	rts
|*
|****************************************************************
|*	Liga/desliga a flag de dire��o				*
|****************************************************************
|*
|*	void
|*	clear_direction_flag (void)
|*
|*	void
|*	set_direction_flag (void)
|*
	.global	_clear_direction_flag, _set_direction_flag

_clear_direction_flag:
	cld
	rts

_set_direction_flag:
	std
	rts
