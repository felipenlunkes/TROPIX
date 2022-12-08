.bp 1
.he 'STRHASH (libc)'TROPIX: Manual de Refer�ncia'STRHASH (libc)'
.fo 'Atualizado em 09.05.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "strhash -"
calcula o �ndice de uma cadeia em uma tabela "hash"
.br

.in
.sp
.b SINTAXE
.(l
#include <string.h>

int	strhash (const char *str, int len, int size);
.)l

.sp
.b DESCRI��O
.in 5
A fun��o "strhash" calcula a entrada correspondente 
� cadeia "str" de "len" caracteres, em uma tabela
"hash" de tamanho "size", devolvendo um n�mero inteiro no intervalo
.wo '[0 .. size-1].'

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
sid, lid, mem
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
