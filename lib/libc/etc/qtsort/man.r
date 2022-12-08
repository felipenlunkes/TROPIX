.bp 1
.he 'QTSORT (libc)'TROPIX: Manual de Refer�ncia'QTSORT (libc)'
.fo 'Atualizado em 23.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
qsort - fun��o para ordena��o r�pida de ponteiros

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

void qtsort (void *base[], size_t nel,
		int (*comp) (const void *p1, const void *p2));
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "qtsort" ordena "nel" registros
dados atrav�s de um vetor de apontadores cujo endere�o � "base".
Cada elemento do vetor aponta para um dos registros a serem ordenados. 

.sp
O vetor � ordenado em ordem ascendente de acordo com a fun��o
de compara��o "comp" (que deve ser fornecida pelo usu�rio).
Esta fun��o recebe ponteiros para 2 registros, "p1" e "p2",
e deve retornar um valor negativo, nulo ou positivo caso "p1"
seja considerado menor do que, igual ou maior do que "p2".

.sp
Se 2 registros s�o considerados iguais por "comp", a sua ordem 
no vetor de ponteiros ordenado � indefinida.

.sp
Esta fun��o movimenta apenas os apontadores, ao inv�s dos registros.
Desta forma, a ordena��o � mais r�pida e os registros
podem ter um tamanho vari�vel.

.in
.sp
.b OBSERVA��ES
.in 5
Esta fun��o foi implementada usando-se o algoritmo 2.21
da refer�ncia dada abaixo, com algumas otimiza��es para se
manter a pilha de tamanho m�nimo e n�o usar recurs�o para
ordenar apenas dois elementos.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sort
.br
.wo "(libc):"
qtsort
.br

.in
.sp
.b
REFER�NCIA
.r
.in 5
Wirth, N., "Algorithms + Data Structures = Programs", Prentice-Hall,
1976.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
