|*
|****************************************************************
|*								*
|*			boot.s					*
|*								*
|*	C�digo inicial simples para o processo 0		* 
|*								*
|*	Vers�o	3.0.0, de 01.09.94				*
|*		3.2.3, de 08.12.99				*
|*								*
|*	M�dulo: N�cleo						*
|*		N�CLEO do TROPIX para PC			*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 1999 NCE/UFRJ - tecle "man licen�a"	*
|*								*
|****************************************************************
|*

EXECE		= 59
EXIT		= 1

|*
|******	Programa Inicial para Carregar o INIT *******************
|*
	.text				|* N�o pode usar SDI
	.global	_bootcode
.begin:					|* C�digo absoluto
_bootcode:
	pushl	#0			|* ENVP
	pushl	#USER_DATA_VA+argv-.begin
	pushl	#USER_DATA_VA+_init_nm-.begin
	pushl	#0			|* "endere�o de retorno"
	movl	#EXECE,r0
	callgl	#SYS_CALL,0

	movl	#EXIT,r0
	callgl	#SYS_CALL,0

	jmp	. 			|* Loop forever

|*
|******	Os argumentos *******************************************
|*
argv:
	.long	USER_DATA_VA+_init_nm-.begin
	.long	0

|*
|****** O nome do "init" ****************************************
|*
	.global	_init_nm
_init_nm:
	.dsl	8			|* == char[32]: O nome do arquivo "init"

|*
|****** O tamanho do c�digo *************************************
|*
	.global	_bcodesz
_bcodesz:				|* Tamanho do c�digo
	.long	_bcodesz-.begin
