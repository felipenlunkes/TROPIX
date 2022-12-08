.bp 1
.he 'LOGIN (cmd)'TROPIX: Manual de Refer�ncia'LOGIN (cmd)'
.fo 'escrito em 22.05.97'Vers�o 3.0.3'Pag. %'

.b NOME
.in 5
login - entra em sess�o

.in
.sp
.b SINTAXE
.in 5
login

.in
.sp
.b DESCRI��O
.in 5
O comando "login" � utilizado no inicio de cada sess�o no
terminal/video/janela,
permitindo a identifica��o do usu�rio.

.sp
O comando pede o nome do usu�rio ap�s "LOGIN: ", e caso 
a conta do usu�rio tenha senha, esta � pedida, tomando-se
o cuidado de evitar o echo dos caracteres no terminal.
.bc	/*************************************/
No caso do usu�rio ser superusu�rio, o comando pede que
a senha seja dada novamente.
.ec	/*************************************/

.sp
Ap�s um "login" com sucesso,  diversos arquivos de contabilidade
s�o atualizados, � indicada a exist�ncia de correspond�ncia
para o usu�rio, e � impressa a "mensagem do dia", caso esta exista.

.sp
S�o tambem atualizadas as identifica��es do usu�rio, o diret�rio
corrente, e o ambiente.

.sp
Para sair de sess�o, basta teclar um
caractere "eof" (normalmente <^D>, ver "stty" (cmd)), ou
o comando "login", em ambos casos transferindo o controle para o
"init", que ir� invocar novamente um "login".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
(cmd): init, mail, passwd.

.in
.sp
.b ARQUIVOS
.nf
     /etc/utmp           Contabilidade
     /usr/adm/wtmp       Contabilidade
     /usr/adm/lastlog	 Contabilidade
     /usr/mail/*         Correspond�ncia
     /etc/motd           Mensagem do Dia
     /etc/passwd	 Contas & Senhas
     /etc/initab         Tabela de Terminais 
     /bin/sh		 Interpretador de comandos
     /dev/video*	 Videos
     /dev/tty*		 Terminais
     /dev/pty*		 Pseudo-terminais
.fi

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
