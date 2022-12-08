.bp
.he 'ITNET_DAEMON (cmd)'TROPIX: Manual de Refer�ncia'ITNET_DAEMON (cmd)'
.fo 'Atualizado em 14.11.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
.wo "itnet_daemon -"
processo gerenciador da internet
.br

.in
.sp
.b SINTAXE
.in 5
.(l
/usr/lib/itnet/itnet_daemon
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "itnet_daemon" � o processo gerenciador da internet.

.sp
Ele l� os arquivos de configura��o "/etc/itnetdev" e "/etc/itnetserv",
e cria os seguintes processos:

.in +3
.ip 1. 3
"in_daemon" (que controla o recebimento de datagramas);

.ip 2. 3
"out_daemon" (que controla a sa�da de datagramas, incluindo as retransmiss�es);

.ip 3. 3
"name_s" (que envia pedidos de endere�os IP para os servidores de nomes do
DNS);

.ip 4. 3
os diversos "serv_daemon" (que esperam pedidos de conex�es/servi�os
para os v�rios servidores).

.ep
.in -3

.sp
Normalmente, o programa "itnet_daemon" � iniciado durante a execu��o
do arquivo "/etc/rc", embora possa tamb�m ser executado manualmente
(principalmente para testes).

.sp
Para cancelar todos estes processos (isto �, a INTERNET), basta dar o
comando

.sp
.nf
		kill -s int pid
.fi

.sp
onde "pid" � o PID do processo "itnet_daemon" (obtido atrav�s do "ps").

.sp
Se for desejado incluir/excluir um servidor, N�O � necess�rio
cancelar/reiniciar a internet. Basta editar o arquivo "/etc/itnetserv",
e executar o comando

.sp
.nf
		kill pid
.fi

.sp
onde "pid" � o mesmo descrito acima. Com isto, "itnet_daemon" rel� o
arquivo "/etc/itnetserv", e ativa/desativa o servidor.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
editscb
.br
.wo "(xti): "
t_intro
.br
.wo "(fmt): "
itnetserv, itnetdev
.br

.in
.sp
.b ARQUIVOS
.in 5
/etc/itnetdev
 /etc/itnetserv
 /etc/rc

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
