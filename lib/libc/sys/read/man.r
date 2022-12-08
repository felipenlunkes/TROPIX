.bp
.he 'READ (sys)'TROPIX: Manual de Refer�ncia'READ (sys)'
.fo 'Atualizado em 18.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "read -"
l� de um arquivo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	read (int fd, void *area, int count);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "read" tenta ler "count" bytes do arquivo
associado ao descritor "fd" na �rea apontada por "area".
O descritor "fd" � obtido por uma das chamadas "creat", "open",
"dup", "fcntl", ou "pipe".

.sp
Em dispositivos capazes de mover o ponteiro de posi��o do arquivo,
a leitura � feita a partir da posi��o dada pelo ponteiro associado a "fd".
Ap�s a leitura, o ponteiro � incrementado do valor de bytes
realmente lidos.

.sp
Em dispositivos incapazes de mover o ponteiro de  posi��o, a leitura
sempre � feita a partir da posi��o corrente. O ponteiro de posi��o
associado neste caso � indefinido.

.sp
Se a opera��o � realizada com sucesso, "read" retorna o n�mero
de bytes realmente lidos e colocados na �rea; este n�mero pode
ser menor do que "count" se o dispositivo � uma linha de comunica��o
(veja "ioctl" (sys) e "termio" (fmt)), ou ent�o se o n�mero
de bytes restantes no arquivo � inferior a "count". Se o final
do arquivo foi atingido, � retornado um valor NULO.

.sp

Quando se tenta ler de um arquivo regular no qual se acessaria
uma regi�o trancada por um outro processo (ver "lockf" (sys)):

.sp
.in +5
Se O_NDELAY (veja "open" (sys)) estiver ligado,
a leitura retorna imediatamente
com o erro "EAGAIN".

.sp
Se O_NDELAY estiver desligado, a leitura � bloqueada at�
o processo liberar a regi�o.
.ep
.in -5
.sp

Quando se tenta ler  de um FIFO vazio:

.sp
.in +5
Se O_NDELAY estiver ligado, a leitura retorna imediatamente
com um valor NULO.

.sp
Se O_NDELAY estiver desligado, a leitura � bloqueada at� que
alguem escreva no FIFO, ou ent�o que ele seja fechado. 
.ep
.in -5
.sp

Quando se tenta ler de uma linha de comunica��o sem dados
dispon�veis no momento:

.sp
.in +5
Se O_NDELAY estiver ligado, a leitura retorna imediatamente
com um valor NULO.

.sp
Se O_NDELAY estiver desligado, a leitura � bloqueada at� que
dados se tornem dispon�veis.
.ep
.in -5

.sp
Temos ainda a possibilidade de usar a chamada ao sistema "read" para
ler dados vindos de uma rede de comunica��es
(veja "t_rcvudata" e "t_rcv" (xti)).

.bc	/*************************************/
.sp
Temos ainda a possibilidade de ler assincronamente de v�rias linhas de
comunica��es simultaneamente (veja "sigread" (sys)).
.ec	/*************************************/

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve um inteiro
n�o negativo, indicando o n�mero de bytes efetivamente lidos. 
Um valor NULO indica o final do arquivo, exceto os casos
indicados acima.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
creat, dup, fcntl, ioctl, intro, lockf, open, pipe,
.br
.wo "(fmt): "
termio
.br
.wo "(xti): "
t_rcv, t_rcvudata
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
