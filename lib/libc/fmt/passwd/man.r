.bp
.he 'PASSWD (fmt)'TROPIX: Manual de Refer�ncia'PASSWD (fmt)'
.fo 'Atualizado em 29.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "passwd -"
formato do arquivo de contas/senhas
.br

.in
.sp
.b DESCRI��O
.in 5
O arquivo "/etc/passwd" cont�m informa��es sobre os
usu�rios do sistema, utilizadas principalmente pelo utilit�rio
"login" (cmd) para verificar a permiss�o do acesso de um usu�rio ao
sistema.

.sp
O arquivo pode ser editado diretamente pelo administrador do sistema
atrav�s de "ed" (cmd) ou "vi" (cmd). O arquivo consiste de uma linha
para cada usu�rio; cada linha cont�m os seguintes campos
separados por ":":

.sp 2
.nf
	conta:senha:nome:uid:gid:cota:expir:tranca:dir:sh
.fi

.sp 2
A "conta" � o nome pelo qual o usu�rio � conhecido pelo
sistema. Pode ter no m�ximo 14 caracteres.

.sp
A "senha" � a senha encriptada, atrav�s da qual � conferida
a permiss�o de acesso do usu�rio no sistema. Este campo n�o
deve ser preenchido pelo administrador; ele deve colocar a
cadeia "-------------" (uma sequ�ncia de 13 menos), o que
significa "sem senha", e posteriormente utilizar o utilit�rio
"passwd" (cmd) para colocar uma senha. 

.sp
O "nome" � um campo utilizado como coment�rio; o sistema
n�o consulta este campo. Normalmente � utilizado para conter
o nome completo do usu�rio.

.sp
O "uid" e "gid" s�o os valores num�ricos do usu�rio
e seu grupo, que ir�o ser utilizados na cria��o de arquivos,
verifica��o de permiss�o de acesso, etc....

.sp
Os campos "cota", "expir" e "tranca" s�o campos reservados
para controle do n�mero m�ximo de blocos que o usu�rio
pode ter em disco, a data de expira��o da conta e um
c�digo de "tranca" que o utilit�rio "login" poder� verificar
para permitir ou n�o o acesso do usu�rio ao sistema
(n�o implementado no momento).

.sp
O campo "dir" cont�m o nome completo (caminho) do diret�rio
inicial do usu�rio (par�metro "HOME" do ambiente (fmt)).

.sp
O campo "sh" � o nome completo do utilit�rio utilizado como
interpretador de comandos pelo usu�rio. Normalmente, este campo
est� vazio, indicando o utilit�rio "/bin/sh" (cmd).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
login, sh, ed, vi, passwd
.br
.wo "(libc):"
pwent, grent
.br
.wo "(fmt): "
environ
.br

.in
.sp
.b ARQUIVOS
.in 5
 /etc/passwd
 /usr/include/pwd.h

.in
.sp
.b EXEMPLO
.nf
	ncd.jos�:Y4LzoX0ZAE5r1:Jos� Farias:104:35:0:0::/u/jos�:
.fi

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
