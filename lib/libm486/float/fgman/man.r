.bp
.he 'FGMAN (libc)'TROPIX: Manual de Refer�ncia'FGMAN (libc)'
.fo 'Escrito em 11.03.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Manipula��o de partes de um n�mero de ponto flutuante:
.sp
.wo "fgman    -"
obt�m o valor da mantissa
.br
.wo "fgexp    -"
obt�m o valor do expoente
.br
.wo "faexp    -"
soma um valor ao expoente
.br
.wo "fgint    -"
obt�m a parte inteira
.br
.wo "fgfra    -"
obt�m a parte fracion�ria
.br
.wo "fhuge    -"
retorna o maior n�mero poss�vel antes de infinito
.br
.wo "HUGE_VAL -"
o maior n�mero poss�vel antes de infinito
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <math.h>

double	fgman (double x);
int	fgexp (double x);
double	faexp (int e, double x);
double	fgint (double x);
double	fgfra (double x);
double	fhuge (void);

extern double	HUGE_VAL;
.)l

.in
.sp
.b DESCRI��O
.in 5
Todos os n�meros de ponto flutuante n�o nulos podem ser escritos
sem ambiguidade como
.wo "(m * (2 ** n))" 
onde "m" � a mantissa (significando), cujo valor absoluto � maior ou igual
a 1.0 e menor que 2.0, e o expoente "n" � um n�mero inteiro. A escolha
destes valores segue a representa��o de n�meros em ponto flutuante
padronizada pelo IEEE (Institute of Electrical and Electronics
Engineers).

.sp
A fun��o "fgman" retorna a mantissa de "x".

.sp
A fun��o "fgexp" retorna o expoente de "x".

.sp
A fun��o "faexp" retorna um valor que � o do argumento "x"
a cujo expoente � somado o valor de "e".
Isto equivale a uma multiplica��o ou divis�o de "x" por uma pot�ncia de 2.

.sp
A fun��o "fgint" retorna a parte inteira de "x".

.sp
A fun��o "fgfra" retorna a parte fracion�ria de "x".

.sp
A fun��o "fhuge" retorna HUGE_VAL (veja abaixo),
o maior n�mero poss�vel antes de infinito.

.sp
A vari�vel externa HUGE_VAL cont�m o maior n�mero poss�vel
antes de infinito. Esta valor � aproximadamente "1.79769...E+308".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Se os argumentos da fun��o "faexp" causarem "overflow",
ela retorna HUGE_VAL ou -HUGE_VAL, dependendo do sinal de "x".
Se eles causarem "underflow", ela retorna ZERO.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
fexcep, frexp
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
