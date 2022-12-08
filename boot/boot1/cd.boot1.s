|*
|****************************************************************
|*								*
|*			cd.boot1.s				*
|*								*
|*	BOOT para o PC (vers�o CD), est�gio 1			*
|*								*
|*	Vers�o	4.6.0, de 29.04.04				*
|*		4.9.0, de 19.06.06				*
|*								*
|*	M�dulo: Boot1						*
|*		N�CLEO do TROPIX para PC			*
|*								*
|*	TROPIX: Sistema Operacional Tempo-Real Multiprocessado	*
|*		Copyright � 2006 NCE/UFRJ - tecle "man licen�a"	*
|*								*
|****************************************************************
|*

	.seg16

|*
|******	Defini��es globais **************************************
|*
DEBUG		= 0			|* Liga ou n�o a depura��o

|*
|******	Defini��es Diversas *************************************
|*
KBSZ		= 1024

CDSHIFT		= 11
CDSZ		= 1 << CDSHIFT

|*
|****** Entrada do bloco de E/S linear **************************
|*
l_cnt		= 2
l_area		= 4
l_seg		= 6
l_bno		= 8

|*
|******	Defini��es das regi�es da mem�ria ***********************
|*
BOOT0ADDR	= 48 * KBSZ		|* Endere�o de carga de "boot0"
BOOT1ADDR	= 31 * KBSZ		|* Endere�o de carga de "boot1"
BOOT2ADDR	= 64 * KBSZ		|* Endere�o de carga de "boot2"

STACKADDR	= 63 * KBSZ		|* Endere�o virtual do in�cio da pilha

HSEG		= 80 / 16		|* No. de segmentos do cabe�alho

BOOT2LOADSEG	= BOOT2ADDR / 16	|* Segmento de carga do "boot2"
BOOT2EXECSEG	= BOOT2LOADSEG+HSEG	|* Segmento de execu��o do "boot2"

|*
|******	Deslocamento das vari�veis na pilha *********************
|*
VIDEOMODE	=  17			|* Modo de v�deo: "S": SVGA, "V": VGA
STDBOOT		=  16			|* Byte informando para n�o esperar
OFFSET		=  8			|* In�cio da parti��o
DEVCODE		=  0			|* C�digo do Dispositivo

CDCODE		= -4			|* C�digo do CD para INT 13
CNT		= -8			|* Um contador

LINK_SZ		=  8			|* Tamanho total alocado na pilha

|*
|****************************************************************
|******	Comeco do Boot1	*****************************************
|****************************************************************
|*
	.text
	.global	start
start:
	clrw	r0
	movw	r0,ds
	movw	r0,es
	movw	r0,ss

|*
|******	Prepara a pilha *****************************************
|*
again:
	movw	#STACKADDR,fp
	movw	#STACKADDR-LINK_SZ,sp

|*
|******	P�e o cabe�alho + prompt ********************************
|*
	movw	#pgversion,r0
	call	putstr

	movb	#' ',VIDEOMODE(fp)	|* Come�a com o modo neutro
1$:
	call	getc

	cmpb	#'\n',r0		|* Fim da linha
	jeq	get_info

	cmpb	#'-',r0			|* Verifica se � o come�o de op��o
	jne	1$

|*
|******	Achou um Sinal de Menos - In�cio de Op��o  **************
|*
10$:
	call	getc

	cmpb	#'v',r0
	jeq	11$

	cmpb	#'V',r0
	jne	12$
11$:
	movb	#'V',VIDEOMODE(fp)	|* Modo VGA
	jmp	15$
12$:
	cmpb	#'s',r0
	jeq	13$

	cmpb	#'S',r0
	jne	15$
13$:
	movb	#'S',VIDEOMODE(fp)	|* Modo SVGA
|***	jmp	15$

15$:
	call	getc			|* Le o caractere ap�s o "s" ou "v"

	cmpb	#'\n',r0		|* Fim da linha
	jne	15$

|*
|****** Obt�m informa��es do BOOT *******************************
|*
get_info:
	movw	#0x4B01,r0
	movw	#boot_info,r4
	int	#0x13			|* INT 13, servi�o 0x4B

	movb	boot_info+2,r0		|* Guarda o dispositivo do CD
	movb	r0,CDCODE(fp)

|*
|****** L� o SB do CD *******************************************
|*
read_sb:
	movw	#linear_cb,r4
	movw	#1,l_cnt(r4)
	movw	#AREA,l_area(r4)
	movw	es,l_seg(r4)
	movl	#16,l_bno(r4)		|* SB da primeira sess�o
1$:
   	movb	#0x42,h0		|* Leitura
	movb	CDCODE(fp),r2		|* Dispositivo
|*	movw	#linear_cb,r4		|* Endere�o do bloco
	int	#0x13
	jcc	get_root_addr

	movb	#'E',r0			|* Em caso de erro, ...
	call	putc
	jmp	1$

|*
|****** Obt�m o ponteiro para o diret�rio da RAIZ ***************
|*
get_root_addr:
	movw	#AREA+156,r3		|* cd_root_dir
	movzbl	1(r3),r0		|* d_ext_attr_len
	addl	2(r3),r0		|* d_first_block

|*
|****** L� o diret�rio da RAIZ **********************************
|*
read_root:
|*	movw	#linear_cb,r4
|*	movw	#1,l_cnt(r4)
|*	movw	#AREA,l_area(r4)
|*	movw	es,l_seg(r4)
	movl	r0,l_bno(r4)
