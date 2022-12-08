.bp
.he 'T_SNDRAW (xti)'TROPIX: Manual de Refer�ncia'T_SNDRAW (xti)'
.fo 'Escrito em 17.08.00'Vers�o 4.0.0'Pag. %'

.b NOME
.in 5
.wo "t_sndraw -"
envia um datagrama no modo-de-acesso-interno
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_sndraw (int fd, const T_UNITDATA *data);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_sndraw" � usada para enviar um datagrama para um
n� da rede no modo-de-acesso-interno.

.sp
O modo-de-acesso-interno interage com o n�vel mais b�sico do
sistema de transporte, permitindo o envio/recep��o de datagramas com
protocolos definidos pelo usu�rio.
O objetivo deste modo � o de possibilitar o uso de protocolos
n�o convencionais e/ou experimentais. Somente o superusu�rio
pode usar este modo.

.sp
.(l
	    +--------------------+------------+------------+
	    |   Argumentos	 | Na chamada | No retorno |
	    +--------------------+------------+------------+
	    | fd		 |     x      |     /      |
	    |			 |	      |		   |
	    | data->addr.maxlen	 |     /      |     /      |
	    | data->addr.len	 |     x      |     /      |
	    | data->addr.buf	 |    x(x)    |     /      |
	    |			 |	      |		   |
	    | data->opt.maxlen	 |     /      |     /      |
	    | data->opt.len	 |     x      |     /      |
	    | data->opt.buf	 |    ?(?)    |     /      |
	    |			 |	      |		   |
	    | data->udata.maxlen |     /      |     /      |
	    | data->udata.len	 |     x      |     /      |
	    | data->udata.buf	 |    x(x)    |     /      |
	    +--------------------+------------+------------+
.)l

.sp
O argumento "fd" indica o "endpoint" local atrav�s do qual o datagrama
ser� enviado e "data" cont�m informa��es associadas ao datagrama
que ser� enviado.
O argumento "data" deve apontar para uma estrutura "T_UNITDATA"
que cont�m os seguintes membros:

.sp
.(l
     NETBUF     addr;
     NETBUF     opt;
     NETBUF     udata;
.)l

.sp
O membro "addr" especifica o endere�o de protocolo (endere�o INTERNET)
do n� destinat�rio da rede e o n�mero do protocolo (em "a_proto"),
"opt" identifica op��es espec�ficas do protocolo associadas ao pedido
e "udata" cont�m os dados a enviar.
O usu�rio pode preferir n�o dar op��es, atribuindo um valor NULO
a "opt.len"; neste caso o sistema de transporte usar� op��es
"default".

.sp
Normalmente, "t_sndraw" opera no modo s�ncrono e pode esperar caso
haja retri��es de controle de fluxo.
No entanto, se o indicador O_NONBLOCK foi ligado
(atrav�s de "t_open" ou "fcntl" (sys)),
"t_sndraw" executa no modo ass�ncrono, e se houver
retri��es de controle de fluxo
retorna imediatamente com -1 e atribui o valor [TFLOW]  a "t_errno".

.sp
A quantidade de dados especificados em "udata" n�o pode exceder
o valor do campo "tsdu" da estrutura "info"
retornada por "t_open" ou "t_getinfo".

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Os dados fornecidos em "data->udata" representam um datagrama
no protocolo definido pelo usu�rio (sobre o qual o sistema de transporte
nada conhece nem interpreta). � de inteira responsabilidade do
usu�rio gerenciar todos os campos deste datagrama,
inclusive o "checksum" (se houver).

.sp
� tamb�m poss�vel especificar o endere�o IP
de fonte do datagrama (isto �, do pr�prio computador).
Isto � �til no caso de roteadores, no qual o computador possui v�rios
endere�os (um para cada interface).
Para dar este endere�o, basta fornecer "data->addr.len" com um tamanho
suficiente para 2 estruturas INADDR; ele dever� ser dado no segundo elemento do
vetor.

.sp
Nesta vers�o, ainda n�o h� op��es dispon�veis;
portanto, na chamada "data->opt.len" deve ser NULO.

.sp
Al�m disto, a fun��o "t_sndraw" s� opera no modo
s�ncrono, isto �, ela sempre ir� esperar caso haja retri��es de
controle de fluxo.

.sp
Se o endere�o/n�mero do protocolo n�o for dado no "t_sndraw"
(isto �, se "data->addr.len" for NULO), ser�o
usados os valores dados no "t_bind" (xti).

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso a fun��o devolve o valor 0.
Em caso contr�rio, devolve -1 e indica em "t_errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
fcntl
.br
.wo "(xti): "
t_open, t_bind
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
