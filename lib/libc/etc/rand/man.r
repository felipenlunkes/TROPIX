.bp 1
.he 'RAND (libc)'TROPIX: Manual de Refer�ncia'RAND (libc)'
.fo 'Atualizado em 19.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Gerador de n�meros aleat�rios:
.sp
.wo "srand -"
inicializa o gerador
.br
.wo "rand  -"
gera um n�mero
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

long	rand (void);
void	srand (long seed);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "rand" gera n�meros pseudo-aleat�rios entre
0 e 2147483647 (2 ** 31 - 1).

.sp
A fun��o "srand" inicializa o gerador com a semente "seed",
que � utilizado como valor inicial para a gera��o da seq��ncia
dos n�meros pseudo-aleat�rios.
Se "srand" n�o for chamada, � utilizado o valor "1" como semente inicial.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A cada chamada, a fun��o "rand" devolve o pr�ximo
n�mero pseudo-aleat�rio.

.in
.sp
.b OBSERVA��O
.in 5
O m�todo usado para a gera��o dos n�meros � o
conhecido m�todo congruencial linear onde o multiplicador
� 314159269 e o incremento � 453806245.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
(libc): getrand

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
