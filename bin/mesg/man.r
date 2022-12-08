.bp
.he 'MESG (cmd)'TROPIX: Manual de Refer�ncia'MESG (cmd)'
.fo 'Atualizado em 23.05.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
.wo "mesg -"
habilita ou desabilita a recep��o de mensagens
.br

.in
.sp
.b SINTAXE
.in 5
.(l
mesg [-nNsSyY]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "mesg" habilita ou desabilita o terminal do usu�rio a receber
mensagens de outros usu�rios (por exemplo atrav�s de "write" ou "to" (cmd)).   

.sp
Sem op��es, o comando imprime o estado corrente do terminal.
 
.sp
As op��es do comando s�o:

.in +3
.ip -n
Desabilita a recep��o (pode tamb�m ser dado "-N").

.ip -s
Habilita a recep��o (pode tamb�m ser dado "-S", "-y" ou "-Y").

.ep
.in -3

.in
.sp
.b
C�DIGO DE RETORNO
.r
.in 5
O comando retorna 0 se o terminal est� habilitado, 1 se est� desabilitado,
e 2 para o caso de erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
to, write
.br

.in
.sp
.b ARQUIVOS
.in 5
 /dev/console
 /dev/tty*

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
