.bp
.he 'ALARM (sys)'TROPIX: Manual de Refer�ncia'ALARM (sys)'
.fo 'Atualizado em 11.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "alarm -"
prepara um alarme do rel�gio
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

unsigned int	alarm (unsigned int seg);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "alarm" prepara o rel�gio de alarme do processo
para enviar o sinal "SIGALRM" daqui a "seg" segundos (de tempo real). 

.sp
Apenas um pedido de alarme pode estar ativo em cada instante; cada
pedido (caso ainda n�o tenha ocorrido o alarme) cancela o anterior.

.sp
Se "seg" � NULO, o pedido de alarme (se houver algum) � cancelado.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A chamada ao sistema retorna o tempo restante do rel�gio de alarme
do processo, ou ZERO se n�o houve uma chamada anterior para "alarm".

.in
.sp
.b OBSERVA��O
.in 5
Se o sinal n�o foi programado para ser ignorado
ou interceptado, o processo � terminado.
.sp
O tempo real do intervalo entre a chamada ao sistema e o envio do sinal
pode ser inferior ao pedido porque o mecanismo
de tempo utilizado pelo sistema � baseado em
intervalos de um segundo, e o 
pedido em geral n�o ocorre exatamente no in�cio de um
intervalo.
Por outro lado, ele tambem pode ser superior ao pedido,
devido ao congestionamento
do sistema.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
fork, pause, signal
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
