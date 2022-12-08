.bp
.he 'PPP (cmd)'TROPIX: Manual de Refer�ncia'PPP (cmd)'
.fo 'Escrito em 14.04.00'Vers�o 3.2.3'Pag. %'

.b NOME
.in 5
.sp
.wo "ppp -"
cria uma comunica��o PPP com um n� remoto
.br

.in
.sp
.b SINTAXE
.in 5
.(l
ppp [-l <linha>] [-t <texto>] [-p <conta>:<senha>]
.)l

.bc	/*************************************/
ppp [-l <linha>] [-s <velocidade>] [-t <texto>] [-f <n>] [-j]

Op��es:	-l: Define a <linha> de comunica��es a utilizar
	    (se n�o dada, � utilizada a linha "/dev/pppline")
	-t: Escreve o <texto> de inicializa��o do modem
	    (contendo o n�mero do telefone)
	-p: Usa a <conta:senha> dada

Obs.:	Para desconectar use "ps -k" ou "kill ..."
.ec	/*************************************/

.in
.sp
.b DESCRI��O
.in 5
O comando "ppp" cria uma conex�o PPP ("Point to Point Protocol")
atrav�s de uma linha de comunica��es.

.sp
Para criar uma conex�o PPP atrav�s do comando "ppp" s�o necess�rios
os seguintes recursos/conhecimentos:

.in +3
.ip 1.
Uma conta em um provedor que permita o acesso atrav�s de linha discada
(por exemplo, o NCE/UFRJ).

.ip 2.
O endere�o IP do servidor de nomes (DNS) do provedor
(por exemplo, 146.164.10.2 no caso do NCE).

.sp
Este endere�o deve ser inclu�do na linha "name_server"
do arquivo "/etc/itnetdev" (veja itnetdev (fmt)). Este endere�o deve
ser dado antes de inicializar a rede (por exemplo, atrav�s de
um "boot").

.ip 3.
O n�mero de telefone a discar (por exemplo, 598-3240 no caso do NCE).

.ip 4.
Configurar o modem. Para isto � necess�rio saber o endere�o ("port")
do modem e o seu IRQ (n�mero da interrup��o). Estes dois dados podem
ser alterados apenas nesta execu��o do TROPIX (durante o "boot") ou
(um pouco mais) definitivamente atrav�s do comando "edscb" (cmd).

.sp
Para facilitar, � �til dar um "link" (isto �, criar um sin�nimo) do 
dispositivo do modem ("/dev/ppp00?") para o nome "default"
("/dev/pppline"); veja a op��o "-l".

.ip 5.
Saber os caracteres de inicializa��o/controle do modem. Normalmente
basta uma cadeia do tipo "atpd5983240" (para discar o NCE), mas dependendo
da marca/modelo do modem, outros caracteres de controle podem ser necess�rios.
Consulte o manual do seu modem.

.sp
Por exemplo, se for desejado teclar no modo de tom (ao inv�s de pulso
como acima), basta trocar o "p" por "t".
Se voc� tiver um "modem" "US Robotics", talvez seja �til
acrescentar os caracteres "s6=5", que aumentam o tempo de espera pelo
sinal de discar para 5 segundos
(considerando que os telefones cariocas (muitas v�zes)
demoram para dar o sinal de discar).
Com estas duas modifica��es, ter�amos a cadeia "ats6=5td5983240".

.sp
Esta cadeia pode ser dada atrav�s da op��o "-t" (ver abaixo), ou ser teclada
manualmente.

.bc	/*************************************/
Com os telefones brasileiros, que (muitas v�zes) demoram para dar o sinal de discar,
� �til acrescentar os caracteres "s6=5"

.ip 6.
Saber a velocidade do modem. Se n�o for usada a op��o "-s" (ver abaixo),
o modem ir� tentar negociar a velocidade de 9600 baud (a n�o ser que ele
seja mais lento do que isto). Normalmente, o mais simples � utilizar
a op��o "-s 38.4", pois neste caso o modem ir� negociar a maior velocidade
comum (isto no atual estado da tecnologia, que s�o modems de at� 33600
baud).
.ec	/*************************************/

.ep
.in -3

.sp
.(t
Ap�s a discagem, quando o modem do provedor atender, inicia-se a fase de
autentica��o, onde negocia-se o nome da conta e da senha. Em seguida, assim que
o provedor enviar o primeiro pacote PPP, o programa "ppp" inicia
automaticamente a negocia��o PPP, ap�s a qual volta o "prompt" do
"sh" (cmd). Neste ponto, fica um processo "ppp" em "background",
e a conex�o recem criada j� pode ser usada.
.)t

.sp
Repare na linha "Entrando em modo PPP ...". Nela s�o dadas a velocidade
da conex�o, e o n�mero do processo ("pid") que ser� usado
mais tarde para terminar a conex�o.

