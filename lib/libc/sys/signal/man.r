.bp
.he 'SIGNAL (sys)'TROPIX: Manual de Refer�ncia'SIGNAL (sys)'
.fo 'Atualizado em 21.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "signal -"
ger�ncia de sinais
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>
#include <signal.h>

void (*signal) (int sig, void (*func) (int, void *, void *))
					(int, void *, void *);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "signal" permite o processo a escolher
uma de tr�s possibilidades de tratar a ocorr�ncia de um sinal.
O argumento "sig" especifica o sinal e o argumento "func"
especifica a escolha desejada.

.sp
O sinal pode ser um dos seguintes, exceto SIGKILL (que sempre
cancela o processo):
.br

.nf

	SIGHUP	1	/* hangup */
	SIGINT	2	/* interrup��o */
	SIGQUIT	3	/* quit */
	SIGILL	4	/* Instru��o inv�lida */
	SIGTRAP	5	/* Trace ou breakpoint */
	SIGIOT	6	/* I/O Trap */
	SIGEMT	7	/* Emulation Trap */
	SIGFPE	8	/* Exce��o de ponto flutuante */
	SIGKILL	9	/* kill, morte inevit�vel */
	SIGBUS	10	/* Bus error */
	SIGSEGV	11	/* Viola��o de segmenta��o */
	SIGSYS	12	/* Erro nos arg. de uma chamada ao sis. */
	SIGPIPE	13	/* Escrita em "pipe" sem leitor */
	SIGALRM	14	/* Alarme de rel�gio */
	SIGTERM	15	/* Sinal normal do comando "kill" */
	SIGADR	16	/* Erro de endere�amento */
	SIGDVZ	17	/* Divis�o por zero */
	SIGCHK	18	/* Instru��o "check" */
	SIGTRPV	19	/* Instru��o "trapv" */
	SIGVIOL	20	/* Viola��o de privilegio */
	SIGCHLD 21	/* T�rmino de um Filho */
	SIGABRT	22	/* Chamada � rotina ABORT */
	SIGUSR1	23	/* Sinal Reservado para o usu�rio (1) */
	SIGUSR2	24	/* Sinal Reservado para o usu�rio (2) */
.fi

.sp
O argumento "func" pode receber um de tr�s valores: SIG_DFL, SIG_IGN,
ou o endere�o de uma fun��o.
Os valores de SIG_DFL e SIG_IGN est�o definidos em <signal.h>,
e s�o macros que n�o podem ser confundidas com nenhuma fun��o
declarada pelo usu�rio.

.sp
As a��es prescritas pelos valores de "func" s�o as seguintes:
.in 8

.ip SIG_DFL 9
Termina o processo.
No caso da ocorr�ncia do sinal, o processo � terminado,
com todas as consequ�ncias descritas em "exit" (sys).
Para alguns destes sinais, uma imagem do processo na mem�ria
pode ser gravada no disco ("core dump"), para exame posterior.

.ip SIG_IGN 9
Ignora o sinal.
O sinal "sig" � ignorado (exceto o sinal SIGKILL, que n�o pode ser ignorado).

.ip fun��o 9
Intercepta o sinal.
No caso da ocorr�ncia do sinal, o processo executa a fun��o
interceptora cujo endere�o � "func".
Esta fun��o deve ter a forma

.sp
.in +5
	void	func (int signo, void *pc,  void *fa);
.in -5

.sp
O argumento "signo" � o n�mero do sinal ocorrido;
o argumento "pc" cont�m
o contador do programa no momento da ocorr�ncia do sinal;
o argumento "fa" cont�m o endere�o de mem�ria que foi tentado
acessar, gerando uma exce��o e um sinal associado
(este �ltimo argumento s� � definido para alguns sinais,
tais como SIGBUS, SIGADR e SIGSEGV). 

.bc	/*************************************/
.sp
No caso particular do sinal SIGREAD, a fun��o interceptora
� chamada com a forma:

.sp
.in +5
	func (signo, fd);
.in -5

.sp
onde "fd" � o descritor do arquivo com os dados dispon�veis
(veja "sigread" (sys)).
.ec	/*************************************/

.sp
Antes de iniciar a fun��o, o valor de "func" do sinal ocorrido
� restaurado para SIG_DFL, exceto para os sinais SIGILL e
SIGTRAP.

.sp
Ap�s a execu��o da fun��o interceptadora, o processo
retorna para o ponto que estava executando quando foi interrompido
pelo sinal. No caso de alguns sinais, tais como SIGBUS, SIGSEGV
e outros, o ponto de retorno pode ser a pr�pria instru��o que
originou o sinal, podendo acarretar malhas sem fim.  

.sp
Quando um sinal que deve ser interceptado ocorre durante um "read" (sys),
"write" (sys), "open" (sys) ou "ioctl" (sys) em um dispositivo lento
(tal como uma linha de comunica��es, mas n�o um arquivo em disco),
ou durante um "pause" (sys) ou "wait" (sys), a fun��o interceptadora
� executada, e a chamada ao sistema interrompida pode retornar
erro -1, com o c�digo de erro "EINTR".

.sp
Resultados imprevis�veis ocorrer�o se for dado um endere�o
inv�lido como sendo de uma fun��o interceptadora.

.sp
O sinal SIGKILL n�o pode ser interceptado.
.ep

.sp
.in 5
Uma chamada a "signal" cancela um sinal pendente, exceto se ele
for o sinal SIGKILL.

.ep
.in 0
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve o valor
antigo de "func" para este sinal.
Em caso contr�rio, devolve SIG_ERR e indica em "errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
kill
.br
.wo "(sys): "
intro, kill, pause, wait
.br
.wo "(libc):"
setjmp
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
