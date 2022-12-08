.bp 1
.he 'SID (libc)'TROPIX: Manual de Refer�ncia'SID (libc)'
.fo 'Atualizado em 04.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
sid - manipula��o de identificadores curtos:
.sp
.wo "sidcan  -"
converte um identificador para sua forma can�nica
.br
.wo "sidcpy  -"
copia um identificador curto
.br
.wo "sidclr  -"
zera um identificador curto
.br
.wo "sidcmp  -"
compara dois identificadores curtos
.br
.wo "sideq   -"
verifica a igualdade de dois identificadores curtos
.br
.wo "sidhash -"
calcula o �ndice de um id. em uma tabela "hash"
.br

.in
.sp
.b SINTAXE
.(l
#include <id.h>

idp_t	sidcan (idp_t sid1, const char *sid2);
idp_t	sidcpy (idp_t sid1, const idp_t sid2);
idp_t	sidclr (idp_t sid1);
int	sidcmp (const idp_t sid1, const idp_t sid2);
int	sideq  (const idp_t sid1, const idp_t sid2);
int	sidhash (const idp_t sid, int size);
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
Passaremos a descrever as fun��es da s�rie "sid". Para os outros
formatos fixos, consulte "id" e "lid" (libc).

.sp
O formato padr�o (tamb�m chamado de forma can�nica) da s�rie "sid"
consiste de 2 inteiros longos (com o alinhamento adequado), contendo
7 bytes do nome do identificador curto seguido de 1 byte NULO.
Caracteres n�o presentes no identificador curto
(quando seu nome tem menos do que 7 caracteres) s�o sempre
caracteres NULOS.

.sp
.in 5
A fun��o "sidcan" converte a cadeia original "sid2"
para um identificador curto "sid1". Se a cadeia original tiver mais
de 7 caracteres, os caracteres excedentes s�o desprezados.
Se tiver menos de 7 caracteres, os restantes s�o zerados.
A fun��o retorna "sid1".

.sp
.in 5
A fun��o "sidcpy" copia o identificador curto "sid2" para "sid1".
Retorna "sid1".

.sp
.in 5
A fun��o "sidclr" zera um identificador curto.
Retorna "sid1".

.sp
.in 5
A fun��o "sidcmp" compara identificadores curtos,
retornando 1 se "sid1" for lexicograficamente
maior do que "sid2", 0 se forem iguais e -1 se "sid1" for menor do que "sid2".

.sp
.in 5
A fun��o "sideq" compara identificadores curtos,
retornando 1 se "sid1" e "sid2" forem iguais
e 0 em caso contr�rio.

.sp
.in 5
A fun��o "sidhash" calcula a entrada correspondente 
ao identificador curto em uma tabela
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
No caso da vers�o ICARUS da fun��o "sidhash",
o seu argumento "size" deve ser menor do que 65536.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
id, lid, mem, strcpy, strcmp, strtok
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
