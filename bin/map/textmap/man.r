.bp
.he 'TEXTMAP (cmd)'TROPIX: Manual de Refer�ncia'TEXTMAP (cmd)'
.fo 'Atualizado em 14.08.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "textmap -"
imprime uma tabela de programas reentrantes em uso
.br

.in
.sp
.b SINTAXE
.in 5
.(l
textmap [-v]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "textmap" imprime uma tabela com informa��es ac�rca
do texto (c�digo execut�vel) dos programas reentrantes
em uso pelo sistema operacional.

.sp
A tabela cont�m as seguintes colunas:

.in +3
.ip TEXT 8
O �ltimo componente do caminho do programa reentrante.

.ip SIZE 8
O tamanho do programa (total) em KB.

.ip M 8
Indica se o programa cont�m o indicador S_IMETX ligado (veja "chmod (sys)).

.ip T 8
Indica se o programa cont�m o indicador S_ISVTX ligado (veja "chmod (sys)).

.ip COUNT 8
D� o n�mero total de processos utilizando o programa
e o n�mero destes programas que est�o na mem�ria interna
(isto �, que n�o est�o em SWAP).

.ip CORE 8
Indica (com a letra "c") que o programa est� na mem�ria interna.

.ip MADDR 8
D� o endere�o (em KB) do programa na mem�ria (caso a letra "c" esteja presente).

.ip SWAP 8
Indica (com a letra "s") que h� uma c�pia do programa no SWAP (em disco).

.ip SADDR 8
D� o endere�o (em blocos) da regi�o reservada para o programa no SWAP.

.ep
.in -3

.sp
As op��es do comando s�o:

.in +3
.ip -v
Verboso.

.ep
.in -3

.in
.sp
.b OBSERVA��O
.in 5
Nas vers�es anteriores do TROPIX (assim como em outros sistemas
operacionais de filosofia UNIX), havia dois tipos de programas
execut�veis: "regulares" e "reentrantes".
Atualmente, no entanto, todos os programas do TROPIX s�o reentrantes. 

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
intro, chmod
.br

.in
.sp
.(t
.b ESTADO
.in 5
Efetivo.
.)t

.in
