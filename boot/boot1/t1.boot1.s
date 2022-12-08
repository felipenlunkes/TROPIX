|*
|****************************************************************
|*								*
|*			t1.boot1.s				*
|*								*
|*	BOOT para o PC, est�gio 1				*
|*								*
|*	Esta etapa do BOOT reside no bloco 0 do disco,		*
|*	e � carregado pela ROM em 31 Kb				*
|*								*
|*	Vers�o	1.0.0, de 27.07.87				*
|*		4.9.0, de 17.06.06				*
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
DEBUG	= 0			|* Liga ou n�o a depura��o

FD	= 1			|* Disquete 1.44 MB
GEO	= 2			|* Disco IDE ou SCSI usando INT13 normal
LINEAR	= 3			|* Disco IDE ou SCSI usando INT13 Extensions

|*
|******	Defini��es dos dispositivos *****************************
|*
.ifndef	DEV

	.error	"Faltou definir o dispositivo"

.elif	DEV == 1440		|* Disquete de 1.44 MB

	TYPE	= FD
	UNIT	= 0
	SECT	= 18
	HEAD	= 2

.elif	DEV == 80		|* Disco IDE ou SCSI usando INT13 normal

	TYPE	= GEO

.elif	DEV == 81		|* Disco IDE ou SCSI usando INT13 Extensions

	TYPE	= LINEAR

.else

	.error	"Valor inv�lido de dispositivo: %X", DEV

.endif

|*
|******	Defini��es Diversas *************************************
|*
ROOTINO		= 3 << 5

LIDSZ		= 32

HDRSZ		= 80

BLSHIFT		= 9
BLSZ		= 1 << BLSHIFT
BLMASK		= BLSZ - 1

KBSZ		= 1024
BL4SZ		= 4096

|*
|****** Entrada do Diret�rio do T1 ******************************
|*
d_ino		= 0
d_ent_sz	= 4
d_nm_len	= 6
d_name		= 8

|*
|****** Entrada do INODE do T1 **********************************
|*
n_addr		= 36

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
LBNO		= -4			|* Bloco l�gico do disco
BA		= -8			|* Endere�o na memoria da leitura
INO		= -12			|* No. do INODE a ler
DIRPTR		= -16			|* Ponteiro para as entradas do diret�rio
NSECT		= -20			|* No. de setores por trilha
NHEAD		= -24			|* No. de cabe�as

LINK_SZ		=  24			|* Tamanho total alocado na pilha

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
.if	TYPE == FD
	movw	#STACKADDR,fp
.else	TYPE == GEO || TYPE == LINEAR
   |***	movw	#...,fp 		|* HD: recebe em fp a parti��o
.endif	TYPE

	movw	#STACKADDR-LINK_SZ,sp

|*
|******	P�e o cabe�alho + prompt ********************************
|*
	movw	#pgversion,r0
	call	putstr

|*
|******	Inicializa o n�mero de cabe�as e setores ****************
|*
.if	TYPE == FD

	movl	#SECT,NSECT(fp)
	movl	#HEAD,NHEAD(fp)

.elif 	TYPE == GEO

	movb	#0x08,h0		|* 8 = obter caracter�sticas
	movb	DEVCODE(fp),r2		|* Dispositivo
	int	#0x13

	andb	#0x3F,r1		|* Guarda o No. de setores/trilha
	movzbl	r1,r0
	movl	r0,NSECT(fp)

	movzbl	h2,r0			|* Guarda o No. de cabe�as
	incl	r0
	movl	r0,NHEAD(fp)

.endif	TYPE

|*
|****** Carrega os blocos seguintes de "boot1" ******************
|*
	movw	#linear_cb,r4
	movw	#[[ETEXT-start+BLMASK]>>BLSHIFT]-1,l_cnt(r4)
	movw	#start+BLSZ,l_area(r4)
	movw	es,l_seg(r4)
	movl	#1,l_bno(r4)

	call	phys_read

|*
|******	Zera o "bss" ********************************************
|*
	clrb	r0
	movw	#EDATA,r5
	movw	#END-EDATA,r1
	up
	rep
	stosb

