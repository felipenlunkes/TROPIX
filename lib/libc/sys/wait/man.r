.bp
.he 'WAIT (sys)'TROPIX: Manual de Refer�ncia'WAIT (sys)'
.fo 'Atualizado em 24.06.97'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "wait -"
espera um processo filho parar ou terminar
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	wait (int *status);

extern void	*_faddr;
extern void	*_fpc;
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "wait" suspende o processo pai (que a chamou)
at� que um dos seus filhos termine ou pare.
Este segundo caso ocorre quando um filho que chamou "ptrace" (sys)
entrou no estado STOP.
O recebimento de um sinal
causa o retorno prematuro da chamada, e se j� havia um
filho terminado ou parado antes da chamada, o retorno � imediato.

.sp
Se o ponteiro "status" for n�o NULO, dois bytes de informa��o
s�o armazenados na parte baixa do inteiro apontado por "status"
que (dependendo da causa do retorno), tem a seguinte interpreta��o:

.sp
.in 10
.ip 1. 3
EXIT:
.nf
			15	       8 7		0
			+---------------+---------------+
			|   byte mais	|   byte menos	|
			| significativo | significativo	|
			|		|		|
			|     exit	|     0x00	|
			+---------------+---------------+
.fi

.sp
Se o processo filho terminou em virtude de uma chamada "exit",
o byte menos significativo ser� igual a zero,
e o byte mais significativo conter�
o c�digo de retorno que o processo filho deu como argumento
� chamada "exit" (sys). 

.ip 2. 3
SINAL:

.nf
			15	       8 7		0
			+---------------+---------------+
			|   byte mais	|   byte menos	|
			| significativo | significativo	|
			|		|		|
			|     0x00	|     sinal	|
			+---------------+---------------+
.fi
.sp
Se o processo terminou em virtude de um sinal, o byte mais significativo
ser� igual a zero, e o byte menos significativo conter� o n�mero do
sinal que causou a termina��o. Al�m disto, se o bite
7 (0x80) estiver ligado, uma imagem do processo na mem�ria
foi copiada para o disco ("core dump"). 
No caso de alguns sinais espec�ficos (por exemplo, "SIGBUS"
e "SIGADR"), as vari�veis "_faddr" e "_fpc" conter�o o endere�o de acesso
e o endere�o de execu��o 
do erro que causou o t�rmino do filho.

.ip 3. 3
STOP:

.nf
			15	       8 7		0
			+---------------+---------------+
			|   byte mais	|   byte menos	|
			| significativo | significativo	|
			|		|		|
			|     sinal	|     0x3F	|
			+---------------+---------------+
.fi

.sp
Se o processo entrou no estado STOP, o byte menos significativo
ser� igual a "0x3F", e o byte mais significativo conter� o n�mero do
sinal que causou o processo a parar.

.ep
.in 5
.sp
Se um processo terminar sem esperar pelos seus processos filhos, o 
novo pai destes processos ser� o "init", o processo especial de
inicializa��o (veja "intro" (sys)).

.sp
Se um processo tiver mais de um filho, ser�o necess�rios
v�rias chamadas "wait", uma para cada filho.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve a identifica��o
do processo filho que terminou.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b OBSERVA��ES
.in 5
Um processo que termina, mas o seu processo pai n�o chama
"wait", permanece em um estado chamado "ZOMBIE", que
ocupa uma entrada da tabela de processos, o que �
indesej�vel.

.sp
.bc	/*************************************/
Tamb�m � poss�vel incluir em uma chamada a "attention" (sys)
.ec	/*************************************/
Tamb�m � poss�vel aguardar o t�rmino de um processo filho atrav�s
da chamada ao sistema "attention" (sys), utilizando o dispositivo
"/dev/grave".
Com isto, podemos aguardar simultaneamente v�rios eventos, como
a disponibilidade de dados para leitura em algum dispositivo, e o
t�rmino de um processo filho.
Ap�s o retorno de "attention" indicando que "h� dados dispon�veis"
em "/dev/grave", deve-se executar a chamada ao sistema "wait".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
exec, exit, fork, intro, pause, ptrace, signal,
.wo "         attention"
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
