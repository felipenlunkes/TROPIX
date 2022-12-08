.bp
.he 'SEMAFREE (cmd)'TROPIX: Manual de Refer�ncia'SEMAFREE (cmd)'
.fo 'Atualizado em 30.06.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
.wo "semafree -"
libera o sem�foro pelo qual o processo est�
.wo "            esperando"
.br

.in
.sp
.b SINTAXE
.in 5
.(l
semafree [-v] <pid>
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "semafree" libera o sem�foro (recurso) pelo qual o processo
de identifica��o <pid> est� esperando.

.sp
Isto � uma a��o que pode acarretar inconsist�ncia das tabelas internas
do n�cleo do TROPIX, e s� deve ser utilizado em situa��es de "p�nico".

.sp
Este comando est� reservado para o superusu�rio.

.sp
As op��es do comando s�o:

.in +3
.ip -v
Verboso

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
ps, prsync
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
