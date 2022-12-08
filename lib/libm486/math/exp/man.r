.bp
.he 'EXP (libc)'TROPIX: Manual de Refer�ncia'EXP (libc)'
.fo 'Escrito em 11.03.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Fun��o exponencial:
.sp
.wo "exp   -"
exponencial na base "e"
.br
.wo "exp2  -"
exponencial na base 2
.br
.wo "exp10 -"
exponencial na base 10
.br
.wo "expb  -"
exponencial na base dada como argumento
.br
.wo "pow   -"
exponencial na base dada como argumento
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <math.h>

double exp (double x);
double exp2 (double x);
double exp10 (double x);
double expb (double base, double x);
double pow (double base, double x);
.)l

.in
.sp
.b DESCRI��O
.in 5
As fun��es "exp", "exp2" e "exp10" retornam, respectivamente,
o valor de "e" (2.718...), 2.0 e 10.0 elevados � pot�ncia dada
por "x".

.sp
As fun��es "expb" e "pow" retornam o valor de "base"
elevado � pot�ncia dada por "x".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Quando o valor absoluto do resultado correto
� maior que HUGE_VAL (maior valor poss�vel
de ser representado), as fun��es retornam o valor HUGE_VAL.

.sp
Quando o valor do resultado correto � menor que o menor valor poss�vel de
ser representado com n�meros normalizados ("underflow"), o resultado
obtido � um n�mero n�o normalizado, embora haja perda de precis�o.
No caso extremo, quando h� total perda de precis�o,
as fun��es retornam o valor ZERO.

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
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
fexcep, log
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