|*
|******	Le o caminho ********************************************
|*
.if	TYPE == GEO || TYPE == LINEAR
	cmpb	#0,STDBOOT(fp)		|* Verifica se � o "std_boot"
	jne	decode_2
.endif	TYPE

	movb	#' ',VIDEOMODE(fp)	|* Come�a com o modo neutro

	movw	#NAMES,r5		|* r5: m�dulos de LIDSZ bytes
3$:
	movw	r5,r4			|* r4: byte do momento
4$:
	call	getc
5$:
	cmpb	#'-',r0			|* Achou o come�o de op��o
	jeq	10$

	cmpb	#'/',r0			|* Barra: novo nome
	jeq	20$

	cmpb	#'\n',r0		|* Fim da linha
	jeq	decode_1

	movb	r0,(r4)
	incw	r4
	jmp	4$

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
	jeq	decode_1

	cmpb	#' ',r0			|* Espa�o em branco
	jeq	18$

	cmpb	#'\t',r0		|* Espa�o em branco
	jne	15$

18$:
	call	getc			|* Le o caractere ap�s o branco

	cmpb	#' ',r0			|* Espa�o em branco
	jeq	18$

	cmpb	#'\t',r0		|* Espa�o em branco
	jeq	18$

	jmp	5$

|*
|******	Achou uma Barra - Separa em Pedacos de LIDSZ caracteres *
|*
20$:
	cmpw	r5,r4			|* Ignora o '/' em "/boot"
	jeq	4$

	movb	#'\0',(r4)		|* Coloca um '\0' no final

	addw	#LIDSZ,r5
	jmp	3$

|*
|******	Le e ecoa um caractere da console ***********************
|*
getc:
1$:
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
|******	Le um Bloco Fisico do Disco *****************************
|*
|*	TODOS os argumentos j� em "linear_cb"
|*
|*	r4   => Endere�o do "linear_cb"
|*
.if	TYPE == LINEAR	|****************************************

phys_read:

.if	DEBUG
	movb	#'P',r0
	call	putc
	movl	l_bno(r4),r0
	call	puthex
.endif	DEBUG

	movl	OFFSET(fp),r0		|* Acrescenta o deslocamento da parti��o
	addl	r0,l_bno(r4)
1$:
   	movb	#0x42,h0		|* Leitura
	movb	DEVCODE(fp),r2		|* Dispositivo
|*	movw	#linear_cb,r4		|* Endere�o do bloco
	int	#0x13
	jcc	9$

	movb	#'E',r0			|* Em caso de erro, ...
	call	putc

	clrw	r0
	int	#0x13

	jmp	1$
9$:
	rts

.else	TYPE == FD || TYPE == GEO |******************************

phys_read:
	pushw	r3

.if	DEBUG
	movb	#'P',r0
	call	putc
	movl	l_bno(r4),r0
	call	puthex
.endif	DEBUG

1$:
	movl	l_bno(r4),r0		|* Dividendo == No. do bloco dado
.if	TYPE == GEO
	addl	OFFSET(fp),r0		|* Acrescenta o deslocamento da parti��o
.endif	TYPE
	clrl	r2			|* Zera a parte alta do dividendo

	divul	NSECT(fp),r0		|* Quociente em r0 (l) (usa 32 bits)
					|* Resto == (setor - 1) em r2 (l)

	movb	r2,r1			|* r1 == setor
	incb	r1

	clrl	r2			|* Zera a parte alta do dividendo

	divul	NHEAD(fp),r0		|* Quociente == cilindro em r0 (w)
					|* Resto == cabe�a em r2 (w)

	movb	r0,h1			|* Cilindro
	lsrw	#2,r0
	andb	#0xC0,r0
	orb	r0,r1

   |***	movb	...,r1			|* Setor
	movb	r2,h2			|* Cabe�a
	movw	#0x0201,r0		|* 2 = ler, 1 bloco == BLSZ
.if	TYPE == GEO || TYPE == LINEAR
	movb	DEVCODE(fp),r2		|* Dispositivo
.else	TYPE == FD
	movb	#UNIT,r2		|* Dispositivo
