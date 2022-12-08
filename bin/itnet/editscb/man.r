.bp
.he 'EDITSCB (cmd)'TROPIX: Manual de Refer�ncia'EDITSCB (cmd)'
.fo 'Atualizado em 14.08.98'Vers�o 3.1.0'Pag. %'

.b NOME
.in 5
.wo "editscb -"
edita/imprime o bloco de controle da INTERNET
.br

.in
.sp
.b SINTAXE
.in 5
.(l
editscb
editscb -e [-v] [<porta>]
editscb -t [-v]
editscb -f [-v] <dev> [<sz>]
editscb -d [-v] [+-][<arg>]
editscb -p [-v] <arg>=<valor>
.)l

.bc	/*************************************/
editscb [-etv] [-f <dev> [<sz>]] [-d [+-][<arg>]]
						[-p <arg>=<valor>]
.ec	/*************************************/

.in
.sp
.b DESCRI��O
.in 5
O comando "editscb" gerencia diversos par�metros da INTERNET. 

.sp
Sem op��es, "editscb" imprime inicialmente uma linha com os
seguinte par�metros gerais (veja "t_intro"):

.in +3
.ip 1.
ITBLOCKs: O n�mero de �reas de entrada/sa�da
em uso/alocadas para datagramas.

.ip 2.
RAW EPs: O n�mero de estruturas ("endpoints") em uso/alocadas
para o modo-de-acesso-interno.

.ip 3.
UDP EPs: O n�mero de estruturas em uso/alocadas para o modo-sem-conex�o.

.ip 4.
TCP EPs: O n�mero de estruturas em uso/alocadas para o modo-com-conex�o.

.ep
.in -3

.sp
Em seguida "editscb" imprime os seguintes par�metros do modo-com-conex�o (TCP):

.in +3
.ip 1.
WND_SZ: O tamanho total da janela:
N�mero de bytes permitidos para a recep��o de dados em uma conex�o.

.ip 2.
GOOD_WND: O "bom" tamanho da janela:
Limite de bytes para permitir o in�cio de transmiss�o em uma conex�o.

.ip 3.
ALPHA: O fator de amortecimento do algoritmo de retransmiss�o TCP em \%
(Veja o RFC 793, pg. 41, para detalhes sobre este algoritmo).

.ip 4.
BETA: O fator de vari�ncia de atraso do algoritmo de retransmiss�o TCP
(Veja o RFC 793, pg. 41, para detalhes sobre este algoritmo).

.ip 5.
SRTT: O tempo amortecido de viagem de ida e volta inicial (em segundos)
do algoritmo de retransmiss�o TCP
(Veja o RFC 793, pg. 41, para detalhes sobre este algoritmo).

.ip 6.
N_TRANS: O n�mero m�ximo de transmiss�es dos datagramas TCP.

.ip 7.
WAIT: O tempo m�ximo (em segundos) de espera para conex�es TCP
ainda n�o completadas.
 
.ip 8.
SILENCE: O tempo m�ximo (em segundos) de manuten��o de conex�es TCP sem
transmiss�o/recep��o de datagramas.

.ip 9.
MAX_SGSZ: O tamanho m�ximo (em bytes) do segmento TCP permitido nas negocia��es.

.ep
.in -3

.in
.sp
.b DEPURA��O/CONTROLE
.in 5
O sistema operacional TROPIX permite que a atividade dos m�dulos da
INTERNET sejam monitorados/controlados (veja a op��o "-d").

.sp
Os argumentos <arg> que alteram a depura��o/controle s�o:

.in +3
.ip 'wi:' 4
Grava a entrada de datagramas no arquivo "itnet.debug".

.ip 'wo:' 4
Grava a sa�da de datagramas no arquivo "itnet.debug".

.ip 'li:' 4
Relata a entrada de datagramas.

.ip 'lo:' 4
Relata a sa�da   de datagramas.

.ip 'rt:' 4
Relata retransmiss�es.

.ip 'oq:' 4
Relata remo��es da fila de retransmiss�o.

.ip 'ce:' 4
Causa erros propositais de "checksum" na recep��o de datagramas.

.ip 'er:' 4
Relata erros.

.ip 'in:' 4
Lista algumas infoma��es adicionais.

.ip 'bs:' 4
Relata segmentos recusados.

.ip 'lw:' 4
Relata tamanhos das janelas.

.ip 'tt:' 4
Relata c�lculos do SRTT.

.ip 'gw:' 4
Executa a fun��o de GATEWAY.

.ip 'pi:' 4
Usa a otimiza��o para conex�es TCP internas.

.ep
.in -3

.in
.sp
.b 'OP��ES DE "EDITSCB"'
.in 5
As op��es do comando s�o:

