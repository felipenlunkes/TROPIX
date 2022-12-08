.bp
.he 'T_SNDDIS (xti)'TROPIX: Manual de Refer�ncia'T_SNDDIS (xti)'
.fo 'Escrito em 04.03.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_snddis -"
envia uma indica��o de desconex�o abortiva
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_snddis (int fd, const T_CALL *call);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_snddis" � usada para iniciar uma desconex�o abortiva
em uma conex�o j� estabelecida ou rejeitar um pedido de conex�o.

.sp
.(l
	+-----------------------+------------+------------+
	|   Argumentos		| Na chamada | No retorno |
	+-----------------------+------------+------------+
	| fd			|     x      |     /	  |
	|			|	     |	   	  |
	| call->addr.maxlen	|     /      |     /	  |
	| call->addr.len	|     /      |     /	  |
	| call->addr.buf	|     /      |     /	  |
	|			|	     |	   	  |
	| call->opt.maxlen	|     /      |     /	  |
	| call->opt.len		|     /      |     /	  |
	| call->opt.buf		|     /      |     /	  |
	|			|	     |	   	  |
	| call->udata.maxlen	|     /      |     /	  |
	| call->udata.len	|     x      |     /	  |
	| call->udata.buf	|    ?(?)    |     /	  |
	|			|	     |	   	  |
	| call->sequence	|     ?      |     /	  |
	|			|	     |	   	  |
	+-----------------------+------------+------------+
.)l

.sp
O argumento "fd" indica o "endpoint" local da conex�o
e "call" especifica informa��es associadas � desconex�o abortiva.
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
Os valores em "call" possuem significados diferentes, dependendo
do contexto no qual a fun��o � chamada.

.sp
Para rejeitar um pedido de conex�o, "call" deve ser um ponteiro
n�o NULO e conter um n�mero v�lido de "sequence" para identificar
univocamente o pedido a ser rejeitado.
O campo "sequence" s� tem significado se o "endpoint"
se encontra no estado "T_INCON".
Os campos "addr" e "opt" de "call" s�o ignorados.

.sp
Em todos os outros casos, "call" somente precisa ser utilizado
se forem enviados dados juntamente com a indica��o de desconex�o.
Os campos "addr", "opt" e "sequence" de "call" s�o ignorados.
Se o usu�rio n�o deseja enviar dados, "call" pode ser um ponteiro NULO.

.sp
A estrutura "udata" especifica os dados a serem enviados ao usu�rio remoto.
A quantidade de dados n�o deve exceder o valor retornado no
campo "discon" do argumento "info", obtido atrav�s de "t_open" ou "t_getinfo".
Se o campo "len" de "udata" � zero, nenhum dado ser�
enviado ao usu�rio remoto.

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Esta implementa��o N�O suporta a transmiss�o de dados
juntamente com uma indica��o de desconex�o abortiva;
portanto, na chamada "call->udata.len" deve ser NULO.

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
.wo "(xti): "
t_connect, t_getinfo, t_listen, t_open
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
