.bp
.he 'PTRACE (sys)'TROPIX: Manual de Refer�ncia'PTRACE (sys)'
.fo 'Atualizado em 18.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "ptrace -"
controla a execu��o de um processo filho
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	ptrace (int req, int pid, int addr, int data);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "ptrace" fornece um m�todo pelo qual um processo
pai pode controlar a execu��o de um processo filho.
Sua utiliza��o principal � na implementa��o da depura��o simb�lica
(veja "wsdb" (cmd)).

.sp
O processo filho comporta-se normalmente at� receber um sinal
(ver "signal" (sys)), quando entra no estado STOP, e o processo
pai � informado atrav�s de uma chamada ao sistema "wait" (sys),
ou assincronamente atrav�s do sinal SIGCHLD (ver "sigchild" (sys)). 

.sp
Quando o processo filho est� no estado STOP, o seu pai pode
examinar e modificar o processo na mem�ria, utilizando a chamada ao
sistema "ptrace". Al�m disto, o pai pode causar o filho a terminar
ou continuar a execu��o, com a possibilidade de ignorar o
sinal que causou a entrada no estado STOP.

.sp
O argumento "req" determina a a��o de "ptrace",
e pode ter um dos seguintes valores:
.in 8

.ip 0 7
Esta a��o deve ser pedida pelo processo filho, para que a sua execu��o possa
ser controlado pelo pai.
Ela liga um indicador para que o processo entre no estado STOP
ao receber um sinal.
Por medida de seguran�a, esta chamada desliga o mecanismo de
"set user ID" e "set group ID", em uma subseq�ente chamada ao sistema
"exec" (sys).
Se o processo filho chamar "exec", ele receber� o sinal SIGTRAP,
entrando no estado STOP.

.sp
Os argumentos "pid", "addr" e "data" s�o ignorados,
e o valor de retorno n�o � definido.
Se o pai do processo n�o controlar a execu��o do filho,
ocorrer�o resultados imprevis�veis.

.ep
.in 5
.sp
As a��es seguintes podem apenas ser pedidas pelo processo pai.
Em cada uma delas, "pid" � a identifica��o do processo filho,
que tem de estar no estado STOP para que estas a��es possam
ser realizadas.
Todas as leituras/escritas s�o realizadas em unidades de palavras
(32 bites), em endere�os pares.
Todos os endere�os s�o virtuais no espa�o de endere�amento do
processo filho, com exce��o dos endere�os da UPROC
(extens�o da tabela de processos, veja <sys/uproc.h>),
que s�o relativos ao in�cio desta.

.sp
.in 8
.ip "1, 2" 7
Uma palavra contida no endere�o "addr" do processo filho
� retornada ao pai. O argumento "data" � ignorado.

.ip 3 7
Uma palavra contida no endere�o "addr" da UPROC
do processo filho
� retornada ao pai. O argumento "data" � ignorado.

.ip "4, 5" 7
O valor dado pelo argumento "data" � escrito na
palavra de endere�o "addr" do processo filho.
Deve-se utilizar a 
a��o "4" para escrever na regi�o do texto do processo
filho e a a��o "5" para a regi�o de dados. 
Isto � importante, principalmente para manter a consist�ncia
dos textos de
programas reentrantes (veja "ld" (cmd)).
No caso de sucesso, o valor escrito � retornado.

.ip "6" 7
Atrav�s desta a��o, podem ser escritas algumas
palavras na UPROC do filho.
O valor a ser escrito � dado pelo argumento "data",
e o endere�o por "addr".
Apenas alguns dos registros internos e os
c�digos de condi��o da palavra de estado do processador
podem ser escritos.

.ip "7" 7
O processo filho continua a execu��o.
Se "addr" for diferente de "1", a execu��o ser� continuada
a partir do endere�o "addr". Em caso contr�rio, ser� continuada
a partir do ponto de interrup��o.
Se "data" for igual a ZERO, todos os sinais pendentes s�o
cancelados antes de continuar a execu��o.
Se "data" contiver um n�mero v�lido de sinal,
os sinais pendentes s�o
cancelados,
e a execu��o continua como se
o processo filho houvesse recebido o sinal "data".
No caso de sucesso, o valor de "data" � retornado.

.ip "8" 7
Esta a��o causa o filho a terminar do mesmo modo que
"exit" (sys).

.ip "9" 7
Esta a��o liga o bite de "trace"
da palavra de estado do processador
e em seguida executa os passos da a��o "7".
Este bite causa a interrup��o ap�s apenas uma
instru��o de m�quina, possibilitando o
controle passo a passo do filho.

.ep
.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Exceto nos casos mencionados acima, "ptrace" retorna 
o valor de "data" em caso de sucesso,
e "-1" em caso contr�rio
(indicando em "errno" a causa do erro).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
wsdb
.br
.wo "(sys): "
signal, wait, sigchild, exit
.br

.in
.sp
.(t
.b ESTADO
.in 5
Efetivo.
.)t