.sp
Nesta vers�o de "ppp" j� � processado o protocolo PAP ("Password
Authentication Protocol").

.sp
Se n�o for conseguida a conex�o na primeira tentativa, o comando "ppp"
executa mais 4 tentativas, ap�s as quais a execu��o � encerrada.
Durante esta fase, o comando pode ser cancelado teclando-se os
caracteres "~.".

.sp
Utilize o comando "editscb" (cmd) com a op��o "-t" para verificar 
se o dispositivo "ppp" foi inclu�do na tabela de roteamento.
Para testar a disponibilidade de n�s da rede, use o comando "ping" (cmd).

.sp
Para encerrar a conex�o, basta cancelar o processo "ppp" (que ficou em
"background"). Para isto usamos o comando "kill" (cmd) para terminar
o processo cujo n�mero foi dado no momento do estabelecimento da conex�o
("pid"), veja acima. Se voc� n�o guardou este n�mero, 
podemos usar o comando "ps" (cmd) com o argumento "-k".
Uma outra alternativa � de usar "ps" apenas para saber o "pid" do processo
"ppp" e em seguida usar o comando "kill".

.sp
As op��es do comando s�o:

.in +3
.ip -l
Define a <linha> de comunica��es a utilizar.
Se esta op��o n�o for dada, � utilizada a linha "/dev/pppline".
Repare que "/dev/ppp000" corresponde a COM1 (do MS-DOS),
"/dev/ppp001" corresponde a COM2,
"/dev/ppp002" corresponde a COM3, e assim por adiante.

.bc	/*************************************/
ppp [-l <linha>] [-s <velocidade>] [-t <texto>] [-f <n>] [-j]

.ip -s
Define a <velocidade> da linha.
Uma lista completa de velocidades � dada em "stty" (cmd).
Se esta op��o n�o for dada, a velocidade da linha ser� estabelecida
em 115200 baud, e posteriormente o modem ir� negociar a maior velocidade
poss�vel com o modem do provedor.
Esta op��o s� precisa ser usada se for desejado utilizar velocidades
mais baixas do que o m�ximo acima mencionado.
.ec	/*************************************/

.ip -t
Escreve o <texto> dado na linha. Este <texto> � normalmente usado
para inicializar um modem e discar o n�mero de telefone desejado. 

.bc	/*************************************/
.ip -f
Define o n�mero m�ximo <n> de caracteres a escrever no FIFO
de sa�da da linha serial em cada interrup��o.
Os valores v�lidos v�o de 1 a 16 (mas dependem do tipo da linha serial).
O objetivo desta op��o � a de reduzir a velocidade de sa�da da
linha serial, e normalmente N�O deve ser usada.

.ip -j
Normalmente, � utilizada a compress�o de "Van Jacobson" nos cabe�alhos
TCP/IP, que reduz o tamanho t�pico de 40 bytes para (at�) 3 bytes. 
Com esta op��o, esta compress�o n�o � utilizada,
e normalmente (a op��o) N�O deve ser usada.
.ec	/*************************************/

.ip -p
Fornece a conta/senha para a conex�o PPP. Normalmente, para a "conta" �
usado o pr�prio nome do usu�rio dado no "login" (cmd), e que est� em geral dispon�vel
atrav�s da vari�vel "USER" do ambiente (veja "environ" (fmt)). Atrav�s desta
op��o podemos dar um outro nome de conta.

.sp
A senha correspondente � pedida no in�cio da execu��o de "ppp". Podemos tamb�m
adicion�-la � op��o "-p" da linha de comando (veja a observa��o, abaixo),
o que por um lado � c�modo, por outro lado torna a senha menos secreta.

.sp
Na forma "-p <conta>:<senha>" s�o dados a conta e senha,
em "-p <conta>" � dada apenas a conta, e em "-p :<senha> � dada apenas a senha.

.ep
.in -3

.in
.sp
.b OBSERVA��O
.in 5
Uma forma c�moda de utilizar o programa "ppp" � o de construir
arquivos contendo j� uma linha de comando para um provedor.
Veja como exemplo o arquivo "/usr/pub/bin/pppnce".

.sp
Durante a conex�o PPP, � adicionada uma entrada para o dispositivo
"ppp" na tabela de roteamento. Esta entrada ter� sempre prioridade
sobre entradas "default" (veja "itnetdev").

.bc	/*************************************/
Lembre-se de que o roteamento para o dispositivo "ppp" N�O ser�
poss�vel se for usado o roteamento "default" (veja "itnetdev").
.ec	/*************************************/

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sh, ps, kill, stty, edscb, editscb, ping
.br
.wo "(fmt): "
itnetdev, environ
.br

.in
.sp
.b
REFER�NCIAS
.r
.in 5
W. Simpson, "The Point-to-Point Protocol (PPP)", RFC 1661,
Julho 1994.

.sp
V. Jacobson, "Compressing TCP/IP Headers for Low-Speed Serial
Links", RFC 1144, Fevereiro 1990.

.in
.sp
.b ARQUIVOS
.in 5
/dev/ppp00?
 /etc/itnetdev
 /usr/pub/bin/pppnce

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
