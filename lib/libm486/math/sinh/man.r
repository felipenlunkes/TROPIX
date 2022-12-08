.bp
.he 'SINH (libc)'TROPIX: Manual de Refer�ncia'SINH (libc)'
.fo 'Escrito em 11.03.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Fun��es hiperb�licas:
.sp
.wo "sinh -"
seno hiperb�lico
.br
.wo "cosh -"
cosseno hiperb�lico
.br
.wo "tanh -"
tangente hiperb�lica
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <math.h>

double	sinh (double x);
double	cosh (double x);
double	tanh (double x);
.)l

.in
.sp
.b DESCRI��O
.in 5
As fun��es "sinh", "cosh" e "tanh" retornam, respectivamente,
o seno, cosseno e a tangente hiperb�licos de "x".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Quando o valor absoluto do resultado correto � maior que
HUGE_VAL (maior n�mero poss�vel de ser representado)
as fun��es "sinh" e "cosh" retornam HUGE_VAL,
exceto a fun��o "sinh", que retorna -HUGE_VAL se "x" � negativo.

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
.b ESTADO
.in 5
Efetivo.

.in