.in +3
.ip -e
Imprime as estruturas ("endpoints") TCP em uso. Para cada conex�o,
s�o dados os endere�os IP ("Internet Protocol"), portas,
o estado da conex�o, os n�meros de seq��ncia,
os tamanhos das janelas, os tamanhos das filas de entrada/sa�da,
e outras vari�veis da estrutura TCP_EP (Veja o arquivo 
"/usr/include/sys/itnet.h" e o RFC 793).

.sp
Se for dada a <porta> opcional, ser�o impressos somente os
dados referentes � esta porta local.

.ip -t
Imprime 3 tabelas: a tabela de endere�os IP conhecidos,
a tabela de roteamento e a tabela de endere�os dos dispositivos "ethernet".

.sp
A tabela de endere�os cont�m uma linha para cada n� conhecido da r�de,
contendo o seu endere�o IP, alguns indicadores e o nome do n�.
Os indicadores s�o:
A coluna "C" cont�m "C" para o nome de um
computador, "A" para um nome "alias" de um computador e "M" para
um dom�nio de correio eletr�nico.
A coluna "E" (erros) cont�m "N" para um nome inexistente, "S" para um �rro
do servidor de nomes e <sp> se n�o houver erros.
A coluna "I" cont�m o �ndice do servidor de nomes utilizado para obter
este endere�o; corresponde � lista dada no final do arquivo "/etc/itnetdev".
A coluna "PRE" cont�m o valor de "prefer�ncia" de um servidor de correio.

.sp
A tabela de roteamento indica para qual dispositivo de sa�da
o datagrama deve ser enviado (baseado no seu endere�o IP destino).
O datagrama � enviado para o dispositivo associado � primeira linha que
satisfizer: ((endere�o & M�SCARA) == REDE).
O campo LOCAL d� o endere�o IP fonte a ser utilizado no datagrama. 
O campo GATEWAY d� o endere�o IP de um roteador, caso a rede destino n�o
esteja conectada diretamente a este computador.
O campo DISPOSITIVO d� o nome simb�lico do dispositivo que deve enviar o
datagrama.

.sp
A tabela de endere�os dos dispositivos "ethernet" fornece o endere�o f�sico
do dispositivo "ethernet" (48 bits) associado ao endere�o IP. 

.ip -v
Verboso.

.ip -f
Consulta/altera o tamanho do FIFO de sa�da da linha serial <dev>.
Esta op��o s� � pertinente se a linha serial for o mod�lo NS16550
(ou equivalentes), e <dev> for um dispositivo SLIP ou PPP.
Se <sz> for dado (de 1 a 16), altera o valor para <sz>.
Se <sz> n�o for dado, imprime o valor corrente.

.ip -d
Depura��o/controle: Esta op��o permite consultar/alterar a
depura��o/controle da INTERNET (veja os argumentos acima).

.sp
Com a op��o "-d -" s�o impressos os estados atuais dos argumentos
(asteriscos no in�cio da linha indicam que o argumento est� ligado);
com a op��o "-d <arg>" ou "-d +<arg>" � ligado o argumento <arg>;
com a op��o "-d -<arg>" � desligado o argumento <arg>.

.ip -p
Altera o par�metros.
Podem apenas ser alterados os par�metros do modo-com-conex�o (TCP):
WND_SZ, GOOD_WND, ALPHA, BETA, SRTT,
N_TRANS, WAIT, SILENCE e MAX_SGSZ.
O par�metro ALPHA deve ser dado como uma percentagem; os demais
deve ser dados com o pr�prio valor; v�rios par�metros pode ser dados
separados por v�rgulas.

.sp
Repare que os valores de ITBLOCKs, RAW EPs, UDP EPs e TCP EPs s�o modificados
por "edscb" e N�O por este comando "editscb".

.sp
Consulte "scb" (fmt), par�metros "nitblock", "nrawep", "nudpep", "ntcpep", 
"ndns", "nroute" e "nether".

.ep
.in -3

.in
.sp
.b OBSERVA��O
.in 5
Repare que N�O h� arquivo de configura��o para os par�metros TCP.
Se for desejado usar (sempre) um valor n�o padr�o, � necess�rio
incluir um linha executando "editscb" no arquivo "/etc/rc".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
edscb, prscb
.br
.wo "(xti): "
t_intro
.br
.wo "(fmt): "
scb
.br

.in
.sp
.b
REFER�NCIAS
.r
.in 5
Postel, J., "Transmission Control Protocol", RFC 793,
USC/Information Sciences Institute, September 1981.

.in
.sp
.b ARQUIVOS
.in 5
/etc/itnetdev
 /etc/rc

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
