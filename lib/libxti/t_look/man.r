.bp
.he 'T_LOOK (xti)'TROPIX: Manual de Refer�ncia'T_LOOK (xti)'
.fo 'Escrito em 04.03.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_look -"
indica a ocorr�ncia de um evento em um "endpoint"
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_look (int fd);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_look" retorna um evento ocorrido no "endpoint" de
transporte especificado por "fd".

.sp
.(l
	    +--------------------+------------+------------+
	    |   Argumentos	 | Na chamada | No retorno |
	    +--------------------+------------+------------+
	    | fd		 |     x      |     /      |
	    +--------------------+------------+------------+
.)l

.sp
Esta fun��o permite ao sistema de transporte notificar um usu�rio
da ocorr�ncia de um evento ass�ncrono quando o usu�rio est� chamando
as fun��es no modo s�ncrono.

.sp
Certos eventos necessitam de notifica��o imediata do usu�rio
e s�o indicados pelo erro [TLOOK] no retorno da fun��o corrente
ou da pr�xima a ser chamada.

.sp
Esta fun��o tamb�m permite a um usu�rio testar periodicamente
a presen�a de eventos ass�ncronos.

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Para facilitar a impress�o de diagn�sticos,
nesta implementa��o est� dispon�vel a fun��o "t_strevent", que
fornece uma cadeia contendo a descri��o de um evento.
Lembre-se no entanto, que esta fun��o n�o faz parte da XTI,
e portanto seu uso deve ser evitado se for desejada portabilidade
para outras implementa��es.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de erro, a fun��o devolve -1 e indica em "t_errno" a causa do erro.
Em caso de sucesso devolve zero se nenhum evento ocorreu,
ou um identificador de eventos da lista abaixo:

.sp
.(t
.nf
   	T_LISTEN	Foi recebido um pedido de conex�o
	T_CONNECT	Foi recebido um resposta a um pedido de
			conex�o
	T_DATA		Foram recebidos dados normais
	T_EXDATA	Foram recebidos dados urgentes
	T_DISCONNECT	Foi recebida uma indica��o de desconex�o
	T_UDERR		Ocorreu um erro no envio de datagrama
	T_ORDREL	Foi recebida uma indica��o de desconex�o
			ordenada
	T_GODATA	O fluxo de dados normais foi restabelecido
	T_GOEXDATA	O fluxo de dados urgentes foi restabelecido
.fi
.)t

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(xti): "
t_intro, t_open, t_snd, t_sndudata, t_sndraw,
.br
.wo "				    t_strevent"
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
.(t
.b ESTADO
.in 5
Efetivo.
.)t

.in
