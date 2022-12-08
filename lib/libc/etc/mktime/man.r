.bp
.he 'MKTIME (libc)'TROPIX: Manual de Refer�ncia'MKTIME (libc)'
.fo 'Atualizado em 27.01.99'Vers�o 3.1.6'Pag. %'

.b NOME
.in 5
Manipula��o de tempos:
.sp
.wo "mktime    -"
convers�o de "TM" no tempo padr�o "time_t"
.br
.wo "strftime  -"
formata��o de v�rios campos de tempo
.br
.wo "strtotime -"
convers�o de uma cadeia externa e "TM" em "time_t"
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <time.h>

time_t	mktime (TM *tp);
size_t	strftime (char *str, size_t maxsize,
				const char *format, const TM *tp);
time_t	strtotime (const char *str, TM *tp);
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
Nenhuma das fun��es aqui descritas realizam convers�es de fuso hor�rio.

.sp
A fun��o "mktime" converte o tempo dado na estrutura "TM" apontada
por "tp" no tempo padr�o interno do sistema ("time_t").
Al�m disto, os campos "tm_wday" e "tm_yday" s�o (re-)calculados e
recebem o valor correto.

.sp
A fun��o "strftime" converte, formata e escreve caracteres no vetor apontado
por "str", de acordo com a cadeia apontada por "format", em um estilo
semelhante � fun��o "sprintf" (libc).

.sp
Diversas cadeias tais como os dias da semana, nomes dos meses, ... s�o
influenciados pelo valor corrente da vari�vel LC_TIME do "locale" (libc).

.sp
A cadeia "format" consistem em zero ou mais especificac�es de convers�o
e caracteres normais. Uma especificac�o de convers�o consiste de um
caractere "\%" seguido de um caractere que determina qual a convers�o/formata��o
a ser feita. Todos os caracteres normais (incluindo o caractere NULO
finalizador) s�o copiados sem modifica��es no vetor.
S�o colocados um m�ximo de "maxsize" caracteres no vetor.
Cada especificac�o de convers�o � substitu�da pelos caracteres apropriados
(como descrito na lista abaixo) a partir de valores obtidos na estrutura
apontada por "tp".

.sp
.(t
As especifica��es de convers�o com os respectivas caracteres
de substitui��o s�o:

.in +3
.ip \%a
Nome do dia da semana abreviado, como por ex. "DOM".
.)t

.ip \%A
Nome do dia da semana completo, como por ex. "domingo".

.ip \%b
Nome do dia do m�s abreviado, como por ex. "jan".

.ip \%B
Nome do dia do m�s completo, como por ex. "janeiro".

.ip \%c
Representa��o da data e hora no estilo
.sp
.ce
"15:10:22 SAB 10 mar 1990".

.ip \%d
Dia do m�s como um n�mero decimal (01-31).

.ip \%H
Hora do dia (ciclo de 24 horas) como um n�mero decimal (00-23).

.ip \%I
Hora do dia (ciclo de 12 horas) como um n�mero decimal (01-12).

.ip \%j
Dia do ano como um n�mero decimal (001-366).

.ip \%m
M�s como um n�mero decimal (01-12).

.ip \%M
Minuto como um n�mero decimal (00-59).

.ip \%p
Parte do dia (AM ou PM).

.ip \%S
Segundo como um n�mero decimal (00-60).

.ip \%U
N�mero da semana no ano (semana come�ando pelo domingo) como um n�mero
decimal (00-53).

.ip \%w
Dia da semana como um n�mero decimal (0-6) (0 = domingo).

.ip \%W
N�mero da semana no ano (semana come�ando pela segunda feira) como um n�mero
decimal (00-53).

.ip \%x
Representa��o da data no estilo "SAB 10 mar 1990".

.ip \%X
Representa��o da hora no estilo "15:10:22".

.ip \%y
Ano (sem s�culo) como um n�mero decimal (00-99).

.ip \%Y
Ano (com s�culo) como um n�mero decimal (1970-2037).

.ip \%Z
Fuso hor�rio (obtido atrav�s de "gettzmin" (sys)) no formato "shhmm",
onde o "s" � o sinal "+" ou "-", "hh"
o n�mero de horas e "mm" o n�mero de minutos (por exemplo "-0300").

.ip \%\%
Caractere "\%"

.in -3
.ep

.sp
A fun��o "strtotime" recebe como argumentos uma cadeia de caracteres
apontada por "str" representando uma data na forma
.sp
.ce
      [[[[[ano]mes]dia]hora]minuto][:segundo]
.sp
e uma estrutura "TM" apontada por "tp", j� contendo uma
(possivelmente outra) data.
A fun��o faz uma fus�o destas informa��es dando prioridade �s
informa��es da cadeia.
Ela retorna a data no tempo padr�o interno do sistema ("time_t"),
al�m de atualizar a estrutura "TM".
Cada campo da cadeia deve ser num�rico, e conter exatamente 2 d�gitos
decimais. Ao inv�s de ":" pode ser usado ".".
Se forem dados todos os campos, n�o ser� utilizada nenhuma informa��o
original da estrutura, enquanto que se for dada uma cadeia vazia,
todas as informa��es ser�o obtidas da estrutura.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a fun��o "mktime" devolve o tempo padr�o interno
do sistema. Se este tempo n�o puder ser representado, ou se o conte�do
da estrutura dada contiver erros, a fun��o retorna -1.

.sp
Em caso de sucesso, a fun��o "strftime" devolve o n�mero de caracteres
colocados no vetor "str" (n�o incluindo o NULO finalizador).
No caso contr�rio, devolve ZERO, e o conte�do do vetor � indeterminado.

.sp
Em caso de sucesso, a fun��o "strtotime" devolve o tempo padr�o interno
do sistema. Se este tempo n�o puder ser representado, ou se o conte�do
da cadeia ou da estrutura dadas contiver erros, a fun��o retorna -1.

.in
.sp
.b OBSERVA��O
.in 5
A fun��o "strftime" n�o se preocupa com a possibilidade dos vetores
apontados por "str" e "format" serem superpostos.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
data
.br
.wo "(sys): "
time, gettzmin
.br
.wo "(libc):"
ctime, localtime, sprintf, locale
.br

.in
.sp
.(t
.b EXEMPLOS
.in 5
O modo usual de utiliza��o da fun��o "strtotime" �:
.sp
.nf
	#include <time.h>
		..........................

		time_t		tempo;
		char		*str;

		..........................

		/* obt�m a cadeia "str" */

		..........................

		time (&tempo);
		tempo = strtotime (str, localtime (&tempo));
.fi
.)t
.sp
Repare que a pr�pria estrutura "TM" local da fun��o "localtime" est�
sendo utilizada e modificada.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
