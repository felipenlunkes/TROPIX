.bp
.he 'SQRT (libc)'TROPIX: Manual de Refer�ncia'SQRT (libc)'
.fo 'Escrito em 11.03.96'Vers�o 2.3'Pag. %'

.b NOME
.in 5
.wo "sqrt -"
raiz quadrada
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <math.h>

double	sqrt (double x);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "sqrt" retorna o valor n�o negativo da
raiz quadrada do argumento "x".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Quando o valor de "x" � negativo, a fun��o "sqrt" retorna um
valor nulo.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
fexcep
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
