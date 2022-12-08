.bp
.he 'STRCPY (libc)'TROPIX: Manual de Refer�ncia' STRCPY (libc)'
.fo 'Atualizado em 10.10.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
Movimenta��es de cadeias:
.sp
.wo "strcat  -"
concatena duas cadeias
.br
.wo "strncat -"
concatena duas cadeias at� "n" caracteres
.br
.wo "strcpy  -"
copia uma cadeia para outra
.br
.wo "strncpy -"
copia uma cadeia para outra at� "n" caracteres
.br
.wo "strscpy -"
como acima, mas com um NULO no final da cadeia
.br
.wo "strmove -"
copia uma cadeia para outra superposta
.br
.wo "strlen  -"
obt�m o tamanho de uma cadeia (sem o NULO)
.br
.wo "strdup  -"
duplica uma cadeia

.in
.sp
.b SINTAXE
.in 5
.(l
#include <string.h>

char	*strcat (char *s1, const char *s2);
char	*strncat (char *s1, const char *s2, size_t n);
char	*strcpy (char *s1, const char *s2);
char	*strncpy (char *s1, const char *s2, size_t n);
char	*strscpy (char *s1, const char *s2, size_t n);
char	*strmove (char *s1, const char *s2);
size_t	strlen (const char *s);
char	*strdup (const char *s);
.)l

.in
.sp
.b DESCRI��O
.in 5
Os parametros "s1", "s2" e "s" s�o ponteiros para cadeias de caracteres
terminadas por NULOs. Para o tratamento de �reas sem NULOs no final,
veja "memcpy" (libc).

.sp
A fun��o "strcat" adiciona uma c�pia de "s2" ao final de "s1".
A fun��o retorna o valor de "s1".

.sp
A fun��o "strncat" adiciona at� "n" caracteres da cadeia "s2"
ao final de "s1".
Pode ser gerada uma cadeia n�o terminada
com um NULO, caso "s2" tenha "n" ou mais caracteres.
A fun��o retorna o valor de "s1".

.sp
A fun��o "strcpy" copia a cadeia "s2" para "s1".
A fun��o retorna o valor de "s1".

.sp
A fun��o "strncpy" copia exatamente "n" caracteres truncando a c�pia de
"s2" ou adicionando caracteres NULOs a "s1"
quando necess�rio. O resultado n�o ser� terminado por um caractere
NULO caso o comprimento de "s2" seja "n" ou maior.
A fun��o retorna o valor de "s1".

.sp
A fun��o "strscpy" � similar � "strncpy", mas garante um NULO
no final da cadeia.
A fun��o retorna o valor de "s1".

.sp
A fun��o "strmove" � semelhante � "strcpy",
mas copia de baixo para cima ou vice-versa, de modo a
n�o perder informa��es no caso das cadeias serem superpostas. 
Pode ser um pouco mais lenta do que "strcpy".
A fun��o retorna o valor de "s1".

.sp
A fun��o "strlen" retorna o comprimento de "s",
isto �, o n�mero de caracteres da cadeia antes do NULO final.

.sp
A fun��o "strdup" devolve um ponteiro para uma nova cadeia
que � uma duplicata da cadeia dada. O espa�o para a
nova cadeia � obtida atrav�s de "malloc" (libc). Se a duplicata
n�o p�de ser criada, devolve um ponteiro NULO.

.in
.sp
.b
OBSERVA��ES
.r
.in 5
As fun��es "strcat", "strncat", "strcpy", "strmove",
"strncpy" e "strscpy" alteram "s1";
elas n�o verificam se ultrapassam a �rea alocada para esta cadeia.

.sp
Se as c�pias forem entre objetos superpostos (exceto para "strmove"),
o resultado ser� imprevis�vel. 

.in
.sp
.b
VEJA TAMBEM
.r
.in 5
(libc): strcmp, strtok, memcpy, malloc

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
