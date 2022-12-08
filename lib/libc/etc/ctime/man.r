.bp 1
.he 'CTIME (libc)'TROPIX: Manual de Refer�ncia'CTIME (libc)'
.fo 'Atualizado em 27.01.99'Vers�o 3.1.6'Pag. %'

.b NOME
.in 5
 Convers�o de datas e tempos:
.sp
.wo "ctime      -"
fornece data e hora em ingl�s em uma cadeia
.br
.wo "btime      -"
fornece data e hora em portugu�s em uma cadeia
.br
.wo "localtime  -"
fornece data e hora locais
.br
.wo "gmtime     -"
fornece data e hora Universal (UT, GMT)
.br
.wo "asctime    -"
fornece data e hora em ingl�s em uma cadeia
.br
.wo "brasctime  -"
fornece data e hora em portugu�s em uma cadeia
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <time.h>

char	*ctime (const time_t *timer);
char	*btime (const time_t *timer);
TM		*localtime (const time_t *timer);
TM		*gmtime (const time_t *timer);
char	*asctime (const TM *tm);
char	*brasctime (const TM *tm);
.)l

.in
.sp
.b DESCRI��O
.in 5
As fun��es aqui descritas trabalham com tempos expressos em
dois formatos:

.in +3
.ip 1. 3
O tempo padr�o interno do sistema ("time_t"),
que cont�m o n�mero de segundos decorridos desde 00:00:00
do dia 1. de janeiro de 1970, hor�rio UT
(Tempo Universal, antes chamado de GMT).
.ip 2. 3
A estrutura "TM", que cont�m o tempo
j� convertido em horas, minutos, segundos, dia, dia da semana, mes, ano, etc..
(veja <time.h>).

.ep
.in -3

.sp
Internamente o tempo � sempre UT, enquanto que na estrutura "TM"
podemos ter o tempo UT ou LOCAL. O tempo LOCAL � obtido somando-se ao tempo
padr�o interno do sistema o valor do fuso hor�rio, retornado pela chamada ao sistema
"gettzmin" (sys).

.sp
As fun��es "ctime" e "btime" convertem um tempo padr�o interno do sistema,
apontado por "timer" em uma cadeia de 25 caracteres representando o tempo
LOCAL, com o seguinte formato:
.ce
	ctime:	"Thu Sep 25 13:25:22 1986\n"
.sp
.ce
	btime:	"13:25:22 QUI 25 set 1986\n"

.sp 
A fun��o "gmtime" converte um tempo padr�o interno do sistema,
apontado por "timer" em uma estrutura "TM", contendo o tempo UT.

.sp
A fun��o "localtime" converte um tempo padr�o interno do sistema,
apontado por "timer" em uma estrutura "TM", contendo o tempo LOCAL.

.sp
As fun��es "asctime" e "brasctime" convertem o tempo dado em uma estrutura
"TM" apontada por "tm" em um cadeia de caracteres como no caso de
"ctime" e "btime" descritas acima.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Um apontador para uma cadeia de 25 caracters ou um apontador
para uma estrutura "TM" definida em <time.h>, conforme a fun��o.

.in
.sp
.b OBSERVA��ES
.in 5
Estas fun��es n�o fazem qualquer ajuste autom�tico para o
hor�rio de ver�o j� que o mesmo no Brasil � adotado de
forma casu�stica e sem qualquer planejamento.

.sp
Todas as fun��es devolvem um ponteiro para uma �rea est�tica, e o
seu conte�do deve ser copiado caso elas sejam chamadas novamente.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
 (cmd) : date, data
 (sys) : time, gettzmin
 (libc): mktime, strftime, strtotime, getenv

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
