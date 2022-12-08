.bp
.he 'ITNETDEV (fmt)'TROPIX: Manual de Refer�ncia'ITNETDEV (fmt)'
.fo 'Atualizado em 30.08.06'Vers�o 4.9.0'Pag. %'

.b NOME
.in 5
.wo "itnetdev -"
tabela de dispositivos/roteamento da INTERNET
.br

.in
.sp
.b DESCRI��O
.in 5
A tabela "itnetdev" � utilizada durante o processo de inicializa��o
da INTERNET para obter informa��es sobre os endere�os IP
(veja t_intro (xti)), dispositivos usados para entrada/sa�da de datagramas
(linhas seriais e "ethernet") e o roteamento (isto �, como decidir
para qual dispositivo deve ser enviado cada datagrama).

.sp
A tabela reside no arquivo "/etc/itnetdev", e pode ser editada
diretamente pelo administrador do sistema atrav�s de "ed" (cmd)
ou "vi" (cmd).

.sp
A configura��o deste arquivo � dependente de como o computador ser�
conectado � INTERNET; h� 3 modos b�sicos:

.in +3
.ip 1. 3
A uma rede INSTITUCIONAL: o computador est� situado
em uma firma ou universidade, etc ...;
a liga��o � normalmente atrav�s de "ethernet"
(embora tamb�m possa ser feita atrav�s de linha
serial usando protocolos SLIP ou PPP).
Neste caso, o nome do computador/dom�nio, endere�o IP, m�scara da
rede e o endere�o do servidor de nomes do DNS s�o dados
pelo gerente da rede ou pelo protocolo DHCP (veja abaixo).

.ip 2. 3
A uma rede DOM�STICA: os computadores est�o situados na casa do usu�rio;
a liga��o entre eles pode ser atrav�s de "ethernet"
ou linha serial usando protocolos SLIP ou PPP.
Neste caso, o nome do computador/dom�nio e o seu endere�o IP
podem ser livremente escolhidos pelo usu�rio;
para os endere�os IP � aconselh�vel utilizar endere�os da forma
"192.168.0.xxx" (isto �, a rede "192.168.0.0"),
pois s�o endere�os reservados para uso local,
evitando a colis�o com endere�os de algum computador presente na
rede mundial INTERNET; n�o � necess�rio o uso de um servidor de nomes;
os endere�os dos v�rios computadores devem ser inclu�dos no
arquivo "/etc/itnetdev".

.ip 3. 3
A uma rede de linha (telef�nica) discada (atrav�s de "modem"),
usando protocolo PPP e utilizando os servi�os de um provedor
(veja "ppp" (cmd)).
Neste caso, o nome do computador/dom�nio
podem ser livremente escolhidos pelo usu�rio, mas de tal modo
a evitar colis�es com redes j� existentes. 
O endere�o IP � automaticamente atribu�do no momento da liga��o,
e o endere�o IP do servidor de nomes do DNS � dado pelo provedor.

.sp
Repare que podemos ter simultaneamente um acesso de linha discada
e um dos dois casos anteriores; se for uma rede institucional, use
os dados fornecidos pelo gerente da rede, conforme acima.


.bc	/*************************************/
Deve-se, no entanto, tomar cuidado com a palavra chave "default"
(ver abaixo).
.ec	/*************************************/

.ep
.in -3

.sp
O arquivo "/etc/itnetdev" consiste de 4 partes.
Acompanhe no arquivo prot�tipo j� presente na distribui��o do
TROPIX (os diversos campos s�o separados por um ou mais
brancos ou caracteres <ht>; linhas come�ando por "#" s�o coment�rios):

.in +3
.ip 1. 3
Uma linha definindo o nome do pr�prio computador, juntamente com
o dom�nio. Este endere�o IP � sempre "127.0.0.1"
(que � usado quando o computador quer referir a si pr�prio).
Exemplo:

.sp
.nf
		127.0.0.1 meu_computador.meu_dom�nio.com.br
.fi

.sp
Ao alterar o nome do "meu_computador", altere tamb�m o campo
"nodename" da estrutura "scb" (veja "edscb" (cmd)).

.ip 2. 3
Linhas dando endere�os IP de computadores previamente escolhidos.
Esta parte s� � necess�ria para redes dom�sticas, embora tamb�m possa
ser inclu�da nos outros dois casos (para que n�o sejam necess�rias
consultas a um servidor de nomes). Exemplo:

.sp
.nf
		192.168.0.3 outro_computador.meu_dom�nio.com.br
.fi

.ip 3. 3
Linhas definindo os dispositivos associados a cada classe de endere�os IP
(ou seja, roteamentos).
Estas linhas N�O s�o necess�rias se o computador estiver
conectado apenas a uma rede de linha discada (veja "ppp" (cmd)).

.sp
No caso de "ethernet" dom�stico, s�o necess�rias linhas do tipo

.sp
.nf
		/dev/ed0		192.168.0.2
		netmask=255.255.255.0
.fi

.sp
onde "/dev/ed0" corresponde ao dispositivo "ethernet".
O valor "192.168.0.2" � o endere�o IP deste computador
(atrav�s deste dispositivo), e "255.255.255.0"
� a m�scara da rede dom�stica, o que ir� definir
a rede "192.168.0.0".

.sp
Estes dados s�o usados na decis�o de roteamento.
Se a opera��o "E BIN�RIO" do endere�o IP destino com a m�scara
der como resultado o endere�o da rede, ent�o
o datagrama ser� enviado atrav�s do dispositivo "/dev/ed0".

