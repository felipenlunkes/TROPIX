.bp
.he 'TIME (sys)'TROPIX: Manual de Refer�ncia'TIME (sys)'
.fo 'Atualizado em 22.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Obtem a data e tempo:
.sp
.wo "time   -"
apenas em segundos
.br
.wo "mutime -"
em segundos e microsegundos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

time_t	time (time_t *tp);

#include <sys/types.h>
#include <sys/times.h>

int	mutime (MUTM *mp);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "time" retorna o n�mero de segundos decorridos
desde 00:00:00 do dia 1. de janeiro de 1970, hor�rio UT
(Tempo Universal, antes chamado de GMT).

.sp
Se "tp" for um ponteiro n�o NULO, este valor ser� tamb�m armazenado
na posi��o apontada por ele.

.sp
A chamada ao sistema "mutime" 
preenche a estrutura "MUTM" apontada por "mp" cujos membros s�o:

.sp
.nf
	time_t	mu_time;	/* Tempo (segundos) */
	time_t	mu_utime;	/* Tempo (micro-segundos) */
.fi

.sp
Esta chamada � uma extens�o da chamada ao sistema "time",
e armazena em "mu_time" o mesmo tempo descrito acima,
e em "mu_utime" o n�mero de microsegundos adicionais transcorridos.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema "time" retorna o tempo
(como descrito acima), e a chamada "mutime" retorna zero.
Em caso contr�rio, as chamadas retornam -1 e indicam em "errno" a causa do erro.

.in
.sp
.b OBSERVA��O
.in 5
A chamada "mutime" retorna o valor do tempo em microsegundos, por�m isto n�o
implica em que o rel�gio interno do computador tenha
esta resolu��o.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
stime
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
