.bp
.he 'WRITE (sys)'TROPIX: Manual de Refer�ncia'WRITE (sys)'
.fo 'Atualizado em 24.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "write -"
escreve em um arquivo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	write (int fd, const void *area, int count);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "write" tenta escrever "count" bytes
da �rea apontada por "area",
no arquivo associado ao descritor "fd".
O descritor "fd" � obtido por uma das chamadas "creat", "open",
"dup", "fcntl", ou "pipe".

.sp
Em dispositivos capazes de mover o ponteiro de posi��o do arquivo,
a escrita � feita a partir da posi��o dada pelo ponteiro associado a "fd".
Ap�s a escrita, o ponteiro � incrementado do valor de bytes
realmente escritos.

.sp
Em dispositivos incapazes de mover o ponteiro de  posi��o, a escrita
sempre � feita a partir da posi��o corrente. O ponteiro de posi��o
associado neste caso � indefinido.

.sp
Se o indicador "O_APPEND" estiver ligado, o ponteiro de posi��o
� colocado no final do arquivo antes de cada escrita.

.sp
Se a opera��o � realizada com sucesso, "write" retorna o n�mero
de bytes realmente escritos e colocados no arquivo; 
normalmente, se este n�mero n�o � igual a "count",
ocorreu alguma situa��o anormal.

.sp
Quando se tenta escrever em um arquivo regular no qual se acessaria
uma regi�o trancada por um outro processo (ver "lockf" (sys)):

.sp
.in +5
Se O_NDELAY (veja "open" (sys)) estiver ligado,
a escrita retorna imediatamente
com o erro "EAGAIN".

.sp
Se O_NDELAY estiver desligado, a escrita � bloqueada at�
o processo liberar a regi�o.
.ep
.in -5

.sp
Quando se tenta escrever  em um FIFO cheio, o comportamento
da chamada depende do indicador "O_NDELAY":

.sp
.in +5
Se O_NDELAY estiver ligado, a escrita retorna imediatamente
com uma indica��o de erro.

.sp
Se O_NDELAY estiver desligado, a escrita � bloqueada at� que
algu�m leia do FIFO (liberando espa�o), ou ent�o que ele seja fechado. 

.in -5
.sp
Temos ainda a possibilidade de usar a chamada ao sistema "write" para
escrever dados em uma rede de comunica��es
(veja "t_sndudata" e "t_snd" (xti)).

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve um inteiro
n�o negativo, indicando o n�mero de bytes efetivamente escritos.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b OBSERVA��O
.in 5
As escritas para um arquivo passam em geral atrav�s do
mecanismo de ger�ncia de blocos do TROPIX, que armazena a
informa��o para posterior escrita f�sica no disco.
Isto significa que
uma chamada ao sistema "write" pode retornar com sucesso,
e ocorrer um erro mais tarde, quando a informa��o for 
efetivamente escrita no disco.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
creat, dup, fcntl, ioctl, intro, lockf, lseek, open,
.br
.wo "        pipe"
.br
.wo "(xti): "
t_snd, t_sndudata
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
