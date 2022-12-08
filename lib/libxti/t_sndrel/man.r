.bp
.he 'T_SNDREL (xti)'TROPIX: Manual de Refer�ncia'T_SNDREL (xti)'
.fo 'Escrito em 04.03.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_sndrel -"
inicia uma desconex�o ordenada
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_sndrel (int fd);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_sndrel" � utilizada para iniciar uma desconex�o ordenada e
indica ao usu�rio remoto que n�o h� mais dados a serem enviados.

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
Depois de chamar "t_sndrel", o usu�rio n�o pode mais
enviar dados atrav�s da conex�o;
no entanto, ele pode continuar a receber dados normalmente,
se uma indica��o de desconex�o ordenada ainda n�o foi recebida.

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
.b OBSERVA��O
.in 5
Normalmente, o usu�rio remoto recebe a indica��o
de que n�o h� mais dados a serem recebidos atrav�s
de um valor NULO (== EOF) retornado pela fun��o "t_rcv".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(xti): "
t_getinfo, t_open, t_rcv, t_rcvrel
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
