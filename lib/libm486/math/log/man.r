.bp
.he 'LOG (libc)'TROPIX: Manual de Refer�ncia'LOG (libc)'
.fo 'Escrito em 11.03.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Fun��o logaritmo:
.sp
.wo "log    -"
logaritmo Neperiano (natural)
.br
.wo "log2   -"
logaritmo na base 2
.br
.wo "log10  -"
logaritmo na base 10
.br
.wo "logb   -"
logaritmo na base dada como argumento
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <math.h>

double log (double x);
double log2 (double x);
double log10 (double x);
double logb (double base, double x);
.)l

.in
.sp
.b DESCRI��O
.in 5
As fun��es "log", "log2" e "log10" retornam, respectivamente,
o logaritmo do argumento "x" nas bases "e" (2.718...), 2.0 e 10.0.

.sp
A fun��o "logb" retorna o logaritmo de "x" na base dada pelo
argumento "base".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Quando o argumento "x" for negativo ou nulo
estas fun��es retornam o valor HUGE_VAL (maior n�mero poss�vel).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
fexcep, exp
.br

.in
.sp
.b
REFER�NCIAS
.r
.in 5
Intel Corporation, "Intel486 Microprocessor Family Programmer's
Reference Manual", 1993.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
