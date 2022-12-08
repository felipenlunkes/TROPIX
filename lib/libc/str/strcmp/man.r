.bp 1
.he 'STRCMP (libc)'TROPIX: Manual de Refer�ncia' STRCMP (libc)'
.fo 'Atualizado em 07.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Compara��o de cadeias:
.sp
.wo "streq     -"
testa a igualdade de duas cadeias
.br
.wo "strcmp    -"
compara duas cadeias
.br
.wo "strrcmp   -"
compara duas cadeias retornando o valor invertido
.br
.wo "stricmp   -"
compara duas cadeias ISO
.br
.wo "strircmp  -"
compara duas cadeias ISO ret. o valor invertido
.br
.wo "strncmp   -"
compara no m�ximo "n" caracteres de duas cadeias
.br
.wo "strtcmp   -"
compara duas cadeias usando uma tabela
.br
.wo "strntcmp  -"
compara no maximo "n" caracteres usando uma tabela
.br
.wo "strttcmp  -"
compara duas cadeias usando duas tabelas
.br
.wo "strnttcmp -"
compara no m�x. "n" carac. usando duas tabelas

.in
.sp
.b SINTAXE
.in 5
.(l
#include <string.h>

int	streq (const char *s1, const char *s2);
int	strcmp (const char *s1, const char *s2);
int	strrcmp (const char *s1, const char *s2);
int	stricmp (const char *s1, const char *s2);
int	strircmp (const char *s1, const char *s2);
int	strncmp (const char *s1, const char *s2, size_t n);
int	strtcmp (const char *s1, const char *s2,
			const char tb[]);
int	strntcmp (const char *s1, const char *s2,
			size_t n, const char tb[]);
int	strttcmp (const char *s1, const char *s2,
			const char tb[], const char tba[]);
int	strnttcmp (const char *s1, const char *s2,
		      size_t n, const char tb[], const char tba[]);
.)l

.in
.sp
.b DESCRI��O
.in 5
Os parametros  "s1" e "s2" s�o ponteiros para cadeias de caracteres
terminadas por NULOs.
Para a compara��o de �reas sem NULOs no final, veja "memcmp" (libc).

.sp
As compara��es realizadas pelas fun��es "streq", "strcmp",
"strrcmp" e "strncmp" utilizam o pr�prio c�digo de representa��o
dos caracteres nas cadeias, o que funciona corretamente desde que as cadeias
n�o contenham letras acentuadas (isto �, as cadeias contenham
apenas caracteres ASCII).
Se as cadeias contiverem letras acentuadas (isto �, utilizarem
caracteres da tabela ISO), devem ser utilizadas as fun��es
"stricmp" e "strircmp".

.sp
A fun��o "streq" compara duas cadeias e retorna 1 se forem
iguais e 0 se diferentes.

.sp
A fun��o "strcmp" compara duas cadeias e retorna um inteiro igual
a -1, 0 ou 1 de acordo se "s1" � lexicograficamente menor, igual ou
maior do que "s2".

.sp
A fun��o "strrcmp" � semelhante � "strcmp", mas devolve o resultado
reverso, isto �, retorna 1, 0 e -1 para os casos de menor, igual ou maior.

.sp
A fun��o "stricmp" compara inicialmente as duas cadeias atrav�s
de uma tabela que mapeia as vogais acentuadas em n�o acentuadas, e o
"�" em "c" (tabela ISO); se a compara��o der diferente,
retorna -1 ou 1 para os casos de menor ou maior.
Se a compara��o der igual, realiza uma segunda compara��o, baseada no
c�digo original de representa��o dos caracteres (como "strcmp").

.sp
A fun��o "strircmp" � semelhante � "stricmp", mas devolve o resultado
reverso, isto �, retorna 1, 0 e -1 para os casos de menor, igual ou maior.

.sp
A fun��o "strncmp" � similar a "strcmp" mas compara no m�ximo
"n" caracteres.

.sp
A fun��o "strtcmp" compara inicialmente as duas cadeias atrav�s
da tabela de convers�o "tb" dada; se a compara��o der diferente,
retorna -1 ou 1 para os casos de menor ou maior.
Se a compara��o der igual, realiza uma segunda compara��o, baseada no
c�digo original de representa��o dos caracteres.
Existem tabelas para caracteres em c�digo ISO, para mapeamento de letras
min�sculas em mai�sculas e outras (veja "cmptb" (libc)).

.sp
A fun��o "strntcmp" � similar � "strtcmp" comparando, por�m, no m�ximo
"n" caracteres.

.sp
A fun��o "strttcmp" � similar � "strtcmp"
utilizando, por�m, uma tabela de convers�o adicional "tba" para resolver
os casos de igualdade obtidos pelo uso da primeira tabela.
Se a tabela adicional n�o for dada (isto �, se for dado um endere�o NULO),
retorna 0 em caso de igualdade obtido pelo uso da primeira tabela.

.sp
A fun��o "strnttcmp" � similar � "strttcmp"
comparando, por�m, no m�ximo "n" caracteres.

.in
.sp
.(t
.b
VEJA TAMBEM
.r
.in 5
.wo "(cmd): "
sort
.br
.wo "(libc):"
strcpy, strtok, memcmp
.br
.wo "(fmt): "
ascii, iso
.br
.in
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
