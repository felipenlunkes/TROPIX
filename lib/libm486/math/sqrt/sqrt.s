|*
|****************************************************************
|*								*
|*			sqrt.c					*
|*								*
|*	Rotina para o c�lculo da Raiz Quadrada			*
|*								*
|*	Vers�o	3.0.0, de 03.02.96				*
|*		3.0.0, de 11.03.96				*
|*								*
|*	M�dulo: sqrt						*
|*		libm486/math					*
|*		Categoria D					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*

|*
|****************************************************************
|*	Rotina que calcula a RAIZ QUADRADA			* 
|****************************************************************
|*
|*	double	sqrt (double arg);
|*
	.global	_sqrt
_sqrt:
	fldd	4(sp)		|* N�mero na stack
	fsqrt
	rts
