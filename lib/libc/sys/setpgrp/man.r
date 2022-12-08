.bp
.he 'SETPGRP (sys)'TROPIX: Manual de Refer�ncia'SETPGRP (sys)'
.fo 'Atualizado em 20.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "setpgrp -"
cria um novo grupo de processos 
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	setpgrp (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "setpgrp" cria um novo grupo de processos
cujo l�der ser� o processo que a chamou (ver "intro" (sys)).

.sp
Os outros membros do grupo ser�o os filhos deste processo.

.sp
A identifica��o do grupo a que pertence o processo
tem import�ncia para a chamada ao sistema "kill" (sys).

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A chamada devolve a identifica��o do novo grupo
de processos (que � igual ao PID do pr�prio processo).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
exec, fork, getpid, intro, kill, signal
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
