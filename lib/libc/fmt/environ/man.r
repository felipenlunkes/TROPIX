.bp
.he 'ENVIRON (fmt)'TROPIX: Manual de Refer�ncia'ENVIRON (fmt)'
.fo 'Atualizado em 27.01.99'Vers�o 3.1.6'Pag. %'

.b NOME
.in 5
.wo "environ -"
ambiente do usu�rio
.br

.in
.sp
.b DESCRI��O
.in 5
Quando um processo � iniciado, ele recebe um vetor de ponteiros
para cadeias chamado de "ambiente" (ou "environment"),
constru�do pela chamada ao sistema "exec" (sys).
Por conven��o, estas cadeias t�m a forma "nome=valor".

.sp
Embora cada usu�rio possa definir seus "nomes" particulares,
existe um conjunto de "nomes" globais,
criado pelos utilit�rios "init" (cmd)
e "login" (cmd),
ao qual (normalmente) todos os utilit�rios t�m acesso.
.sp

A lista dos "nomes" globais � a seguinte:

.in +3
.ip PATH 8
Cont�m a sequ�ncia de diret�rios pesquisados pelas fun��es
"execvp" e "execlp" (libc) e o utilit�rio "sh" (cmd)
para a busca dos arquivos que cont�m os utilit�rios.
Os diret�rios s�o separados por ":".
O valor inicial de "PATH", atribu�do pelo utilit�rio "login" 
� "PATH=.:/bin:/usr/bin".

.ip HOME 8
Cont�m o nome do diret�rio inicial do usu�rio, atribu�do por
"login" a partir do arquivo de contas e senhas "passwd" (fmt).

.ip TERM 8
Cont�m o tipo do terminal, atribu�do por "init", a partir do arquivo
"/etc/initab".
Esta informa��o pode ser utilizada pelos utilit�rios
(como por ex. "vi" (cmd)), para obter as caracter�sticas
peculiares de cada terminal.

.ip TZMIN 8
Esta vari�vel N�O est� mais no ambiente; o fuso hor�rio agora
� obtido atrav�s da chamada ao sistema "gettzmin" (sys).

.ip USER 8
Cont�m o nome do usu�rio, como dado ao entrar em sess�o.

.ip SHELL 8
Cont�m o nome do utilit�rio utilizado como interpretador
de comandos pelo usu�rio.

.in -3
.ep
.in 5
.sp
Nomes adicionais podem ser colocados no ambiente atrav�s
de "putenv" (libc) e "exec" (sys), ou ent�o atrav�s
dos comandos "set" e "export" do "sh" (cmd). 
N�o � recomend�vel utilizar "nomes" que entrem em conflito
com os nomes das vari�veis do "sh", tais como "PS1", "PS2", "IFS".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
init, login, sh, vi
.br
.wo "(sys): "
exec, gettzmin
.br
.wo "(libc):"
getenv, putenv
.br
.wo "(fmt): "
passwd
.br

.in
.sp
.b ARQUIVOS
.in 5
 /etc/passwd
 /etc/initab
 /etc/globalenv

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