.endif	TYPE
	movw	l_area(r4),r3		|* �rea
	int	#0x13

	jcc	9$

	movb	#'E',r0			|* Em caso de erro, ...
	call	putc

	clrw	r0
	int	#0x13

	jmp	1$
9$:					|* Leu corretamente
	decb	l_cnt(r4)
	jle	20$

	addw	#BLSZ,l_area(r4)
	incl	l_bno(r4)

	jmp	1$
20$:
	popw	r3
	rts

.endif	TYPE

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

	movb	#'\n',r0
	call	putc

	popw	r2
	popl	r3
	rts
.endif	DEBUG

|*
|******	Mensagens ***********************************************
|*
pgversion:
	.iso	"\nTROPIX T1"
.if	TYPE == LINEAR
	.iso	" linear"
.elif	TYPE == GEO
	.iso	" geo"
.elif	TYPE == FD
	.iso	" 1440"
.endif	TYPE
	.iso	" boot1, Versao: 4.9.0, de 17.06.06\n"
	.isoz	"\n> "

|*
|****** �rea para leitura linear ********************************
|*
	.org	start+BLSZ-2-16-2
linear_cb:
	.byte	16			|* Para a INT13 estendida
	.dsb	15

|*
|******	N�mero m�gico *******************************************
|*
	.org	start+BLSZ-2

	.byte	0x55, 0xAA

|*
|****************************************************************
|******	Aqui inicia o segundo bloco de "boot1" ******************
|****************************************************************
|*

|*
|******	O caminho terminou: decodifica **************************
|*
decode_1:
	movb	#'\0',(r4)		|* Coloca um '\0' no final
decode_2:
	movl	#ROOTINO,INO(fp) 	|* Come�a da raiz do sistema de arq.

	movw	#NAMES,r3		|* r3: In�cio de cada ID

	cmpb	#'\0',(r3)		|* Verifica se a linha est� vazia
	jne	7$

	movl	#0x746F6F62,(r3) 	|* Default = "boot" (little-endian)
7$:
	clrw	LBNO(fp)		|* Come�a do bloco 0 do diret�rio

	call	iget			|* L� um INODE

	cmpb	#'\0',(r3)		|* desvia se foi o fim do caminho
	jeq	read_boot2
9$:
	movw	#AREA,BA(fp)		|* Le um bloco do diret�rio ou arq.
	call	log_read

	jcs	again			|* Desvia se EOF

	movw	#AREA,DIRPTR(fp) 	|* Ponteiro para a primeira entrada

|*
|******	Verifica se esta entrada est� vazia (d_ino == 0) ********
|*
10$:
	movw	DIRPTR(fp),r5		|* r5 => entrada do diret�rio

	cmpl	#0,d_ino(r5)
	jeq	25$

|*
|******	Compara um identificador ********************************
|*
	movw	d_nm_len(r5),r1		|* r1 => Comprimento + 1
	incw	r1
	addw	#d_name,r5		|* r5 => ID do diret�rio
	movw	r3,r4			|* r4 => ID lido
   |***	up
	repe
	cmpsb

	jeq	30$

|*
|******	A entrada est� vazia ou o nome n�o confere **************
|*
25$:
	movw	DIRPTR(fp),r5		|* r5 => entrada do diret�rio
	movw	d_ent_sz(r5),r0
	addw	r0,DIRPTR(fp)		|* Aponta para a entrada seguinte

	cmpw	#AREA+BL4SZ,DIRPTR(fp)	|* Testa o nome seguinte
	jlt	10$

	jmp	9$			|* Se � o fim de bloco, le o seguinte

|*
|******	Achou o nome ********************************************
|*
30$:
	movw	DIRPTR(fp),r5		|* Novo INODE
	movl	d_ino(r5),r0
	movl	r0,INO(fp)

	addw	#LIDSZ,r3		|* Pula este nome
	jmp	7$

|*
|******	Acabou o caminho. Le o BOOT2 ****************************
|*
read_boot2:
	movw	#BOOT2LOADSEG,r3 	|* Endereco de Leitura (relativo a "es")
	clrw	BA(fp)
