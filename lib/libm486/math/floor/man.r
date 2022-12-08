.bp
.he 'FLOOR (libc)'TROPIX: Manual de Refer�ncia'FLOOR (libc)'
.fo 'Escrito em 11.03.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Fun��es matem�ticas auxiliares:
.sp
.wo "floor -"
valor �nfimo
.br
.wo "ceil  -"
valor supremo
.br
.wo "fmod  -"
resto da divis�o
.br
.wo "fabs  -"
valor absoluto
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <math.h>

double	floor (double x);
double	ceil (double x);
double	fmod (double x, double y);
double	fabs (double x);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "floor" retorna o maior valor inteiro (formato flutuante)
n�o maior que o valor de "x".

.sp
A fun��o "ceil" retorna o menor valor inteiro (formato flutuante)
n�o menor que o valor de "x".

.sp
A fun��o "fmod" retorna o resto da divis�o (formato flutuante) de
"x" por "y", ou, ent�o, retorna um valor nulo se "y" � zero ou se
a divis�o de "x" por "y" der um resultado maior que HUGE_VAL
(maior valor poss�vel de ser representado).
Nos casos normais, a fun��o retorna um valor "f" que tem o mesmo
sinal de "x" e tal que
.wo "{ x = i * y + f }"
para algum inteiro "i" e tal que o valor absoluto de "f" seja
menor que o valor absoluto de "y".

.sp
A fun��o "fabs" retorna o valor absoluto de "x".

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
.b ESTADO
.in 5
Efetivo.

.in