1$:
   	movb	#0x42,h0		|* Leitura
	movb	CDCODE(fp),r2		|* Dispositivo
|*	movw	#linear_cb,r4		|* Endere�o do bloco
	int	#0x13
	jcc	dir_search

	movb	#'E',r0			|* Em caso de erro, ...
	call	putc
	jmp	1$

|*
|****** Procura "BOOT" no diret�rio RAIZ ************************
|*
dir_search:
	movw	#AREA,r3		|* endere�o inicial do diret�rio
1$:
	movb	32(r3),r0
	tstb	r0
	jne	2$

	movw	#notfound,r0
	call	putstr

	jmp	.
2$:
	cmpb	#7,r0			|* "BOOT.;1"
	jne	9$

	cmpl	#0x544F4F42,33(r3)	|* Compara com "BOOT"
	jne	9$

	cmpb	#';',33+5(r3)
	jeq	read_boot
9$:
	movzbw	0(r3),r0		|* Vai para a entrada seguinte
	addw	r0,r3
	jmp	1$

|*
|****** L� o BOOT2 **********************************************
|*
read_boot:
	movl	10(r3),r0		|* Calcula o no. de blocos
	addl	#CDSZ-1,r0
	lsrl	#CDSHIFT,r0
	movw	r0,CNT(fp)

|*	movw	#linear_cb,r4
|*	movw	#1,l_cnt(r4)
	movw	#0,l_area(r4)
	movw	#BOOT2LOADSEG,l_seg(r4)
	movzbl	1(r3),r0		|* d_ext_attr_len
	addl	2(r3),r0		|* d_first_block
	movl	r0,l_bno(r4)
1$:
   	movb	#0x42,h0		|* Leitura
	movb	CDCODE(fp),r2		|* Dispositivo
|*	movw	#linear_cb,r4		|* Endere�o do bloco
	int	#0x13
	jcc	9$

	movb	#'E',r0			|* Em caso de erro, ...
	call	putc
	jmp	1$
9$:
	decw	CNT(fp)
	jle	10$

	addw	#{CDSZ/16},l_seg(r4)
	addl	#1,l_bno(r4)

	jmp	1$

10$:
	movb	#0xFE,DEVCODE(fp)	|* Para informar o BOOT2 do CD

	farjmpw	#BOOT2EXECSEG,0		|* Desvia para o inicio do BOOT2

|*
|****** �rea para leitura linear ********************************
|*
linear_cb:
	.byte	16			|* Para a INT13 estendida
	.dsb	15

|*
|******	Mensagens ***********************************************
|*
pgversion:
	.isoz	"\nTROPIX CD boot1, Versao: 4.9.0, de 19.06.06\n\n> "
notfound:
	.isoz	"Arquivo BOOT nao encontrado\n\n"
.if	DEBUG
antes:
	.isoz	"Vou ler o BOOT\n\n"
depois:
	.isoz	"Vou executar o BOOT\n\n"
.endif	DEBUG

|*
|******	Le e ecoa um caractere da console ***********************
|*
getc:
	clrb	h0			|* Le um caractere (em r0)
	int	#0x16

	cmpb	#'\r',r0		|* Transforma '\r' em '\n'
	jne	2$

	movb	#'\n',r0
2$:
	pushw	r0			|* Salva o caractere lido

	call	putc			|* Ecoa o caractere

	popw	r0			|* Restaura o caractere lido

	rts

|*
|******	Imprime um caractere (em r0) na console	*****************
|*
putc:
	pushw	r3			|* Salva r3

	cmpb	#'\n',r0		|* Verifica se � '\n'
	jne	1$

	movb	#'\r',r0		|* Imprime tamb�m o '\r'
	call	putc

	movb	#'\n',r0
1$:
	clrb	h3			|* Escreve o caractere (em r0)
	movb	#14,h0
	int	#0x10

	popw	r3			|* Restaura r3
	rts

|*
|******	Escreve uma cadeia (endere�o em r0) *********************
|*
putstr:
	pushw	r4			|* Salva r4
	movw	r0,r4
1$:
	movb	(r4),r0			|* Obt�m um caractere
	incw	r4

	cmpb	#'\0',r0		|* Verifica se chegou no final
	jeq	2$

	call	putc			|* Imprime um caractere
	jmp	1$
2$:
	popw	r4			|* Restaura r4
	rts

.if	DEBUG
|*
|******	Escreve um valor hexadecimal (em r0) ********************
|*
puthex:
	pushl	r3
	pushw	r2

	movl	r0,r3
	movb	#8,r2
1$:
	movl	r3,r0
	lsll	#4,r3

	lsrl	#32-4,r0
	andb	#0x0F,r0

	cmpb	#10,r0
	jge	2$

	addb	#'0',r0
	jmp	4$
2$:
	addb	#'A'-10,r0
4$:
	call	putc

	decb	r2
	jgt	1$

	movb	#' ',r0
	call	putc

	popw	r2
	popl	r3
	rts
.endif	DEBUG

|*
|******	�reas e V�riaveis ***************************************
|*
	.bss
	.global	boot_info
boot_info:
	.dsb	32

AREA:
	.dsb	CDSZ			|* �rea para ler os diret�rios e inodes
