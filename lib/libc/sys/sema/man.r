.bp
.he 'SEMA (sys)'TROPIX: Manual de Refer�ncia'SEMA (sys)'
.fo 'Atualizado em 18.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Manuseia sem�foros:
.sp
.wo "semactl   -"
opera��es de controle de sem�foros
.br
.wo "semalock  -"
obt�m um recurso associado ao sem�foro
.br
.wo "semafree  -"
libera um recurso associado ao sem�foro
.br
.wo "sematestl -"
o mesmo que "semalock" mas sem bloquear o processo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>
#include <unistd.h>

int	semactl (int op, int fd, ...);
int	semalock (int semadescr);
int	semafree (int semadescr);
int	sematestl (int semadescr);
.)l

.in
.sp
.b INTRODU��O
.in 5
Sem�foros s�o formas de comunica��o entre processos. Geralmente est�o associados 
a recursos cr�ticos do sistema que s� podem ser utilizados com exclusividade
por um processo de cada vez.
Quando um processo atualiza uma estrutura de dados que � compartilhada por
v�rios processos ele deve utilizar um sem�foro de valor inicial igual a um para
garantir indivisibilidade do procedimento de atualiza��o.

.sp
No TROPIX, os sem�foros s�o coordenados pelo n�cleo do sistema operacional
e est�o dispon�veis para o usu�rio. Eles possuem contadores associados,
que indicam os n�meros de recursos dispon�veis de cada tipo.
A medida em que os processos v�o utilizando os recursos, este contadores s�o
decrementados. A partir do momento em que um certo contador atinge o valor 0,
os processos que pedirem o recurso associado a este contador s�o bloqueados,
at� que (pelo menos) um processo libere um recurso deste tipo.

.sp
A identifica��o de um sem�foro no TROPIX se faz atrav�s de um arquivo regular
(do qual apenas o nome � relevante) seguido do n�mero de identifica��o
do sem�foro. O par "fd" (descritor do arquivo aberto associado ao sem�foro)
e "semaid" (n�mero de identifica��o do sem�foro)
identificam o sem�foro de forma n�o amb�gua.
Diversos sem�foros (com n�meros de identifica��o diferentes) podem ser
associados a um mesmo arquivo. 

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "semactl" com o argumento "op" igual a US_ALLOC
e o argumento (adicional) "n", aloca "n" sem�foros ao arquivo cujo
descritor � dado pelo argumento "fd".
Estes sem�foros s�o identificados pelos pares ("fd", 0), ("fd", 1), ...,
("fd", "n"-1). Em caso de sucesso, retorna o valor zero.

.sp
A chamada ao sistema "semactl", com o argumento "op" igual a US_GET
e argumentos (adicionais) "n" e "initval",
retorna o descritor de sem�foro (um n�mero n�o negativo) associado ao
sem�foro definido pelo par ("fd", "n"), que dever� ser usado para identificar
este sem�foro nas chamadas ao sistema "semalock", "semafree", "sematestl" e
"semactl" com as opera��es US_AVAIL e US_WAIT.
O quarto argumento "initval", d� o valor inicial do sem�foro, isto �, o n�mero
de recursos associados ao sem�foro.
Na presente implementa��o do TROPIX, este valor inicial n�o pode
ser maior que 32767.

.sp
A chamada ao sistema "semactl", com o argumento "op" igual a US_AVAIL,
retorna o n�mero de recursos associados ao sem�foro definido pelo descritor
de sem�foros "fd" que ainda se encontram dispon�veis para aloca��o.

.sp
A chamada ao sistema "semactl", com o argumento "op" igual a US_WAIT,
retorna o n�mero de processos e "threads"  que aguardam pela libera��o
de recursos associados ao sem�foro definido pelo descritor
de sem�foros "fd".

.sp
A chamada ao sistema "semalock" bloqueia o processo at� a 
libera��o do recurso associado ao sem�foro indicado pelo descritor
"semadescr".
O valor retornado � o n�mero de recursos ainda dispon�vel ap�s o sucesso
na obten��o do recurso.

.sp
A chamada "semafree" libera um recurso associado ao sem�foro indicado pelo
descritor "semadescr".
A chamada sempre retorna imediatamente dando o n�mero de recursos ainda
dispon�veis ap�s a libera��o do recurso em quest�o.

.sp
A chamda "sematestl" � equivalente a "semalock" com a �nica diferen�a que
o processo n�o fica bloqueado quando n�o h� recursos dispon�veis. Se 
"sematestl" retorna um valor n�o negativo, significa que o recurso foi
obtido e indica o n�mero de recursos ainda dispon�veis.
O retorno do valor -1 indica que o recurso n�o foi obtido.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Os valores de retorno das v�rias chamadas em caso de sucesso
j� foram descritas acima.
Em caso de erro, elas devolvem -1 e indicam em "errno" a causa do erro.

.bc	/*************************************/
Em caso de sucesso,  a n�o ser a "semactl" que devolve 0 com
"op" igual a US_ALLOC e o descritor do sem�foro com "op" igual a US_GET,
todas as chamadas ao sistema devolvem o n�mero de recursos
associados a um determinado sem�foro dispon�veis para aloca��o.
Em caso contr�rio, devolvem -1 e indicam em "errno" a causa do erro.
.ec	/*************************************/

.in
.sp
.b OBSERVA��ES
.in 5
N�O confunda "descritor do arquivo" com  "descritor do sem�foro":
a chamada ao systema "semactl", quando executa opera��es
relativas a sem�foros ainda n�o existentes (US_ALLOC e US_GET)
recebe como argumento o descritor do arquivo associado;
quando as opera��es s�o executadas sobre sem�foros j� existentes
(US_AVAIL e US_WAIT) ela recebe diretamente o descritor do sem�foro.

.bc	/*************************************/
.sp
O arquivo associado a um conjunto de sem�foros pode ser utilizado
normalmente a qualquer instante. Observar, por�m, que um "close" no
mesmo faz o conjunto de sem�foros ficar inacess�vel.
.ec	/*************************************/

.sp
No TROPIX os sem�foros existem enquanto o seu arquivo associado estiver aberto.
Quando o arquivo associado a um conjunto de sem�foros � fechado, o processo
perde o acesso a estes sem�foros. Quando o �ltimo processo fecha este arquivo
os sem�foros s�o destru�dos.
Desta forma, a libera��o de sem�foros � feita,
simplesmente, fechando-se seus arquivos associados.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
open
.br

.in
.sp
.b EXEMPLOS
.in 7
A aplica��o usual da chamada ao sistema em procedimento de exclus�o m�tua
� feita da seguinte forma:
.sp 2
.(l
	fd = open ("nome", ...); /* Abre o arquivo associado */

	if (semactl (US_ALLOC, fd, 1) == -1)
		printf ("N�o consegui alocar o sem�foro\n");

	if ((sdesc = semactl (US_GET, fd, 0, 1)) == -1)
		printf ("N�o consegui obter o descritor\n");

	semalock (sdesc);

	printf ("peguei recurso exclusivo para este processo\n");

	semafree (sdesc);

	close (fd);	/* Libera os sem�foros alocados */

.)l

.in
.sp
.b ESTADO
.in 5
Efetivo.
