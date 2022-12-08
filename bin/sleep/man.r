.bp
.he 'SLEEP (cmd)'TROPIX: Manual de Refer�ncia'SLEEP (cmd)'
.fo 'Atualizado em 05.07.97'Vers�o 3.0.1'Pag. %'

.b NOME
.in 5
.wo "sleep -"
suspende a execu��o por um intervalo de tempo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
sleep <n>
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "sleep" suspende a execu��o por <n> segundos.

.sp
� utilizado normalmente para executar um comando ap�s um determinado tempo.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
alarm
.br
.wo "(libc):"
sleep
.br

.in
.sp
.b EXEMPLO
.in 5
A linha de comandos
.sp
.nf
		(sleep 90; <comando> )  &
.fi
.sp
Ir� executar o <comando> ap�s 90 segundos, mas permitindo executar
outros comandos antes deste intervalo de tempo.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
