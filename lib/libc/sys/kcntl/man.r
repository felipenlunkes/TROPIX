.bp
.he 'KCNTL (sys)'TROPIX: Manual de Refer�ncia'KCNTL (sys)'
.fo 'Atualizado em 22.08.01'Vers�o 4.0.0'Pag. %'

.b NOME
.in 5
.wo "kcntl -"
fun��es de controle do n�cleo do sistema operacional
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/kcntl.h>
#include <sys/syscall.h>

int	kcntl (int cmd, ...);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "kcntl" engloba uma s�rie de fun��es auxiliares
do n�cleo do sistema operacional TROPIX, visando efetuar um controle
din�mico sobre certos fun��es do n�cleo, assim como auxiliar o
implementa��o de alguns utilit�rios especiais.

.sp
O argumento "cmd" especifica a fun��o desejada,
e tanto o tipo do valor de retorno da chamada, assim como os tipos
dos argumentos adicionais s�o vari�veis, dependendo da fun��o
espec�fica.

.sp
As fun��es dispon�veis s�o:

.in +3
.ip 1. 4
K_GETSYMGN: preenche a estrutura apontada por "sym" com uma c�pia
da entrada da tabela de s�mbolos do n�cleo do sistema operacional
TROPIX referente ao identificador contido na estrutura.

.sp
No argumento "len" deve ser dado o comprimento do identificador.

.sp
Neste caso, a chamada tem a forma:

.sp
.(l
		#include <sys/types.h>
		#include <sys/kcntl.h>
		#include <sys/syscall.h>

		#include <a.out.h>

		int kcntl (K_GETSYMGN, int len, SYM *sym);
.)l

.sp
Esta fun��o � similar � fun��o "nlist" (libc) utilizada com o
arquivo "/tropix", s� que � bem mais r�pida, pois utiliza
a tabela de s�mbolos da mem�ria interna. Naturalmente,
s� pode ser utilizada se a carga do sistema operacional
foi realizada com a tabela de s�mbolos.

.sp
Em caso de sucesso, a fun��o retorna zero.

.ip 2. 4
K_GETSYMGA: preenche a estrutura apontada por "sym" com uma c�pia
da entrada da tabela de s�mbolos do n�cleo do sistema operacional
TROPIX referente ao identificador cujo endere�o � o mais pr�ximo de
"addr" (mas n�o superior).

.sp
No membro "s_nm_len" da estrutura deve ser dado o comprimento
do identificador m�ximo para o qual a estrutura "sym" foi alocada.

.sp
.(t
Neste caso, a chamada tem a forma:

.sp
.(l
		#include <sys/types.h>
		#include <sys/kcntl.h>
		#include <sys/syscall.h>

		#include <a.out.h>

		int kcntl (K_GETSYMGN, ulong addr, SYM *sym);
.)l
.)t

.sp
Esta fun��o s� pode ser utilizada se a carga do sistema operacional
foi realizada com a tabela de s�mbolos.

.sp
Em caso de sucesso, a fun��o retorna zero.

.ip 3. 4
K_GETDEV: obtem a identifica��o ("major" + "minor") do dispositivo
especial de blocos cujo nome � apontado por "dev_nm" (sem o "/dev").

.sp
Neste caso, a chamada tem a forma:

.sp
.(l
		#include <sys/kcntl.h>
		#include <sys/syscall.h>

		int kcntl (K_GETDEV, const char *dev_nm);
.)l

.sp
Esta fun��o consulta a tabela interna "disktb" do n�cleo do
sistema operacional TROPIX. O Utilit�rio "prdisktb" (cmd) fornece
uma listagem completa desta tabela.

.sp
Em caso de sucesso, a fun��o retorna a identifica��o do dispositivo.

.ip 4. 4
K_GETDEVNM: obtem o nome (sem o "/dev") do dispositivo especial de
blocos cuja identifica��o ("major" + "minor") do dispositivo �
dada por "dev". O nome � armazenado na �rea apontada por "dev_nm"
(que deve ter espa�o para no m�nimo 16 caracteres).

.sp
Neste caso, a chamada tem a forma:

.sp
.(l
		#include <sys/kcntl.h>
		#include <sys/syscall.h>

		int kcntl (K_GETDEVNM, int dev, char *dev_nm);
.)l

.sp
Esta fun��o consulta a tabela interna "disktb" do n�cleo
do sistema operacional TROPIX. O Utilit�rio "prdisktb" (cmd)
fornece uma listagem completa desta tabela.

