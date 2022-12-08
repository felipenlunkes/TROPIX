.bp 1
.he 'MKTEMP (libc)'TROPIX: Manual de Refer�ncia'MKTEMP (libc)'
.fo 'Atualizado em 22.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
mktemp - gera um nome para um arquivo tempor�rio

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

char	*mktemp (const char *pattern);
.)l

.in
.sp
.b DESCRI��O
.in 5
O objetivo de "mktemp" � gerar uma cadeia que possa ser usada
como o nome de um arquivo tempor�rio. 

.sp
O argumento "pattern" da fun��o deve ser o ponteiro para uma cadeia
de caracteres terminada por seis caracteres "X", na forma "......XXXXXX".
A fun��o "mktemp" copia a cadeia e substitui os seis caracteres "X"
por uma configura��o de caracteres tal que o nome gerado n�o coincida
com o de um arquivo j� existente.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A rotina "mktemp" devolve um ponteiro para uma cadeia que pode ser usada
como o nome de um arquivo.

.in
.sp
.b DIAGN�STICOS
.in 5
Se o padr�o dado n�o for v�lido, ou "mktemp" n�o conseguir um nome
que corresponda a um arquivo inexistente, devolve um ponteiro NULO.

.in
.sp
.b OBSERVA��ES
.in 5
A fun��o "mktemp" copia o padr�o dado para uma �rea est�tica,
de tal modo que o padr�o dado PODE estar
situado na regi�o "text" de um programa reentrante,
ou ent�o em uma
�rea autom�tica, que ir� ser liberada quando a fun��o
que chamou "mktemp" retornar. 

.sp
Repare que a cadeia de caracteres dada (apontada por "pattern")
N�O � modificada.

.sp
A rotina "mktemp" usa o n�mero do processo na identifica��o
do arquivo tempor�rio.

.sp
Em um mesmo processo, "mktemp" s� consegue gerar 26 nomes
distintos a partir de um mesmo padr�o.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys):  "
getpid
.br
.wo "(libc): "
tmpfile
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
