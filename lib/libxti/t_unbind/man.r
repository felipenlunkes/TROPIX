.bp
.he 'T_UNBIND (xti)'TROPIX: Manual de Refer�ncia'T_UNBIND (xti)'
.fo 'Escrito em 24.06.92'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_unbind -"
desativa um "endpoint" de transporte
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_unbind (int fd);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_unbind" desativa o "endpoint" de transporte especificado
por "fd" (que foi previamente ativado atrav�s de "t_bind").

.sp
.(l
	    +--------------------+------------+------------+
	    |   Argumentos	 | Na chamada | No retorno |
	    +--------------------+------------+------------+
	    | fd		 |     x      |     /      |
	    +--------------------+------------+------------+
.)l

.sp
Ap�s a chamada a esta fun��o, nenhuma dado ou evento
destinados a este "endpoint" ser� mais aceito pelo sistema de transporte.

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
.br
.wo "(xti): "
t_bind
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