.sp
Em caso de sucesso, a fun��o retorna o pr�prio endere�o de "dev_nm"
(deve-se usar um "cast" para "char *").

.ip 5. 4
K_PUTCVTB: modifica uma das tabelas de convers�o de caracteres
das linhas de comunica��o.

.sp
Neste caso, a chamada tem a forma:

.sp
.(l
		#include <sys/types.h>
		#include <sys/kcntl.h>
		#include <sys/syscall.h>

		#include <termio.h>

		int kcntl (K_PUTCVTB, int tb, const char *addr);
.)l

.sp
O c�digo de caracteres padr�o do TROPIX � o ISO (CBII),
mas esta fun��o permite a utiliza��o de terminais/impressoras
com outros c�digos de caracteres.

.sp
O argumento "tb" deve ter um dos valores "USER1" ou "USER2", modificando
as tabelas correspondentes a estes parametros do comando
"stty" (cmd). As outras duas tabelas n�o podem ser modificadas. 

.sp
O argumento "addr" � um ponteiro para um vetor de 256
caracteres, onde "addr[i]" deve ter o c�digo desejado
correspondente ao caracter ISO "i".

.sp
Em caso de sucesso, a fun��o retorna zero.

.ip 6. 4
K_SEMAFREE: libera o recurso pelo qual o processo "pid" est�
esperando.

.sp
Neste caso, a chamada tem a forma:

.sp
.(l
		#include <sys/kcntl.h>
		#include <sys/syscall.h>

		int kcntl (K_SEMAFREE, long pid);
.)l

.sp
Esta fun��o for�a a libera��o do recurso pelo qual o processo "pid"
est� esperando, seja qual for o seu tipo ("SLEEP", "SEMA" ou "EVENT"),
fazendo com que o processo seja "acordado".
Isto � uma opera��o de "p�nico", s� permitida ao superusu�rio,
e devendo ser empregada apenas em situa��es graves,
pois pode causar inconsist�ncias na ger�ncia do sincronismo.

.sp
Em caso de sucesso, a fun��o retorna zero.

.ip 7. 4
K_GETPSZ: preenche a estrutura apontada por "kpsz", forncecento os
tamanhos das diversas partes do processo que chamou "kcntl".

.sp
Neste caso, a chamada tem a forma:

.sp
.(l
		#include <sys/kcntl.h>
		#include <sys/syscall.h>

		int kcntl (K_GETPSZ, KPSZ *kpsz);
.)l

.sp
A estrutura "KPSZ" cont�m os membros "k_tsize" (tamanho do texto),
"k_dsize" (tamanho do data+bss) e  "k_ssize" (tamanho da pilha de execu��o),
todos em bytes (ver <sys/kcntl.h>).
Estes tamanhos s�o obtidos a partir das regi�es de mem�ria efetivamente
alocadas pelo sistema operacional para o processo.

.sp
Repare que, no entanto, os tamanhos s�o arredondados de acordo com a ger�ncia
de mem�ria do processador e que o texto de um processo n�o reentrante
� considerado como parte do "data".

.sp
Em caso de sucesso, a fun��o retorna zero.

.ip 8. 4
K_GETMMU: preenche uma estrutura "UPROC" e uma �rea com informa��es
relativas � ger�ncia de mem�ria.

.sp
Neste caso, a chamada tem a forma:

.sp
.(l
		#include <sys/common.h>
		#include <sys/dir.h>
		#include <sys/uerror.h>
		#include <sys/uproc.h>
		#include <sys/kcntl.h>
		#include <sys/syscall.h>

		int kcntl (K_GETMMU, UPROC *up, void *mmu);
.)l

.sp
A �rea apontada por "up" � preenchida com a estrutura UPROC
do processo.

.sp
No caso do ICARUS, a �rea apontada por "mmu" � preenchida com os
4096 "shorts" que comp�e a "PCT" (Page control table).

.sp
No caso do PC, a �rea apontada por "mmu" � preenchida seq�encialmente
com 5 tabelas de p�ginas (cada uma com 4096 bytes): a de "text", "data",
"phys", "ipc" e "stack".

.sp
De posse destas tabelas, um programa de usu�rio pode verificar
se a ger�ncia de mem�ria est� corretamente carregada.

.sp
Em caso de sucesso, a fun��o retorna zero.

.ip 9. 4
K_SETPREEMTION: liga/desliga a "preemption", ou seja, a capacidade da
troca de processos durante a execu�ao do sistema operacional em
modo "supervisor".

.sp
Neste caso, a chamada tem a forma:

