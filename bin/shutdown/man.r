.bp
.he 'SHUTDOWN (cmd)'TROPIX: Manual de Refer�ncia'SHUTDOWN (cmd)'
.fo 'Atualizado em 10.09.02'Vers�o 4.3.0'Pag. %'

.b NOME
.in 5
.wo "shutdown -"
reinicializa o computador ap�s um certo tempo
.br
.wo "reboot   -"
reinicializa o computador imediatamente
.br

.in
.sp
.b SINTAXE
.in 5
.(l
shutdown [-t <tempo>] [-p] [-v]
reboot
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "shutdown" reinicializa o computador ap�s um certo intervalo de tempo.

.sp
Inicialmente, o comando envia para todos os usu�rios em sess�o, mensagens
a cada 10 segundos, informando que o computador ir� "sair do ar" (veja a op��o "-p").

.sp
Ap�s um certo tempo (normalmente 30 segundos, veja a op��o "-t"), os blocos dos
discos s�o atualizados, e o computador � reinicializado (atrav�s da chamada ao
sistema "boot").

.sp
O comando "reboot" � uma variante para reinicializar o computador imediatamente.

.sp
Estes comandos s� podem ser usados pelo superusu�rio.

.sp
As op��es do comando s�o:

.in +3
.ip -t
Reinicializa o computador ap�s <tempo> segundos ao inv�s de 30.
O <tempo> dado � arredondado para o pr�ximo m�ltiplo de 10 segundos.

.ip -p
Reinicializa o computador imediatamente, sem enviar as mensagens nem
atualizar os blocos dos discos.
Este procedimento pode ser necess�rio em situa��es "de p�nico".

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
.wo "(sys): "
sync, boot
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
