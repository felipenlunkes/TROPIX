.bp
.he 'ASIN (libc)'TROPIX: Manual de Refer�ncia'ASIN (libc)'
.fo 'Escrito em 11.03.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Fun��es trigonom�tricas inversas:
.sp
.wo "asin  -"
arco-seno
.br
.wo "acos  -"
arco-cosseno
.br
.wo "atan  -"
arco-tangente
.br
.wo "atan2 -"
arco-tangente dados os catetos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <math.h>

double	asin (double x);
double	acos (double x);
double	atan (double x);
double	atan2 (double y, double x);
.)l

.in
.sp
.b DESCRI��O
.in 5
As fun��es "asin" e "acos" retornam, respectivamente,
em radianos, o arco-seno e o arco-cosseno do argumento "x".
O valor de "x" deve estar no intervalo [-1, +1].

.sp
A fun��o "atan" retorna em radianos o arco-tangente do argumento "x".

.sp
A fun��o "atan2" retorna o arco-tangente da raz�o "y/x"
usando os sinais de "y" e "x" para determinar o quadrante.

.in
.sp
.b
VALORES DE RETORNO
.r
.in 5
As fun��es "asin" e "atan" retornam valores no intervalo [-PI/2, PI/2].

.sp
A fun��o "acos" retorna valores no intervalo [0, PI].

.sp
A fun��o "atan2" retorna valores no intervalo [-PI, PI].

.sp
As fun��es "asin" e "acos" retornam um valor NULO quando
o valor de "x" est� fora do intervalo [-1, +1].
A fun��o "atan2" tamb�m retona um valor NULO quando ambos argumentos
s�o NULOs.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
fexcep, sin
.br

.in
.sp
.b
REFER�NCIAS
.r
.in 5
Intel Corporation, "Intel486 Microprocessor Family Programmer's
Reference Manual", 1993.

.sp
.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