.sp
.(l
		#include <sys/kcntl.h>
		#include <sys/syscall.h>

		int kcntl (K_SETPREEMPTION, int flag, int cpuid);
.)l

.sp
Com um valor positivo para "flag", a "preemption" da CPU "cpuid" � ligada;
com um valor negativo, a "preemption" � desligada; um valor NULO
possibilita obter o estado atual da "preemption" sem alter�-lo.

.sp
Em caso de sucesso, a fun��o retorna o estado atual (ap�s a chamada) da
"preemption": 1 se ligada, 0 se desligada.

.ip 10. 4
K_GET_DEVTB: obtem uma entrada ou a tabela completa "disktb" de dispositivos,
dispon�vel no n�cleo do sistema operacional TROPIX.

.sp
Neste caso, a chamada tem a forma:

.sp
.(l
		#include <sys/types.h>
		#include <sys/disktb.h>
		#include <sys/kcntl.h>
		#include <sys/syscall.h>

		int kcntl (K_GET_DEV_TB, int dev, DISKTB *dp);
.)l

.sp
Se "dev" for diferente de NODEV, a chamada preenche a estrutura
apontada por "dp" com a entrada correspondente ao dispositivo "dev".
Neste modo, em caso de sucesso, a fun��o retorna zero.

.sp
Se "dev" for igual a NODEV, e o ponteiro "dp" for NULO,
a chamada retorna o n�mero de entradas da tabela
(incluindo uma entrada vazia ao final).

.sp
Se "dev" for igual a NODEV, e o ponteiro "dp" for n�o NULO, a chamada
copia a tabela inteira (incluindo uma entrada vazia ao final) para a
�rea apontada por "dp".
Neste modo, em caso de sucesso, a fun��o retorna o n�mero de entradas
da tabela (incluindo uma entrada vazia ao final).

.ip 11. 4
K_GET_PARTNM: obtem o nome correspondente a um tipo de parti��o
dos discos do PC.

.sp
.(t
Neste caso, a chamada tem a forma:

.sp
.(l
		#include <sys/kcntl.h>
		#include <sys/syscall.h>

		int kcntl (K_GET_PARTNM, int type, char *nm);
.)l
.)t

.sp
O vetor de caracteres apontado por "nm" � preenchido com o nome
simb�lico correspondente ao valor num�rico "type" dado.
Este valor "type" pode ser obtido atrav�s do membro "p_type" da
estrutura DISKTB (ver K_GET_DEVTB).
O vetor "nm" deve ter espa�o para (no m�nimo) PARTNM_MAXSZ caracteres.
 
.sp
Em caso de sucesso, a fun��o retorna zero.

.ip 12. 4
K_GET_FD_TYPE: obtem os tipos dos disquetes.

.sp
.(t
Neste caso, a chamada tem a forma:

.sp
.(l
		#include <sys/kcntl.h>
		#include <sys/syscall.h>

		int kcntl (K_GET_FD_TYPE);
.)l
.)t

.sp
O inteiro retornado cont�m no seu byte de mais baixa ordem o tipo
de "/dev/fd0" e no byte seguinte o tipo de /dev/fd1".

.sp
O tipo � codificado do seguinte modo:

.sp
.(l
		0: Unidade de disquete n�o dispon�vel.
		1: Unidade de 5�, 360 Kb.
		2: Unidade de 5�, 1.2 Mb.
		3: Unidade de 3�, 720 Kb.
		4: Unidade de 3�, 1.44 Mb.
.)l

.ip 13. 4
K_DEBUG: consulta/atribui o valor de depura��o do n�cleo do TROPIX.

.sp
.(t
Neste caso, a chamada tem a forma:

.sp
.(l
		#include <sys/kcntl.h>
		#include <sys/syscall.h>

		int kcntl (K_DEBUG, valor);
.)l
.)t

.sp
Se "valor" for negativo, a fun��o retorna o valor atual de depura��o.

.sp
Se "valor" for nulo ou positivo, a fun��o atribui o "valor" dado � depura��o,
e retorna este valor.
Isto s� � permitido ao superusu�rio.

.ep
.in -3

.in
.sp
.(t
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, os respectivos valores de retorno j� foram dados.
Em caso contr�rio, a chamada retorna -1 e indica em "errno" a causa do erro.
.)t

.in
.sp
.b OBSERVA��O
.in 5
Esta chamada ao sistema n�o � padr�o, e pode sofrer
extens�es/altera��es conforme as necessidades.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd):  "
stty, prdisktb
.br
.wo "(libc): "
nlist
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
