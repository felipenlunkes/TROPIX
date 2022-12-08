.bp
.he 'INTRO (xti)'TROPIX: Manual de Refer�ncia'INTRO (xti)'
.fo 'Escrito em 04.03.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "intro -"
introdu��o aos conceitos da interface XTI

.in
.sp 2
.b INTRODU��O
.in 5
A especifica��o XTI ("X/Open Transport Interface") define uma interface
de servi�o de transporte que tenta ser independente do ve�culo
espec�fico do transporte (isto �, do sistema de transporte e do
protocolo nele usado).
A interface � definida atrav�s de um conjunto de fun��es para a
linguagem de programa��o "C" (a biblioteca "xti", ou "libxti").

.sp
XTI engloba um grande conjunto de fun��es e facilidades que pode
variar de import�ncia e/ou utilidade. Uma aplica��o ser� port�til
atrav�s de v�rios sistemas com implementa��es diversas da XTI, se
uma (ou ambas) das seguintes afirmativas for verdadeira:

.in +3

.ip a. 3
A aplica��o foi programada para modificar seu comportamento de
acordo com o subconjunto das fun��es e facilidades dispon�veis
em cada uma das implementa��es nas quais a aplica��o deve funcionar.

.ip b. 3
A aplica��o s� utiliza as fun��es e facilidades b�sicas, que
garantidamente est�o presentes em todas as implementa��es.

.ep
.in -3

.sp
Aos poucos, nesta introdu��o, ser�o indicadas quais as fun��es
e facilidades suportadas nesta implementa��o.

.in
.sp 2
.(t
.b 'MODELO DE PROGRAMA��O'
.in 5

.sp
.(l
	+---------------+			+---------------+
	|		|			|		|
	|   Aplica��o	| 			|   Aplica��o	|
	|		|			|		|
	+-------+-------+			+-------+-------+
		|					|
		|					|
	+-------+-------+			+-------+-------+
	|		|			|		|
	|  Sistema de	| 			|  Sistema de	|
	|		+--->>--( REDE )---<<---+		|
	|  Transporte	|			|  Transporte	|
	|		|			|		|
	+---------------+			+---------------+
.)l
.)t

.sp
O modelo de programa��o abstrato que ser� utilizado em toda esta
introdu��o (e nos demais manuais de refer�ncia das fun��es da "libxti")
cont�m apenas dois n�veis: o n�vel de usu�rio (ou programa de aplica��o),
que utiliza os servi�os da XTI, e o (assim chamado) sistema de transporte,
que executa todos os servi�os relacionados � rede de comunica��es.
A comunica��o entre este dois n�veis se d� exclusivamente atrav�s das
fun��es da "libxti".

.sp
Em uma implementa��o real, o sistema de transporte � na
verdade um sistema complexo composto de v�rios n�veis, que no entanto
n�o precisam ser considerados aqui
(pois s�o transparentes para o usu�rio da rede).

.in
.sp 2
.b 'CODIFICA��O DAS CHAVES DOS ARGUMENTOS DAS FUN��ES'
.in 5
Cada manual de refer�ncia de uma fun��o da "libxti"
cont�m uma tabela que resume os conte�dos dos argumentos de entrada
e sa�da da fun��o.
Os significados das chaves s�o as seguintes:

.in +3
.ip ' x ' 5
O valor do argumento � significativo
(se for um argumento de entrada
ele deve ter um valor atribu�do antes da chamada, e se for um argumento
de sa�da ele cont�m um valor que pode ser consultado ap�s a chamada).

.ip (x) 5
O conte�do do objeto apontado pelo argumento � significativo.

.ip ' ? ' 5
O valor do argumento � significativo, mas o argumento � opcional.

.ip (?) 5
O conte�do do objeto apontado pelo argumento � opcional.

.ip ' / ' 5
O valor do argumento � irrelevante.

.ip ' = ' 5
O valor do argumento (ap�s a chamada) n�o � modificado.


.in -3
.ep

.in
.sp 2
.b 'COMPATIBILIDADE ENTRE OS PROTOCOLOS ISO E UDP/TCP'
.in 5
A XTI foi originalmente definida em fun��o do protocolo ISO,
e posteriormente estendida para os protocolos da INTERNET (TCP e UDP).
Esta implementa��o disp�e (na presente vers�o)
apenas dos protocolos TCP, UDP e o modo-de-acesso-interno.

.sp
O modo-de-acesso-interno ("raw") permite o uso de protocolos
pr�prios definidos a n�vel de usu�rio, que o sistema de transporte
encapsula com um cabe�alho IP. O objetivo deste modo � o de 
possibilitar a defini��o e teste de novos protocolos
(que possivelmente mais tarde ser�o incorporados ao sistema
de transporte), e tamb�m o uso do protocolo ICMP.
Este modo n�o faz parte da XTI, e portanto seu uso deve ser evitado
se for desejada portabilidade para outras implementa��es.

.sp
O restante desta se��o utiliza conceitos que ir�o ser definidos
apenas mais adiante, e em um primeira leitura, o leitor pode
passar para o in�cio da se��o seguinte.

.sp
Embora tornar o protocolo utilizado "invis�vel" para o usu�rio
seja um dos objetivos da XTI, isto n�o se efetivou integralmente,
principalmente em virtude dos indicadores "T_MORE" e "T_EXPEDITED"
e da desconex�o ordenada.

.sp
Os indicadores "T_MORE" e "T_EXPEDITED" originam-se do protocolo ISO,
e embora o protocolo TCP tenha conceitos semelhantes nos indicadores
PUSH e URGENT, eles n�o s�o intercambi�veis.

.sp
Nesta implementa��o, foram introduzidos os indicadores "T_PUSH" e "T_URGENT",
e os 4 indicadores t�m os seguintes efeitos:

.in +3
.ip T_MORE 13
No protocolo ISO, este indicador � utilizado para assinalar
segmentos/datagramas incompletos. Nesta implementa��o, este
indicador � sempre ignorado, exceto na fun��o "t_rcvudata",
para indicar que o datagrama n�o foi recebido integralmente.

.ip T_EXPEDITED 13
No protocolo ISO, este indicador � utilizado para assinalar
segmentos transmitidos/recebidos com dados de prioridade mais alta
(e s�o processados em um outro fluxo de dados).
Nesta implementa��o, este indicador � sempre ignorado.
� poss�vel fazer com que este indicador
tenha o efeito de URGENT (veja abaixo) com as linhas

.sp
.(l
			#undef	T_EXPEDITED
			#define	T_EXPEDITED	T_URGENT
.)l

.sp
ap�s a inclus�o de <xti.h>.

.ip T_URGENT 13
Este indicador � semelhante a EXPEDITED, isto �, indica a
transmiss�o/recep��o de dados de prioridade mais alta.
No entanto, o protocolo TCP disp�e de apenas um fluxo de dados.

