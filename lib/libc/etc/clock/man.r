.bp 1
.he 'CLOCK (libc)'TROPIX: Manual de Refer�ncia'CLOCK (libc)'
.fo 'Atualizado em 05.01.00'Vers�o 3.2.3'Pag. %'

.b NOME
.in 5
Rotinas para a medi��o de tempo:
.sp
.wo "clock       -"
fornece o tempo de processador usado
.br
.wo "clockstamp  -"
marca o inicio da contagem de tempo
.br
.wo "clocktostr  -"
converte o tempo decorrido em uma cadeia 
.br
.wo "difftime    -"
calcula a diferen�a entre dois tempos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <time.h>

clock_t	clock (void);
int	clockstamp (void);
char	*clocktostr (char *line);
double	difftime (time_t time1, time_t time0);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "clock" retorna o tempo de processamento utilizado pelo programa
desde o seu in�cio.
Neste c�lculo s�o inclu�dos os tempos em modo usu�rio e supervisor  
tanto do pr�prio programa como de todos os seus filhos terminados.
Para obter o tempo em segundos, o valor retornado deve ser dividido
por CLK_TCK. 

.sp
O objetivo das fun��es "clockstamp" e "clocktostr"
� a medi��o dos tempos gastos em trechos de programas.
Ao contr�rio de "clock", os tempos dos filhos n�o s�o computados.

.sp
A fun��o "clockstamp" marca o tempo inicial, a partir
do qual ser� feita a contagem.

.sp
A fun��o "clocktostr" escreve na �rea fornecida atrav�s do ponteiro "line"
uma cadeia de 65 bytes, no formato

.sp
.nf
  REAL  0:00:06.868       USER  0:00:06.622       SYS   0:00:00.098
.fi

.sp
contendo o tempo real transcorrido, o tempo do trecho do programa
em modo usu�rio e o tempo em modo do sistema.

.sp
Os tempos s�o dados em
horas, minutos, segundos e mil�simos de segundos.

.sp
A fun��o "clocktostr" pode ser chamada repetidas vezes, para obter
o tempo transcorrido desde uma marca de tempo comum.
Novas marcas de tempo
podem ser obtidas chamando-se "clockstamp" repetidas vezes.

.sp
A fun��o "difftime" calcula a diferen�a de dois tempos na representa��o
padr�o interna do sistema (tipo "time_t", ver "ctime" (libc)).
Ela devolve a diferen�a "time1 - time0" expressado em segundos como um "double". 

.in
.sp
.b
VALORES DE RETORNO
.r
.in 5
A fun��o "clock" retorna o tempo de processamento em "ticks".

.sp
A fun��o "clockstamp" retorna 0 se conseguiu alocar as �reas necess�rias,
e -1 em caso contr�rio.

.sp
A fun��o "clocktostr" retorna o argumento "line" dado.

.sp
A fun��o "difftime" retorna o intervalo do tempo em "double".

.in
.sp
.(t
.b OBSERVA��ES
.in 5
Apesar de os valores retornados conterem milisegundos, a precis�o deste 
valor depende do rel�gio interno do computador, que nem sempre
tem ciclo t�o pequenos.
.)t

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
time, mutime, mutimes
.br
.wo "(libc):"
ctime
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
