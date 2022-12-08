.bp
.he 'WRITE (cmd)'TROPIX: Manual de Refer�ncia'WRITE (cmd)'
.fo 'Atualizado em 14.07.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
.wo "write -"
escreve mensagens para um outro usu�rio
.br

.in
.sp
.b SINTAXE
.in 5
.(l
write <usu�rio> [<tty>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "write" copia linhas do seu terminal para o terminal do
<usu�rio>, com a finalidade de estabelecer uma comunica��o entre dois usu�rios.

.sp
Ao iniciar, "write" envia a mensagem

.sp
.nf
	MENSAGEM de "seu nome" ("seu terminal"):
.fi

.sp
Se a conex�o � completada com sucesso, � escrita a mensagem

.sp
.nf
	Conectado com o usu�rio "<usu�rio>" no terminal "<tty>"
.fi

.sp
no seu terminal, al�m de soar a campainha,
para indicar que as mensagens digitadas est�o sendo enviadas.

.sp
Neste ponto, o <usu�rio> deve utilizar o comando "write" para estabelecer
uma comunica��o no sentido inverso.

.sp
A comunica��o continua at� que seja lido um EOF (normalmente <^D>,
ver "stty" (cmd)), seja enviado um sinal de interrup��o
("SIGINT", normalmente <^C>, ver "stty"),
ou o <usu�rio> execute o comando "mesg -n" (ver "mesg" (cmd)).
Neste ponto, "write" envia a mensagem

.sp
.nf
	FIM da mensagem de "seu nome" ("seu terminal")
.fi

.sp
Se o <usu�rio> est� em sess�o em mais de um terminal, pode ser usado
o argumento <tty> para indicar para qual dos terminais devem ser enviadas
as mensagens.  Se isto n�o for feito, as mensagens ser�o enviadas para
a primeira entrada do <usu�rio> no arquivo "/etc/utmp" (conforme pode
ser visto atrav�s de "who" (cmd)) .

.sp
O comando "write" obedece �s permiss�es atribu�das pelo comando "mesg"
(cmd), inclusive para superusu�rios.

.sp
Se o primeiro caractere da linha de uma mensagem for "!", a linha
ser� interpretada como sendo uma linha de comando, e executada atrav�s
do "sh" (cmd).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
mesg, stty, mail, who
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
