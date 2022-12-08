.bp
.he 'GROUP (fmt)'TROPIX: Manual de Refer�ncia'GROUP (fmt)'
.fo 'Atualizado em 29.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "group -"
formato do arquivo de grupos
.br

.in
.sp
.b DESCRI��O
.in 5
O arquivo "/etc/group" cont�m informa��es sobre os
grupos do sistema. Este arquivo
usualmente � utilizado por utilit�rios para obter o nome simb�lico do grupo
a partir do valor num�rico.

.sp
O arquivo pode ser editado diretamente pelo administrador do sistema
atrav�s de "ed" (cmd) ou "vi" (cmd). O arquivo consiste de uma linha
para cada grupo; cada linha cont�m os seguintes campos
separados por ":":

.sp 2
.nf
		grupo:senha:gid:membros
.fi

.sp 2
O "grupo" � o nome simb�lico do grupo.
Pode ter no m�ximo 14 caracteres.

.sp
A "senha" � a senha encriptada de acesso ao grupo. No momento
n�o � utilizada.

.sp
O "gid" � o valor num�rico do grupo.

.sp
O campo "membros" cont�m os nomes simb�licos dos membros
do grupo, isto �, os nomes dos usu�rios (contas) que pertencem
a este grupo, separados por v�rgulas.
No momento, este campo n�o � utilizado.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
ed, vi
.br
.wo "(libc):"
pwent, grent
.br

.in
.sp
.b ARQUIVOS
.in 5
 /etc/group
 /usr/include/group.h

.in
.sp
.b EXEMPLO
.nf
	sys::0:
	lsi::10:
	tropix::11:
.fi

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
