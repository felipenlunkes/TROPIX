.bp
.he 'TO (cmd)'TROPIX: Manual de Refer�ncia'TO (cmd)'
.fo 'Atualizado em 12.07.97'Vers�o 3.0.1'Pag. %'

.b NOME
.in 5
.wo "to -"
escreve uma linha de mensagem para um usu�rio
.br

.in
.sp
.b SINTAXE
.in 5
.(l
to <usu�rio> <mensagem>
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "to" envia a <mensagem> curta para o <usu�rio>.

.sp
Se o <usu�rio> estiver em sess�o em v�rios terminais,
a <mensagem> ser� enviada para todos eles. 

.sp
Se o nome do <usu�rio> for "all",
a <mensagem> ser� enviada para todos os usu�rios em sess�o,
em todos os terminais.

.in
.sp
.b OBSERVA��O
.in 5
O comando "to" envia apenas mensagens de uma linha.
Para enviar mensagens maiores, deve-se utilizar o comando "write" (cmd).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
write, mail
.br

.in
.sp
.b ARQUIVOS
.in 5
/etc/utmp

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
