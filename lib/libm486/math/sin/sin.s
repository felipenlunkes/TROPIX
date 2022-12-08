|*
|****************************************************************
|*								*
|*			sin.s					*
|*								*
|*	Rotinas para o c�lculo de Seno e Cosseno		*
|*								*
|*	Vers�o	3.0.0, de 03.02.96				*
|*		3.0.0, de 11.03.96				*
|*								*
|*	Rotinas: 						*
|*		sin,	cos					*
|*								*
|*	M�dulo: sin						*
|*		libm/math					*
|*		Categoria D					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

|*
|****************************************************************
|*	Rotina para c�lculo do SENO				*
|****************************************************************
|*
|*	double	sin (double arg);
|*
	.global	_sin
_sin:
	fldd	4(sp)		|* Argumento na stack
	fsin
	rts

|*
|****************************************************************
|*	Rotina para c�lculo do COSSENO				*
|****************************************************************
|*
|*	double	cos (double arg);
|*
	.global	_cos
_cos:
	fldd	4(sp)		|* Argumento na stack
	fcos
	rts
