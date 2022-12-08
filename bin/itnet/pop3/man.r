.bp
.he 'POP3 (cmd)'TROPIX: Manual de Refer�ncia'POP3 (cmd)'
.fo 'Atualizado em 01.01.03'Vers�o 4.4.0'Pag. %'

.b NOME
.in 5
.sp
.wo "pop3 -"
acessa uma caixa postal remota
.br

.in
.sp
.b SINTAXE
.in 5
.(l
pop3 [-av] [<usu�rio_remoto>@][<n�_remoto>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "pop3" permite o acesso a uma caixa postal remota, atrav�s
do protocolo POP3 (Post Office Protocol, Version 3).

.sp
Ap�s a conex�o com o <n�_remoto>, o programa "pop3" verifica se h�
cartas para o <usu�rio_remoto> na caixa postal remota, que ainda n�o estejam
presentes na caixa postal local (isto �, cartas "novas").
Se houverem cartas "novas" o usu�rio � consultado para decidir se deseja copi�-las
para a caixa postal local.

.sp
Para cada carta "nova", o usu�rio � consultado para saber se deseja copi�-la para
a caixa postal local, e em seguida, remove-la da caixa postal remota.
As respostas seguem as conven��es da fun��o "askyesno" (libc) no modo "de for�a",
isto �, letras min�sculas decidem a��es sobre uma carta em particular e
letras mai�sculas decidem a��es sobre todas as cartas seguintes. As a��es
das c�pias e remo��es s�o independentes.

.sp
As cartas, uma vez copiadas para a caixa postal local, podem ser lidas atrav�s
do programa "mail" (cmd).

.sp
As op��es do comando s�o:

.in +3
.ip -a
Normalmente, "pop3" apenas oferece para a remo��o as cartas novas da caixa
postal remota. Com a op��o "-a", todas as cartas da caixa postal remota
s�o oferecidas para remo��o. Tamb�m neste caso s�o seguidas as
conven��es da fun��o "askyesno" (libc) no modo "de for�a".

.ip -v
Verboso.

.ep
.in -3

.in
.sp
.b 'ARGUMENTOS NO AMBIENTE'
.in 5
Para simplificar o uso do programa, o nome do <usu�rio_remoto> e/ou do <n�_remoto>
podem ser dados no ambiente (fmt).
A cadeia do ambiente deve ter uma das formas

.sp
.nf
		POP3=<usu�rio_remoto>@<n�_remoto>
		POP3=<n�_remoto>
.fi

.sp
O nome do <n�_remoto> � procurado seguindo a ordem: 
argumento da linha de execu��o do programa,
ambiente (cadeia "POP3").

.sp
O nome do <usu�rio_remoto> � procurado seguindo a ordem: 
argumento da linha de execu��o do programa,
ambiente (cadeia "POP3").

.sp
O nome do <usu�rio_local> � procurado seguindo a ordem: 
ambiente (cadeia "USER"), 
nome dado ao entrar na conta (conforme o programa "who" (cmd)),
nome obtido atrav�s da identifica��o num�rica do usu�rio (UID).

.in
.sp
.(t
.b OBSERVA��ES
.in 5
O programa "pop3" espera que o servidor do <n�_remoto> processe
o comando "UIDL", para permitir a identifica��o das cartas.
Se isto n�o ocorrer, ele sup�e que t�das as cartas remotas
s�o novas. Neste caso, uma estrategia aconselh�vel � a de sempre copiar
t�das as cartas para a caixa postal local, removendo as cartas
da caixa postal remota.
.)t

.sp
O servidor "pop3" processa os seguintes comandos:
"HELP", "USER", "PASS", "QUIT", "NOOP", "LIST", "UIDL",
"STAT", "TOP", "LAST", "RETR", "DELE" e "RSET".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
mail, who
.br
.wo "(libc):"
askyesno
.br
.wo "(fmt): "
ambiente
.br

.in
.sp
.b
REFER�NCIAS
.r
.in 5
 J. Myers & M. Rose: "Post Office Protocol - version 3", RFC 1725, Novembro de 1994.

.in
.sp
.b ARQUIVOS
.in 5
 /var/spool/mail/$USER/l.*.t
 /var/spool/mail/$USER/status

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in




.bc	/*************************************/
.bp
.he 'POP3 (cmd)'TROPIX: Manual de Refer�ncia'POP3 (cmd)'
.fo 'Atualizado em 21.08.98'Vers�o 1.0.0'Pag. %'

.b NOME
.in 5
.wo "pop3_s -"
envia as cartas do correio eletr�nico segundo o protocolo POP3
.br

.in
.sp
.b DESCRI��O
.in 5
O servidor pop3_s permite o processamento remoto de correspond�ncia,
que � manipulada segundo o protocolo POP3, tornando simples o
acesso remoto atrav�s de programas de correio eletr�nico que executem
em esta��es de trabalho n�o UNIX.

.sp
As op��es do comando s�o:

.ip 'HELP [<cadeia>]' 24
Fornece informa��es sobre os comandos.

.ip 'USER <nome do usu�rio>' 24
Especifica o nome do usu�rio.

.ip 'PASS <senha>' 24
Fornece a senha.

.ip QUIT 24
Encerra o servi�o do servidor.

.ip NOOP 24
Apenas responde +OK

.ip 'LIST [<num.mensagem>]' 24
Fornece tamanho de uma mensagem (ou de todas).

.ip STAT 24
Fornece n�mero de mensagens e tamanho total.

.ip 'TOP  <num.mensagem> [<num.linhas>]' 24
Fornece o cabecalho e as primeiras linhas de uma mensagem.

.ip LAST 24
Informa o n�mero da �ltima mensagem processada.

.ip 'RETR <nome arquivo>' 24
Obt�m o conte�do de uma mensagem.

.ip 'DELE <Num.mensagem>' 24
Remove uma mensagem.

.ip RSET 24
Desapaga todas as mensagens.

.ep
.in -3

.in
.sp
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
mail
.br

.in
.sp
.(t
.b
REFER�NCIAS
.r
.in 5
Rose, M: "Post Office Protocol - version 3", RFC 1225, Maio de 1991.
.)t

.in
.sp
.(t
.b ARQUIVOS
.in 5
/usr/spool/mail/$USER/l.*.a
.br
/usr/spool/mail/$USER/status
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
.ec	/*************************************/
