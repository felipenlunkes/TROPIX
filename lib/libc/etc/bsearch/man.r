.bp
.he 'BSEARCH (libc)'TROPIX: Manual de Refer�ncia'BSEARCH (libc)'
.fo 'Atualizado em 09.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "bsearch -"
busca bin�ria
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#define <stdlib.h>

void *bsearch (const void *key, const void *base, size_t n,
	size_t size, int (*compar) (const void *, const void *));
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "bsearch" realiza uma busca bin�ria em um vetor de "n" objetos,
procurando por um membro correspondente ao objeto apontado por "key".
A correspond�ncia � decidida pela fun��o de compara��o apontada por "compar".
O in�cio do vetor � apontado por "base", e o tamanho de cada membro
� dado por "size".

.sp
O vetor deve estar ordenado em ordem ascendente, de acordo com a fun��o
de compara��o. Esta fun��o � chamada com dois
argumentos que apontam para o objeto "key" e um membro do vetor, nesta
ordem. Ela deve retornar um inteiro negativo, nulo ou positivo se o objeto
"key" �, respectivamente, menor, igual ou maior do que o membro do vetor.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Se houver um membro do vetor aceito por "compar", "bsearch" devolve
um ponteiro para este membro.
Em caso contr�rio, devolve um ponteiro NULO.

.in
.sp
.b OBSERVA��O
.in 5
Se houverem membros repetidos, isto �, se mais de um membro do
vetor for aceito por "compar", � imprevis�vel qual deles ser� devolvido.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
qsort, qtsort
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
