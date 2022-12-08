.bp
.he 'ABS (libc)'TROPIX: Manual de Refer�ncia'ABS (libc)'
.fo 'Atualizado em 08.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Valor absoluto:
.sp
.wo "abs  -"
de um inteiro
.br
.wo "labs -"
de um inteiro longo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

int	abs (int j);
long	labs (long j);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "abs" calcula o valor absoluto de um inteiro "j".

.sp
A fun��o "labs" � an�loga � "abs", exceto que o argumento e o valor de
retorno tem o tipo "long".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
As fun��es devolvem o valor absoluto do argumento.

.in
.sp
.b OBSERVA��O
.in 5
Ambas fun��es obt�m o valor correto exceto para o n�mero mais negativo
(-2147483648) cujo valor absoluto n�o tem representa��o.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
fabs
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
