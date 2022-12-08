|*
|****************************************************************
|*								*
|*			excep.s					*
|*								*
|*	Vetores de Interrup��o e fun��es auxiliares		*
|*								*
|*	Vers�o	3.0.0, de 12.08.94				*
|*		3.1.6, de 05.01.99				*
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
|****************************************************************
|*	Ponto de entrada das exce��es				*
|****************************************************************
|*
	.text
	.global	_div_vector
	.align	4
_div_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#0		|* C�digo da exce��o
	jmp	excep

	.global	_debug_vector
	.align	4
_debug_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#1		|* C�digo da exce��o
	jmp	excep

	.global	_nmi_vector
	.align	4
_nmi_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#2		|* C�digo da exce��o
	jmp	excep

	.global	_breakpoint_vector
	.align	4
_breakpoint_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#3		|* C�digo da exce��o
	jmp	excep

	.global	_overflow_vector
	.align	4
_overflow_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#4		|* C�digo da exce��o
	jmp	excep

	.global	_bound_vector
	.align	4
_bound_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#5		|* C�digo da exce��o
	jmp	excep

	.global	_inv_opcode_vector
	.align	4
_inv_opcode_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#6		|* C�digo da exce��o
	jmp	excep

	.global	_coprocessor_vector
	.align	4
_coprocessor_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#7		|* C�digo da exce��o
	jmp	excep

	.global	_double_fault_vector
	.align	4
_double_fault_vector:
	pushl	#8		|* C�digo da exce��o
	jmp	excep

	.global	_segment_overrun_vector
	.align	4
_segment_overrun_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#9		|* C�digo da exce��o
	jmp	excep

	.global	_invalid_tss_vector
	.align	4
_invalid_tss_vector:
	pushl	#10		|* C�digo da exce��o
	jmp	excep

	.global	_segment_not_present_vector
	.align	4
_segment_not_present_vector:
	pushl	#11		|* C�digo da exce��o
	jmp	excep

	.global	_stack_vector
	.align	4
_stack_vector:
	pushl	#12		|* C�digo da exce��o
	jmp	excep

	.global	_general_protection_vector
	.align	4
_general_protection_vector:
	pushl	#13		|* C�digo da exce��o
	jmp	excep

	.global	_page_fault_vector
	.align	4
_page_fault_vector:
	pushl	#14		|* C�digo da exce��o
	jmp	excep

	.global	_reser_15_vector
	.align	4
_reser_15_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#15		|* C�digo da exce��o
	jmp	excep

	.global	_coprocessor_error_vector
	.align	4
_coprocessor_error_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#16		|* C�digo da exce��o
	jmp	excep

	.global	_alignment_vector
	.align	4
_alignment_vector:
	pushl	#17		|* C�digo da exce��o
	jmp	excep

	.global	_reser_18_vector
	.align	4
_reser_18_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#18		|* C�digo da exce��o
	jmp	excep

	.global	_reser_19_vector
	.align	4
_reser_19_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#19		|* C�digo da exce��o
	jmp	excep

	.global	_reser_20_vector
	.align	4
_reser_20_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#20		|* C�digo da exce��o
	jmp	excep

	.global	_reser_21_vector
	.align	4
_reser_21_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#21		|* C�digo da exce��o
	jmp	excep

	.global	_reser_22_vector
	.align	4
_reser_22_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#22		|* C�digo da exce��o
	jmp	excep

	.global	_reser_23_vector
	.align	4
_reser_23_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#23		|* C�digo da exce��o
	jmp	excep

	.global	_reser_24_vector
	.align	4
_reser_24_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#24		|* C�digo da exce��o
	jmp	excep

	.global	_reser_25_vector
	.align	4
_reser_25_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#25		|* C�digo da exce��o
	jmp	excep

	.global	_reser_26_vector
	.align	4
_reser_26_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#26		|* C�digo da exce��o
	jmp	excep

	.global	_reser_27_vector
	.align	4
_reser_27_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#27		|* C�digo da exce��o
	jmp	excep

	.global	_reser_28_vector
	.align	4
_reser_28_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#28		|* C�digo da exce��o
	jmp	excep

	.global	_reser_29_vector
	.align	4
_reser_29_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#29		|* C�digo da exce��o
	jmp	excep

	.global	_reser_30_vector
	.align	4
_reser_30_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#30		|* C�digo da exce��o
	jmp	excep

	.global	_reser_31_vector
	.align	4
_reser_31_vector:
	pushl	#0		|* Substitui o c�digo de erro
	pushl	#31		|* C�digo da exce��o
   |***	jmp	excep
 
|*
|****************************************************************
|*	Interface para as exce��es internas			*
|****************************************************************
|*
   |***	.text
	.global	excep
excep:
	pushal
   	nop

	pushl	ds
	pushl	es

	movw	#KERNEL_DS,r0
	movw	r0,ds
	movw	r0,es

	cmpl	#0,u.u_dontpanic	|* Desvia se ele n�o foi programado
	jeq	5$

	cmpl	#14,4*10(sp)		|* Desvia se n�o for PAGE FAULT
	jne   	5$

	movl	u.u_dontpanic,sp	|* Desaloca a pilha (ignora o resto)
	clrl	u.u_dontpanic		|* Apaga o Indicador

	movl	#-1,r0			|* Retorna -1
	rts
5$:
	pushl	#0			|* C�digo da exce��o

	testb	#3,14*4(sp)		|* Guarda o "frame" se for de usu�rio
	jeq	1$
	movl	sp,u.u_frame
1$:
	call	_excep

	cmpb	#0,_mmu_dirty+CPUID	|* Carrega a ger�ncia de mem�ria
	jeq	30$

	movl	u.u_mmu_dir,r0
	andl	#~SYS_ADDR,r0
	movl	r0,cr3	

	clrb	_mmu_dirty+CPUID
30$:
	popl	r0			|* Tira o c�digo

	popl	es
	popl	ds

	popal
   	nop

	addl	#8,sp			|* Retira os 2 c�digos
	rte

|*
|****************************************************************
|*	Interface para a chamada ao sistema			*
|****************************************************************
|*
	.global	_syscall_vector:
_syscall_vector:
	pushfl				|* Guarda o "status register"

	pushal				|* Guarda os 8 registros
   	nop

	movw	#KERNEL_DS,r0
	movw	r0,ds
	movw	r0,es

	pushl	#2			|* C�digo da chamada ao sistema

	movl	sp,u.u_frame		|* S� pode ser do usu�rio

	call	_syscall

	cmpb	#0,_mmu_dirty+CPUID	|* Carrega a ger�ncia de mem�ria
	jeq	30$

	movl	u.u_mmu_dir,r0
	andl	#~SYS_ADDR,r0
	movl	r0,cr3	

	clrb	_mmu_dirty+CPUID
30$:
	popl	r0			|* Tira o c�digo

	movw	#USER_DS,r0
	movw	r0,ds
	movw	r0,es

	popal				|* Restaura os 8 registros
   	nop

	popfl				|* Restaura o "status register"

	farrts

|*
|****************************************************************
|*	Tabela IDT						*
|****************************************************************
|*
	.const
	.global	_idt_48
	.align	4
	.word	0
_idt_48:
	.word	_end_idt-_idt-1	|* Limite
	.long	_idt		|* Endere�o

|*
|*	A Tabela IDT propriamente dita
|*
	.data
	.global	_idt
_idt:
	.dsl	256 * 2
_end_idt:
