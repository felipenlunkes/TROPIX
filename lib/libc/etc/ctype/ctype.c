/*
 ****************************************************************
 *								*
 *			ctype.c					*
 *								*
 *	Tabela de classifica��o dos caracteres ISO		*
 *								*
 *	Vers�o	1.0.0, de 13.11.86				*
 *		3.0.0, de 01.11.95				*
 *								*
 *	M�dulo: _ctype						*
 *		libc/etc					*
 *		Categoria B					*
 *								*
 *	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
 *		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
 * 								*
 ****************************************************************
 */

#include "ctype.h"

/*
 ****************************************************************
 *	Tabela de classifica��o dos caracteres			*
 ****************************************************************
 */
static const char	eof[] =  { _C, _C, _C, _C };

/*
 *	Cuidar para que os dois vetores fiquem
 *	adjacentes no m�dulo objeto!
 */
entry const char	_ctype[] =
{

/*	NUL	SOH	STX	ETX	EOT	ENQ	ACK	BEL	*/
	_C,	_C,	_C,	_C,	_C,	_C,	_C,	_C,

/*	BS	HT	LF	VT	FF	CR	SO	SI	*/
	_C,	_S|_C,	_S|_C,	_S|_C,	_S|_C,	_S|_C,	_C,	_C,

/*	DLE	DC1	DC2	DC3	DC4	NAK	SYN	ETB	*/
	_C,	_C,	_C,	_C,	_C,	_C,	_C,	_C,

/*	CAN	EM	SUB	ESC	FS	GS	RS	US	*/
	_C,	_C,	_C,	_C,	_C,	_C,	_C,	_C,

/*	branco	!	"	#	$	%	&	'	*/
	_S,	0,	0,	0,	0,	0,	0,	0,

/*	(	)	*	+	,	-	.	/	*/
	0,	0,	0,	0,	0,	0,	0,	0,

/*	0	1	2	3	4	5	6	7	*/
	_D|_X,	_D|_X,	_D|_X,	_D|_X,	_D|_X,	_D|_X,	_D|_X,	_D|_X,

/*	8	9	:	;	<	=	>	?	*/
	_D|_X,	_D|_X,	0,	0,	0,	0,	0,	0,

/*	@	A	B	C	D	E	F	G	*/
	0,	_U|_X,	_U|_X,	_U|_X,	_U|_X,	_U|_X,	_U|_X,	_U,

/*	H	I	J	K	L	M	N	O	*/
	_U,	_U,	_U,	_U,	_U,	_U,	_U,	_U,

/*	P	Q	R	S	T	U	V	W	*/
	_U,	_U,	_U,	_U,	_U,	_U,	_U,	_U,

/*	X	Y	Z	[	\	]	^	_	*/
	_U,	_U,	_U,	0,	0,	0,	0,	0,

/*	`	a	b	c	d	e	f	g	*/
	0,	_L|_X,	_L|_X,	_L|_X,	_L|_X,	_L|_X,	_L|_X,	_L,

/*	h	i	j	k	l	m	n	o	*/
	_L,	_L,	_L,	_L,	_L,	_L,	_L,	_L,

/*	p	q	r	s	t	u	v	w	*/
	_L,	_L,	_L,	_L,	_L,	_L,	_L,	_L,

/*	x	y	z	{	|	}	~	DEL	*/
	_L,	_L,	_L,	0,	0,	0,	0,	_C,

/*	80	81	82	83	84	85	86	87	*/
	0,	0,	0,	0,	0,	0,	0,	0,

/*	88	89	8A	8B	8C	8D	8E	8F	*/
	0,	0,	0,	0,	0,	0,	0,	0,

/*	90	91	92	93	94	95	96	97	*/
	0,	0,	0,	0,	0,	0,	0,	0,

/*	98	99	9A	9B	9C	9D	9E	9F	*/
	0,	0,	0,	0,	0,	0,	0,	0,

/*	A0 nbs	A1 .	A2 .	A3 .	A4 .	A5 .	A6 .	A7 .	*/
	_S,	0,	0,	0,	0,	0,	0,	0,

/*	A8 .	A9 .	AA .	AB <<	AC .	AD .	AE .	AF .	*/
	0,	0,	0,	0,	0,	0,	0,	0,

/*	B0 .	B1 +-	B2 .	B3 .	B4 .	B5 .	B6 .	B7 .	*/
	0,	0,	0,	0,	0,	0,	0,	0,

/*	B8 .	B9 .	BA .	BB >>	BC 1/4	BD 1/2	BE 3/4	BF �    */
	0,	0,	0,	0,	0,	0,	0,	0,

/*	C0 �	C1 �	C2 �	C3 �	C4 :A	C5 .A	C6 AE	C7 �	*/
	_U,	_U,	_U,	_U,	_U,	_U,	_U,	_U,

/*	C8 `E	C9 �	CA �	CB :E	CC `I	CD �	CE ^I�	CF :I	*/
	_U,	_U,	_U,	_U,	_U,	_U,	_U,	_U,

/*	D0 -D	D1 �   	D2 `O�	D3 �	D4 �	D5 �	D6 :O��	D7 OE	*/
	_U,	_U,	_U,	_U,	_U,	_U,	_U,	_U,

/*	D8 /O	D9 `U	DA �	DB ^U	DC �	DD 'Y	DE PP	DF sz	*/
	_U,	_U,	_U,	_U,	_U,	_U,	_U,	_L,

/*	E0 �	E1 �	E2 �	E3 �	E4 :a	E5 .a	E6 ae	E7 �	*/
	_L,	_L,	_L,	_L,	_L,	_L,	_L,	_L,

/*	E8 `e�	E9 �	EA �	EB :e	EC `i	ED �	EE ^i	EF :i	*/
	_L,	_L,	_L,	_L,	_L,	_L,	_L,	_L,

/*	F0 -d	F1 � 	F2 `o	F3 �	F4 �	F5 �	F6 :o	F7 oe	*/
	_L,	_L,	_L,	_L,	_L,	_L,	_L,	_L,

/*	F8 /o	F9 `u	FA �	FB ^u	FC �	FD 'y	FE pp	FF :y	*/
	_L,	_L,	_L,	_L,	_L,	_L,	_L,	_L

}	/* end _ctype */;