.sp
Se a "ethernet" for institucional, h� duas possibilidades:
na primeira, estes valores s�o dados pelo gerente da rede e na
segunda � utilizado o protocolo DHCP (que obt�m automaticamente
estes valores).

.sp
Na primeira hip�tese (valores dados pelo gerente da rede),
as linhas podem (por exemplo) ter a forma

.sp
.nf
		/dev/ed0		146.164.16.220
		netmask=255.255.255.192, default
.fi

.sp
onde "/dev/ed0" corresponde ao dispositivo "ethernet".
O valor "146.164.16.220" � o endere�o IP deste computador
(atrav�s deste dispositivo), e "255.255.255.192"
� a m�scara da rede, o que define a rede "146.164.16.192"
(atrav�s de um "E BIN�RIO").

.sp
A palavra chave "default" ao final da linha indica que um roteador
deve ser usado caso o endere�o IP n�o seja da rede "146.164.16.192".
O roteador tem (quase sempre) o primeiro endere�o da rede, no caso
"146.164.16.193".

.sp
No segundo caso (protocolo DHCP),
as linhas podem (por exemplo) ter a forma

.sp
.nf
		/dev/ed0		dhcp
		netmask=0.0.0.0, default
.fi

.sp
Repare que "default" finaliza a tabela de roteamento, isto �,
ela indica que todos os datagramas ainda n�o enviadas ser�o dirigidas
para o �ltimo dispositivo.

.bc	/*************************************/
.sp
Se for usada (adicionalmente) uma linha discada ("modem"),
a tabela de roteamento � modificada automaticamente no momento do
estabelecimento da conex�o: se a tabela ainda N�O tiver uma entrada
"default", a linha discada ser� utilizada como "default"; caso contr�rio,
ela ser� posta em pen�ltimo lugar. Isto significa que uma linha discada
tem prioridade sobre uma entrada "default".
.ec	/*************************************/

.bc	/*************************************/
Em particular, se foi usado o "default",
n�o poder� ser usado linha discada ("modem").
.ec	/*************************************/

.sp
No caso de uma linha serial PPP, estas linhas t�m a forma

.sp
.nf
	      /dev/ppp002,-clocal,fifo=16,115.2,ppp=vj 192.168.0.2
	      netmask=255.255.255.0
.fi

.sp
onde "/dev/ppp002" corresponde � linha serial com protocolo PPP.
Lembre-se de que "ppp000" corresponde a COM1, "ppp002" a COM2, ...

.sp
O argumento "-clocal" deve ser dado caso o cabo f�sico contenha os
sinais de controle de fluxo por "hardware" (RTS/CTS); em caso contr�rio
deve ser posto "clocal". O argumento "fifo" determina o n�mero de caracteres
transmitidos de cada vez; normalmente n�o precisa ser alterado.
A velocidade (no caso "115.2") � a taxa de transmiss�o (no caso
115200 baud, ou seja 115200 bits/segundo). Veja os outros valores
poss�veis atrav�s de "stty" (cmd). O argumento "ppp=vj" deve ser dado
caso seja utilizada a compress�o do cabe�alho TCP/IP.
Naturalmente, todos estes argumentos devem ser iguais nas duas extremidades
da liga��o PPP.

.sp
No caso de uma linha serial SLIP, estas linhas t�m a forma

.sp
.nf
		/dev/slip002,-clocal,fifo=16,115.2 192.168.0.2
		netmask=255.255.255.0
.fi

.sp
onde "/dev/slip002" corresponde � linha serial com protocolo SLIP.
Lembre-se de que "slip000" corresponde a
COM1, "slip002" a COM2, ...

.sp
Os argumentos "-clocal", "fifo" e "115.2" s�o an�logos ao caso PPP,
acima.

.sp
Se for usada (adicionalmente) uma linha discada ("modem"),
a tabela de roteamento � modificada automaticamente no momento do
estabelecimento da conex�o: se a tabela ainda N�O tiver uma entrada
"default", a linha discada ser� utilizada como "default"; caso contr�rio,
ela ser� posta em pen�ltimo lugar. Isto significa que uma linha discada
tem prioridade sobre uma entrada "default".

.ip 4. 3
Uma (ou mais) linha(s) contendo os endere�os IP dos servidores de nomes DNS.
Um servidor de nomes executa a tradu��o de nomes simb�licos tais
como "rocinha.nce.ufrj.br" em endere�os IP (no caso "146.164.8.2").

.sp
Uma linha tem a forma:

.sp
.nf
		name_server 200.17.63.121 146.164.10.2
.fi

.sp
onde podem ser dados v�rios endere�os. Ser� utilizado o servidor
que oferecer resposta mais r�pida.

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
internet, ppp, vi, ed, edscb
.br
.wo "(xti): "
t_intro
.br
.br
.wo "(fmt): "
scb

.in
.sp
.(t
.b ARQUIVOS
.in 5
/etc/itnetdev
.)t

.in
.sp
.(t
.b EXEMPLO
.nf
	#
	#	R�de dom�stica (pode haver linha discada)
	#
	127.0.0.1		jupiter.tropix.com.br

	192.168.0.3		marte.tropix.com.br
	192.168.0.4		venus.tropix.com.br

	146.164.8.7		barra.nce.ufrj.br
	146.164.8.3		vidigal.nce.ufrj.br
	146.164.8.2		rocinha.nce.ufrj.br

	/dev/ed0				192.168.0.2
	netmask=255.255.255.0

	name_server		200.17.63.121	146.164.10.2
.fi
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.
