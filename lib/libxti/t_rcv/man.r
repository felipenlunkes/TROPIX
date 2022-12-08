.bp
.he 'T_RCV (xti)'TROPIX: Manual de Refer�ncia'T_RCV (xti)'
.fo 'Escrito em 08.01.93'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_rcv -"
recebe dados atrav�s de uma conex�o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_rcv (int fd, void *buf, int nbytes, int *flags);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_rcv" recebe dados normais ou urgentes atrav�s de uma conex�o.

.sp
.(l
	    +-------------------+------------+------------+
	    |   Argumentos	| Na chamada | No retorno |
	    +-------------------+------------+------------+
	    | fd		|     x      |     /      |
	    | buf		|     x      |    (x)     |
	    | nbytes		|     x      |     /      |
	    | flags		|     ?      |    (?)     |
	    +-------------------+------------+------------+
.)l

.sp
O argumento "fd" identifica o  "endpoint" local de transporte,
atrav�s do qual os dados s�o recebidos, "buf" aponta para a �rea
onde os dados ser�o colocados e "nbytes" especifica o tamanho da
�rea. O argumento "flags" aponta para uma vari�vel onde ser�o
retornados indicadores opcionais, como descritos abaixo. Se "flags"
for um ponteiro NULO, n�o ser�o retornados os indicadores.

.sp
Normalmente, "t_rcv" opera no modo s�ncrono e espera a chegada
de dados, caso n�o haja dados dispon�veis no momento da chamada.
No entanto, se o indicador O_NONBLOCK foi ligado
(atrav�s de "t_open" ou "fcntl" (sys)),
"t_rcv" executa no modo ass�ncrono, e se n�o houver dados dispon�veis
retorna imediatamente com -1 e atribui o valor [TNODATA]  a "t_errno".

.sp
Como nesta implementa��o o sistema de transporte utiliza o protocolo
TCP (INTERNET) para o modo-com-conex�o, os indicadores "T_EXPEDITED"
e "T_MORE" n�o s�o suportados. Em compensa��o s�o dispon�veis os
indicadores "T_URGENT" e "T_PUSH"
(veja "t_intro" e os DETALHES DE IMPLEMENTA��O abaixo).

.sp
No modo s�ncrono, se o usu�rio deseja evitar ficar bloqueado em uma
chamada a "t_rcv", pode utilizar a fun��o "t_look" (verificando
se ocorreu um dos eventos "T_DATA" ou "T_EXDATA").

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
Se houver dados suficientes para completar a �rea "buf" antes de
utilizar um segmento TCP com "PUSH", a �rea ser� completada, mas o indicador
"T_PUSH" de "flags" n�o ser� ligado. Por outro lado, se o segmento
recebido tiver o indicador "PUSH",  a �rea ser� completada parcialmente,
e o indicador "T_PUSH" ser� ligado.

.ip - 2
Se o indicador "T_URGENT" de "flags" estiver ligado, significa que os
dados armazenados em "buf" s�o "urgentes".

.ep
.in -3

.sp
Repare que (no modo s�ncrono) a fun��o "t_rcv" s� retornar� com sucesso se
a �rea "buf" tiver sido completada ou tiver sido recebido um segmento
com o indicador "PUSH".

.sp
Nesta implementa��o, tamb�m � poss�vel a utiliza��o da chamada ao
sistema "read" (sys) para receber dados atrav�s de uma conex�o.
A chamada 

.sp
.(l
	  read (fd, buf, nbytes);
.)l

.sp
� equivalente a

.sp
.(l
	  t_rcv (fd, buf, nbytes, (int *)NULL);
.)l

.sp
Um outro modo dispon�vel nesta implementa��o,
de n�o ficar bloqueado em uma chamada a "t_rcv"
(no modo s�ncrono) � a utiliza��o da fun��o "t_nread",
que fornece o n�mero de bytes de dados dispon�veis.

.sp
A chamada ao sistema "attention" (sys) pode ser usada para aguardar
a disponibilidade de dados para "t_rcv".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso a fun��o devolve um inteiro n�o negativo,
indicando o n�mero de bytes de dados efetivamente armazenados em "buf".
Um valor NULO indica o "final de arquivo", que ocorre quando o usu�rio
remoto chama a fun��o "t_sndrel" para terminar a conex�o.
Em caso contr�rio, devolve -1 e indica em "t_errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
read, fcntl, attention
.br
.wo "(xti): "
t_intro, t_getinfo, t_look, t_open, t_sndrel,
.br
.wo '        t_rcvrel, t_snd, t_nread'
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
