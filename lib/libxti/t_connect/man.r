.bp
.he 'T_CONNECT (xti)'TROPIX: Manual de Refer�ncia'T_CONNECT (xti)'
.fo 'Escrito em 04.03.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_connect -"
estabelece uma conex�o com um usu�rio remoto
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_connect (int fd, const T_CALL *sndcall, T_CALL *rcvcall);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_connect" estabelece uma conex�o com um outro usu�rio
atrav�s do envio de um pedido de conex�o e da confirma��o da aceita��o
deste pedido.

.sp
.(l
	+-----------------------+------------+------------+
	|   Argumentos		| Na chamada | No retorno |
	+-----------------------+------------+------------+
	| fd			|     x      |     /	  |
	|			|	     |	   	  |
	| sndcall->addr.maxlen	|     /      |     /	  |
	| sndcall->addr.len	|     x      |     /	  |
	| sndcall->addr.buf	|    x(x)    |     /	  |
	|			|	     |	   	  |
	| sndcall->opt.maxlen	|     /      |     /	  |
	| sndcall->opt.len	|     x      |	   /	  |
	| sndcall->opt.buf	|    ?(?)    |	   /	  |
	|			|	     |		  |
	| sndcall->udata.maxlen	|     /      |	   /	  |
	| sndcall->udata.len	|     x      |	   /	  |
	| sndcall->udata.buf	|    ?(?)    |	   /	  |
	|			|	     |		  |
	| sndcall->sequence	|     /	     |	   /	  |
	|			|	     |		  |
	| rcvcall->addr.maxlen	|     x      |	   /	  |
	| rcvcall->addr.len	|     /      |	   x	  |
	| rcvcall->addr.buf	|     x      |	  (x)	  |
	|			|	     |		  |
	| rcvcall->opt.maxlen	|     x      |	   /	  |
	| rcvcall->opt.len	|     /      |	   x	  |
	| rcvcall->opt.buf	|     x      |	  (x)	  |
	|			|	     |		  |
	| rcvcall->udata.maxlen	|     x      |	   /	  |
	| rcvcall->udata.len	|     /      |	   x	  |
	| rcvcall->udata.buf	|     x      |	  (?)	  |
	|			|	     |		  |
	| rcvcall->sequence	|     /	     |	   /	  |
	+-----------------------+------------+------------+
.)l

.sp
Esta fun��o s� pode ser chamada no estado T_IDLE.
O argumento "fd" indica o "endpoint" local no qual
se estabelecer� a conex�o.

.sp
.(t
Os argumentos "sndcall" e "rcvcall" devem apontar para estruturas
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
O argumento "sndcall" cont�m informa��es necess�rias pelo sistema
de transporte para o estabelecimento da conex�o e o argumento "rcvcall"
fornece informa��es sobre a conex�o estabelecida.

.sp
Em "sndcall": "addr" especifica o endere�o de protocolo
(endere�o INTERNET e "port") do usu�rio remoto,
"opt" cont�m informa��es espec�ficas do protocolo
a serem utilizadas na conex�o,
"udata" cont�m dados opcionais a serem enviados juntamente
com o pedido de conex�o e "sequence" n�o tem significado para esta fun��o.

.sp
No retorno, em "rcvcall": "addr" indica o endere�o do "endpoint"
remoto (atrav�s do qual foi aceita a conex�o),
"opt" cont�m informa��es espec�ficas do protocolo associadas
� conex�o, "udata" cont�m dados opcionais recebidos juntamente com
a aceita��o do pedido de conex�o e "sequence" n�o tem significado para
esta fun��o.

.sp
O argumento "opt" permite o usu�rio a definir op��es espec�ficas
do protocolo utilizado na conex�o.
O usu�rio pode escolher n�o negociar op��es,
bastando para isto atribuir uma valor NULO ao campo "sndcall->opt.len".
Neste caso, o sistema de tranporte assumir� o funcionamento
padr�o.

.bc	/*************************************/
.sp
Nesta implementa��o (se utilizado) "sndcall->opt.buf" deve apontar para
a estrutura "TCP_OPTIONS" (ver <xti.h>), da qual (nesta vers�o) apenas
o membro "max_seg_size" � relevante.
Os campos "maxlen" e "buf" de "rcvcall->addr" e "rcvcall->opt"
devem estar inicializados antes da chamada.
.ec	/*************************************/

.sp
O argumento "udata" permite que o usu�rio envie dados ao usu�rio
remoto e receba dados deste usu�rio durante o estabelecimento
da conex�o.
No entanto, a quantidade de dados n�o pode exceder o limite
suportado pelo sistema de tranporte como indicado no  campo
"connect" do argumento "info" da fun��o "t_open" ou "t_getinfo".
Se o campo "len" da estrutura "udata" em "sndcall" tiver um valor NULO,
nenhum dado ser� enviado ao usu�rio remoto.

.sp
No retorno, os campos "addr", "opt" e "udata" de "rcvcall"
conter�o valores associados � conex�o estabelecida.
Deste modo, o campo "maxlen" de cada argumento deve ser inicializado,
antes da chamada a esta fun��o, para indicar o tamanho m�ximo da �rea
de cada um. No entanto, "rcvcall" pode ser um ponteiro NULO,
caso em que nenhuma informa��o ser� retornada ao usu�rio.

.sp
Normalmente, "t_connect" executa no modo s�ncrono,
e ap�s ter enviado o pedido de conex�o,
espera pela resposta do usu�rio remoto antes de retornar.
Um retorno com sucesso, indica que a conex�o
requisitada foi estabelecida.
No entanto, se o indicador O_NONBLOCK foi ligado
(atrav�s de "t_open" ou "fcntl" (sys)),
"t_connect" executa no modo ass�ncrono.
Neste caso, "t_connect" n�o espera a resposta do usu�rio remoto
ap�s o envio do pedido de conex�o, retornando -1 imediatamente
com o valor [TNODATA]  em "t_errno".
No modo ass�ncrono, a fun��o "t_connect" apenas inicia o processo
de estabelecimento da conex�o atrav�s do envio de um pedido de conex�o;
a fun��o "t_rcvconnect" deve ser utilizada posteriormente
para completar o estabelecimento da conex�o.

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Esta implementa��o N�O suporta a negocia��o de par�metros
espec�ficos de protocolo nem a transmiss�o de dados
durante o estabelecimento da conex�o;
portanto, na chamada os valores de "sndcall->udata.len"
e "sndcall->opt.len" devem ser NULOs.

.sp
O endere�o retornado em "rcvcall->addr" � o endere�o fornecido pelo
usu�rio remoto na confirma��o da conex�o, que ser� o endere�o efetivamente
utilizado na conex�o. Pode ser diferente do endere�o dado na chamada
em "sndcall->addr", no caso de servidores que mant�m endere�os
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
t_accept, t_alloc, t_getinfo, t_listen, t_open,
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
