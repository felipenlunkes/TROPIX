.bp
.he 'FCNTL (sys)'TROPIX: Manual de Refer�ncia'FCNTL (sys)'
.fo 'Atualizado em 14.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "fcntl -"
controle de arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>
#include <fcntl.h>

int	fcntl (int fd, int op, int arg);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "fcntl" permite controlar alguns dos atributos dos
arquivos abertos.
O argumento "fd" � um descritor de arquivos obtido atrav�s de uma
das chamadas "creat", "open", "dup", "fcntl", ou "pipe".

.sp
A opera��o executada � dada pelo argumento "op".
As opera��es dispon�veis s�o:

.in +3
.ip F_DUPFD 10
Devolve um novo descritor de arquivos com as seguintes caracter�sticas:

.sp
.in +5
Descritor de n�mero mais baixo dispon�vel, mas igual ou maior do que
"arg".

.sp
Mesmo arquivo aberto do que o descritor dado.

.sp
Mesmo ponteiro de posi��o do arquivo.

.sp
Mesmo modo de acesso (leitura, escrita ou leitura/escrita).

.sp
Mesmos indicadores de estado do arquivo dado.

.sp
Mesmas trancas nos arquivos (veja "lockf" (sys)).

.sp
Indicador de "feche na execu��o" desligado (ver "exec" (sys)).

.sp
.in -5
.ip F_GETFD 10
Obtem os indicadores do descritor "fd".
Atualmente, o �nico indicador implementado � o de "feche na execu��o"
(veja as observa��es).

.ip F_SETFD 10
Atribui o valor de "arg" aos indicadores do descritor "fd".

.ip F_GETFL 10
Obtem os indicadores de estado do arquivo associado ao descritor "fd".
Estes indicadores est�o descritos no arquivo <fcntl.h>. 

.ip F_SETFL 10
Atribui o valor de "arg" aos  indicadores do estado do arquivo associado ao
descritor "fd". Apenas os indicadores "O_APPEND" e "O_NDELAY"
("O_NONBLOCK") podem ser alterados (veja as observa��es).

.ep
.in -3

.(b
.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, o valor de retorno da chamada depende de "op"
como indica a lista seguinte:
.in 10
.ip F_DUPFD 10
Um novo descritor de arquivos.

.ip F_GETFD 10
Os valores dos indicadores.

.ip F_SETFD 10
O valor zero.

.ip F_GETFL 10
Os valores dos indicadores.

.ip F_SETFL 10
O valor zero.

.ep

.sp
.in 5
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.
.)b

.in
.sp
.b OBSERVA��ES
.in 5
N�o confunda os "indicadores do descritor do arquivo" com
os "indicadores do estado do arquivo".

.sp
Nesta vers�o do sistema, os indicadores do descritor dos arquivos
cont�m apenas um indicador definido (o de mais baixa ordem),
o de "feche na execu��o" (veja "execl" (sys)).

.sp
Entre os indicadores do estado dos arquivos temos "O_RDONLY",
"O_WRONLY", ..., "O_LOCK" (veja <fcntl.h>). Destes indicadores, apenas
"O_NDELAY" ("O_NONBLOCK") e "O_APPEND" 
podem ser alterados pela chamada "fcntl". 

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
close, creat, dup, exec, fork, lockf, open, pipe
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
