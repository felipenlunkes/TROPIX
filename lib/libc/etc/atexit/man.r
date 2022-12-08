.bp
.he 'ATEXIT (libc)'TROPIX: Manual de Refer�ncia'ATEXIT (libc)'
.fo 'Atualizado em 08.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "atexit -"
registra fun��es para que sejam executadas no "exit"
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

int	atexit (void (*func) (void));
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "atexit" registra a fun��o apontada por "func", para que ela
seja chamada (sem argumentos) ao t�rmino normal do programa.

.sp
Ao t�rmino normal do programa (seja pela execu��o de "exit" (sys),
ou o retorno da fun��o "main"), todas as fun��es registradas atrav�s
de "atexit" ser�o chamadas, na ordem inversa dos registros.
Cada fun��o � executada tantas vezes quantas foi registrada. 

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A fun��o devolve ZERO se conseguiu registrar a fun��o, e -1
no caso contr�rio.

.in
.sp
.b OBSERVA��ES
.in 5
No momento � poss�vel registrar um m�ximo de 32 fun��es.

.sp
Repare que em caso de t�rmino ANORMAL do programa,
as fun��es N�O s�o chamadas (exceto no caso de "abort" (libc)).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys):  "
exit
.br
.wo "(libc): "
abort
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
