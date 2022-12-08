.bp
.he 'PCNTL (sys)'TROPIX: Manual de Refer�ncia'PCNTL (sys)'
.fo 'Atualizado em 17.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "pcntl -"
fun��es de controle para processos e threads
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/pcntl.h>
#include <sys/syscall.h>

int	pcntl (int cmd, ...);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "pcntl" engloba uma s�rie de fun��es auxiliares
do sistema operacional TROPIX que controlam a execu��o de processos e/ou
threads.

.sp
O argumento "cmd" especifica a fun��o desejada,
e tanto o tipo do valor de retorno da chamada, assim como os tipos
dos argumentos adicionais s�o vari�veis, dependendo da fun��o
espec�fica.

.sp
As fun��es dispon�veis s�o:

.in +3
.ip 1. 4
P_PMUTIMES: preenche numa estrutura "PMUTMS"; os membros "seqtime" com
o valor do tempo de execu��o sequencial do processo ou thread;
os membros "cseqtime" com o tempo total de todos os processos e/ou
threads que s�o filhos do processo em quest�o;
os membros "partime" d� uma estimativa do tempo da
execu��o deste thread em paralelo com seus filhos se houvesse
processadores dispon�veis que permitissem todos os threads serem executados
em paralelo; e os membros "cpartime" d�o uma estimativa
do maior tempo gasto por um thread filho se houvesse processadores
dispon�veis e todos eles pudessem ser executados em paralelo.
Neste caso, a chamada tem a forma

.sp
.(l
		#include <sys/pcntl.h>
		#include <sys/times.h>
		#include <sys/syscall.h>

		int	pcntl (P_PMUTIMES, PMUTIMES *pmutimes);
.)l

.sp
Na estimativa dos tempos de processamento paralelo, esta fun��o leva em
considera��o os tempos em que os diversos threads est�o se sincronizando
atrav�s de eventos e sem�foros. Desta forma, tr�s threads, que necessitam
para a sua execu��o o uso exclusivo de uma regi�o cr�tica, ter�o uma estimativa
de tempo de execu��o em paralelo semelhante � execu��o sequencial.

.sp
Observar que enquanto todos os tempos do processo come�am a ser contados a
partir do in�cio do "fork", os tempos desta chamada s�o contados a partir do
final do "exec". Desta forma, por exemplo, o tempo sequencial que � obtido
pelo comando "ptime" (que usa esta chamada) � sempre inferior
� soma dos tempos "user" mais "sys" obtidos pelo comando "time", al�m de
ser, obviamente, independente do tempo de carga do programa.

.sp
A estimativa do tempo paralelo � aproximada. � f�cil verificar, entretanto,
que quanto maior a resolu��o do rel�gio do computador e quanto menor o
"time-slice" de execu��o de cada "thread", mais correta � a estimativa
deste tempo. 

.sp
Em caso de sucesso, a fun��o retorna o tempo em segundos desde a
�ltima carga do sistema operacional.

.ip 2. 4
P_GETSTKRGSZ: retorna o valor em bytes do tamanho da regi�o de stack
do processo. Neste caso, a chamada tem a forma

.sp
.(l
		#include <sys/pcntl.h>
		#include <sys/syscall.h>

		int	pcntl (P_GETSTKRGSZ);
.)l

.sp
Em caso de sucesso, a fun��o retorna o tamanho em bytes da regi�o de stack.

.ip 3. 4
P_SETSTKRGSZ:
aumenta o tamanho da regi�o de stack do processo. Se o valor dado,
sempre em bytes, � menor que o atual, o tamanho n�o � alterado.
Neste caso, a chamada tem a forma

.sp
.(l
		#include <sys/pcntl.h>
		#include <sys/syscall.h>

		int	pcntl (P_SETSTKRGSZ, int size);
.)l

.sp
Em caso de sucesso, a fun��o retorna o tamanho em bytes da regi�o de stack.

.ip 4. 4
P_GETPRI: retorna o valor da prioridade moment�nea do processo.
Esses valores no TROPIX est�o limitados entre 0 e 1999.
Neste caso, a chamada tem a forma


.sp
.(l
		#include <sys/pcntl.h>
		#include <sys/syscall.h>

		int	pcntl (P_GETPRI);
.)l

.sp
Em caso de sucesso, a fun��o retorna o valor moment�neo da prioridade do
processo.

.ip 5. 4
P_SETPRI:
altera a prioridade moment�nea de um processo.
Esses valores devem estar entre 0 e 999, para processos comuns, e
entre 0 e 1999 para processos de tempo real.
sempre em bytes, � menor que o atual, o tamanho n�o � alterado.
Esta chamada ao sistema � de uso restrito para superusu�rios.
Neste caso, a chamada tem a forma

.sp
.(l
		#include <sys/pcntl.h>
		#include <sys/syscall.h>

		int	pcntl (P_SETPRI, int value);
.)l

.sp
Em caso de sucesso, a fun��o retorna o valor moment�neo da
prioridade do processo.

.ip 6. 4
P_SETRTPROC: se "flag" � igual a 1,
transforma um processo ou thread qualquer em processo ou thread de tempo real. 
Se "flag" � igual a -1, 
transforma um processo ou thread qualquer em processo ou thread regular.
Outros valores de "flag" n�o alteram as caracter�sticas do processo ou
thread.
Esta chamada ao sistema � de uso restrito para superusu�rios.
Neste caso, a chamada tem a forma

.sp
.(l
		#include <sys/pcntl.h>
		#include <sys/syscall.h>

		int	pcntl (P_SETRTPROC, int flag);
.)l

.sp
Em caso de sucesso, a fun��o retorna zero,
se processo � regular e um se o processo � de tempo real.

.ip 7. 4
P_SETFPREGADDR:
indica ao sistema operacional o endere�o de usu�rio dos registros de
emula��o do coprocessador de ponto flutuante para que aquele possa fazer
o carga e o armazenamento dos valores corretos por ocasi�o das
trocas de contexto.
 Somente � usado pelas rotinas de emula��o do coprocessador de ponto
flutuante.
Neste caso, a chamada tem a forma

.sp
.(l
		#include <sys/pcntl.h>
		#include <sys/syscall.h>

		int	pcntl (P_SETFPREGADDR, void *addr);
.)l

.sp
Em caso de sucesso, a fun��o retorna zero,
se o endere�o est� no espa�o de dados do usu�rio.

.ep
.in -3

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, os respectivos valores de retorno j� foram dados.
Em caso contr�rio, a chamada retorna -1 e indica em "errno" a causa do erro.

.bc	/*************************************/
.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, o valor de retorno da chamada depende de "cmd"
como indica a lista seguinte:
.in 10
.ip P_PMUTIMES: 12
tempo em segundos desde o �ltimo boot.
.ip P_GETSTKRGSZ: 12
tamanho em bytes da regi�o de stack.
.ip P_SETSTKRGSZ: 12
tamanho em bytes da regi�o de stack.
.ip P_GETPRI: 12
valor moment�neo da prioridade do processo.
.ip P_SETPRI: 12
valor moment�neo da prioridade do processo.
.ip P_SETRTPROC: 12
zero, se processo comum, um, se processo de tempo real.
.ip P_SETRTPROC: 12
zero, se o endere�o est� no espa�o de dados do usu�rio.
.ep
.sp
.in 5
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.
.ec	/*************************************/

.in
.sp
.b OBSERVA��O
.in 5
Esta chamada n�o � padr�o, e pode sofrer
extens�es/altera��es conforme as necessidades.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd):  "
ptime, time
.br
.wo "(libc): "
times
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
