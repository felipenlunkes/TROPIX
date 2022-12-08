.bp
.he 'FFBS (libc)'TROPIX: Manual de Refer�ncia'FFBS (libc)'
.fo 'Atualizado em 26.12.99'Vers�o 3.2.3'Pag. %'

.b NOME
.in 5
.wo "ffbs -"
determina o �ndice do primeiro bit ligado
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

int	ffbs (unsigned long value);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "ffbs" retorna o �ndice do primeiro bit ligado de "value".

.sp
Os bits s�o numerados a partir de 0, do menos para o mais significativo.
Se n�o houver nenhum bit ligado (isto �, "value" for NULO), a fun��o
retorna -1.

.sp
Repare que, se "value" s� contiver um bit ligado, a fun��o retorna o logar�tmo
de "value" na base 2.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
