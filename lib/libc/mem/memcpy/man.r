.bp 1
.he 'MEM (libc)'TROPIX: Manual de Refer�ncia' MEM (libc)'
.fo 'Atualizado em 06.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Opera��es com �reas de mem�ria: 
.sp
.wo "memcpy   -"
copia uma �rea de mem�ria
.br
.wo "memmove  -"
c�pia otimizada de uma �rea de mem�ria
.br
.wo "memccpy  -"
copia uma �rea para outra at� encontrar caractere
.br
.wo "memeq    -"
testa a igualdade de duas �reas de mem�ria
.br
.wo "memcmp   -"
compara duas �reas de mem�ria
.br
.wo "memtcmp  -"
compara duas �reas de mem�ria  usando uma tabela
.br
.wo "memttcmp -"
compara duas �reas de mem�ria usando duas tabelas
.br
.wo "memchr   -"
acha a 1a. ocorr�ncia de um caractere
.br
.wo "memset   -"
preenche uma �rea de mem�ria com um caractere
.br
.wo "memsetw  -"
preenche um vetor de palavras com um valor
.br
.wo "memsetl  -"
preenche um vetor de longos com um valor
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <string.h>

void	*memcpy (void *a1, const void *a2, size_t n);
void	*memmove (void *a1, const void *a2, size_t n);
void	*memccpy (void *a1, const void *a2, int c, size_t n);
int	memeq   (const void *a1, const void *a2, size_t n);
int	memcmp (const void *a1, const void *a2, size_t n);
int	memtcmp (const void *a1, const void *a2, size_t n,
				const char tb[]);
int	memttcmp (const void *a1, const void *a2, size_t n,
				const char tb[], const char tba[]);
void	*memchr (const void *a, int c, size_t n);
void	*memset (void *a, int c, size_t n);
void	*memsetw (void *a, int c, size_t nelem);
void	*memsetl (void *a, int c, size_t nelem);
.)l
.sp

.in
.sp
.b DESCRI��O
.in 5
Estas fun��es s�o indicadas para uso com �reas de mem�ria
cujos tamanhos s�o conhecidos a priori.
N�o � necess�rio que as �reas sejam terminadas com caracteres
NULOs. 
Os parametros "a", "a1" e "a2" s�o ponteiros para �reas de mem�ria.

.sp
As compara��es realizadas pelas fun��es "memeq" e "memcmp"
utilizam o pr�prio c�digo de representa��o dos caracteres nas �reas,
o que funciona corretamente desde que as cadeias
n�o contenham letras acentuadas (isto �, se as cadeias contiverem
apenas caracteres ASCII).
Se as cadeias contiverem letras acentuadas (isto �, utilizarem
caracteres da tabela ISO), devem ser utilizadas as fun��es
"memtcmp" e "memttcmp" com a tabela "cmpisotb".

.sp
A fun��o "memcpy" copia "n" caracteres da �rea de mem�ria "a2"
para "a1".
A fun��o retorna o valor de "a1".

.sp
A fun��o "memmove" � an�loga � fun��o "memcpy", mas, se for poss�vel,
copia a �rea de mem�ria de palavra em palavra (4 bytes),
o que � bem mais r�pido.
Al�m disto, ela copia de baixo para cima ou vice-versa, para
impedir a destrui��o de informa��o no caso de �reas superpostas.
A fun��o retorna o valor de "a1".

.sp
A fun��o "memccpy" copia caracteres da �rea "a2" para "a1",
at� encontrar o caractere "c" ou transferir "n" caracteres.
A fun��o retorna um ponteiro para o caractere seguinte � c�pia de "c"
em "a1", ou um ponteiro NULO caso "c" n�o foi encontrado nos "n"
primeiros caracteres de "a2".

.sp
A fun��o "memeq" compara duas �reas de mem�ria de "n" caracteres
e retorna 1 se forem iguais e 0 se diferentes.

.sp
A fun��o "memcmp" compara as duas �reas de mem�ria de "n" caracteres,
e retorna um inteiro igual a -1, 0 ou 1 de acordo se "a1" �
lexicograficamente menor, igual ou maior do que "a2".

.sp
A fun��o "memtcmp" compara inicialmente as duas �reas de mem�ria
de "n" caracteres atrav�s da tabela de convers�o "tb" dada;
se a compara��o der diferente, retorna -1 ou 1 para os casos de menor ou maior.
Se a compara��o der igual, realiza uma segunda compara��o, baseada no
c�digo original de representa��o dos caracteres.
Existem tabelas para caracteres em c�digo ISO, para mapeamento de letras
min�sculas em mai�sculas e outras (veja "cmptb" (libc)).

.sp
A fun��o "memttcmp" � similar � "memtcmp"
utilizando, por�m, uma tabela de convers�o adicional "tba" para resolver
os casos de igualdade obtidos durante o uso da primeira tabela.
Se a tabela adicional n�o for dada (isto �, se for dado um endere�o NULO),
retorna 0 em caso de igualdade.

.sp
A fun��o "memchr" retorna um apontador para a primeira ocorr�ncia do
caractere "c" nos primeiros "n" caracteres da �rea "a", ou
um apontador NULO, caso ele n�o ocorra nesta �rea.

.sp
A fun��o "memset" preenche os "n" caracteres da �rea de mem�ria "a",
com o caractere "c".
A fun��o retorna o valor de "a".

.sp
A fun��o "memsetw" preenche o vetor de palavras curtas "a" (de 16 bites),
contendo "nelem" elementos, com o valor "c".
A fun��o retorna o valor de "a".

.sp
A fun��o "memsetl" preenche o vetor de palavras longas "a" (de 32 bites),
contendo "nelem" elementos, com o valor "c".
A fun��o retorna o valor de "a".

.in
.sp
.b
OBSERVA��ES
.r
.in 5
As fun��es "memcpy", "memmove", "memccpy", "memset", "memsetw"
e "memsetl" alteram as �reas "a1"/"a"; elas n�o verificam se
ultrapassam o seu espa�o alocado.

.sp
Se as c�pias forem entre objetos superpostos (exceto para "memmove"),
o resultado ser� imprevis�vel. 

.sp
Repare que nas fun��es "memsetw" e "memsetl", o tamanho � dado
pelo n�mero de palavras curtas/longas, e n�o pelo n�mero de bytes.

.in
.sp
.(t
.b
VEJA TAMBEM
.r
.in 5
.wo "(libc):"
strcpy, strcmp, strtok, cmptb
.br
.wo "(fmt): "
ascii, iso
.)t
.in

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
