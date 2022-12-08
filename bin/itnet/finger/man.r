.bp
.he 'FINGER (cmd)'TROPIX: Manual de Refer�ncia'FINGER (cmd)'
.fo 'Atualizado em 17.07.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "finger -"
obt�m informa��es sobre usu�rios remotos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
finger [-v] [-u <usu�rio_remoto>] <n�_remoto>
finger [-v] [<usu�rio_remoto>@]<n�_remoto>
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "finger" fornece algumas informa��es sobre usu�rios de n�s
remotos.

.sp
Se o <usu�rio_remoto> n�o for dado, imprime os seguintes dados sobre
todos os usu�rios remotos em sess�o:
nome (da conta) do usu�rio, terminal/v�deo, data/hora em que entrou em sess�o,
e o nome do local do n�.
Repare que este formato � semelhante ao do comando "who" (cmd).

.bc	/*************************************/
.sp
Para usu�rios em sess�o, fornece o nome (da conta) do usu�rio,
o terminal/v�deo, a data/hora em que entrou em sess�o e o nome do local
do n�, em um formato semelhante ao comando "who" (cmd).
.ec	/*************************************/

.sp
As op��es do comando s�o:

.in +3
.ip -u
Com esta op��o, somente s�o dadas a informa��es acima para o
<usu�rio_remoto> dado.

.sp
Al�m disto, s�o dados o nome completo do <usu�rio_remoto>,
o seu diret�rio "home", o seu interpretador de comandos (veja "edusr" (cmd)),
a data/hora da sua �ltima entrada em sess�o, a data/hora da �ltima
recep��o de correio eletr�nico e o seu "plano" (conte�do do arquivo
"$HOME/.plan").

.sp
Esta op��o pode ser dada tamb�m na forma com o caractere "@" (veja acima).

.ip -v
Verboso.

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
who, edusr
.br

.in
.sp
.b
REFER�NCIAS
.r
.in 5
"Name/Finger", K. Harrenstein, Request for Comments 742.

.in
.sp
.b ARQUIVOS
.in 5
/etc/passwd
 /usr/mail/*
 /var/adm/lastlog
 /var/adm/utmp
 /var/adm/wtmp
 $HOME/.plan

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
