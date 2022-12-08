.bp
.he 'T_RCVCONNECT (xti)'TROPIX: Manual de Refer�ncia'T_RCVCONNECT (xti)'
.fo 'Escrito em 04.03.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_rcvconnect -"
recebe a aceita��o de um pedido de conex�o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_rcvconnect (int fd, T_CALL *call);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_rcvconnect" permite um usu�rio a determinar o estado
de um pedido de conex�o enviado anteriormente, e � usado em conjunto
com "t_connect" para estabelecer uma conex�o no modo ass�ncrono.
A conex�o estar� completada ap�s um retorno com sucesso desta fun��o.

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
O argumento "fd" indica o "endpoint" local no qual
se estabelecer� a conex�o, e no retorno o argumento "call" conter�
informa��es sobre a conex�o estabelecida.
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
Em "call", "addr" retorna o endere�o ("port" e endere�o INTERNET)
associado ao "endpoint" remoto (atrav�s do qual foi aceita a conex�o),
"opt" cont�m informa��es espec�ficas do protocolo associadas
� conex�o, "udata" cont�m dados opcionais recebidos juntamente com
a aceita��o do pedido de conex�o e "sequence" n�o tem significado para
esta fun��o.

.sp
Como esta fun��o retorna valores nos campos "addr", "opt" e "udata"
da estrutura "call", o campo "maxlen" de cada um deles deve
ser inicializado antes da chamada � fun��o, para indicar o tamanho
dispon�vel de cada uma das �reas. No entanto, "call" pode ser um
ponteiro NULO, caso em que nenhuma informa��o � dada ao usu�rio no
retorno de "t_rcvconnect".

.bc	/*************************************/
.sp
Nesta implementa��o (se utilizado) "call->opt.buf" deve apontar para
a estrutura "TCP_OPTIONS" (ver <xti.h>), da qual (nesta vers�o) apenas
o membro "max_seg_size" � relevante.
.ec	/*************************************/

.sp
Normalmente, "t_rcvconnect" executa no modo s�ncrono e
espera a chegada da aceita��o do pedido de conex�o antes de retornar.
No retorno, os campos "addr", "opt" e "udata" refletem dados
associados com a conex�o.

.sp
Se o indicador O_NONBLOCK foi ligado (atrav�s de "t_open" ou "fcntl" (sys)),
"t_rcvconnect" executa no modo ass�ncrono, apenas testando a presen�a
de uma aceita��o de pedido de conex�o. 
Se nenhuma est� presente, retorna -1 e atribui o valor [TNODATA] 
a "t_errno". Neste caso, "t_rcvconnect" tem de ser chamada novamente
para completar o estabelecimento da conex�o, e obter a informa��o
fornecida em "call".

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Esta implementa��o N�O suporta a negocia��o de par�metros
espec�ficos de protocolo nem a transmiss�o de dados
durante o estabelecimento da conex�o;
portanto, no retorno os valores de "call->udata.len"
e "call->opt.len" ser�o sempre NULOs.

.sp
O endere�o retornado em "call->addr" � o endere�o fornecido pelo
usu�rio remoto na confirma��o da conex�o, que ser� o endere�o efetivamente
utilizado na conex�o. Pode ser diferente do endere�o dado em "sndcall->addr"
na chamada de "t_connect", no caso de servidores que mant�m endere�os
(constantes) conhecidos para cada servi�o prestado, e novos endere�os
v�o sendo criados para as conex�es com os diversos clientes. 

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
t_accept, t_alloc, t_bind, t_connect, t_listen, t_open
.br
.wo "        t_optmgmt"
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
