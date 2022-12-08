.bp
.he 'T_GETADDR (xti)'TROPIX: Manual de Refer�ncia'T_GETADDR (xti)'
.fo 'Escrito em 08.01.93'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_getaddr -"
obt�m os endere�os associados a um "endpoint"
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_getaddr (int fd, INADDR *addr);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_getaddr" retorna os endere�os associados ao
"endpoint" de transporte especificado pelo descritor de arquivo "fd".
A fun��o permite o usu�rio a obter os endere�os
durante qualquer fase da comunica��o, tanto no modo-com-conex�o,
no modo-sem-conex�o assim como no modo-de-acesso-interno.

.sp
.(l
	    +-------------------+------------+------------+
	    |    Argumentos	| Na chamada | No retorno |
	    +-------------------+------------+------------+
	    | fd		|     x      |     /      |
	    |			|	     |		  |
	    | addr[0].a_addr	|     /      |     x      |
	    | addr[0].a_family	|     /      |     /      |
	    | addr[0].a_port	|     /      |     x      |
	    |			|	     |		  |
	    | addr[1].a_addr	|     /      |     x      |
	    | addr[1].a_family	|     /      |     /      |
	    | addr[1].a_port	|     /      |     x      |
	    |			|	     |		  |
	    | addr[2].a_addr	|     /      |     x      |
	    | addr[2].a_family	|     /      |     /      |
	    | addr[2].a_port	|     /      |     x      |
	    |			|	     |		  |
	    | addr[3].a_addr	|     /      |     x      |
	    | addr[3].a_family	|     /      |     /      |
	    | addr[3].a_port	|     /      |     x      |
	    |			|	     |		  |
	    +-------------------+------------+------------+
.)l

.in
.sp
.b MODO-COM-CONEX�O
.in 5
No modo-com-conex�o, o ponteiro "addr" deve apontar para um vetor
de duas estruturas "INADDR", cujo primeiro elemento � preenchido com
o endere�o local e o segundo com o endere�o remoto da conex�o.
Os endere�os s�o significativos a partir do estado 
T_DATAXFER (isto �, ap�s um "t_accept" ou "t_connect").

.in
.sp
.b MODO-SEM-CONEX�O
.in 5
No modo-sem-conex�o, o ponteiro "addr" deve apontar para um vetor
de quatro estruturas "INADDR", cujos elementos s�o preenchidos respectivamente
com o endere�o local, endere�o remoto (obtido no "t_bind"),
endere�o remoto (obtido na �ltima emiss�o de um datagrama),
e o endere�o remoto (obtido na �ltima recep��o de um datagrama).

.sp
O quarto endere�o (endere�o remoto obtido na �ltima recep��o
de um datagrama) � especialmente �til quando se utiliza a interface
"read" ao inv�s de "t_rcvudata".

.in
.sp
.b MODO-DE-ACESSO-INTERNO
.in 5
No modo-de-acesso-interno, o ponteiro "addr" deve apontar para um vetor
de quatro estruturas "INADDR", cujos elementos s�o preenchidos respectivamente
com o endere�o local, endere�o remoto (obtido no "t_bind"),
endere�o remoto (obtido na �ltima emiss�o de um datagrama),
e o endere�o remoto (obtido na �ltima recep��o de um datagrama).

.sp
Neste modo, o membro "a_port" representa na realidade o n�mero do protocolo
("a_proto", veja em <xti.h>).

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
Em caso de sucesso a fun��o preenche a estrutura e devolve o valor 0.
Em caso contr�rio, devolve -1 e indica em "t_errno" a causa do erro.

.in
.sp
.b OBSERVA��O
.in 5
Nesta vers�o os campos "a_family" n�o s�o utilizados.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(xti): "
t_intro, t_addr, t_rcvraw, t_rcvudata
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
