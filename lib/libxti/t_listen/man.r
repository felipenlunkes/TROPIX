.bp
.he 'T_LISTEN (xti)'TROPIX: Manual de Refer�ncia'T_LISTEN (xti)'
.fo 'Escrito em 27.07.92'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_listen -"
recebe pedidos de conex�o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_listen (int fd, T_CALL *call);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_listen" recebe pedidos de conex�o de usu�rios remotos.

.sp
.(l
	    +--------------------+------------+------------+
	    |   Argumentos	 | Na chamada | No retorno |
	    +--------------------+------------+------------+
	    | fd		 |     x      |     /      |
	    |			 |	      |		   |
	    | call->addr.maxlen	 |     x      |     /      |
	    | call->addr.len	 |     /      |     x      |
	    | call->addr.buf	 |     x      |    (x)     |
	    |			 |	      |		   |
	    | call->opt.maxlen	 |     x      |     /      |
	    | call->opt.len	 |     /      |     x      |
	    | call->opt.buf	 |     x      |    (x)     |
	    |			 |	      |		   |
	    | call->udata.maxlen |     x      |     /      |
	    | call->udata.len	 |     /      |     x      |
	    | call->udata.buf	 |     x      |    (?)     |
	    |			 |	      |		   |
	    | call->sequence	 |     /      |     x      |
	    +--------------------+------------+------------+
.)l

.sp
O argumento "fd" indica o "endpoint" local que receber�
os pedidos de conex�o, e no retorno o argumento "call" conter�
informa��es descrevendo o pedido recebido.
O argumento "call" deve apontar para uma estrutura "T_CALL"
que cont�m os seguintes membros:

.sp
.(l
     NETBUF     addr;
     NETBUF     opt;
     NETBUF     udata;
     int        sequence;
.)l

.sp
No retorno, "addr" cont�m o endere�o ("port" e endere�o INTERNET)
do usu�rio remoto que enviou o pedido,
"opt" cont�m par�metros espec�ficos do protocolo associados
� conex�o requisitada,
"udata" cont�m dados recebidos juntamente com o pedido de conex�o,
e "sequence" � um n�mero que identifica univocamente o pedido de conex�o.
O valor de "sequence" possibilita o usu�rio a receber v�rios pedidos de
conex�o antes de responder a qualquer um deles.

.sp
Como esta fun��o retorna valores nos campos "addr", "opt" e "udata"
da estrutura "call", o campo "maxlen" de cada um deles deve
ser inicializado antes da chamada � fun��o, para indicar o tamanho
dispon�vel de cada uma das �reas.

.sp
Normalmente, "t_listen" executa no modo s�ncrono e
espera a chegada de um pedido de conex�o antes de retornar.
No entanto, se o indicador O_NONBLOCK foi ligado
(atrav�s de "t_open" ou "fcntl" (sys)),
"t_listen" executa no modo ass�ncrono, apenas testando a presen�a
de um pedido de conex�o. 
Se nenhum est� presente, retorna -1 e atribui o valor [TNODATA] 
a "t_errno".

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Esta implementa��o N�O suporta a negocia��o de par�metros
espec�ficos de protocolo nem a transmiss�o de dados
durante o estabelecimento da conex�o;
portanto, no retorno "call->udata.len" e "call->opt.len" ser�o
sempre NULOs.

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
t_accept, t_alloc, t_bind, t_connect, t_open,
.br
.wo "        t_optmgmt, t_rcvconnect"
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
