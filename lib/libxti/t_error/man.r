.bp
.he 'T_ERROR (xti)'TROPIX: Manual de Refer�ncia'T_ERROR (xti)'
.fo 'Escrito em 06.08.92'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_error -"
imprime uma mensagem de erro
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>
#include <errno.h>

int t_error (const char *errmsg);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_error" escreve uma mensagem na sa�da de erro padr�o
("stderr"), descrevendo o �ltimo erro ocorrido durante uma
chamada a uma fun��o do sistema de transporte.

.sp
.(l
	    +--------------------+------------+------------+
	    |   Argumentos	 | Na chamada | No retorno |
	    +--------------------+------------+------------+
	    | errmsg		 |     x      |     /      |
	    +--------------------+------------+------------+
.)l

.sp
Em primeiro lugar � impressa  a cadeia
"errmsg" (que em geral cont�m o nome do programa), seguida de
":" (dois pontos), um <sp>, a mensagem de erro e um <nl>.
O n�mero do erro � obtido da vari�vel
externa "t_errno", que recebe o n�mero do erro quando este ocorre.

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Nesta implementa��o, os erros da interface de transporte
est�o unificados com os erros do sistema operacional, de tal
modo que a vari�vel "t_errno" � id�ntica � vari�vel "errno",
e a fun��o "t_error" � id�ntica � fun��o "perror" (libc).
Isto j� est� definido no arquivo <xti.h>, e portanto � transparente
para o usu�rio.

.sp
Como conseq��ncias desta unifica��o, o erro [TSYSERR] nunca ocorre
e a fun��o "strerror" (libc) pode ser usada para facilitar
a formata��o das mensagens de erro.

.sp
Para facilitar a impress�o de diagn�sticos,
nesta implementa��o est� dispon�vel a fun��o "t_strevent", que
fornece uma cadeia contendo a descri��o de um evento.

.in
.sp
.b DIAGN�STICOS
.in 5
A fun��o "t_error" imprime as mensagens
"Erro Desconhecido" ou "Erro ZERO", caso a vari�vel "t_errno" contenha
um n�mero de erro inv�lido ou NOERR (zero), respectivamente.

.in
.sp
.b OBSERVA��O
.in 5
A vari�vel "t_errno" n�o � zerada quando � feita uma chamada correta
ao sistema de transporte.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
perror, strerror
.br
.wo "(xti): "
t_intro, t_look, t_strevent
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
