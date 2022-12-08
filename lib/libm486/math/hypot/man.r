.bp
.he 'HYPOT (libc)'TROPIX: Manual de Refer�ncia'HYPOT (libc)'
.fo 'Escrito em 11.03.96'Vers�o 2.3'Pag. %'

.b NOME
.in 5
.sp
.wo "hypot -"
dist�ncia Euclideana
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <math.h>

double	hypot (double x, double y);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "hypot" retorna o valor
.wo "{ sqrt ((x * x) + (y * y)) }"
tomando cuidado para n�o causar "overflow" desnecess�rio
durante o c�lculo.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Quando o valor absoluto do resultado � maior que
HUGE_VAL (maior n�mero poss�vel de ser representado)
a fun��o retorna o valor HUGE_VAL.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
fexcep, sqrt
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
