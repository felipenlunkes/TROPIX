.bp
.he 'STIME (sys)'TROPIX: Manual de Refer�ncia'STIME (sys)'
.fo 'Atualizado em 22.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "stime -"
inicializa o tempo do sistema
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	stime (const time_t *tp);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "stime" inicializa o rel�gio do sistema.

.sp
O tempo dado no conte�do de "tp" deve conter o n�mero de segundos
decorridos desde 00:00:00 do dia 1. de janeiro de 1970,
hor�rio UT (Tempo Universal, antes chamado de GMT).
.sp
Somente superusu�rios podem alterar o rel�gio do sistema.

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
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
time
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
