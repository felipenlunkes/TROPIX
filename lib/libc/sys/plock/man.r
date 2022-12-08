.bp
.he 'PLOCK (sys)'TROPIX: Manual de Refer�ncia'PLOCK (sys)'
.fo 'Atualizado em 18.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "plock -"
tranca/libera um processo na mem�ria interna
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	plock (int flag);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "plock" permite a uma processo ficar trancado
na mem�ria interna. Esta chamada � permitida apenas a processos
cujo UID efetivo � de superusu�rio.

.sp
Processos trancados na mem�ria interna ficam imunes ao "swapping",
exceto se n�o houver espa�o adjacente ao processo na mem�ria
durante um aumento de tamanho do processo.

.sp
Se "flag" for n�o-NULO, o processo � trancado; em caso contr�rio
� destrancado.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve ZERO.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b OBSERVA��O
.in 5
Processos trancados na mem�ria interna interferem com a compacta��o
da mem�ria interna e podem causar "deadlock".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
exec, exit, fork
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
