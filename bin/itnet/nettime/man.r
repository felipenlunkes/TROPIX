.bp
.he 'NETTIME (cmd)'TROPIX: Manual de Refer�ncia'NETTIME (cmd)'
.fo 'Atualizado em 23.08.97'Vers�o 3.0.1'Pag. %'

.b NOME
.in 5
.wo "nettime -"
obt�m a data/hora corrente de um n� remoto
.br

.in
.sp
.b SINTAXE
.in 5
.(l
nettime [-scdv] <n�_remoto>
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "nettime" obt�m a data/hora corrente do <n�_remoto> dado,
e imprime-o no hor�rio local (levando em conta o fuso hor�rio, conforme
os comandos "data" ou "date" (cmd)).

.sp
As op��es do comando s�o:

.in +3
.ip -s
Atualiza o tempo local a partir do tempo remoto obtido
(somente para superusu�rios).

.ip -c
Compara os tempos local e remoto, indicando a diferen�a de dias, horas,
minutos e segundos entre os n�s.

.ip -d
Imprime tamb�m o tempo obtido sem convers�o, em decimal/hexadecimal.

.ip -v
Verboso.

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
data, date
.br

.in
.sp
.b
REFER�NCIAS
.r
.in 5
"Time Protocol", J. Postel, Request for Comments 868.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
