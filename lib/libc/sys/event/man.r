.bp
.he 'EVENT (sys)'TROPIX: Manual de Refer�ncia'EVENT (sys)'
.fo 'Atualizado em 13.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Manuseia eventos:
.sp
.wo "eventctl  -"
opera��es de controle de eventos
.br
.wo "eventwait -"
espera pela ocorr�ncia de um evento
.br
.wo "eventdone -"
sinaliza a ocorr�ncia de um evento
.br
.wo "eventtest -"
obt�m o n�mero do �ltimo evento ocorrido
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>
#include <sys/unistd.h>

int	eventctl (int op, int fd, int n);
int	eventwait (int eventdescr, int eventordno);
int	eventdone (int eventdescr);
int	eventtest (int eventdescr);
.)l

.in
.sp
.b INTRODU��O
.in 5
Eventos s�o formas de comunica��o entre processos. Geralmente est�o associados 
a acontecimentos ass�ncronos que, muitas vezes, s�o exteriores ao pr�prio
sistema. Quando um processo espera pelo final da leitura de um bloco
de disco, por exemplo, ele est� esperando por um evento.

.sp
No TROPIX, eventos s�o coordenados pelo n�cleo do sistema operacional
e est�o dispon�veis para o usu�rio.
Est�o associados a um contador (n�mero de ordem da ocorr�ncia do evento)
que indica o n�mero de ocorr�ncias de eventos daquele tipo desde a sua
cria��o (o contador � sempre inicializado com o valor zero).

.sp
A identifica��o de um evento no TROPIX se faz atrav�s de um arquivo regular
(do qual apenas o nome � relevante) seguido do n�mero de identifica��o
do evento. O par "fd" (descritor do arquivo aberto associado ao evento)
e "eventid" (n�mero de identifica��o do evento)
identificam o evento de forma n�o amb�gua.
Diversos eventos (com n�meros de identifica��o diferentes) podem ser
associados a um mesmo arquivo. 

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "eventctl" com o argumento "op" igual a UE_ALLOC,
aloca "n" eventos ao arquivo cujo descritor � dado pelo argumento "fd".
Estes eventos s�o identificados pelos pares ("fd", 0), ("fd", 1), ...,
("fd", "n"-1). Em caso de sucesso, retorna o valor zero.

.sp
A chamada ao sistema "eventctl", com o argumento "op" igual a UE_GET,
retorna o descritor de evento (um n�mero n�o negativo) associado ao
evento definido pelo par ("fd", "n"), que dever� ser usado para identificar
este evento nas chamadas ao sistema "eventwait",  "eventdone" e  "eventtest".

.sp
A chamada ao sistema "eventwait" bloqueia o processo at� a ocorr�ncia do
"eventordno"-�simo evento indicado pelo descritor "eventdescr".
Se "eventordno" � menor ou igual ao n�mero de ocorr�ncias
atual, a chamada ao sistema "eventwait" retorna imediatamente.
A chamada ao sistema retorna o n�mero de ocorr�ncias atual.

.sp
A chamada "eventdone" sinaliza a ocorr�ncia do evento indicado pelo descritor
"eventdescr". O contador de eventos correspondente � incrementado do valor 1.
A chamada ao sistema retorna o n�mero de ocorr�ncias atual.

.sp
A chamada "eventtest" retorna o n�mero de ocorr�ncias atual
do evento indicado pelo descritor "eventdescr".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Os valores de retorno das v�rias chamadas em caso de sucesso
j� foram descritas acima.
Em caso de erro, elas devolvem -1 e indicam em "errno" a causa do erro.

.in
.sp
.b OBSERVA��ES
.in 5
Observe que a contagem dos eventos se faz de acordo com uma aritm�tica
circular: os contadores s�o inteiros de 32 bits, e desta forma,
em qualquer ponto da contagem, os 2^31 n�meros
anteriores ao n�mero de ocorr�ncias atual s�o considerados menores 
que esse n�mero, correspondendo, portanto, aos eventos
j� ocorridos. Os 2^31 n�meros seguintes ao n�mero de ocorr�ncias atual
s�o considerados maiores e correspondem aos eventos a ocorrer.

.sp
Observe, tamb�m, que se h� diversos processos (ou "thread"s) esperando por
um mesmo "eventordno" de um determinado evento, assim que este evento
ocorrer ("eventdone"), TODOS os processos (ou "thread"s) esperando por
este evento s�o desbloqueados. Compare com o caso de sem�foros onde
apenas um processo (ou "thread") � acordado quando um recurso �
liberado ("semafree").

.sp
No TROPIX os eventos existem enquanto o seu arquivo associado estiver aberto.
Quando o arquivo associado a um conjunto de eventos � fechado, o processo
perde o acesso a estes eventos. Quando o �ltimo processo fecha este arquivo
os eventos s�o destru�dos.
Desta forma, a libera��o de eventos � feita,
simplesmente, fechando-se seus arquivos associados.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
open, thread
.br

.in
.sp
.(t
.b EXEMPLO
.in 7
A aplica��o usual das chamadas ao sistema para sinaliza��o de eventos
entre processos � feita da seguinte forma:
.sp 2
.(l
		/* Parte comum aos dois processos */

	fd = open ("nome", ...);	/* Abre o arquivo associado */

	if (eventctl (UE_ALLOC, fd, 1) == -1)
		printf ( "N�o consegui alocar o evento\n");

	if ((edesc = eventctl (UE_GET, fd, 0)) == -1)
		printf ( "N�o consegui obter o descritor do evento\n");

			/* Parte diferente */
	/* Processo 1 */		/* Processo 2 */

	eno = eventwait (edesc, 1);	eno = eventdone (edesc);

	printf ("recebi o evento\n");	printf ("sinalizei o evento\n");

		/* Parte comum aos dois processos */

	close (fd);			/* Libera os eventos alocados */

.)l
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.
