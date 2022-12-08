|*
|****************************************************************
|*								*
|*			fexcep.s				*
|*								*
|*	Habilita as exce��es da FPU				*
|*								*
|*	Vers�o	3.0.0, de 15.02.96				*
|*		3.0.0, de 11.03.96				*
|*								*
|*	M�dulo: fexcep						*
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
|*	Indica as condi��es que devem gerar exce��o 		*
|****************************************************************
|*
|*	int	fexcep (int a);
|*
	.global	_fexcep
_fexcep:
	fstcw	-4(sp)		|* Guarda a antiga CW da FPU
	movw	-4(sp),r1	|* 	em r1
	orw	allexcep,r1	|* Liga todos os bits da m�scara

	movw	4(sp),r0	|* Argumento em r0
	andw	allexcep,r0	|* Extrai os bits para a m�scara
	notw	r0		|* Inverte os bits
	andw	r0,r1		|* Zera os bits corr. ao argumento

	movw	-4(sp),r0	|* Guarda a antiga CW em r0
	notw	r0		|* Inverte os bits
	andw	allexcep,r0	|* Prepara o valor de retorno
	andl	#0xFFFF,r0	|*	como um longo

	movw	r1,-4(sp)	|* Carrega a nova CW em r1
	fldcw	-4(sp)		|*	na FPU

	rts

|*
|****************************************************************
|*	Rotina que l� o fsr (Status Register)			*
|****************************************************************
|*
|*	long	_fgsr (void);
|*
	.global	__fgsr
__fgsr:
	clrl	r0
	fnstsw			|* Armazena Status em r0
	sahf			|* Armazena os c�digos de condi��o
	rts	

|*
|****************************************************************
|*	Rotina que escreve no fsr (Status Register)		*
|*	No 486 n�o � poss�vel escrever diretamente		*
|*	Os bits de indica��o de exce��es s�o zerados		*
|****************************************************************
|*
|*	int	_fssr (long x);
|*
	.global	__fssr
__fssr:
	fnstsw			|* Armazena Status em r0
	fclex			|* Zera os bits das exce��es
	rts	

|*
|****************************************************************
|*	Rotina que l� o fcr (Control Register)			*
|****************************************************************
|*
|*	long	_fgcr (void);
|*
	.global	__fgcr
__fgcr:
	clrl	r0
	fstcw	-4(sp)
	movw	-4(sp),r0
	rts	

|*
|****************************************************************
|*	Rotina que escreve no fcr (Control Register)		*
|****************************************************************
|*
|*	int	_fscr (long x);
|*
	.global	__fscr
__fscr:
	clrl	r0
	fstcw	-4(sp)
	movw	-4(sp),r0
	fldcw	4(sp)
	rts	

|*
|****************************************************************
|*	Rotina que l� do fiar (Instruction Address Register)	*
|*	No 486 n�o � poss�vel ler diretamente			*
|****************************************************************
|*
|*	long	_fgiar (void);
|*
	.global	__fgiar
__fgiar:
	fstcw	-4(sp)		|* Armazena a CW
	fstenv	-32(sp)		|* Armazena o ambiente na stack
				|*	e desliga bits de exce��o
	movl	-20(sp),r0	|* Extrai o endere�o da �ltima
				|* 	instru��o num�rica
	fldcw	-4(sp)		|* Carrega a CW novamente
	rts

|*
|****************************************************************
|*	M�scara para extrair da CW os bits de todas as exce��es	*
|****************************************************************
|*
	.const
allexcep:
	.word	0x003F
