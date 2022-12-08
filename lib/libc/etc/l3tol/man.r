.bp
.he 'L3TOL (libc)'TROPIX: Manual de Refer�ncia'L3TOL (libc)'
.fo 'Atualizado em 22.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "l3tol -"
converte uma lista de inteiros de 3 bytes para 4 bytes
.br
.wo "ltol3 -"
converte uma lista de inteiros de 4 bytes para 3 bytes
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

void	l3tol (long *dp, const char *c3p, int n);
void	ltol3 (char *c3p, const long *dp, int n);
.)l

.in
.sp
.b DESCRI��O
.in 5
.bc	/*************************************/
Endere�os de discos usualmente cont�m 4 bytes (tipo "daddr_t").
No entanto, no sistema de arquivos (no disco),
eles cont�m apenas  3; esta compacta��o � poss�vel
pelo fato de que os endere�os nunca ultrapassam
2 ** 24 (16777216), ou em outras palavras, os bytes de mais alta
ordem s�o sempre NULOs.
Estas fun��es fazem as convers�es entre os dois formatos.

Certos sistemas de arquivos utilizam endere�os de blocos com
3 bytes. Estas fun��es convertem vetores de endere�os do formato
de 3 para 4 bytes e vice-versa.
.ec	/*************************************/

A fun��o "l3tol" converte uma lista de "n" inteiros de 3 bytes
apontada por "c3p" em uma lista de
inteiros de 4 bytes na �rea apontada por "dp".

.sp
A fun��o "ltol3" realiza a convers�o inversa,
do formato de 4 bytes ("dp") para
o formato de 3 bytes ("c3p").


.in
.sp
.b OBSERVA��O
.in 5
Estas fun��es s�o �teis para os utilit�rios de manuten��o de certos
sistemas de arquivos que utilizam endere�os de blocos de 3 bytes.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
mkfs, fsck
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
