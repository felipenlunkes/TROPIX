|*
|****************************************************************
|*								*
|*			fpu.s					*
|*								*
|*	C�digo para inicializa��o do coprocessador		* 
|*								*
|*	Vers�o	3.0.0, de 08.07.95				*
|*		3.0.0, de 12.08.95				*
|*								*
|*	M�dulo: N�cleo						*
|*		N�CLEO do TROPIX para PC			*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 1999 NCE/UFRJ - tecle "man licen�a"	*
|*								*
|****************************************************************
|*

|*
|****** Defini��es **********************************************
|*
FPUCW		= 0x003F
FPUCWMASK	= 0x103F

|*
|******	Teste da Exist�ncia do Coprocessador de Ponto Flutuante *
|*
|*	void	_fpu_test (void);
|*
	.text
	.global	_fpu_test
_fpu_test:
	fwait
	finit				|* Inicializa

	clrb	r1			|* Imagina FPU ausente
	leal	-4(sp),r0		|* Endere�o da "fpu_cw"
	fwait
	fstcw	(r0)			|* L� a Control Word do FPU
	movw	-4(sp),r0
	andw	#FPUCWMASK,r0		|* Verifica os bits
	cmpw	#FPUCW,r0
	jne	1$
	incb	r1			|* Est� presente
1$:
	movb	r1,_fpu_present		|* Armazena o estado
	rts

|*
|******	Inicializa��o do Coprocessador de Ponto Flutuante *******
|*
|*	void	fpu_init (void);
|*
	.text
	.global	_fpu_init
_fpu_init:
	fwait
	finit
	rts

|*
|******	Salva o Estado do Coprocessador de Ponto Flutuante *****
|*
|*	void	fpu_save (long *state);
|*
	.global	_fpu_save
_fpu_save:
	movl	4(sp),r0
|*	fwait		|* Sem "fwait" para evitar exce��o em modo supervisor
	fsave	(r0)
	rts

|*
|******	Restaura o Estado do Coprocessador de Ponto Flutuante **
|*
|*	void	fpu_restore (const long *state);
|*
	.global	_fpu_restore
_fpu_restore:
	movl	4(sp),r0
	frstor	(r0)
	rts

|*
|******	Liga o bit de Emula��o no CR0 **************************
|*
|*	void	fpu_set_embit (void);
|*
	.global	_fpu_set_embit
_fpu_set_embit:
	movl	cr0,r0
	orb	#4,r0
	movl	r0,cr0
	rts

|*
|******	Desliga o bit de Emula��o no CR0 **************************
|*
|*	void	fpu_reset_embit (void);
|*
	.global	_fpu_reset_embit
_fpu_reset_embit:
	movl	cr0,r0
	andb	#~4,r0
	movl	r0,cr0
	rts

.if 0	|*******************************************************|
|*
|******	Testa o bit de Emula��o no CR0 **************************
|*
|*	int	fpu_test_embit (void);
|*
	.global	_fpu_test_embit
_fpu_test_embit:
	movl	cr0,r0
	andl	#4,r0		|* Retorna 4 se o bit estava ligado
	rts			|* ou 0, se estava desligado

|*
|******	Teste da Exist�ncia do Coprocessador de Ponto Flutuante *
|*
|*	void	_fpu_test (void);
|*
	.text
	.global	_fpu_read
_fpu_read:
	leal	-4(sp),r0		|* Endere�o da "fpu_cw"
	fwait
	fstcw	(r0)			|* L� a Control Word do FPU
	movw	-4(sp),r0
|#	andw	#FPUCWMASK,r0		|* Verifica os bits
	rts
.endif	|*******************************************************|
