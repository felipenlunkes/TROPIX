.bp
.he 'THREAD (sys)'TROPIX: Manual de Refer�ncia'THREAD (sys)'
.fo 'Atualizado em 22.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "thread -"
cria um processo (compartilhando a regi�o "data")

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	thread (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "thread" cria um novo processo.
Este novo processo (processo "filho") compartilha as regi�es "text" e "data"
com o processo original (processo "pai"), e recebe uma c�pia da regi�o
"stack" (tamb�m do processo pai).

.sp
Para ver como criar um processo filho sem compartilhar a
regi�o "data", veja "fork" (sys).

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
.b OBSERVA��ES
.in 5
Repare que a identifica��o de um processo no
TROPIX � um inteiro longo,
e pode ser maior do que 30000.

.sp
Como a regi�o "data" � compartilhada entre os processos pai e filho,
� necess�rio usar os mecanismos oferecidos por
"event" e "sema" (sys) para sincronizar a utiliza��o das vari�veis
alocadas nesta regi�o entre os dois processos.

.sp
Em caso particular, vale a pena lembrar de que as estruturas de
controle da "stdio" est�o situadas na regi�o "data", e � poss�vel
que as diversas sa�das dos processos fiquem "embaralhadas" sem
a utiliza��o de sincronismo.

Al�m disto, todos os "treads" (exceto o �ltimo) devem usar a chamada
ao sistema "_exit" ao inv�s de "exit" (sys) para impedir que a "stdio"
seja fechada e que as fun��es registradas por "atexit" sejam chamadas
prematuramente.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
exec, intro, fork, nice, signal, times, umask, wait,
.br
.wo "        event, sema, exit, atexit"
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
