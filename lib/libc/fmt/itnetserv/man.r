.bp
.he 'ITNETSERV (fmt)'TROPIX: Manual de Refer�ncia'ITNETSERV (fmt)'
.fo 'Atualizado em 30.08.06'Vers�o 4.9.0'Pag. %'

.b NOME
.in 5
.wo "itnetserv -"
tabela de servidores da INTERNET
.br

.in
.sp
.b DESCRI��O
.in 5
A tabela "itnetserv" � utilizada durante o processo de inicializa��o
da INTERNET para obter informa��o
sobre quais servidores devem ser ativados (veja "internet" (cmd)).

.sp
A tabela reside no arquivo "/etc/itnetserv", e pode ser editada
diretamente pelo administrador do sistema atrav�s de "ed" (cmd)
ou "vi" (cmd). A tabela consiste de uma linha para cada servidor;
cada linha � composta de 5 campos separados por ":":

.sp
.nf
      *:protocolo:porta:conex�es:/usr/lib/itnet/servidor_s [-op��es]
.fi

.sp
O primeiro campo deve consistir de um �nico caractere, que
deve ser um asterisco ("*") para indicar um servidor ativo, e um branco
para inativo.

.sp
O segundo campo d� o nome do protocolo utilizado pelo servidor:
"tcp" ou "udp" (veja "t_intro" (xti)).

.sp
O terceiro campo d� o n�mero da porta atrav�s da qual o servidor deve
esperar pedidos de conex�o/servi�os.

.sp
O quarto campo d� o n�mero m�ximo de conex�es de um mesmo cliente
concomitantemente aceitas pelo servidor. O valor NULO significa
n�mero m�ximo ilimitado.

.sp
O quinto campo d� a linha de comando (com poss�veis op��es), que deve ser executada quando
vierem os pedidos de conex�o/servi�os (isto �, o c�digo do servidor).
Repare que (normalmente) os servidores residem no diret�rio
"/usr/lib/itnet".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
internet, vi, ed
.br
.wo "(xti): "
t_intro
.br

.in
.sp
.b ARQUIVOS
.in 5
/etc/itnetserv

.in
.sp
.(t
.b EXEMPLO
.nf
	*:udp: 53:0:/usr/lib/itnet/name_s
	*:tcp: 21:0:/usr/lib/itnet/ftp_s
	*:tcp: 23:0:/usr/lib/itnet/telnet_s
	*:tcp: 37:0:/usr/lib/itnet/nettime_s
	 :tcp: 79:0:/usr/lib/itnet/finger_s
	*:tcp: 80:3:/usr/lib/itnet/www_s
	*:tcp:137:0:/usr/lib/itnet/tcmpto_s -p
	 :tcp:513:0:/usr/lib/itnet/rlogin_s
.fi
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.
