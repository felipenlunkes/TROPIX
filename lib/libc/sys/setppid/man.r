.bp
.he 'SETPPID (libc)'TROPIX: Manual de Refer�ncia'SETPPID (libc)'
.fo 'Atualizado em 20.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "setppid -"
altera o pai de um processo

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	setppid (long ppid);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "setppid" � usada para modificar a paternalidade de
um processo. O novo pai do processo (que executou a chamada ao sistema)
passa a ser "ppid".

.sp
No momento, somente superusu�rios podem utilizar esta chamada ao sistema,
e o �nico valor de "ppid" aceito � 0 (zero), simbolizando o
processo "init". 

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
.b OBSERVA��O
.in 5
No momento, a �nica fun��o de "setppid" � a de tornar o processo um
filho de "init", para que o antigo processo pai n�o precise dar um
"wait" (sys).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
intro, getpid, getppid, wait
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