38$:
	movw	r3,es			|* O segmento "es" � que vai sendo incrementado

	call	log_read		|* Se EOF, desvia para o boot2
	jcs	callout

	addw	#BL4SZ/16,r3		|* Incrementa o segmento de BL4SZ
	jmp	38$

|*
|******	Acabou de Ler o BOOT2. Desvia para Ele ******************
|*
callout:
	farjmpw	#BOOT2EXECSEG,0		|* Desvia para o inicio do BOOT2

|*
|******	Fun��o para Ler um INODE ********************************
|*
|*	INO(fp) => N�mero do INODE
|*
iget:
	pushw	r3			|* Salva r3
	pushw	r4			|* Salva r4

.if	DEBUG
	movb	#'I',r0
	call	putc
	movl	INO(fp),r0
	call	puthex
.endif	DEBUG

	movw	#linear_cb,r4
	movb	#8,l_cnt(r4)
	movw	#AREA,l_area(r4)
   |***	movw	es,l_seg(r4)	***|
	movl	INO(fp),r0
	lsrl	#5,r0			|* Calcula o n�mero do bloco (BL4)
	lsll	#3,r0			|* Transforma BL4 em BL
	movl	r0,l_bno(r4)

	call	phys_read

	movw	INO(fp),r4		|* Calcula o deslocamento
	andw	#31,r4
	lslw	#7,r4
	addw	#AREA+n_addr,r4

|*	Copia os 16 endere�os diretos + indireto simples

   |***	movw	#...,r4			|* r4 => endere�os no INODE
	movw	#BLADDR,r5  		|* r5 => endere�os diretos
	movw	#16+1,r1
   |***	up
	repe
	movsl

|*	Ve se tem bloco indireto

7$:
	movl	IBADDR,r0
	tstl	r0
	jeq	9$

	movw	#linear_cb,r4
	movb	#8,l_cnt(r4)
	movw	#IBADDR,l_area(r4)
   |***	movw	es,l_seg(r4)	***|
	lsll	#3,r0			|* Transforma BL4 em BL
	movl	r0,l_bno(r4)

	call	phys_read

9$:
.if	DEBUG
	movb	#'a',r0
	call	putc
	movl	BLADDR,r0
	call	puthex
.endif	DEBUG

	popw	r4			|* Restaura r4
	popw	r3			|* Restaura r3

	rts

|*
|******	Fun��o para ler um Bloco Logico do Disco ****************
|*
|*	O No. do Bloco Logico � dado em LBNO, que � incrementado
|*	a cada chamada. No caso de leitura normal, a rotina retorna
|*	com o valor 1 em r0, e 0 em caso de EOF
|*
|*	LBNO => No. do Bloco Fisico
|*	BA   => Endereco do Buffer
|*
log_read:
	pushw	r4			|* Salva r4

.if	DEBUG
	movb	#'L',r0
	call	putc
	movl	LBNO(fp),r0
	call	puthex
.endif	DEBUG

	movw	LBNO(fp),r4		|* Obtem o no. l�gico e incrementa
	addw	#1,LBNO(fp)

	lslw	#2,r4			|* (4 bytes por endereco)

	movl	BLADDR(r4),r0		|* Carrega o Endereco Fisico

	tstl	r0			|* Desvia se N�O EOF
	jne	2$

	stc				|* Carry on => EOF
	jmp	3$
2$:
	movw	#linear_cb,r4
	movb	#8,l_cnt(r4)
	movw	BA(fp),r1
	movw	r1,l_area(r4)
	movw	es,l_seg(r4)
	lsll	#3,r0			|* Transforma BL4 em BL
	movl	r0,l_bno(r4)

   	call	phys_read 		|* L� o bloco e retorna com 1

	clc				|* Carry off => leu o bloco
3$:
	popw	r4			|* Restaura r3

	rts

|*
|******	�reas e V�riaveis ***************************************
|*
	.text
ETEXT:					|* Para marcar o final do TEXT

	.bss
EDATA:

BLADDR: .dsl	16			|*   16 Blocos Diretos
IBADDR: .dsl	1024			|* 1024 Blocos Indiretos

NAMES: 	.dsb	256			|* Caminho do boot2

AREA:	.dsb	BL4SZ			|* �rea para ler os diret�rios e inodes

END:
