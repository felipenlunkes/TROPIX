.bp 1
.he 'ID (libc)'TROPIX: Manual de Refer�ncia'ID (libc)'
.fo 'Atualizado em 29.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
id - manipula��o de identificadores:
.sp
.wo "idcan  -"
converte um identificador para sua forma can�nica
.br
.wo "idcpy  -"
copia um identificador
.br
.wo "idclr  -"
zera um identificador
.br
.wo "idcmp  -"
compara dois identificadores
.br
.wo "ideq   -"
verifica a igualdade de dois identificadores
.br
.wo "idhash -"
calcula o �ndice de um id. em uma tabela "hash"
.br

.in
.sp
.b SINTAXE
.(l
#include <id.h>

idp_t	idcan (idp_t id1, const char *id2);
idp_t	idcpy (idp_t id1, const idp_t id2);
idp_t	idclr (idp_t id1);
int	idcmp (const idp_t id1, const idp_t id2);
int	ideq  (const idp_t id1, const idp_t id2);
int	idhash (const idp_t id, int size);
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
Passaremos a descrever as fun��es da s�rie "id". Para os outros
formatos fixos, consulte "sid" e "lid" (libc).

.sp
O formato padr�o (tamb�m chamado de forma can�nica) da s�rie "id"
consiste de 4 inteiros longos (com o alinhamento adequado), contendo
14 bytes do nome do identificador seguido de 2 bytes NULOS.
Caracteres n�o presentes no identificador 
(quando seu nome tem menos do que 14 caracteres) s�o sempre
caracteres NULOS.


.sp
.in 5
A fun��o "idcan" converte a cadeia original "id2"
para um identificador "id1". Se a cadeia original tiver mais
de 14 caracteres, os caracteres excedentes s�o desprezados.
Se tiver menos de 14 caracteres, os restantes s�o zerados.
A fun��o retorna "id1".

.sp
.in 5
A fun��o "idcpy" copia o identificador "id2" para "id1".
Retorna "id1".

.sp
.in 5
A fun��o "idclr" zera um identificador.
Retorna "id1".

.sp
.in 5
A fun��o "idcmp" compara identificadores,
retornando 1 se "id1" for lexicograficamente
maior do que "id2", 0 se forem iguais e -1 se "id1" for menor do que "id2".

.sp
.in 5
A fun��o "ideq" compara identificadores,
retornando 1 se "id1" e "id2" forem iguais
e 0 em caso contr�rio.

.sp
.in 5
A fun��o "idhash" calcula a entrada correspondente 
ao identificador em uma tabela
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
No caso da vers�o ICARUS da fun��o "idhash",
o seu argumento "size" deve ser menor do que 65536.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
sid, lid, mem, strcpy, strcmp, strtok
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
