.bp
.he 'KILL (cmd)'TROPIX: Manual de Refer�ncia'KILL (cmd)'
.fo 'Atualizado em 08.05.97'Vers�o 3.0.1'Pag. %'

.b NOME
.in 5
.wo "kill -"
envia sinais a processos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
kill [-s <sinal>] <pid> ...
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "kill" envia o sinal SIGTERM (15) (veja a op��o "-s")
para os processos (ou grupo de processos)
dados atrav�s de suas identifica��es num�ricas <pid>s.

.sp
Isto ir� normalmente cancelar os processos, a n�o ser que eles
ignorem ou interceptem o sinal enviado.

.sp
A filosofia e uma lista completa dos sinais s�o dadas em "kill" (sys)
e "signal" (sys).

.sp
As op��es do comando s�o:

.in +3
.ip -s
Com esta op��o, iremos enviar o <sinal> no lugar de SIGTERM.
O <sinal> pode ser dado na forma num�rica (de acordo com as conven��es
da linguagem "C", por ex. "22", "0x16", "026") ou na forma simb�lica
(por ex. "SIGABRT", "ABRT", "sigabrt" ou "abrt").

.ep
.in -3

.in
.sp
.b OBSERVA��ES
.in 5
Os <pid>s dos processos em "background" s�o dados diretamente pelo
"sh" (cmd); al�m disto, os <pid>s dos processos podem ser obtidos
atrav�s de "ps" (cmd).

.sp
Ao enviar um sinal para o <pid> igual a "0" , ser�o sinalizados todos
os processos do grupo de processos do usu�rio do "kill" (veja "intro" (sys)),
o que � �til para cancelar todos os processos em "background". 

.sp
Os processos sinalizados devem pertencer ao usu�rio do "kill", a n�o
ser que este seja um superusu�rio.

.sp
Como o sinal SIGKILL n�o pode ser ignorado nem interceptado,
ele garante o t�rmino de um processo.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sh, ps
.br
.wo "(sys): "
intro, signal, kill
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
