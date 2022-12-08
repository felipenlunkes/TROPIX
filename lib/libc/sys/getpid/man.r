.bp
.he 'GETPID (sys)'TROPIX: Manual de Refer�ncia'GETPID (sys)'
.fo 'Atualizado em 14.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Obtem a identifica��o do:
.sp
.wo "getpid  -"
processo
.br
.wo "getpgrp -"
grupo de processos
.br
.wo "getppid -"
pai do processo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

long	getpid (void);
long	getpgrp (void);
long	getppid (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "getpid" devolve a identifica��o do processo.

.sp
A chamada ao sistema "getpgrp" devolve a identifica��o do
grupo de processos do qual este processo � membro.

.sp
A chamada ao sistema "getppid" devolve a identifica��o do 
pai do processo.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
exec, fork, intro, setpgrp, signal
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
