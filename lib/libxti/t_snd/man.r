.bp
.he 'T_SND (xti)'TROPIX: Manual de Refer�ncia'T_SND (xti)'
.fo 'Escrito em 04.03.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_snd -"
envia dados atrav�s de uma conex�o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_snd (int fd, const void *buf, int nbytes, int flags);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_snd" envia dados normais ou urgentes atrav�s de uma conex�o.

.sp
.(l
	    +-------------------+------------+------------+
	    |   Argumentos	| Na chamada | No retorno |
	    +-------------------+------------+------------+
	    | fd		|     x      |     /      |
	    | buf		|    x(x)    |     /      |
	    | nbytes		|     x      |     /      |
	    | flags		|     x      |     /      |
	    +-------------------+------------+------------+
.)l

.sp
O argumento "fd" identifica o  "endpoint" local de transporte
atrav�s do qual os dados s�o enviados, "buf" aponta para a �rea
de dados do usu�rio, "nbytes" especifica o n�mero de bytes de
dados que devem ser enviados e o argumento "flags" especifica
um (ou mais) indicadores opcionais, como descritos abaixo.

.sp
Como nesta implementa��o o sistema de transporte utiliza o protocolo
TCP (INTERNET) para o modo-com-conex�o, os indicadores "T_EXPEDITED"
e "T_MORE" n�o s�o suportados. Em compensa��o s�o dispon�veis os
indicadores "T_URGENT" e "T_PUSH"
(veja "t_intro" e os DETALHES DE IMPLEMENTA��O abaixo).

.sp
Normalmente, "t_snd" opera no modo s�ncrono e pode esperar caso
haja retri��es de controle de fluxo.
No entanto, se o indicador O_NONBLOCK foi ligado
(atrav�s de "t_open" ou "fcntl" (sys)),
"t_snd" executa no modo ass�ncrono, e se houver
retri��es de controle de fluxo
retorna imediatamente com -1 e atribui o valor [TFLOW]  a "t_errno".

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Esta implementa��o utiliza o protocolo TCP (INTERNET) para o
modo-com-conex�o (veja "t_intro"), e portanto o envio de dados �
orientado a uma seq��ncia de bytes, o que n�o preserva as
fronteiras entre as mensagens
(isto �, n�o s�o suportados os conceitos de TSDU e ETSDU).

.sp
Pela mesma raz�o, os indicadores "T_EXPEDITED" e "T_MORE" n�o s�o
suportados; em compensa��o s�o dispon�veis os indicadores
"T_URGENT" e "T_PUSH", (que embora semelhantes, n�o s�o iguais):

.in +3
.ip - 2
Se o indicador "T_URGENT" estiver ligado, os dados ser�o enviados como dados
"urgentes", e o usu�rio remoto ser� notificado disto
quando receb�-los atrav�s de "t_rcv".

.ip - 2
Normalmente (isto �, se o indicador "T_PUSH" N�O estiver ligado),
o sistema de transporte s� envia efetivamente os dados para o usu�rio remoto
quando um segmento TCP for completado.
No entanto, se o indicador "T_PUSH" estiver ligado, os dados ser�o
enviados imediatamente (possivelmente juntos com dados anteriores
ainda n�o enviados; veja tamb�m a fun��o "t_push").
O usu�rio remoto ser� notificado disto
quando receber estes dados atrav�s de "t_rcv".

.ep
.in -3

.sp
Nesta implementa��o, tamb�m � poss�vel a utiliza��o da chamada ao
sistema "write" (sys) para enviar dados atrav�s de uma conex�o.
A chamada

.sp
.(l
	  write (fd, buf, nbytes);
.)l

.sp
� equivalente a

.sp
.(l
	  t_snd (fd, buf, nbytes, NULL);
.)l

.sp
Al�m disto, nesta implementa��o a fun��o "t_snd" s� opera no modo
s�ncrono, isto �, ela sempre ir� esperar caso haja retri��es de
controle de fluxo.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso a fun��o devolve um inteiro n�o negativo,
indicando o n�mero de bytes de dados aceitos pelo sistema de transporte.
Normalmente este n�mero � igual ao n�mero de bytes especificado
em "nbytes".
No entanto, se o indicador O_NONBLOCK estiver ligado, � poss�vel
que apenas parte dos dados sejam aceitos pelo sistema de transporte.
Neste caso, "t_snd" retornar� um valor que � menor do que "nbytes".

.sp
Em caso de falha, devolve -1 e indica em "t_errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
write, fcntl
.br
.wo "(xti): "
t_intro, t_open, t_rcv, t_push
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
