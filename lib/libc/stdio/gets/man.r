.bp 1
.he 'GETS (libc)'TROPIX: Manual de Refer�ncia'GETS (libc)'
.fo 'Atualizado em 10.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
L� uma cadeia de um arquivo:
.sp
.wo "gets   -"
l� da entrada padr�o
.br
.wo "fngets -"
l� de um arquivo dado omitindo o <nl>
.br
.wo "fgets  -"
l� de um arquivo dado mantendo o <nl>
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>

char	*gets (char *s);
char	*fngets (char *s, int n, FILE *fp);
char	*fgets (char *s, int n, FILE *fp);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "gets" l� caracteres da entrada padr�o ("stdin") e os armazena
no vetor apontado por "s",
at� que seja encontrado um <nl> ou seja detetado o final do arquivo.
O <nl> � substitu�do por um NULO na cadeia.

.sp
A fun��o "fngets" l� caracteres do arquivo "fp" e os armazena
no vetor apontado por "s", at� que (n-1) caracteres sejam lidos,
seja encontrado um <nl> ou seja detetado o final do arquivo.
O <nl> � substitu�do por um NULO na cadeia.

.sp
A fun��o "fgets" � an�loga � fun��o "fngets", com a diferen�a
de que o <nl> � mantido, seguido de um NULO.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Se for detetado o final do arquivo, e nenhum caractere foi lido,
n�o h� transfer�ncia de caracteres e um ponteiro NULO � retornado. Caso
ocorra algum erro de leitura, um ponteiro NULO
tamb�m � retornado. Em caso contr�rio, � retornado "s".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
ferror, fopen, fread, getc, scanf, stdio
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
