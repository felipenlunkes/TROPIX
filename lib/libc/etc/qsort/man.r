.bp 1
.he 'QSORT (libc)'TROPIX: Manual de Refer�ncia'QSORT (libc)'
.fo 'Atualizado em 23.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
qsort - fun��o para ordena��o r�pida

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

void qsort (void *base, size_t nel, size_t size,
		int (*comp) (const void *p1, const void *p2));
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "qsort" ordena o vetor de "nel" elementos 
de "size" bytes cada, apontado por "base".

.sp
O vetor � ordenado em ordem ascendente de acordo com a fun��o
de compara��o "comp" (que deve ser fornecida pelo usu�rio).
Esta fun��o recebe ponteiros para 2 elementos do vetor, "p1" e "p2",
e deve retornar um valor negativo, nulo ou positivo caso "p1"
seja considerado menor do que, igual ou maior do que "p2".

.sp
Se 2 elementos s�o considerados iguais por "comp", a sua ordem 
no vetor ordenado � indefinida.

.in
.sp
.b OBSERVA��ES
.in 5
Esta fun��o foi implementada usando-se o algoritmo 2.21
da refer�ncia dada abaixo, com algumas otimiza��es para se
manter a pilha de tamanho m�nimo e n�o usar recurs�o para
ordenar apenas dois elementos.

.sp
A fun��o n�o requer qualquer �rea adicional de mem�ria pois os
registros s�o intercambiados usando-se a mesma �rea de
mem�ria onde os registros est�o armazenados.

.sp
A fun��o "qtsort" (libc) realiza uma ordena��o utilizando
movimenta��o de ponteiros, e � mais r�pida do que "qsort"
(embora precise de mais mem�ria).

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
