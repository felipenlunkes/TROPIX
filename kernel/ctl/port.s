|*
|****************************************************************
|*								*
|*			port.s					*
|*								*
|*	Interface para ler/escrever de uma porta		*
|*								*
|*	Vers�o	3.0.0, de 26.06.94				*
|*		3.0.0, de 08.05.96				*
|*								*
|*	M�dulo: N�cleo						*
|*		N�CLEO do TROPIX para PC			*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 1999 NCE/UFRJ - tecle "man licen�a"	*
|*								*
|****************************************************************
|*

	.seg32

|*
|****************************************************************
|*	L� um byte de uma porta					*
|****************************************************************
|*
|*	int
|*	read_port (int portno);
|*
	.text
	.global	_read_port

_read_port:
	inb	#IO_NOP,r0	|* Espera um pouco
	inb	#IO_NOP,r0

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
|*	write_port (int val, int portno);
|*
	.global	_write_port

_write_port:
	inb	#IO_NOP,r0	|* Espera um pouco
	inb	#IO_NOP,r0

	movl	4(sp),r0	|* Valor
	movl	8(sp),r2	|* No. do port

	outb	r0,r2		|* Escreve o byte

	rts

|*
|****************************************************************
|*	L� um "word" de uma porta				*
|****************************************************************
|*
|*	int
|*	read_port_short (int portno);
|*
	.global	_read_port_short
_read_port_short:
	inb	#IO_NOP,r0	|* Espera um pouco
	inb	#IO_NOP,r0

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
|*	write_port_short (int val, int portno);
|*
	.global	_write_port_short
_write_port_short:
	inb	#IO_NOP,r0	|* Espera um pouco
	inb	#IO_NOP,r0

	movl	4(sp),r0	|* Valor
	movl	8(sp),r2	|* No. do port

	outw	r0,r2		|* Escreve o short

	rts

|*
|****************************************************************
|*	L� um "long" de uma porta				*
|****************************************************************
|*
|*	long
|*	read_port_long (int portno);
|*
	.global	_read_port_long
_read_port_long:
	inb	#IO_NOP,r0	|* Espera um pouco
	inb	#IO_NOP,r0

	movl	4(sp),r2	|* No. do port

	inl	r2,r0		|* L� o long

	rts

|*
|****************************************************************
|*	Escreve um "long" em uma porta				*
|****************************************************************
|*
|*	void
|*	write_port_long (long val, int portno);
|*
	.global	_write_port_long
_write_port_long:
	inb	#IO_NOP,r0	|* Espera um pouco
	inb	#IO_NOP,r0

	movl	4(sp),r0	|* Valor
	movl	8(sp),r2	|* No. do port

	outl	r0,r2		|* Escreve o long

	rts

|*
|****************************************************************
|*	L� um byte do CMOS 					*
|****************************************************************
|*
|*	int
|*	read_cmos (int addr);
|*
	.text
	.global	_read_cmos

_read_cmos:
	movl	4(sp),r0	|* Endere�o
	outb	r0,#0x70

	clrl	r0
	inb	#0x71,r0	|* L� o byte

	rts

|*
|****************************************************************
|*	L� uma seq��ncia de "longs" de uma porta		*
|****************************************************************
|*
|*	void
|*	read_port_string_long (int portno, void *area, int long_count);
|*
	.global	_read_port_string_long
_read_port_string_long:
	pushl	r5

	movl	8(sp),r2	|* No. do port
	movl	12(sp),r5	|* Area
	movl	16(sp),r1	|* Long_count

	up

	rep
	insl

	popl	r5
	rts

|*
|****************************************************************
|*	Escreve uma seq��ncia de "longs" em uma porta		*
|****************************************************************
|*
|*	void
|*	write_port_string_long (int portno, void *area, int long_count);
|*
	.global	_write_port_string_long
_write_port_string_long:
	pushl	r4

	movl	8(sp),r2	|* No. do port
	movl	12(sp),r4	|* Area
	movl	16(sp),r1	|* Long_count

	up

	rep
	outsl

	popl	r4
	rts

|*
|****************************************************************
|*	L� uma seq��ncia de "words" de uma porta		*
|****************************************************************
|*
|*	void
|*	read_port_string_short (int portno, void *area, int short_count);
|*
	.global	_read_port_string_short
_read_port_string_short:
	pushl	r5

	movl	8(sp),r2	|* No. do port
	movl	12(sp),r5	|* Area
	movl	16(sp),r1	|* Short_count

	inb	#IO_NOP,r0	|* Espera um pouco
	inb	#IO_NOP,r0

	up

	rep
	insw

|*	outb	r0,#0x80	|* Delay (?!!)

	popl	r5
	rts

|*
|****************************************************************
|*	Escreve uma seq��ncia de "words" em uma porta		*
|****************************************************************
|*
|*	void
|*	write_port_string_short (int portno, void *area, int short_count);
|*
	.global	_write_port_string_short
_write_port_string_short:
	pushl	r4

	movl	8(sp),r2	|* No. do port
	movl	12(sp),r4	|* Area
	movl	16(sp),r1	|* Short_count

	up

	rep
	outsw

	outb	r0,#0x80	|* Delay (?!!)

	popl	r4
	rts

|*
|****************************************************************
|*	L� uma seq��ncia de bytes de uma porta			*
|****************************************************************
|*
|*	void
|*	read_port_string_byte (int portno, void *area, int byte_count);
|*
	.global	_read_port_string_byte
_read_port_string_byte:
	pushl	r5

	movl	8(sp),r2	|* No. do port
	movl	12(sp),r5	|* Area
	movl	16(sp),r1	|* Short_count

	up

	rep
	insb

	outb	r0,#0x80	|* Delay (?!!)

	popl	r5
	rts

|*
|****************************************************************
|*	Escreve uma seq��ncia de bytes em uma porta		*
|****************************************************************
|*
|*	void
|*	write_port_string_byte (int portno, void *area, int byte_count);
|*
	.global	_write_port_string_byte
_write_port_string_byte:
	pushl	r4

	movl	8(sp),r2	|* No. do port
	movl	12(sp),r4	|* Area
	movl	16(sp),r1	|* Short_count

	up

	rep
	outsb

	outb	r0,#0x80	|* Delay (?!!)

	popl	r4
	rts
