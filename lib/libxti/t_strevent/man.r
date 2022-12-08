.bp
.he 'T_STREVENT (xti)'TROPIX: Manual de Refer�ncia'T_STREVENT (xti)'
.fo 'Escrito em 27.11.92'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_strevent -"
obt�m uma cadeia com a descri��o de um evento
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

char *t_strevent (int fd, int event);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "strevent" devolve um ponteiro para uma cadeia contendo uma
descri��o correspondente ao c�digo num�rico "event" de um evento
ocorrido em um "endpoint".
A cadeia n�o cont�m o <nl> de final de linha.

.sp
Para a utiliza��o da fun��o, � necess�rio j� haver algum "endpoint"
de transporte dispon�vel (argumento "fd"), isto �, ela s� pode ser
utilizada ap�s um "t_open" (xti).

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Lembre-se de que esta fun��o n�o faz parte da XTI
e portanto seu uso deve ser evitado se for desejada portabilidade
para outras implementa��es.

.in
.sp
.b DIAGN�STICOS
.in 5
A fun��o "strevent" devolve um ponteiro para a mensagem
"Evento Desconhecido" caso o argumento "event" contenha um c�digo
num�rico de evento inv�lido.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(xti): "
t_intro, t_open, t_look
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
