.bp
.he 'RLOGIN (cmd)'TROPIX: Manual de Refer�ncia'RLOGIN (cmd)'
.fo 'Atualizado em 15.08.97'Vers�o 3.0.2'Pag. %'

.b NOME
.in 5
.wo "rlogin -"
entra em sess�o em um n� remoto
.br

.in
.sp
.b SINTAXE
.in 5
.(l
rlogin [-iv] [-l <usu�rio_remoto>] <n�_remoto>

rlogin [-iv] [<usu�rio_remoto>@]<n�_remoto>
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "rlogin" estabelece uma sess�o no <n�_remoto> da r�de de
comunica��es.

.sp
Uma vez tendo completada a conex�o e entrado em sess�o com o <n�_remoto>,
"rlogin" l� caracteres do teclado, enviado-os para o <n�_remoto>
e l� caracteres recebidos do <n�_remoto>, escrevendo-os na tela do terminal.

.sp
O eco � realizado no <n�_remoto> (isto �, pelo servidor), de tal
modo que a sess�o remota � transparente (a n�o ser pela menor velocidade).

.sp
O tipo do terminal remoto � o mesmo do que o local
(como dado na vari�vel "TERM" do ambiente).

.sp
As op��es do comando s�o:

.in +3
.ip -i
N�o converte o c�digo na recep��o: normalmente, � efetuada a convers�o
dos c�digos recebidos atrav�s da r�de para o c�digo apropriado do
terminal local (por exemplo ISO para ABICOMP). Com a op��o
"-i" esta convers�o n�o � efetuada; isto � �til quando o c�digo
recebido atrav�s de r�de j� � o adequado para o terminal.  

.ip -v
Verboso: Diversas informa��es s�o impressas, entre as quais os nomes
do usu�rio local e remoto.

.ip -l
Define o nome do usu�rio remoto (pode tamb�m ser dado no formato
com o caractere "@"): se n�o for dado, o nome do usu�rio remoto
� o mesmo do que o nome do usu�rio local.
.ep
.in -3

.in
.sp
.b OBSERVA��O
.in 5
J� � processado o protocolo de c�pia do tamanho da janela.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
telnet
.br

.in
.sp
.b
REFER�NCIAS
.r
.in 5
"BSD Rlogin", B. Kanter, Request for Comments 1282.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