.sp
Neste manual de refer�ncia e nos manuais de todas as fun��es da "libxti",
o termo "urgente" e "expedito" � usado como sin�nimo.
Do mesmo modo, os eventos "T_EXDATA" e "T_GOEXDATA" e
referem-se a dados "urgentes". 

.ip T_PUSH 13
Por quest�es de efici�ncia, normalmente um segmento TCP s� �
transmitido quando completa um determinado tamanho "ideal".
Em certas situa��es, no entanto, � necess�rio transmitir o segmento
mesmo estando incompleto. Para isto, utilizamos este indicador
na fun��o "t_snd", ou ainda, podemos utilizar a fun��o "t_push"
(que no entanto n�o � padr�o da "libxti").

.ep
.in -3

.sp
Outra diferen�a entre os protocolos � a presen�a
da desconex�o ordenada (fun��es "t_sndrel" e "t_rcvrel")
no protocolo TCP, que efetua uma desconex�o mais elegante
do que a desconex�o abortiva do protocolo ISO.

.sp
� claro que se forem usados os indicadores "T_PUSH" e "T_URGENT",
a desconex�o ordenada ou a fun��o "t_push", fica comprometida a
portabilidade para outra implementa��o da XTI.

.in
.sp 2
.(t
.b '"ENDPOINTS" DE TRANSPORTE'
.in 5
Um "endpoint" de transporte � uma estrutura de dados interna do sistema
de transporte que cont�m as informa��es necess�rias para
o controle de uma comunica��o em andamento.
.)t

.sp
A fun��o "t_open" aloca um "endpoint" para o usu�rio, recebendo como
primeiro argumento o nome de um identificador de protocolo
(como por exemplo "/dev/itntcp" para o protocolo TCP, "/dev/itnudp"
para o protocolo UDP e "/dev/itnraw" para o modo-de-acesso-interno),
e devolve um descritor de arquivos ("fd").
Este descritor de arquivos "fd" deve ser usado como argumento
em todas as chamadas subseq��ntes a fun��es da "libxti" para
se referir a este "endpoint".

.sp
Para estar ativo, um "endpoint" deve ter um endere�o de protocolo
associado, o que � feito atrav�s da fun��o "t_bind".

.sp
Repare que n�o existe uma associa��o direta dos processos ao
sistema de transporte. Deste modo, v�rios outros processos que podem
obter o "fd" (ou um "fd" equivalente) atrav�s das fun��es "fork", "thread",
"dup" e "fcntl" (sys), podem acessar o mesmo "endpoint",
e portanto o mesmo caminho de comunica��es.

.in
.sp 2
.b 'ENDERE�OS DE PROTOCOLO'
.in 5
Em uma rede de computadores, para que um usu�rio possa determinar com qual
n� da rede (computador) deseja estabelecer uma comunica��o, s�o utilizados
os endere�os de protocolo.
A interface XTI n�o define o formato destes endere�os.

.sp
Nesta implementa��o, um endere�o de protocolo consiste da estrutura
"INADDR", com 3 membros (veja o arquivo de inclus�o <xti.h>):
O endere�o INTERNET do n� na rede ("a_addr"), a porta de servi�o no n�
("a_port") e a fam�lia de protocolos ("a_family", n�o usado nesta vers�o).
No modo-de-acesso-interno, n�o existe o conceito de porta de servi�o,
e o membro "a_port" cont�m o n�mero do protocolo (atrav�s do "#define"
"a_proto").

.sp
Normalmente, em cada n� da rede, s�o executados
diversos (assim chamados) servidores, cada um deles oferecendo
um determinado servi�o. A porta de servi�o determina com qual destes
servidores a comunica��o deve ser estabelecida.

.in
.sp 2
.b 'ASSOCIA��O DE UM PROCESSO A UM "ENDPOINT"'
.in 5
Um processo pode alocar simultaneamente v�rios "endpoints". No entanto,
no modo s�ncrono, o processo deve executar seq�encialmente as
diversas a��es do sistema de transporte nos "endpoints" associados.

.sp
� importante lembrar que o sistema de transporte trata todos os
usu�rios de um "endpoint" como se fosse um �nico usu�rio.
Assim, se diversos processos compartilharem o mesmo
"fd" (atrav�s de "fork", "thread", "dup" ou "fcntl"), eles devem
sincronizar as suas a��es para que n�o executem uma fun��o que
seja inapropriada num certo estado de um "endpoint".

.sp
As fun��es "t_getstate" e "t_sync" retornam o estado corrente do
sistema de transporte, possibilitando deste modo o usu�rio
a verificar este estado antes de tomar novas a��es.

.sp
Um processo pode esperar por um pedido de conex�o (fun��o "t_listen")
em um "fd" e aceitar a conex�o em um outro "fd", para o qual foi
associado um endere�o com o argumento "qlen" igual a zero
(veja a fun��o "t_bind"). Isto facilita a confec��o de servidores
que aguardam pedidos de conex�o em uma dada porta. O servidor
aceita a conex�o em um novo "endpoint" e cria um processo filho
("fork" ou "thread") para executar o servi�o, sem bloquear a recep��o de outros
pedidos de conex�o no "endpoint" original.

.in
.sp 2
.(t
.b 'MODOS DE SERVI�O'
.in 5
A interface de servi�o de transporte suporta tr�s modos de servi�o:
o modo-com-conex�o, o modo-sem-conex�o e o modo-de-acesso-interno.
Um "endpoint" n�o pode suportar mais de um modo simultaneamente.
.)t

.sp
O modo-com-conex�o oferece um servi�o orientado a circuito, e possibilita
a transfer�ncia de dados de uma maneira confi�vel e ordenada.
Este servi�o possibilita a negocia��o de par�metros e op��es que
governam a transfer�ncia de dados.
Ele prov� um mecanismo de identifica��o que evita a perda de tempo
gerada pela transmiss�o e resolu��o de endere�os durante a fase de
transfer�ncia de dados.
Al�m disto, ele prov� um contexto no qual unidades sucessivas de dados
transferidas entre usu�rios est�o relacionadas logicamente.
Este tipo de servi�o � atrativo para aplica��es que necessitam de
intera��es relativamente longas e orientadas a um fluxo de dados.
Este � o servi�o oferecido pelo protocolo TCP.

.sp
Em contraste, o modo-sem-conex�o � orientado a mensagem e suporta
transfer�ncias em unidades auto-contidas sem nenhuma rela��o
l�gica necess�ria entre as unidades. Estas unidades s�o chamadas
de "datagramas". Este servi�o necessita de uma conven��o entre os
usu�rios envolvidos, que determina as caracter�sticas dos dados
a serem transmitidos. Este servi�o n�o suporta nenhuma negocia��o
de par�metros e/ou op��es.
Toda a informa��o necess�ria para a entrega de um datagrama
(por ex. o endere�o do destinat�rio) � fornecida ao sistema de
transporte, juntamente com os dados a serem transmitidos, em
um pedido �nico de servi�o, que n�o tem nenhuma rela��o
com nenhum outro pedido (anterior ou posterior).
Este tipo de servi�o � atrativo para aplica��es que envolvem
intera��es de pedido/resposta de curta dura��o, exibem um
alto n�vel de redund�ncia, s�o reconfigur�veis dinamicamente
ou n�o necessitam de entrega de dados garantida nem sequencial.
Este � o servi�o oferecido pelo protocolo UDP.

