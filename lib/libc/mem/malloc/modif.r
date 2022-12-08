.bp
.he 'MALLOC (libc)'TROPIX: Manual de Modifica��es'MALLOC (libc)'
.fo 'Atualizado em 15.09.92'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
Aloca��o din�mica de mem�ria:
.sp
.wo "malloc  -"
aloca��o de mem�ria
.br
.wo "free    -"
libera��o de mem�ria
.br
.wo "realloc -"
realoca��o de mem�ria
.br
.wo "calloc  -"
aloca��o de �rea zerada
.br

.in
.sp 2
.ip "01.04.87  1.0" 20
VERS�O CORRENTE
.sp

.ip "17.07.87  1.0.1" 20
O seguinte refinamento foi acrescentado � estrat�gia para aloca��o de blocos
em "malloc.c":
se um bloco adquirido do Sistema � cont�guo � Arena,
ent�o ele � aglutinado aos �ltimos blocos livres da Arena.
.sp
Esta modifica��o resulta em uma menor fragmenta��o da Arena.

.in
.sp 2
.ip "17.07.87  2.1.0" 20
VERS�O CORRENTE
.sp

.ip "15.08.89  2.2.1" 20
Eliminados erros relativos � inicia��o da "malloc",
quando chamada pela primeira vez em um programa.

.ip "15.12.91  2.3.0" 20
As fun��es sofreram (ou deliciaram-se com) uma revis�o global.

.ip "15.09.92  3.0.0" 20
Foi reimplantado o "smalloc".
