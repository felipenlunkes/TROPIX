|*
|****************************************************************
|*								*
|*			abs.s					*
|*								*
|*	Obt�m o valor absoluto					*
|*								*
|*	Vers�o	2.3.0, de 05.03.90				*
|*		3.0.0, de 08.06.95				*
|*								*
|*	M�dulo: abs						*
|*		libc/etc					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

|*
|****************************************************************
|*	Obt�m o valor absoluto					*
|****************************************************************
|*
|*	#include <stdlib.h>
|*
|*	int	abs (int j);
|*	long	labs (long j);
|*
	.global	_abs, _labs
_abs:
_labs:
	movl	4(sp),d0
	jge	1$

	negl	d0
1$:
	rts	