.sp
O modo-de-acesso-interno ("raw") interage com um n�vel mais b�sico do
sistema de transporte, e assim como o modo-sem-conex�o,
ele � orientado � transfer�ncia de datagramas.
Ele permite o uso de protocolos pr�prios definidos a n�vel de aplica��o,
e o objetivo � o de possibilitar a defini��o e teste de novos protocolos
(que possivelmente mais tarde ser�o incorporados ao sistema de transporte).
Todos os detalhes do novo protocolo s�o de responsabilidade da aplica��o;
o sistema de transporte apenas adiciona/retira ao/do datagrama um cabe�alho IP
e o transmite/recebe.


.bc	/*************************************/
Na transmiss�o, o datagrama j� deve conter (al�m dos dados
propriamente ditos), o cabe�alho do protocolo que o usu�rio deseja 
utilizar, com todos os campos devidamente preenchidos
(inclusive o "checksum", se houver).
Na recep��o, o usu�rio recebe o datagrama completo com o cabe�alho
do protocolo e � sua responsabilidade processar todos os campos.
(o sistema de transporte

Neste modo, n�o existe o conceito de "porta de servi�o", e portanto
o datagrama n�o pode ser enviado para um determinado processo
(a aplica��o � que deve decidir se o datagrama recebido
destina-se a ela). 
Na recep��o, pode ser indicado o n�mero de um protocolo, 
.ec	/*************************************/

.in
.sp 2
.b 'TRATAMENTO DE ERROS'
.in 5
Cada chamada a uma fun��o da biblioteca "libxti" pode retornar
com um c�digo de erro de um repert�rio de um ou mais c�digos.
Retornos com erro s�o indicados pelo valor -1.
Uma vari�vel externa, "t_errno", que est� definida no arquivo
de inclus�o <xti.h>, cont�m o n�mero espec�fico do erro ocorrido.
Este valor � atribu�do quando ocorre um erro, mas ele n�o � removido
por uma chamada com sucesso a uma fun��o da biblioteca, de tal modo
que ele s� deve ser consultado quando um erro foi detetado pelo c�digo de
retorno. Uma fun��o de diagn�stico, "t_error", pode ser usada
para imprimir uma mensagem de erro.
O estado de um "endpoint" pode mudar em caso de erro.

.sp
Nesta implementa��o, os erros da interface de transporte
est�o unificados com os erros do sistema operacional, de tal
modo que a vari�vel "t_errno" � id�ntica � vari�vel "errno",
e a fun��o "t_error" � id�ntica � fun��o "perror" (libc).
Isto j� est� definido no arquivo <xti.h>, e portanto � transparente
para o usu�rio. Em conseq�encia, o erro [TSYSERR] nunca ocorre.

.in
.sp 2
.b 'MODOS DE EXECU��O S�NCRONO E ASS�NCRONO'
.in 5
A interface de servi�o de transporte � inerentemente ass�ncrona;
v�rios eventos podem ocorrer independentemente das a��es do
usu�rio do sistema de transporte. Por exemplo, um usu�rio pode estar
enviando dados atrav�s de uma conex�o de transporte quando chega uma
indica��o ass�ncrona de desconex�o. O usu�rio deve ser informado
(de algum modo) que a conex�o foi desfeita.

.sp
A interface de servi�o de transporte suporta dois modos para tratar
eventos ass�ncronos: o modo s�ncrono e o modo ass�ncrono. No modo
s�ncrono de opera��o, as primitivas de transporte esperam por
determinados eventos antes de retornarem ao usu�rio. Enquanto
espera, o usu�rio n�o pode executar outras tarefas. Por exemplo,
uma fun��o que tenta receber dados no modo s�ncrono s� ir� retornar
o controle para o usu�rio quando houver dados dispon�veis.
O modo s�ncrono � o modo normal ("default") de execu��o. � um
modo �til para processos de usu�rios que querem esperar pela
ocorr�ncia de eventos, ou para processos de usu�rios que mant�m
apenas uma conex�o de transporte. Note que, se ocorrer um sinal,
chamadas bloqueadas s�o interrompidas e retornam com -1 (a
vari�vel "t_errno" recebe o valor [EINTR], ver <errno.h>).
Neste caso a chamada � fun��o n�o tem efeito.

.sp
Por outro lado, o modo ass�ncrono prov� um mecanismo para
notificar um usu�rio da ocorr�ncia de um evento sem for�a-lo a
esperar pelo evento. A possibilidade de manusear eventos de um
modo ass�ncrono � uma capacidade desej�vel para uma interface de
transporte. Isto possibilita a usu�rios efetuarem trabalhos �teis
enquanto esperam por um evento em particular. Por exemplo, uma
fun��o que tenta receber dados no modo ass�ncrono vai retornar
o controle imediatamente para o usu�rio, se nenhum dado est�
dispon�vel. O usu�rio pode ent�o testar periodicamente por dados
at� que eles cheguem. O modo ass�ncrono � adequado para aplica��es que
t�m longas esperas entre eventos e t�m outras tarefas que podem
ser executadas neste meio tempo, ou ent�o para aplica��es que
processam m�ltiplas conex�es concorrentemente.

.sp
Os dois modos de execu��o n�o s�o oferecidos atrav�s de interfaces
distintas ou dois conjuntos de fun��es. Ao inv�s disto, as fun��es
que processam eventos de entrada t�m dois modos de opera��o:
s�ncrono e ass�ncrono. O modo desejado � especificado atrav�s do
indicador O_NONBLOCK, que pode ser dado quando o "endpoint" � criado
(fun��o "t_open"), ou antes de utilizar qualquer fun��o espec�fica
atrav�s da chamada ao sistema "fcntl" (sys). O efeito deste indicador
� local para este processo, e est� descrito no manual de refer�ncia
de cada fun��o.

.sp
A interface de servi�o de transporte define 9 eventos ass�ncronos
para cobrir os servi�os no modo-com-conex�o,
modo-sem-conex�o e modo-de-acesso-interno.
Eles s�o representados como indicadores distintos em uma m�scara de
bits, usando os seguintes nomes simb�licos: T_LISTEN, T_CONNECT,
T_DATA, T_EXDATA, T_DISCONNECT, T_ORDREL, T_UDERR, T_GODATA, T_GOEXDATA.
Eles s�o descritos mais adiante, na se��o GER�NCIA DE EVENTOS.

.sp
Mesmo que um processo chame as fun��es no modo s�ncrono, ele necessita
de reconhecer certos eventos ass�ncronos e tomar determinadas provid�ncias,
caso necess�rio. Isto � efetuado atrav�s do erro especial [TLOOK], que
� retornado por uma fun��o quando ocorre um evento ass�ncrono.
A fun��o "t_look" deve ser ent�o utilizada para identificar o
evento espec�fico que ocorreu.

.sp
Outro modo de notificar um processo de que um evento ass�ncrono ocorreu
� atrav�s do teste peri�dico por um dos eventos ass�ncronos listados
acima.
Neste modo, o processo realiza trabalho �til, e periodicamente
testa se ocorreu algum evento. Esta facilidade � obtida utilizando-se
o indicador O_NONBLOCK.

.in
.sp 2
.b 'EVENTOS E A FUN��O "t_look"'
.in 5
Todos os eventos que ocorrem em um "endpoint" s�o armazenados pela
XTI. Este eventos s�o obtidos (um de cada vez) atrav�s da fun��o "t_look".
Se ocorreram m�ltiplos eventos, a ordem na qual "t_look" fornece
os eventos � dependente da implementa��o, e a aplica��o n�o deve
depender de uma ordem espec�fica.
Um evento fica armazenado em um "endpoint" at� que seja tratado.
Cada evento tem uma fun��o correspondente que o trata e o retira
do "endpoint". Dois eventos, T_GODATA e T_GOEXDATA s�o tamb�m
retirados do "endpoint" j� pela pr�pria chamada a "t_look".

.sp
.(t
A seguinte tabela resume estas id�ias:

.sp
.(l
	+---------------+---------------+-----------------------+
	|    Evento	|    Removido  	|  Fun��o que o trata	|
	| 		| por "t_look"?	|			|
	+---------------+---------------+-----------------------+
	| T_LISTEN	|	N�o	|  t_listen		|
	| T_CONNECT	|	N�o	|  t_rcvconnect		|
	| T_DATA	|	N�o	|  t_rcv[udata|raw]	|
	| T_EXDATA	|	N�o	|  t_rcv		|
	| T_DISCONNECT	|	N�o	|  t_rcvdis		|
	| T_UDERR	|	N�o	|  t_rcvuderr		|
	| T_ORDREL	|	N�o	|  t_rcvrel		|
	| T_GODATA	|	Sim	|  t_snd[udata|raw]	|
	| T_GOEXDATA	|	Sim	|  t_snd		|
	+---------------+---------------+-----------------------+
.)l
.)t

.in
.sp 2
.b 'GER�NCIA DE EVENTOS'
.in 5
Cada chamada a uma fun��o da interface XTI trata de um "endpoint"
de cada vez. N�o � poss�vel esperar simultaneamente por diversos
eventos de diferentes fontes, particularmente de diversas conex�es.
A interface XTI possui um servi�o de ger�ncia de eventos, que
possibilita um processo a ser notificado dos seguintes eventos:

.in +3

.ip * 2
T_LISTEN: Um pedido de conex�o de um usu�rio remoto foi recebido
pelo sistema de transporte (somente no modo-com-conex�o);
este evento pode ocorrer apenas quando j� foi atribu�do um endere�o v�lido
ao "endpoint" (fun��o "t_bind") e ainda n�o foi estabelecida uma
conex�o de transporte.

.ip * 2
T_CONNECT: Uma resposta de conex�o foi recebida pelo sistema de transporte;
ocorre apenas ap�s um "t_connect" (somente no modo-com-conex�o).

.ip * 2
T_DATA: Dados normais foram recebidos pelo sistema de transporte.

.ip * 2
T_EXDATA: Dados urgentes (expeditos) foram recebidos pelo sistema de transporte.

.ip * 2
T_DISCONNECT: Um pedido de desconex�o abortiva foi recebido pelo sistema de
transporte; pode ser reportado pelas duas fun��es de transfer�ncias
de dados e pelas fun��es "t_accept" e "t_snddis"
(somente no modo-com-conex�o).

.ip * 2
T_ORDREL: Um pedido de desconex�o ordenada foi recebido pelo sistema de
transporte (somente no modo-com-conex�o com desconex�o ordenada).

.ip * 2
T_UDERR: Foi detetado um erro na transmiss�o anterior de um datagrama.
Pode ser notificado pelas fun��es "t_rcvudata" e "t_unbind"
(somente no modo-sem-conex�o).

.ip * 2
T_GODATA: As restri��es de fluxo para a transmiss�o de dados normais foram
suspensas. Dados normais podem ser transmitidos novamente.

.ip * 2
T_GOEXDATA: As restri��es de fluxo para a transmiss�o de dados urgentes foram
suspensas. Dados urgentes podem ser transmitidos novamente.

.in -3
.ep

.in
.sp 2
.b 'VIS�O GERAL DO MODO-COM-CONEX�O'
.in 5
O servi�o de transporte do modo-com-conex�o consiste de 4 fases de
comunica��o:

.in +3

.ip * 2
Inicializa��o/de-inicializa��o.

.ip * 2
Estabelecimento de uma conex�o.

.ip * 2
Transfer�ncia de dados.

.ip * 2
Desconex�o.

.in -3
.ep

.sp
Com o objetivo de estabelecer uma conex�o de transporte, uma
aplica��o do usu�rio deve:

.in +3

.ip 1. 3
Fornecer um identificador de transporte do modo desejado
ao sistema de transporte (usando "t_open"); isto cria
um "endpoint" de transporte atrav�s do qual o usu�rio pode
requisitar servi�os ao sistema de transporte.

.ip 2. 3
Associar um endere�o ao "endpoint" (usando "t_bind").

.ip 3. 3
Utilizar as fun��es de conex�o apropriadas ("t_connect" ou
"t_listen" e "t_accept") para estabelecer uma conex�o de transporte.
O conjunto de fun��es depende de o usu�rio ser um cliente ou servidor.

.ip 4. 3
Uma vez com a conex�o estabelecida, podemos intercambiar dados
normais e expeditos (urgentes).
O protocolo ISO prev� o conceito de dados "expeditos", e o protocolo
TCP o conceito de dados "urgentes". Embora as id�ias sejam
similares, significando dados "de alta prioridade", o protocolo
ISO sup�e a exist�ncia de dois canais de comunicac�o
independentes, um para dados normais e outro para expeditos.
Com isto, no protocolo ISO, dados expeditos podem chegar ao
destino e serem processados por ele antes de dados normais, que
possivelmente foram enviados anteriormente.
O protocolo TCP cont�m apenas um canal de comunica��o, e os dados
urgentes s�o enviados do mesmo modo que os normais, apenas com
uma indica��o de urgente, para que a aplica��o no destino
saiba que se tratam de dados "de alta prioridade", e tome as
devidas provid�ncias.
Como esta implementa��o oferece apenas o protocolo TCP, utilizaremos
o termo expedito como sendo urgente.

.ip 5. 3
A conex�o pode ser desfeita a qualquer momento, usando as
fun��es de desconex�o. Em seguida o usu�rio pode de-inicializar
o "endpoint" de transporte fechando o descritor de arquivos devolvido
por "t_open" (e portanto liberando os recursos para uso futuro),
ou especificar um novo endere�o (ap�s o antigo ter sido
liberado atrav�s de "t_unbind"), ou ainda utilizar o mesmo endere�o
e estabelecer uma nova conex�o de transporte.

.in -3
.ep

.in
.sp 2
.b 'FASE DE INICIALIZA��O/DE-INICIALIZA��O'
.in 5
Um resumo das fun��es que efetuam a inicializa��o/de-inicializa��o
� dado abaixo. Todas estas fun��es realizam apenas opera��es locais;
nenhuma informa��o � transmitida atrav�s da rede de comunica��es.


.in +3

.ip 't_open ()' 15
Esta fun��o cria um "endpoint" de transporte e retorna informa��es
espec�ficas de protocolo associadas ao "endpoint". Tamb�m retorna
um descritor de arquivos que serve de identificador local para o
"endpoint".

.ip 't_bind ()' 15
Esta fun��o associa um endere�o de protocolo a um "endpoint",
e deste modo ativando o "endpoint". Ela tamb�m pode pedir para iniciar
a aceita��o de indica��es de conex�o.

.ip 't_optmgmt ()' 15
Esta fun��o possibilita o usu�rio a obter ou negociar op��es do
protocolo com o sistema de transporte.

.ip 't_unbind ()' 15
Esta fun��o incapacita um "endpoint" de tal modo que mais nenhum
pedido destinado a este "endpoint" seja aceito pelo sistema de transporte.

.ip 't_close ()' 15
Esta fun��o informa ao sistema de transporte que o usu�rio terminou
suas opera��es com o "endpoint", e libera todos os recursos locais
associados a este "endpoint".

.in -3
.ep

.sp
As fun��es seguintes s�o tamb�m opera��es de ger�ncia locais,
mas podem ser executadas durante qualquer fase da comunica��o:

.in +3

.ip 't_getinfo ()' 15
Esta fun��o retorna informa��es espec�ficas de protocolo associadas
ao "endpoint".

.ip 't_getstate ()' 15
Esta fun��o retorna o estado corrente do "endpoint".

.ip 't_sync ()' 15
Esta fun��o sincroniza as estruturas de dados gerenciadas pela biblioteca
de transporte com o sistema de transporte.

.ip 't_alloc ()' 15
(OPCIONAL, N�O DISPON�VEL) Esta fun��o aloca mem�ria para a estrutura
de dados especificada.

.ip 't_free ()' 15
(OPCIONAL, N�O DISPON�VEL) Esta fun��o libera a mem�ria da estrutura
de dados que foi alocada por "t_alloc".

.ip 't_error ()' 15
Esta fun��o imprime uma mensagem descrevendo o �ltimo erro encontrado
durante uma chamada a uma fun��o do sistema de tansporte.

.ip 't_look ()' 15
Esta fun��o retorna o evento corrente associado com um "endpoint".

.in -3
.ep

.in
.sp 2
.(t
.b 'VIS�O GERAL DO ESTABELECIMENTO DE UMA CONEX�O'
.in 5
Esta fase possibilita dois usu�rios da rede de comunica��es a estabelecerem
uma conex�o de transporte entre si. Neste cen�rio, um dos usu�rios
� considerado ativo e inicia a conversa��o (cliente), enquanto o outro
usu�rio � passivo e espera por um pedido de conex�o (servidor).
.)t

.sp
No modo-com-conex�o:

.in +3

.ip * 2
O usu�rio deve inicialmente criar um "endpoint".

.ip * 2
Em seguida, deve ser atribu�do um endere�o para o "endpoint".

.ip * 2
Um "endpoint" pode ser associado com uma, e apenas uma,
conex�o de transporte estabelecida.

.ip * 2
� poss�vel usar um "endpoint" para receber pedidos de conex�o
e coloc�-los em uma fila. Este tipo de opera��o � declarado na
chamada a "t_bind", com o argumento "qlen" com um valor maior do que 0.

.ip * 2
A fun��o "t_listen" � usada para verificar se h� algum pedido de
conex�o na fila. Se h� algum, retorna detalhes da indica��o da
conex�o, e um n�mero de seq��ncia local que identifica univocamente
este pedido de conex�o. No modo ass�ncrono, se a fila estiver vazia,
retorna com um valor negativo e a vari�vel "t_errno" com o valor
[TNODATA]. O n�mero de pedidos de conex�o ainda n�o processados na
fila � limitado pelo valor de "qlen" dado por ocasi�o da chamada
� fun��o "t_bind".

.ip * 2
Se o "endpoint" tiver mais do que um pedido de conex�o na fila, o usu�rio
deve tirar da fila todos os pedidos de conex�o (assim como os de
desconex�o), antes de aceitar ou rejeitar algum deles ou todos.

.ip * 2
Ao aceitar uma conex�o, o servidor pode utilizar o mesmo "endpoint"
(o utilizado pela fun��o "t_listen") ou um outro.

.sp
Se o mesmo "endpoint" for utilizado, ele n�o pode mais ser usado
para receber (e enfileirar) novos pedidos de conex�o.
O endere�o do protocolo estar� "ocupado" enquanto o "endpoint" estiver
ativo. Nenhum outro "endpoint" pode receber o mesmo endere�o enquanto
o "endpoint" original estiver na fase de transfer�ncia de dados
ou na fase de desconex�o (isto �, at� que seja dado um "t_unbind").

.sp
Se for utilizado um "endpoint" diferente, o "endpoint" utilizado pela
fun��o "t_listen" pode continuar a receber e enfileirar pedidos de
conex�o.

.bc	/*************************************/
.ip * 2
Se o usu�rio chamar a fun��o "t_connect" em um "endpoint" no qual
tinha sido chamado "t_listen", este "endpoint" n�o pode mais ser
usado para receber e enfileirar pedidos de conex�o.
.ec	/*************************************/

.in -3
.ep

.sp
.(t
As fun��es que efetuam estas opera��es de conex�o s�o as seguintes:

.in +3

.ip 't_connect ()' 17
Esta fun��o pede uma conex�o a um usu�rio de transporte em um destino
espec�fico e espera pela resposta do usu�rio remoto. Esta fun��o
pode ser efetuada no modo s�ncrono ou ass�ncrono. No modo s�ncrono,
a fun��o espera pela resposta do usu�rio remoto antes de retornar o
controle ao usu�rio local. No modo ass�ncrono, a fun��o inicia o
estabelecimento da conex�o, mas retorna o controle ao usu�rio local
antes de uma resposta chegar.
.)t

.ip 't_rcvconnect ()' 17
Esta fun��o possibilita a um usu�rio ativo (cliente) a determinar
o estado de um pedido de conex�o enviado anteriormente. Se o pedido
foi aceito, a fase de estabelecimento de conex�o estar� completa no
retorno desta fun��o. Esta fun��o � utilizada em conjunto com
"t_connect" para estabelecer uma conex�o no modo ass�ncrono.

.ip 't_listen ()' 17
Esta fun��o possibilita um usu�rio passivo (servidor) a receber
pedidos de conex�o de outros usu�rios (clientes).

.ip 't_accept ()' 17
Esta fun��o � chamada por um usu�rio passivo (servidor) para aceitar
uma determinada conex�o ap�s o recebimento de um pedido.

.in -3
.ep

.in
.sp 2
.b 'VIS�O GERAL DA TRANSFER�NCIA DE DADOS'
.in 5
Uma vez que uma conex�o de transporte tenha sido estabelecida entre
dois usu�rios, dados podem ser transferidos em um e outro sentidos
atrav�s da conex�o, em um modo "full duplex". Para efetuar estas
transfer�ncias de dados no modo-com-conex�o s�o utilizadas as fun��es:

.in +3

.ip 't_snd ()' 17
Esta fun��o possibilita usu�rios de transporte a enviarem dados normais
ou urgentes atrav�s de uma conex�o.

.ip 't_rcv ()' 17
Esta fun��o possibilita usu�rios de transporte a receberem dados normais
ou urgentes atrav�s de uma conex�o.

.in -3
.ep

.sp
Nesta implementa��o podemos tamb�m usar as chamadas ao sistema "read" e
"write" (sys) para transferir dados. Lembre-se no entanto, de que isto
ir� prejudicar a portabilidade da aplica��o.
Veja detalhes nas fun��es "t_snd" e "t_rcv".

.sp
Na fase de transfer�ncia de dados, a ocorr�ncia do evento T_DISCONNECT
implica em um retorno com falha das fun��es "t_snd" ou "t_rcv" com
"t_errno" com o valor [TLOOK]. O usu�rio deve ent�o chamar "t_look" para
obter mais detalhes.

.in
.sp 2
.b 'RECEBENDO DADOS'
.in 5
Se houver dados (normais ou urgentes) dispon�veis, ent�o uma chamada
a "t_rcv" retorna dados imediatamente. Se a conex�o de transporte n�o
existir mais, ent�o a chamada retorna imediatamente com uma indica��o
de falha. Se n�o houver dados dispon�veis imediatamente, e a conex�o
existe, ent�o o resultado de uma chamada a "t_rcv" depende do modo:

.in +3

.ip * 2
Modo ass�ncrono: a chamada retorna imediatamente, indicando falha.
O usu�rio tem de verificar a chegada de dados, ou por repetidas chamadas
a "t_rcv" ou utilizando a fun��o "t_look".

.ip * 2
Modo s�ncrono: a chamada � bloqueada at� que dados estejam dispon�veis,
seja recebida uma indica��o de desconex�o ou chegue um sinal.
O usu�rio pode usar a fun��o "t_look" para determinar se h� dados
dispon�veis, ao inv�s de chamar a fun��o "t_rcv", que pode
bloquear o processo.

.sp
Nesta implementa��o podemos tamb�m usar a fun��o "t_nread"
para verificar se h� dados dispon�veis. Lembre-se no entanto, de que isto
ir� prejudicar a portabilidade da aplica��o.

.in -3
.ep

.in
.sp 2
.b 'ENVIANDO DADOS'
.in 5

Se os dados podem ser aceitos imediatamente pelo sistema de transporte,
ent�o eles s�o aceitos e a chamada retorna o n�mero de bytes aceitos.
Se os dados n�o podem ser aceitos em virtude de uma condi��o de falha
permanente, ent�o a chamada retorna com uma indica��o de falha. Se os
dados n�o podem ser aceitos imediatamente em virtude de condi��es
transientes (por ex. falta de "buffers" ou controle de fluxo), ent�o
o resultado de uma chamada a "t_snd" depende do modo de execu��o:

.in +3

.ip * 2
Modo ass�ncrono: a chamada retorna imediatamente, indicando falha.
Se a falha foi causada por restri��es de fluxo de dados, ent�o �
poss�vel que somente uma parte dos dados seja aceita pelo sistema de
transporte. Neste caso, "t_snd" retornar� um valor de bytes menor
do que o pedido para ser transmitido. Neste caso, o usu�rio pode
chamar "t_snd" novamente para transmitir os dados restantes, ou
ent�o esperar a libera��o da restri��o de fluxo atrav�s de "t_look",
e ent�o transmitir os dados.

.ip * 2
Modo s�ncrono: a chamada � bloqueada at� que uma das seguintes
condi��es seja verdadeira:

.in +3
.ip - 2
As restri��es de controle de fluxo sejam removidas, e o sistema de
transporte esteja apto a aceitar todos os dados a transmitir.
Neste caso, "t_snd" retorna com sucesso.

.ip - 2
� recebida uma indica��o de desconex�o. Neste caso, "t_snd" retorna
com falha, com "t_errno" contendo o valor [TLOOK]. O usu�rio deve
ent�o chamar "t_look", que indicar� o evento T_DISCONNECT.
Os dados que estavam sendo transmitidos ser�o perdidos.

.ip - 2
Ocorre um problema interno. Neste caso, a fun��o "t_snd" retorna
com falha, com "t_errno" contendo o c�digo do erro.
Os dados que estavam sendo transmitidos ser�o perdidos.

.in -3
.ep

.in -3
.ep

.sp
Pelo padr�o XTI, dados normais e urgentes (expeditos) constituem
dois fluxos de dados distintos. Como isto no entanto, � imcompat�vel
com o protocolo TCP, nesta implementa��o, os dados normais e urgentes
utilizam apenas um fluxo de dados.

.sp
O padr�o XTI prev� tamb�m dois modos de enviar dados, o orientado
a registro e o orientado a uma seq��ncia de bytes. A diferen�a entre
os dois � a de que o modo orientado a registro preserva as fronteiras
entre as mensagens, o que n�o ocorre no modo orientado a uma seq��ncia de
bytes. Um usu�rio pode determinar este modo diretamente no "t_open",
ou posteriormente atrav�s de "t_getinfo". O campo "tsdu" fornece
o tamanho m�ximo do registro. Se for igual a zero, � oferecido o modo
orientado a uma seq��ncia de bytes, o que � o caso desta implementa��o.
Para maiores detalhes, veja "t_getinfo".

.in
.sp 2
.b 'VIS�O GERAL DA DESCONEX�O'
.in 5
O protocolo TCP suporta a desconex�o ordenada e a desconex�o abortiva.

.sp
Uma desconex�o abortiva pode ser invocada durante
a fase de estabelecimento da conex�o, ou durante
a fase de transfer�ncia de dados.
Durante a fase de estabelecimento da conex�o, um usu�rio pode usar
a desconex�o abortiva para rejeitar um pedido de conex�o.
Durante a fase de transfer�ncia de dados, qualquer um dos dois
usu�rio pode abortar a conex�o a qualquer momento.
A desconex�o abortiva n�o � negociada pelos usu�rios e ela tem
efeito imediato. O usu�rio do outro lado da conex�o � notificado
quando a conex�o � abortada. O sistema de transporte pode tamb�m
iniciar uma desconex�o abortiva, caso em que ambos usu�rio s�o
informados que a conex�o n�o exite mais. N�o h� garantia da
entrega de dados uma vez que uma desconex�o abortiva tenha sido
iniciada.

.sp
Qualquer que seja o estado de uma conex�o de transporte, os
seus usu�rios s�o informados, assim que poss�vel, de uma
falha atrav�s de um evento de desconex�o ou um retorno com
falha de uma chamada a "t_snd" ou "t_rcv". Se o usu�rio deseja
prevenir a perda de dados pela notifica��o do usu�rio remoto
de uma desconex�o iminente, � de sua responsabilidade utilizar um
mecanismo de n�vel mais alto. Por exemplo, o usu�rio pode enviar
dados espec�ficos (urgentes) e esperar pela resposta antes de
iniciar uma desconex�o abortiva.

.sp
A desconex�o ordenada, que pode ser iniciada apenas na
fase de transfer�ncia de dados, possibilita a dois usu�rios
a terminarem "graciosamente" uma conex�o. O procedimento
da desconex�o ordenada evita a perda de dados que pode ocorrer
durante uma desconex�o abortiva.

.sp
As fun��es que efetuam a desconex�o s�o:

.in +3

.ip 't_snddis ()' 15
Esta fun��o pode ser chamada por qualquer um dos usu�rios para
iniciar uma desconex�o abortiva. Pode tamb�m ser usada para rejeitar
um pedido de conex�o durante a fase de estabelecimento da conex�o.

.ip 't_rcvdis ()' 15
Esta fun��o identifica a raz�o da desconex�o abortiva, onde a
conex�o � liberada pelo sistema de transporte ou outro usu�rio.

.ip 't_sndrel ()' 15
Esta fun��o pode ser chamada por qualquer um dos usu�rios para
iniciar uma desconex�o ordenada. A conex�o permance intacta at�
que ambos os usu�rios chamem esta fun��o e "t_rcvrel".

.ip 't_rcvrel ()' 15
Esta fun��o deve ser chamada quando um usu�rio � informado de um
pedido de uma desconex�o ordenada, como um modo de informar o
sistema de transporte de que o usu�rio est� ciente das a��es do
usu�rio remoto.

.in -3
.ep

.in
.sp 2
.b 'VIS�O GERAL DO MODO-SEM-CONEX�O'
.in 5
O servi�o de transporte do modo-sem-conex�o consiste de duas fases
de comunica��o: Inicializa��o/de-inicializa��o e transfer�ncia de dados.
Com a finalidade de efetuar uma transfer�ncia de dados no modo-sem-conex�o,
um usu�rio deve:

.in +3
.ip 1. 3
Obter um "endpoint" apropriado para este modo, usando a fun��o "t_open".

.ip 2. 3
Associar a este "endpoint" um endere�o, usando a fun��o "t_bind".

.ip 3. 3
O usu�rio pode ent�o enviar e/ou receber dados utilizando as
fun��es "t_sndudata" e "t_rcvudata".

.ip 4. 3
Uma vez terminada a fase de transfer�ncia de dados, o usu�rio
pode ou fechar diretamente o descritor de arquivos retornado por
"t_open" (usado "t_close"), ou ent�o iniciar uma nova transfer�ncia
de dados utilizando um novo endere�o (usando "t_unbind" e
"t_bind").

.in -3
.ep

.in
.sp 2
.b 'FASE DE INICIALIZA��O/DE-INICIALIZA��O'
.in 5
As fun��es que efetuam a inicializa��o/de-inicializa��o s�o as
mesmas das usadas no servi�o de transporte do modo-com-conex�o
(veja acima).

.in
.sp 2
.b 'VIS�O GERAL DA TRANSFER�NCIA DE DADOS'
.in 5
Uma vez que o "endpoint" tenha sido ativado, o usu�rio pode
enviar e receber dados atrav�s do "endpoint", atrav�s das seguintes fun��es:

.in +3
.ip 't_sndudata ()' 15
Esta fun��o possibilita um usu�rio a enviar uma unidade completa de
dados (datagrama) para o endere�o especificado.

.ip 't_sndudata ()' 15
Esta fun��o possibilita um usu�rio a receber unidades completas de
dados (datagramas) de outros usu�rios.

.ip 't_rcvuderr ()' 15
Esta fun��o possibilita um usu�rio a receber informa��es de erro
referentes a um datagrama enviado anteriormente.

.in -3
.ep

.sp
Os �nicos eventos que podem ser reportados ao usu�rio s�o
T_UDERR, T_DATA e T_GODATA. Dados urgentes (expeditos) n�o
podem ser usados no servi�o de transporte do modo-sem-conex�o.

.in
.sp 2
.b 'RECEBENDO DADOS'
.in 5
Se houver dados dispon�veis (um datagrama), ent�o uma chamada
a "t_rcvudata" retorna imediatamente indicando o n�mero de bytes
recebidos. Se n�o houver dados dispon�veis imediatamente, ent�o
o resultado de uma chamada a "t_rcvudata" depende do modo:

.in +3

.ip * 2
Modo ass�ncrono: a chamada retorna imediatamente, indicando falha.
O usu�rio tem de verificar a chegada de dados, ou por repetidas chamadas
a "t_rcvudata" ou utilizando a fun��o "t_look".

.ip * 2
Modo s�ncrono: a chamada � bloqueada at� que dados estejam dispon�veis,
seja detetado um erro ou chegue um sinal.
O usu�rio pode usar a fun��o "t_look" para determinar se h� dados
dispon�veis, ao inv�s de chamar a fun��o "t_rcvudata", que pode
bloquear o processo.

.sp
Nesta implementa��o podemos tamb�m usar a fun��o "t_nread"
para verificar se h� dados dispon�veis. Lembre-se no entanto, de que isto
ir� prejudicar a portabilidade da aplica��o.

.in -3
.ep

.in
.sp 2
.b 'ENVIANDO DADOS'
.in 5

.in +3

.ip * 2
Modo ass�ncrono: O sistema de transporte pode n�o ter a capacidade de
enviar o datagrama imediatamente, por restri��es de controle de fluxo.
Neste caso, a fun��o "t_sndudata" retorna com falha, contendo o erro
[TFLOW] em "t_errno". Neste caso, o us�rio pode tentar novamente mais
tarde, ou utilizar a fun��o "t_look" para verificar se a restri��o de
controle de fluxo foi removida.

.ip * 2
Modo s�ncrono: Com o objetivo de manter algum controle de fluxo,
a fun��o "t_sndudata" retorna somente quando for poss�vel enviar
novamente um datagrama.
Um processo que envia dados no modo s�ncrono pode ficar
bloqueado durante algum tempo.

.in -3
.ep

.sp
Se a fun��o "t_sndudata" for chamada antes de o usu�rio destinat�rio
ativar o seu "endpoint" de transporte, o datagrama pode ser perdido.

.in
.sp 2
.b 'VIS�O GERAL DO MODO-DE-ACESSO-INTERNO'
.in 5
O servi�o de transporte do modo-de-acesso-interno consiste de duas fases
de comunica��o: Inicializa��o/de-inicializa��o e transfer�ncia de dados.
Com a finalidade de efetuar uma transfer�ncia de dados no
modo-de-acesso-interno, um usu�rio deve:

.in +3
.ip 1. 3
Obter um "endpoint" apropriado para este modo, usando a fun��o "t_open".

.ip 2. 3
Associar a este "endpoint" um endere�o e/ou n�mero de protocolo,
usando a fun��o "t_bind".

.ip 3. 3
O usu�rio pode ent�o enviar e/ou receber datagramas utilizando as
fun��es "t_sndraw" e "t_rcvraw".

.ip 4. 3
Uma vez terminada a fase de transfer�ncia de dados, o usu�rio
pode ou fechar diretamente o descritor de arquivos retornado por
"t_open" (usado "t_close"), ou ent�o iniciar uma nova transfer�ncia
de dados utilizando um novo endere�o/n�mero de protocolo
(usando "t_unbind" e "t_bind").

.in -3
.ep

.in
.sp 2
.b 'FASE DE INICIALIZA��O/DE-INICIALIZA��O'
.in 5
As fun��es que efetuam a inicializa��o/de-inicializa��o s�o as
mesmas das usadas no servi�o de transporte do modo-com-conex�o
(veja acima).

.in
.sp 2
.b 'VIS�O GERAL DA TRANSFER�NCIA DE DADOS'
.in 5
Uma vez que o "endpoint" tenha sido alocado e ativado, o usu�rio pode
enviar e receber dados atrav�s do "endpoint", atrav�s das seguintes fun��es:

.in +3
.ip 't_sndraw ()' 15
Esta fun��o possibilita um usu�rio a enviar um datagrama (contendo
o cabe�alho do protocolo e dados) para o endere�o especificado.

.ip 't_rcvraw ()' 15
Esta fun��o possibilita um usu�rio a receber um datagrama (contendo
o cabe�alho do protocolo e dados) de outros n�s da rede.

.in -3
.ep

.sp
Os �nicos eventos que podem ser reportados ao usu�rio s�o
T_DATA e T_GODATA. Dados urgentes (expeditos) n�o
podem ser usados no servi�o de transporte do modo-de-acesso-interno.

.in
.sp 2
.(t
.b 'RECEBENDO DADOS'
.in 5
Se houver dados dispon�veis (um datagrama), ent�o uma chamada
a "t_rcvraw" retorna imediatamente indicando o n�mero de bytes
recebidos. Se n�o houver dados dispon�veis imediatamente, ent�o
o resultado de uma chamada a "t_rcvraw" depende do modo:
.)t

.in +3

.ip * 2
Modo ass�ncrono: a chamada retorna imediatamente, indicando falha.
O usu�rio tem de verificar a chegada de dados, ou por repetidas chamadas
a "t_rcvraw" ou utilizando a fun��o "t_look".

.ip * 2
Modo s�ncrono: a chamada � bloqueada at� que dados estejam dispon�veis,
seja detetado um erro ou chegue um sinal.
O usu�rio pode usar a fun��o "t_look" para determinar se h� dados
dispon�veis, ao inv�s de chamar a fun��o "t_rcvraw", que pode
bloquear o processo.

.sp
Nesta implementa��o podemos tamb�m usar a fun��o "t_nread"
para verificar se h� dados dispon�veis. Lembre-se no entanto, de que isto
ir� prejudicar a portabilidade da aplica��o.

.in -3
.ep

.in
.sp 2
.b 'ENVIANDO DADOS'
.in 5

.in +3

.ip * 2
Modo ass�ncrono: O sistema de transporte pode n�o ter a capacidade de
enviar o datagrama imediatamente, por restri��es de controle de fluxo.
Neste caso, a fun��o "t_sndraw" retorna com falha, contendo o erro
[TFLOW] em "t_errno". Neste caso, o us�rio pode tentar novamente mais
tarde, ou utilizar a fun��o "t_look" para verificar se a restri��o de
controle de fluxo foi removida.

.ip * 2
Modo s�ncrono: Com o objetivo de manter algum controle de fluxo,
a fun��o "t_sndraw" retorna somente quando for poss�vel enviar
novamente um datagrama. Um processo que envia dados no modo
s�ncrono pode ficar bloqueado durante algum tempo.

.in -3
.ep

.in
.sp 2
.b 'ESTADOS DA INTERFACE DE TRANSPORTE'
.in 5

A interface de servi�o de transporte XTI gerencia um "endpoint" de
transporte usando um m�ximo de 8 estados: T_UNINIT, T_UNBND, T_IDLE,
T_OUTCON, T_INCON, T_DATAXFER, T_INREL e T_OUTREL.

.sp
Os estados T_OUTCON, T_INCON e T_DATAXFER s�o significativos somente
no modo-com-conex�o.

.sp
Os estados T_INREL e T_OUTREL s�o significativos somente
no modo-com-conex�o, se a fun��o de desconex�o ordenada for usada.

.sp
.(t
A tabela abaixo descreve todos os estados como vistos pelo usu�rio
do sistema de transporte:

.sp
.(l
	+---------------+-------------------------------+
	|    Estado	|	   Descri��o		|
	+---------------+-------------------------------+
	| T_UNINIT	| N�o inicializado - estado	|
	|		| inicial e final da interface	|
	+---------------+-------------------------------+
	| T_UNBND	| Inicializado, mas sem endere�o|
	+---------------+-------------------------------+
	| T_IDLE	| Inicializado e com endere�o,	|
	|		| mas sem conex�o		|
	+---------------+-------------------------------+
	| T_OUTCON	| Aguardando resposta de um	|
	|		| pedido de conex�o (cliente)	|
	+---------------+-------------------------------+
	| T_INCON	| Aguardando um	pedido de	|
	|		| conex�o (servidor)		|
	+---------------+-------------------------------+
	| T_DATAXFER	| Transferindo dados		|
	+---------------+-------------------------------+
	| T_OUTREL	| Aguardando resposta de um	|
	|		| pedido de desconex�o ordenada	|
	+---------------+-------------------------------+
	| T_INREL	| Aguardando um	pedido de	|
	|		| desconex�o ordenada		|
	+---------------+-------------------------------+
.)l
.)t

.in
.sp 2
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
fork, thread, dup, fcntl
.br
.wo "(libc):"
perror
.br

.in
.sp
.(t
.b
REFER�NCIAS
.r
.in 5
"X/OPEN Portability Guide: Networking Services",
X/OPEN Company Ltd.,
Prentice Hall, New Jersey, 1st Edition, 1988.
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
