.bp
.he 'T_NREAD (xti)'TROPIX: Manual de Refer�ncia'T_NREAD (xti)'
.fo 'Escrito em 09.07.98'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_nread -"
informa o n�mero de bytes dispon�veis para recep��o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_nread (int fd);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_nread" fornece o n�mero de bytes dispon�veis na fila de
entrada do "endpoint" de transporte "fd", prontos para a recep��o
(atrav�s de "t_rcv", "t_rcvudata" ou "t_rcvraw").

.sp
.(l
	    +--------------------+------------+------------+
	    |   Argumentos	 | Na chamada | No retorno |
	    +--------------------+------------+------------+
	    | fd		 |     x      |     /      |
	    +--------------------+------------+------------+
.)l

.sp
A fun��o "t_nread" pode ser usada tanto no modo-com-conex�o,
no modo-sem-conex�o como no modo-de-acesso-interno;
ela � normalmente usada no modo s�ncrono para
evitar que o processo fique bloqueado em uma recep��o.

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Esta fun��o n�o faz parte da XTI, e portanto seu uso deve ser evitado
se for desejada portabilidade para outras implementa��es.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso a fun��o devolve o n�mero de bytes dispon�veis
(ou ZERO, caso a fila de entrada esteja vazia).
Em caso contr�rio, devolve -1 e indica em "t_errno" a causa do erro.

.sp
No modo-com-conex�o, se a fila de entrada estiver vazia,
mas tiver sido recebida uma indica��o de "final de arquivo",
a fun��o retorna -1 com [TLOOK] em "t_errno" e o evento "T_ORDREL"
(veja "t_look" (xti)).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(xti): "
t_rcv, t_rcvudata, t_rcvraw, t_look
.br

.in
.sp
.b
REFER�NCIAS
.r
.in 5
"X/OPEN Portability Guide: Networking Services",
X/OPEN Company Ltd.,
Prentice Hall, New Jersey, 1st Edition, 1988.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
