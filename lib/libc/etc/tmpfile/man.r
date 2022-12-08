.bp
.he 'TMPFILE (libc)'TROPIX: Manual de Refer�ncia'TMPFILE (libc)'
.fo 'Atualizado em 26.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "tmpfile -"
cria um arquivo tempor�rio
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>

FILE	*tmpfile (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "tmpfile" cria um arquivo tempor�rio que � automaticamente
removido quando for fechado ou quando o programa terminar.

.sp
O arquivo � aberto para atualiza��es (isto �, para leituras/escritas)
com o modo "w+" (ver "fopen" (libc)).

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a fun��o devolve um ponteiro para a estrutura "FILE"
correspondente ao arquivo.
No caso contr�rio, devolve um ponteiro NULO.

.in
.sp
.b OBSERVA��O
.in 5
O arquivo � removido mesmo que o programa termine anormalmente. 

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
mktemp, tmpnam, fopen 
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
