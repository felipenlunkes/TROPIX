.bp
.he 'FORK (sys)'TROPIX: Manual de Refer�ncia'FORK (sys)'
.fo 'Atualizado em 14.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "fork -"
cria um processo (sem compartilhar a regi�o "data")
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	fork (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "fork" cria um novo processo.
Este novo processo (processo "filho") compartilha a regi�o "text" com o
processo original (processo "pai"), e recebe c�pias das regi�es
"data" e "stack" (tamb�m do processo pai).

.sp
Para ver como criar um processo filho compartilhando tamb�m a
regi�o "data", veja "thread" (sys).

.sp
O processo filho herda do processo pai os seguintes atributos:

.sp
.in 10
Ambiente.

.sp
Indicadores de "feche na execu��o" dos descritores dos
arquivos abertos (veja "exec" (sys)).

.sp
Estados dos sinais (veja "signal" (sys)).

.sp
UID/GID real e efetivo.

.sp
Valor de "nice" (veja "nice" (sys)).

.sp
Identifica��o do grupo de terminais e de processos (veja "intro" (sys)).

.sp
Diret�rio corrente e raiz.

.sp
M�scara de cria��o de arquivos (veja "umask" (sys)).

.sp
.in 5
O processo filho difere do processo pai nos seguintes itens:

.sp
.in 10
O processo filho tem uma
identifica��o �nica (o seu PID, um inteiro de 1 a
2147483647).

.sp
Identica��o do pai do processo (os dois processos n�o
tem o mesmo pai).

.sp
O processo filho tem sua c�pia pr�pria dos descritores dos
arquivos abertos. No entanto, estes descritores t�m os ponteiros
de posi��o em comum com os descritores respectivos do
processo pai.

.sp
Trancas em regi�es de arquivos n�o s�o herdadas (ver "lockf" (sys)).

.sp
Os tempos do processo filho s�o zerados.

.sp
O alarme do rel�gio do processo filho � desligado.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema retorna zero para o processo filho
e retorna o PID do filho para o pai.
Em caso contr�rio, retorna -1 para o processo pai,
nenhum filho � criado, e indica em "errno" a causa do erro.

.in
.sp
.b OBSERVA��O
.in 5
Repare que a identifica��o de um processo no
TROPIX � um inteiro longo,
e pode ser maior do que 30000.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
exec, intro, thread, nice, signal, times, umask, wait
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
