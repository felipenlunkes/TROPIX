.bp
.he 'COREMAP (cmd)'TROPIX: Manual de Refer�ncia'COREMAP (cmd)'
.fo 'Atualizado em 23.05.97'Vers�o 3.0.1'Pag. %'

.b NOME
.in 5
.wo "coremap -"
imprime um mapa de aloca��o da mem�ria
.br

.in
.sp
.b SINTAXE
.in 5
.(l
coremap [<per�odo>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "coremap" imprime um mapa de aloca��o da mem�ria interna
do computador.
O mapa � atualizado cada <per�odo> segundos (1 segundo se o <per�odo>
n�o for dado).

.sp
O mapa cont�m uma coluna � esquerda com o endere�o da mem�ria (em KB)
correspondente ao primeiro caractere do mapa na linha.
Abaixo do mapa, temos uma linha informando
o n�mero de bytes correspondentes a cada
caractere do mapa, a mem�ria total dispon�vel para programas do
usu�rio, a parte usada e a percentagem.

.sp
Os significados dos caracteres s�o:

.in +3
.ip '"."'
Parte livre da mem�ria.

.ip '"+"'
No in�cio da mem�ria: parte usado pelo n�cleo do TROPIX, incluindo
as diversas tabelas.
No final da mem�ria: parte alocada para a simula��o dos discos
em mem�ria (dispositivos "/dev/ramd0" e "/dev/ramd1").

.ip '"*"'
Partes usados pelos diversos programas.

.ep
.in -3

.sp
Para encerrar o programa, tecle o caractere "intr" (normalmente
<^C>, veja "stty" (cmd)).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
stty
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
