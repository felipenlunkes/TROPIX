.bp 1
.he 'TTY (cmd)'TROPIX: Manual de Refer�ncia'TTY (cmd)'
.fo 'Atualizado em 13.07.97'Vers�o 1.0'Pag. %'

.b NOME
.in 5
tty - imprime o nome do terminal/v�deo

.in
.sp
.b SINTAXE
.in 5
tty [-s]

.in
.sp
.b DESCRI��O
.in 5
O comando "tty" escreve o caminho ("pathname") do terminal/v�deo
no qual o usu�rio se encontra.

.sp
Com a op��o "-s", o comando "tty" apenas
fornece o c�digo de retorno 1 ou 0,
se a entrada padr�o respectivamente � ou n�o um terminal/v�deo.

.in
.sp
.b OBSERVA��O
.in 5
Se a entrada padr�o n�o for um terminal/v�deo e a op��o "-s" n�o
for dada, "tty" imprime "Terminal/v�deo desconhecido".

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
