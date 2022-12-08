.bp
.he 'SIGCHILD (sys)'TROPIX: Manual de Refer�ncia'SIGCHILD (sys)'
.fo 'Atualizado em 21.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "sigchild -"
prepara um processo filho para enviar o sinal
.wo "           SIGCHLD"
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	sigchild (long pid);
.)l

.in
.sp
.b DESCRI��O
.in 5
Normalmente, um processo pai espera
um processo filho terminar ou entrar no estado STOP (ver "ptrace" (sys)),
atrav�s da chamada ao sistema "wait".
Esta espera, no entanto, � s�ncrona, o que significa que
o processo pai s� ir� retornar da chamada ao sistema "wait" quando
um de seus filhos terminar ou entrar no estado STOP.

.sp
A chamada ao sistema "sigchild" permite efetuar este protocolo
de maneira ass�ncrona. Isto � feito do seguinte modo:
ap�s a cria��o do processo filho, o pai chama "sigchild" dando
como argumento "pid" a identifica��o do processo filho. 
Quando este filho terminar ou entrar no estado STOP,
ele enviar� o sinal
"SIGCHLD" ao pai (ver "signal" (sys)),
o qual, atrav�s da
intercepta��o do sinal, pode efetuar
a chamada "wait", j� com a certeza de que um dos filhos terminou ou
est� no estado STOP.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve zero.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b OBSERVA��ES
.in 5
N�o esquecer de que, se o processo pai n�o programar o
sinal "SIGCHLD"
para ser interceptado ou ignorado, ele causar� o seu t�rmino.

.sp
A chamada ao sistema "sigchild" � irrevers�vel,
isto �,
uma vez efetuada a chamada, o filho inexoravelmente enviar� o sinal.
Se o sinal se tornar desnecess�rio,
o pai deve tomar provid�ncias para ignor�-lo.

.sp
Se o processo filho entrar no estado STOP mais de uma vez,
o sinal ser� enviado cada
vez que isto ocorrer
(al�m, naturalmente, de quando o processo terminar).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
signal, ptrace
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
