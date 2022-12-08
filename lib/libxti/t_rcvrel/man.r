.bp
.he 'T_RCVREL (xti)'TROPIX: Manual de Refer�ncia'T_RCVREL (xti)'
.fo 'Escrito em 15.05.92'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_rcvrel -"
recebe uma indica��o de desconex�o ordenada
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_rcvrel (int fd);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_rcvrel" � usada para notificar a recep��o de uma
desconex�o ordenada.

.sp
.(l
	    +--------------------+------------+------------+
	    |   Argumentos	 | Na chamada | No retorno |
	    +--------------------+------------+------------+
	    | fd		 |     x      |     /      |
	    +--------------------+------------+------------+
.)l

.sp
O argumento "fd" indica o "endpoint" local onde existe a conex�o.

.sp
Depois da recep��o de uma desconex�o ordenada, o usu�rio n�o deve tentar
receber mais dados pois poder� ficar bloqueado para sempre.
No entanto, o usu�rio pode continuar a enviar dados atrav�s
da conex�o se a fun��o "t_sndrel" ainda n�o foi chamada.

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
t_getinfo, t_open, t_sndrel
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
