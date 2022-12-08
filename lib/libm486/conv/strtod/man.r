.bp 1
.he 'STRTOD (libc)'TROPIX: Manual de Refer�ncia'STRTOD (libc)'
.fo 'Escrito em 10.03.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Convers�o de cadeias em n�meros de ponto flutuante:
.sp
.wo "strtod  -"
com indicador para o final do n�mero
.br
.wo "atof    -"
sem indicador
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

double		strtod (const char *str, const char **ptr);
double		atof (const char *str);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "strtod" tenta interpretar a cadeia de caracteres apontada
por "str" como um n�mero de ponto flutuante, e retorna o seu valor
convertido para "double".

.bc	/*************************************/
A fun��o "strtod" retorna como um "double" o valor flutuante
representado pela cadeia de caracteres apontada por "str".
.ec	/*************************************/

A cadeia � processada at� o primeiro caracter inconsistente
com a sintaxe de n�meros flutuantes (veja abaixo). Caracteres brancos e
tabula��es (<ht>) antes do in�cio do n�mero s�o ignorados.

.sp
Se "ptr" for um ponteiro n�o NULO, um ponteiro para o primeiro caracter
n�o reconhecido � armazenado na posi��o apontada por "ptr". 
Se nenhum n�mero de ponto flutuante foi reconhecido,  a
fun��o  devolve  "0.0",  e a posi��o apontada por "ptr" cont�m
"str".

.sp
A fun��o "atof" � equivalente � "strtod", com a exce��o de que
n�o  devolve  um  ponteiro  para  o  primeiro   caracter   n�o
reconhecido.

.sp
A sintaxe de n�meros flutuantes aceita consiste de um sinal
("+" ou "-", opcional), uma mantissa e uma parte de expoente (opcional).
A mantissa pode ter a forma "ddd", "ddd.ddd", "ddd." ou ".ddd",
onde "d" s�o d�gitos decimais.
A parte de expoente consiste de um caractere "e" ou "E" seguido de
um sinal ("+" ou "-", opcional) e de um expoente decimal.

.in
.sp
.b OBSERVA��ES
.in 5
Em  caso  de  "overflow",  as  fun��es  devolvem  +HUGE_VAL ou
-HUGE_VAL.
.sp
Em caso de "underflow", as fun��es devolvem "0.0".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
scanf, strtol
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
