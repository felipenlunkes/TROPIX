.bp 1
.he 'STRTOK (libc)'TROPIX: Manual de Refer�ncia' STRTOK(libc)'
.fo 'Atualizado em 11.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Manipula��es diversas em cadeias:
.sp
.wo "strchr   -"
acha a 1a. ocorr�ncia de um caractere em uma cadeia
.br
.wo "strrchr  -"
acha a �ltima ocorr�ncia de um carac. em uma cadeia
.br
.wo "strend   -"
acha a posi��o do nulo final de uma cadeia
.br
.wo "strpbrk  -"
acha a ocorr�ncia de um caractere de outra cadeia
.br
.wo "strspn   -"
d� o no. de carac. que constam de outra cadeia
.br
.wo "strcspn  -"
d� o no. de carac. que n�o constam de outra cadeia
.br
.wo "strtok   -"
acha um "token" em uma cadeia
.br
.wo "strfield -"
acha um campo em uma cadeia
.br
.wo "strstr   -"
acha uma subcadeia em uma cadeia
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <string.h>

char	*strchr (const char *s, int c);
char	*strrchr (const char *s, int c);
char	*strend (const char *s);
char	*strpbrk (const char *s1, const char *s2);
int	strspn (const char *s1, const char *s2);
int	strcspn (const char *s1, const char *s2);
char	*strtok (char *s1, const char *s2);
char	*strfield (char *s1, int c);
char	*strstr (const char *s1, const char *s2);
.)l

.in
.sp
.(t
.b DESCRI��O
.in 5
Os parametros "s1", "s2" e "s" s�o ponteiros para cadeias terminadas por NULOs.

.sp
A fun��o "strchr" retorna um ponteiro para a primeira ocorr�ncia do
caractere "c" na cadeia "s".
Se a cadeia n�o cont�m o caractere "c", retorna um ponteiro NULO.
O caractere NULO final � considerado parte da cadeia.
.)t

.sp
A fun��o "strrchr" � semelhante � "strchr", mas retorna um ponteiro
para a �ltima ocorr�ncia do caractere "c".

.sp
A fun��o "strend" retorna o endere�o do NULO final da cadeia. 

.sp
A fun��o "strpbrk" retorna um ponteiro na cadeia "s1",
para a primeira ocorr�ncia de qualquer caractere da cadeia "s2".
Se n�o existir nenhum caractere de "s2" em "s1" retorna um ponteiro NULO.

.sp
A fun��o "strspn" retorna o tamanho do primeiro segmento de "s1"
que consiste inteiramente de caracteres presentes na cadeia "s2".

.sp
A fun��o "strcspn" retorna o tamanho do primeiro segmento de "s1"
que consiste inteiramente de caracteres ausentes na cadeia "s2".

.sp
A fun��o "strtok"
retorna um ponteiro para o primeiro caractere do primeiro "token" de "s1"
cujos delimitadores s�o os caracteres de "s2".
Os v�rios "tokens" s�o separados por um ou mais delimitadores.
Delimitadores antes do primeiro "token" s�o pulados.
Um caractere NULO � escrito em "s1"
no lugar do primeiro delimitador ap�s o "token".
Para  a busca do pr�ximo token, "s1"
deve ser um ponteiro NULO e "s2"
pode ser modificado. Dessa maneira sucessivas chamadas da fun��o,
fornecer�o todos os "tokens" de "s1".
Quando acabarem os "tokens" de "s1", � retornado um ponteiro NULO.

.sp
A fun��o "strfield" � semelhante � "strtok", mas com as
seguintes diferen�as:
apenas um delimitador pode ser dado (o caractere "c"); os campos
devem ser separados por apenas um delimitador;
delimitadores antes do primeiro campo n�o s�o pulados,
e s�o interpretados como campos vazios.

.sp
A fun��o "strstr" procura a primeira ocorr�ncia da subcadeia "s2" na
cadeia "s1" (excluindo o caractere NULO que termina "s2").
Ela devolve um ponteiro para a subcadeia encontrada
em "s1", ou um ponteiro NULO se n�o for encontrada.
Se a subcadeia procurada tem tamanho NULO, � retornado "s1". 

.in
.sp
.b
OBSERVA��O
.br
.in 5
.r
Repare que as fun��es "strtok" e "strfield" alteram "s1".

.in
.sp
.b
VEJA TAMBEM
.r
.in 5
(libc): strcpy, strcmp, memcpy, memcmp, memchr

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
