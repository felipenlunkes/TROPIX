.bp
.he 'PING (cmd)'TROPIX: Manual de Refer�ncia'PING (cmd)'
.fo 'Atualizado em 24.03.98'Vers�o 3.0.3'Pag. %'

.b NOME
.in 5
.wo "ping -"
teste de acesso a um n� remoto
.br

.in
.sp
.b SINTAXE
.in 5
.(l
ping [-spv] [-n <n>] <n� remoto>
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "ping" envia datagramas de "pedido de eco" (ECHO_REQUEST)
do protocolo ICMP para o <n� remoto>. Dependo do recebimento dos
datagramas de "resposta de eco" (ECHO_RESPONSE) do <n� remoto>, podemos
verificar se ele est� dispon�vel, e obter uma no��o do tempo 
necess�rio para a viagem de ida e volta de datagramas.

.sp
Sem op��es, "ping" envia apenas um datagrama, imprimindo o tempo de
viagem obtido, ou indicando que n�o obteve resposta
(ap�s 20 segundos de espera).

.sp
As op��es do comando s�o:

.in +3
.ip -s
Envia 10 datagramas e emite uma estat�stica (veja a op��o "-n").

.ip -p
Envia 10 datagramas e imprime um diagrama de barra (veja a op��o "-n").

.ip -v
Verboso.

.ip -n
Envia <n> datagramas ao inv�s de 10 (m�ximo de 20 datagramas).

.ep
.in -3

.in
.sp
.b OBSERVA��O
.in 5
Ao usar "ping" para a dete��o de erros, � recomend�vel utiliz�-lo
inicialmente para o pr�prio computador, para verificar
se a r�de est� operacional.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(xti): "
t_intro
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
