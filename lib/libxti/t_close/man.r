.bp
.he 'T_CLOSE (xti)'TROPIX: Manual de Refer�ncia'T_CLOSE (xti)'
.fo 'Escrito em 08.01.93'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_close -"
fecha um "endpoint" de transporte
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_close (int fd);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_close" informa o sistema de transporte que o usu�rio
terminou a utiliza��o do "endpoint" de transporte especificado por "fd".

.sp
.(l
	    +--------------------+------------+------------+
	    |   Argumentos	 | Na chamada | No retorno |
	    +--------------------+------------+------------+
	    | fd		 |     x      |     /      |
	    +--------------------+------------+------------+
.)l

.sp
A fun��o "t_close" deve ser chamada no estado T_UNBND (veja "t_getstate").
No entanto, isto n�o � verificado, de tal modo que ela pode ser chamada
em qualquer estado.

.sp
Em todos os casos, s�o liberados todos os recursos associados ao "endpoint".

.sp
No modo-com-conex�o, t_close" ser� abortiva para o usu�rio remoto, no caso
em que seja verificado (pelo estado do "endpoint") que o usu�rio
remoto n�o est� esperando o t�rmino da conex�o.

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
t_getstate, t_open, t_unbind
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
