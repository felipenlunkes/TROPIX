.bp
.he 'SIN (libc)'TROPIX: Manual de Refer�ncia'SIN (libc)'
.fo 'Escrito em 11.03.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Fun��es trigonom�tricas diretas:
.sp
.wo "sin -"
seno
.br
.wo "cos -"
cosseno
.br
.wo "tan -"
tangente
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <math.h>

double	sin (double x);
double	cos (double x);
double	tan (double x);
.)l

.in
.sp
.b DESCRI��O
.in 5
As fun��es "sin", "cos" e "tan" retornam, respectivamente,
o seno, cosseno e a tangente do argumento "x" dado em
radianos.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
As fun��es "sin" de "cos" devolvem valores no intervalo
.wo '[-1, +1].'

.in
.sp
.b OBSERVA��O
.in 5
O valor calculado pelas fun��es "sin" e "cos" perde precis�o � medida que
o valor absoluto do argumento "x" cresce. Nos casos de valores de "x"
muito grandes, o resultado pode ser incorreto. Veja "Refer�ncias" abaixo.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
fexcep, asin
.br

.in
.sp
.(t
.b
REFER�NCIAS
.r
.in 5
Intel Corporation, "Intel486 Microprocessor Family Programmer's
Reference Manual", 1993.
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
