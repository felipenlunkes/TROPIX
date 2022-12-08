.bp
.he 'FREXP (libc)'TROPIX: Manual de Refer�ncia'FREXP (libc)'
.fo 'Escrito em 25.02.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Manipula��o de partes de um n�mero de ponto flutuante:
.sp
.wo "frexp -"
obt�m mantissa e expoente
.br
.wo "ldexp -"
soma valor ao expoente
.br
.wo "modf  -"
obt�m parte inteira e fracion�ria
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <math.h>

double	frexp (double x, int *pe);
double	ldexp (double x, int e);
double	modf (double x, double *pint);
.)l

.in
.sp
.b DESCRI��O
.in 5
Todos os n�meros de ponto flutuante n�o nulos podem ser escritos
sem ambiguidade como
.wo "(m * (2 ** n))" 
onde "m" � a fra��o (mantissa), cujo valor absoluto � maior ou igual
a 1.0 e menor que 2.0, e "n" � o expoente inteiro. A escolha destes
valores segue a representa��o dos n�meros em ponto flutuante
padronizada pelo IEEE (Institute of Electrical and Electronics
Engineers).
foram escolhidos

.sp
A fun��o "frexp" retorna a mantissa de "x" e armazena
o expoente inteiro de "x" no local apontado pelo ponteiro "pe".

.sp
A fun��o "ldexp" retorna um valor que � o de "x"
com seu expoente somado ao valor de "e". Equivale a uma
multiplica��o ou divis�o de "x" por uma pot�ncia de 2.

.sp
A fun��o "modf" retorna a parte fracion�ria de "x"
(com o mesmo sinal de "x") e armazena a parte inteira de "x"
(como um "double") no local apontado pelo ponteiro "pint".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Se o resultado da fun��o "ldexp" causar "overflow",
ela retorna HUGE_VAL ou -HUGE_VAL conforme o sinal de "x".
Se ele causar "underflow", retorna ZERO.

.in
.sp
.b OBSERVA��ES
.in 5
Estas fun��es foram mantidas no TROPIX simplesmente por
compatibilidade com outros sistemas operacionais. No TROPIX somente s�o
usadas as fun��es contidas no t�tulo "fgman".
.sp
Verifique que mantissa e expoente seguem a representa��o de n�meros em
ponto flutuante padronizada pelo IEEE. As fun��es "frexp" e "modf" de
antigos sistemas operacionais s�o anteriores a esta padroniza��o e
representam a mantissa entre 0.5 e 1.0. Na improv�vel necessidade de
se transformar os novos valores nos antigos, basta dividir a mantissa
por 2 e somar 1 ao expoente.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
fexcep, fgman
.br

.sp
.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
