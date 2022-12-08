|*
|****************************************************************
|*								*
|*			fgman.s					*
|*								*
|*	Rotinas para manuseio em separado dos compoentes	*
|*								*
|*	Vers�o	3.0.0, de 14.07.95				*
|*		3.0.0, de 11.03.96				*
|*								*
|*	Fun��es:						*
|*		fgman,	fgexp,	faexp,				*
|*		fgint,	fgfra,	fhuge				*
|*								*
|*	M�dulo: fgman						*
|*		libm486/float					*
|*		Categoria B					*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2000 NCE/UFRJ - tecle "man licen�a"	*
|* 								*
|****************************************************************
|*
 
|*
|****************************************************************
|*	Retorna a mantissa no intervalo [0.5, 1.0)		*
|****************************************************************
|*
|*	double	fgman (double a);
|*
	.global	_fgman
_fgman:
	fldd	4(sp)
	fxtract			|* Mantissa em f0
	fstp	f0,f1		|* Pop stack
	rts

|*
|****************************************************************
|*	Retorna o expoente sem BIAS				*
|****************************************************************
|*
|*	int	fgexp (double a);
|*
	.global	_fgexp
_fgexp:
	fldd	4(sp)
	fxtract			|* Expoente flutuante em f1
	fstp	f0,f0		|* Expoente flutuante em f0
	fistpl	-4(sp)		|* Expoente inteiro na mem�ria
	movl	-4(sp),r0	|* Expoente em r0
	rts

|*
|****************************************************************
|*	Retorna um n�mero com o expoente somado			*
|****************************************************************
|*
|*	double	faexp (int expalt, double a);
|*
	.global	_faexp
_faexp:
	fildl	4(sp)		|* Altera��o do expoente em f0
	fldd	8(sp)		|* N�mero em f0
	fscale
	fstp	f0,f1		|* Resultado em f0
	rts

|*
|****************************************************************
|*	Retorna a parte inteira					*
|****************************************************************
|*
|*	double	fgint (double a);
|*
	.global	_fgint
_fgint:
	fstcw	-4(sp)
	fldcw	trunc
	fldd	4(sp)		|* Carrega o operando
	frndint	
	fldcw	-4(sp)
	rts

|*
|****************************************************************
|*	Retorna a parte fracion�ria				*
|****************************************************************
|*
|*	double	fgfra (double a);
|*
	.global	_fgfra
_fgfra:
	fstcw	-4(sp)		|* Guarda a antiga CW
	fldcw	trunc		|* Carrega CW que trunca
	fldd	4(sp)		|* Carrega o operando
	frndint			|* Parte inteira em f0
	fsubd	4(sp)		|* Subtrai o n�mero da parte
	fchs			|* inteira sobrando a parte
				|* fracion�ria com sinal invertido
	fldcw	-4(sp)
	rts

|*
|****************************************************************
|*	Retorna o maior n�mero poss�vel antes de infinito	*
|****************************************************************
|*
|*	double	fhuge (void);
|*
	.global	_fhuge
_fhuge:
	fldd	_HUGE_VAL
	rts
	
|*
|****************************************************************
|*	Constante necess�ria para o tipo de arredondamento	* 
|****************************************************************
|*
	.const
trunc:
	.word	0x0F7F		|* arredondamento para zero 
				|* (truncamento)
|*
|****************************************************************
|*	Constante que representa o maior n�mero	represent�vel	* 
|****************************************************************
|*
|*	fhuge = 0x7FFE0000 0xFFFFFFFF 0xFFFFFFFF (Motorola)
|*	fhuge = 0x7FEFFFFF 0xFFFFFFFF (IEEE double)
|*
	.const
	.global	_HUGE_VAL
_HUGE_VAL:
	.long	0xFFFFFFFF
	.long	0x7FEFFFFF
