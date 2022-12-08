.bp 1
.he 'LID (libc)'TROPIX: Manual de Refer�ncia'LID (libc)'
.fo 'Atualizado em 03.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
lid - manipula��o de identificadores longos:
.sp
.wo "lidcan  -"
converte um identificador para sua forma can�nica
.br
.wo "lidcpy  -"
copia um identificador longo
.br
.wo "lidclr  -"
zera um identificador longo
.br
.wo "lidcmp  -"
compara dois identificadores longos
.br
.wo "lideq   -"
verifica a igualdade de dois identificadores longos
.br
.wo "lidhash -"
calcula o �ndice de um id. em uma tabela "hash"
.br

.in
.sp
.b SINTAXE
.(l
#include <id.h>

idp_t	lidcan (idp_t lid1, const char *lid2);
idp_t	lidcpy (idp_t lid1, const idp_t lid2);
idp_t	lidclr (idp_t lid1);
int	lidcmp (const idp_t lid1, const idp_t lid2);
int	lideq  (const idp_t lid1, const idp_t lid2);
int	lidhash (const idp_t lid, int size);
.)l

.sp
.b DESCRI��O
.in 5
No sistema TROPIX, al�m da s�rie "str" e "mem", temos tamb�m as s�ries
"sid", "id" e "lid". Estas s�ries de fun��es destinam-se � manipula��o
de identificadores nos formatos fixos de 7, 14 e 31 caracteres.
Estas fun��es aproveitam estes formatos fixos, e processando em
inteiros longos (32 bits), obt�m uma velocidade superior �s fun��es da s�rie
"str" e "mem".
Passaremos a descrever as fun��es da s�rie "lid". Para os outros
formatos fixos, consulte "id" e "sid" (libc).

.sp
O formato padr�o (tamb�m chamado de forma can�nica) da s�rie "lid"
consiste de 8 inteiros longos (com o alinhamento adequado), contendo
31 bytes do nome do identificador longo seguido de 1 byte NULO.
Caracteres n�o presentes no identificador longo
(quando seu nome tem menos do que 31 caracteres) s�o sempre
caracteres NULOS.

.sp
.in 5
A fun��o "lidcan" converte a cadeia original "lid2"
para um identificador longo "lid1". Se a cadeia original tiver mais
de 31 caracteres, os caracteres excedentes s�o desprezados.
Se tiver menos de 31 caracteres, os restantes s�o zerados.
A fun��o retorna "lid1".

.sp
.in 5
A fun��o "lidcpy" copia o identificador longo "lid2" para "lid1".
Retorna "lid1".

.sp
.in 5
A fun��o "lidclr" zera um identificador longo.
Retorna "lid1".

.sp
.in 5
A fun��o "lidcmp" compara identificadores longos,
retornando 1 se "lid1" for lexicograficamente
maior do que "lid2", 0 se forem iguais e -1 se "lid1" for menor do que "lid2".

.sp
.in 5
A fun��o "lideq" compara identificadores longos,
retornando 1 se "lid1" e "lid2" forem iguais
e 0 em caso contr�rio.

.sp
.in 5
A fun��o "lidhash" calcula a entrada correspondente 
ao identificador longo em uma tabela
"hash" de tamanho "size", devolvendo um n�mero inteiro no intervalo
.wo '[0 .. size-1].'

.in
.sp
.b OBSERVA��ES
.in 5
Repare que na forma can�nica, ap�s o �ltimo caracter temos sempre um
caracter NULO.
Isto significa, que tamb�m podemos utilizar as fun��es da s�rie "str"
para identificadores desta forma.

.sp
� utilizada a compara��o sem sinal. Isto � �til para utiliza��o
do c�digo de caracteres ISO de 8 bites.

.sp
No caso da vers�o ICARUS da fun��o "lidhash",
o seu argumento "size" deve ser menor do que 65536.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
id, sid, mem, strcpy, strcmp, strtok
.br
.wo "(fmt): "
iso
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
