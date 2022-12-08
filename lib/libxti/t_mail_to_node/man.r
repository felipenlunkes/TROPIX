.bp
.he 'T_MAIL_TO_NODE (xti)'TROPIX: Manual de Refer�ncia'T_MAIL_TO_NODE (xti)'
.fo 'Escrito em 29.11.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
.wo "t_mail_to_node -"
obt�m um servidor de correio para um dom�nio
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

char *t_mail_to_node (int fd, const char *domain,
				int preference, int &new_preference);
.)l

.in
.sp
.b DESCRI��O
.in 5
Esta fun��o fornece um servidor de correio eletr�nico para o dom�nio "domain" dado.

.sp
Ser� fornecido o servidor de menor c�digo num�rico de prefer�ncia dispon�vel, por�m
de c�digo igual ou maior do que o valor "preference" dado.
Repare que quanto maior este c�digo num�rico, menor a "prefer�ncia".

.sp
Se em "new_preference" for dado um ponteiro n�o NULO, o seu conte�do receber�
a "prefer�ncia" do servidor fornecido.

.sp
Os diversos servidores podem ser obtidos, dando o c�digo "0" de prefer�ncia 
na primeira chamada a "t_mail_to_node", e fornecendo o c�digo obtido anteriormente
para cada nova chamada, at� obter um ponteiro NULO com o c�digo de erro NOENT (veja abaixo).

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
Em caso de sucesso, � retornado um ponteiro para o nome simb�lico de um n�;
em caso de erro  � retornado um ponteiro NULO.
Se n�o houver nenhum servidor com c�digo de prefer�ncia igual ou maior ao dado,
� retornado o c�digo de erro NOENT.

.in
.sp
.b OBSERVA��ES
.in 5
Repare que n�o � fornecido o endere�o do n�; para isto � necess�rio usar
posteriormente a fun��o "t_node_to_addr".

.sp
A fun��o devolve um ponteiro para uma �rea est�tica, e o
seu conte�do deve ser copiado caso ele seja necess�rio ap�s
a fun��o ser chamada novamente.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.br
.wo "(xti): "
t_addr
.br

.in
.sp
.b
REFER�NCIAS
.r
.in 5
"Domain Names - Concepts and Facilities", RFC 1034,
P. Mockapetris, November 1987.

.sp
"Domain Names - Implementation and Specification", RFC 1035,
P. Mockapetris, November 1987.

.sp
"X/OPEN Portability Guide: Networking Services",
X/OPEN Company Ltd.,
Prentice Hall, New Jersey, 1st Edition, 1988.

.in
.sp
.(t
.b ESTADO
.in 5
Efetivo.
.)t

.in
