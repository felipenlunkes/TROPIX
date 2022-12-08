.bp
.he 'SU (cmd)'TROPIX: Manual de Refer�ncia'SU (cmd)'
.fo 'Atualizado em 11.07.97'Vers�o 3.0.2'Pag. %'

.b NOME
.in 5
.wo "su -"
muda de conta temporariamente
.br

.in
.sp
.b SINTAXE
.in 5
.(l
su [-e] [<conta nova>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "su" muda temporariamente de conta (identifica��o do usu�rio)
para a "<conta nova>".
No caso de a <conta nova> n�o ser dada, assume-se "root", ou
seja, "superusu�rio".

.sp
O comando "su" pede a senha necess�ria (a n�o ser que o usu�rio de "su"
seja um superusu�rio) e se esta for dada corretamente, troca para
a conta especificada, executando o seu interpretador de comandos
(normalmente "sh" (cmd)).

.sp
Normalmente, nem o "ambiente" nem o diret�rio corrente s�o modificados
(veja a op��o "-e").

.sp
O usu�rio permanece nesta nova conta at� que o "sh" termine
(com "exit" ou EOF, normalmente <^D>), ou ent�o seja executado outro "su".

.sp
As op��es do comando s�o:

.in +3
.ip -e
Utiliza o ambiente da <conta nova>: o diret�rio corrente � trocado
para o diret�rio "HOME" da <conta nova>, e � executado o seu ".profile".
O novo ambiente ser� um out�rio dos ambientes antigo e novo, onde
as vari�veis em comum ter�o os valores do ambiente novo.

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
login, sh
.br
.wo "(fmt): "
environ, passwd
.br

.in
.sp
.b ARQUIVOS
.in 5
.(l
/etc/passwd		arquivo de contas e senhas
$HOME/.profile		"profile" do usu�rio
.)l

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
