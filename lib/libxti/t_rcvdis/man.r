.bp
.he 'T_RCVDIS (xti)'TROPIX: Manual de Refer�ncia'T_RCVDIS (xti)'
.fo 'Escrito em 03.08.92'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_rcvdis -"
recebe uma indica��o de desconex�o abortiva
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_rcvdis (int fd, T_DISCON *discon);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_rcvdis" � usada para identificar a causa de uma desconex�o
abortiva e obter dados do usu�rio enviados com a desconex�o.

.sp
.(l
	+-----------------------+------------+------------+
	|   Argumentos		| Na chamada | No retorno |
	+-----------------------+------------+------------+
	| fd			|     x      |     /	  |
	|			|	     |	   	  |
	| discon->udata.maxlen	|     x      |     /	  |
	| discon->udata.len	|     /      |     x	  |
	| discon->udata.buf	|     x      |    (?)	  |
	|			|	     |	   	  |
	| discon->reason	|     /      |     x	  |
	|			|	     |	   	  |
	| discon->sequence	|     /      |     ?	  |
	|			|	     |	   	  |
	+-----------------------+------------+------------+
.)l

.sp
O argumento "fd" indica o "endpoint" local onde existe (ou existia)
a conex�o e o argumento "discon" deve apontar para uma estrutura
"T_DISCON" que cont�m os seguintes membros:

.sp
.(l
     NETBUF     udata;
     int        reason;
     int        sequence;
.)l

.sp
Ap�s o retorno, o campo "reason" especifica a raz�o pela qual
a conex�o foi desfeita (atrav�s de um c�digo dependente do protocolo),
"udata" cont�m dados recebidos juntamente com a indica��o da desconex�o
abortiva e "sequence" pode identificar um pedido de conex�o pendente com o
qual a desconex�o est� associada.

.sp
O campo "sequence" s� tem significado quando "t_rcvdis" � chamado
por um usu�rio passivo (servidor) que j� chamou "t_listen" uma ou mais
vezes e est� processando os pedidos de conex�o obtidos.
Neste caso, "sequence" identifica qual dos pedidos de conex�o pendentes
� associado � desconex�o.

.sp
Se um usu�rio n�o se interessa pelos dados associados � desconex�o
nem pelos valores de "reason" e "sequence", "discon" pode ser
um ponteiro NULO. Neste caso, os dados associados ao pedido de
desconex�o ser�o descartados.
No entanto, se um "endpoint" possuir
mais de um pedido de conex�o pendente (via "t_listen") e receber um pedido
de desconex�o para um deles, o usu�rio n�o ser� capaz de identificar
a qual dos pedidos a indica��o de desconex�o est� associada.

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Esta implementa��o N�O suporta a transmiss�o de dados
durante uma desconex�o abortiva;
portanto, no retorno "discon->udata.len" ser� sempre NULO.

.sp
Al�m disto, no retorno os campos e "discon->reason" e "discon->sequence"
ser�o tamb�m sempre NULOs.

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
t_alloc, t_connect, t_listen, t_open, t_snddis
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
