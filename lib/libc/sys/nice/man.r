.bp
.he 'NICE (sys)'TROPIX: Manual de Refer�ncia'NICE (sys)'
.fo 'Atualizado em 17.08.95'Vers�o 3.0'Pag. %'

.b NOME
.br
.in 5
.wo "nice -"
modifica a prioridade de um processo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	nice (int incr);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "nice" modifica a prioridade do processo para a
obten��o de um processador.
O valor dado "incr" � acrescentado ao valor do "nice" atual
do processo.
Valores positivos de "incr" diminuem a prioridade do processo,
e valores negativos a aumentam. 
.sp
A prioridade m�xima � obtida com o valor de "nice" de 0 e a
prioridade m�nima � obtida com o valor de 40.
O valor normal � de 20.
Caso a chamada resulte em valores abaixo ou acima deste limite,
o valor utilizado � o do limite correspondente.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve o novo valor de "nice".
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b OBSERVA��O
.in 5
Somente superusu�rios podem usar "incr" negativo.
.sp
A defini��o n�o intuitiva dada acima, em que aumentando o valor
de "nice" diminue-se a prioridade e vice-versa, corresponde
� vis�o do usu�rio da chamada ao sistema; internamente,
o TROPIX utiliza valores de -20 a +20, com valores maiores
correspondendo a prioridades maiores. S�o estes �ltimos
valores que s�o obtidos com o comando "ps" (cmd).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
ps, nice
.br
.wo "(sys): "
exec
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
