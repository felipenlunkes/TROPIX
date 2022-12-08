.bp
.he 'PRSCB (cmd)'TROPIX: Manual de Refer�ncia'PRSCB (cmd)'
.fo 'Atualizado em 04.12.01'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "prscb -"
imprime o bloco de controle do n�cleo do TROPIX
.br

.in
.sp
.b SINTAXE
.in 5
.(l
prscb [-v]
.)l

.in
.sp
.b DESCRI��O
.in 5
O n�cleo do sistema operacional TROPIX cont�m um bloco de controle
(SCB) com diversos par�metros,
cujo objetivo � definir a configura��o do sistema.
Alterando um (ou mais) destes par�metros podemos modificar v�rios
aspectos do sistema operacional,
e deste modo atender a diversos desejos e necessidades.
Os par�metros do SCB s�o descritos em "scb" (fmt).

.sp
O comando "prscb" imprime o bloco de controle do n�cleo do TROPIX.
Os valores impressos s�o dos par�metros em uso efetivo no momento.

.sp
Para alterar os valores dos par�metros, veja "edscb" (cmd).

.sp
As op��es do comando s�o:

.in +3
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
edscb
.br
.wo "(fmt): "
scb
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
