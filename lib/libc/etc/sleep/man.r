.bp 1
.he 'SLEEP (libc)'TROPIX: Manual de Refer�ncia'SLEEP (libc)'
.fo 'Atualizado em 26.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
sleep - suspende a execu��o do processo por um per�odo

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

int	sleep (int n);
.)l

.in
.sp
.b DESCRI��O
.in 5
O processo corrente tem a sua execu��o suspensa por um per�odo 
de "n" segundos.

.sp
O tempo real da suspens�o pode
ser inferior ao pedido por duas raz�es: em primeiro lugar, o mecanismo
de tempo utilizado pelo sistema � baseado em
intervalos de um segundo, e o
pedido em geral n�o ocorre exatamente no in�cio de um
intervalo; em segundo lugar, um outro sinal (por exemplo, vindo
de um outro processo), pode vir antes do final do per�odo desejado.

.sp
O tempo real da suspens�o pode tamb�m
ser superior ao pedido, devido ao congestionamento do sistema.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Normalmente, "sleep" retorna zero. No caso de haver um SIGALRM pendente
antes do final do per�odo desejado, "sleep" retorna o n�mero de segundos
que o processo retornou prematuramente.

.in
.sp
.b OBSERVA��O
.in 5
A rotina � implementada utilizando o sinal SIGALRM. O estado anterior
deste sinal � restaurado, ap�s a suspens�o do processo. 

.in
.sp
.b
VEJA TAMB�M
.r
.nf
     (sys): alarm, pause, signal
.fi


.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
