.bp
.he 'TOUCH (cmd)'TROPIX: Manual de Refer�ncia'TOUCH (cmd)'
.fo 'Atualizado em 08.05.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "touch -"
atualiza/modifica os tempos de arquivos
.br

.in
.sp
.b SINTAXE
.in 5
touch [-vcN] [-d <tempo>] [-r <dias>] [-f <base>]
.nf
						    [<arquivo> ...]
.fi

.in
.sp
.b DESCRI��O
.in 5
O comando "touch" altera os tempos de acesso, modifica��o
(e opcionalmente o tempo de cria��o) dos <arquivos> dados
(veja "stat" (sys)).
Se n�o for dado nenhum tempo (veja abaixo),
� usado o tempo corrente.

.sp
Se algum <arquivo> ainda n�o existir, ele � criado como um arquivo regular
de tamanho NULO.

.sp
Como alternativa ao tempo corrente, o novo tempo pode ser dado de v�rios modos:
.bc	/*************************************/
Dependendo das op��es, o novo tempo pode ser dado de v�rios modos:
.ec	/*************************************/

.in +3
.ip "-d <tempo>" 12
Tempo absoluto: com esta op��o, o novo tempo deve ser dado no formato
do comando "data" (cmd).

.ip "-r <dias>" 12
Tempo relativo: o novo tempo deve ser dado pelo n�mero de
<dias> no passado, relativos ao tempo corrente.

.ip "-f <base>" 12
Tempo do arquivo <base>: o novo tempo ser� o tempo de modifica��o
do arquivo <base>.

.bc	/*************************************/
.ip "-- " 12
Tempo corrente: se n�o for dada nenhuma das op��es anteriores,
o novo tempo do arquivo ser� o momento corrente.
.ec	/*************************************/

.ep
.in -3
.sp
Al�m disto, temos ainda as seguintes op��es:

.in +3
.ip "-v "
Lista os nomes dos <arquivo>s modificados, juntamente com o novo tempo.

.ip "-c "
Altera tamb�m o tempo de cria��o do arquivo.
Isto s� pode ser feito pelo superusu�rio.

.ip "-N "
L� os nomes dos <arquivo>s da entrada padr�o.
Esta op��o � impl�cita se n�o forem dados <arquivo>s.

.ep
.in -3

.in
.sp
.b OBSERVA��O
.in 5
O uso indiscriminado de "touch" pode causar o comando "make"
a perder o controle dos m�dulos a atualizar.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
data, make
.br
.wo "(sys): "
stat, utime
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
