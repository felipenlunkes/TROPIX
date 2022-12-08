.bp
.he 'T_ACCEPT (xti)'TROPIX: Manual de Refer�ncia'T_ACCEPT (xti)'
.fo 'Escrito em 30.07.92'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_accept -"
aceita um pedido de conex�o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_accept (int fd, int resfd, const T_CALL *call);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_accept" � utilizada para aceitar um pedido de conex�o.

.sp
.(l
	    +--------------------+------------+------------+
	    |   Argumentos	 | Na chamada | No retorno |
	    +--------------------+------------+------------+
	    | fd		 |     x      |     /      |
	    |			 |	      |		   |
	    | resfd		 |     x      |     /      |
	    |			 |	      |		   |
	    | call->addr.maxlen	 |     /      |     /      |
	    | call->addr.len	 |     x      |     /      |
	    | call->addr.buf	 |    ?(?)    |     /      |
	    |			 |	      |		   |
	    | call->opt.maxlen	 |     /      |     /      |
	    | call->opt.len	 |     x      |     /      |
	    | call->opt.buf	 |    ?(?)    |     /      |
	    |			 |	      |		   |
	    | call->udata.maxlen |     /      |     /      |
	    | call->udata.len	 |     x      |     /      |
	    | call->udata.buf	 |    ?(?)    |     /      |
	    |			 |	      |		   |
	    | call->sequence	 |     x      |     /      |
	    +--------------------+------------+------------+
.)l

.sp
O argumento "fd" indica o "endpoint" local no qual chegou o pedido
de conex�o, "resfd" identifica o "endpoint" local no qual
a conex�o deve ser estabelecida, e "call" cont�m informa��es
necess�rias pelo sistema de transporte para completar a conex�o.

.sp
.(t
O argumento "call" deve apontar para uma estrutura
"T_CALL" que cont�m os seguintes membros:

.sp
.(l
     NETBUF     addr;
     NETBUF     opt;
     NETBUF     udata;
     int        sequence;
.)l
.)t

.sp
Em "call": "addr" especifica o endere�o de protocolo
(endere�o INTERNET e "port") do usu�rio remoto,
"opt" cont�m informa��es espec�ficas do protocolo
a serem utilizadas na conex�o,
"udata" cont�m dados opcionais a serem retornados juntamente
com a aceita��o da conex�o e "sequence" � o valor retornado por
"t_listen", que identifica univocamente a aceita��o com uma
indica��o de conex�o recebida anteriormente.

.sp
Um usu�rio pode estabelecer a conex�o no mesmo "endpoint"
no qual recebeu o pedido de conex�o ("fd" == "resfd")
ou em um outro "endpoint" ("fd" != "resfd"). 
Para que o mesmo "endpoint" possa ser utilizado,
o usu�rio deve ter respondido a todos os pedidos
de conex�o nele pendentes (atrav�s de "t_accept" ou "t_snddis").
Em caso contr�rio, "t_accept" ir� falhar com [TBADF] em "t_errno".

.sp
Se o usu�rio especificar um "endpoint" diferente,
este "endpoint" j� deve ter um endere�o local associado
(fun��o "t_bind") e deve estar no estado T_IDLE (veja "t_getstate"),
antes de chamar "t_accept".

.sp
Para ambos os tipos de "endpoint", "t_accept" ir� falhar com [TLOOK] em
"t_errno" se houver indica��es de conex�o ou desconex�o
(eventos T_LISTEN ou T_DISCONNECT) no "endpoint".

.sp
O argumento "opt" permite ao usu�rio definir op��es espec�ficas
do protocolo utilizado na conex�o.
O usu�rio pode escolher n�o definir op��es,
bastando para isto atribuir uma valor NULO ao campo "call->opt.len".
Neste caso, o sistema de tranporte assumir� o funcionamento
padr�o.

.bc	/*************************************/
.sp
Nesta implementa��o (se utilizado) "call->opt.buf" deve apontar para
a estrutura "TCP_OPTIONS" (ver <xti.h>), da qual (nesta vers�o) apenas
o membro "max_seg_size" � relevante.
.ec	/*************************************/

.sp
O argumento "udata" permite que o usu�rio envie dados ao usu�rio
remoto juntamente com a aceita��o do pedido de conex�o.
No entanto, a quantidade de dados n�o pode exceder o limite
suportado pelo sistema de tranporte como indicado no  campo
"connect" do argumento "info" da fun��o "t_open" ou "t_getinfo".
Se o campo "len" da estrutura "udata" em "call" tiver um valor NULO,
nenhum dado ser� enviado ao usu�rio remoto.

.sp
Todos os campos "maxlen" s�o irrelevantes.

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
O fornecimento do endere�o de protocolo do usu�rio remoto
� opcional, pois ele � determinado atrav�s de "call->sequence".
Se for dado, no entanto, e n�o conferir com o endere�o dispon�vel,
"t_accept" ir� falhar com [TBADADDR] em "t_errno".

.sp
Esta implementa��o N�O suporta a negocia��o de par�metros
espec�ficos de protocolo nem a transmiss�o de dados
durante o estabelecimento da conex�o;
portanto, na chamada os valores de "call->udata.len"
e "call->opt.len" devem ser NULOs.

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
t_connect, t_getstate, t_listen, t_open, t_optmgmt,
.br
.wo "        t_rcvconnect"
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
