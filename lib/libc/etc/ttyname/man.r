.bp 1
.he 'TTYNAME (libc)'TROPIX: Manual de Refer�ncia'TTYNAME (libc)'
.fo 'Atualizado em 27.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Informa��es sobre o terminal:
.sp
.wo "ttyname -"
obt�m o nome do terminal
.br
.wo "isatty  -"
verifica se o arquivo � um terminal
.br

.in
.sp
.b SINTAXE
.(l
#include <stdlib.h>

char	*ttyname (int fd);
int	isatty (int fd);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "ttyname" devolve um ponteiro para uma cadeia contendo
o nome do terminal associado ao descritor "fd".

.sp
A fun��o "isatty" retorna um n�mero n�o NULO se o arquivo
associado ao descritor "fd" for um terminal, e zero no caso contr�rio.

.in
.sp
.b DIAGN�STICOS
.in 5
A fun��o "ttyname" devolve  um ponteiro NULO,
se ao descritor n�o estiver associado um terminal.

.in
.sp
.b OBSERVA��O
.in 5
A fun��o "ttyname" devolve um ponteiro para uma �rea est�tica, e o
seu conte�do deve ser copiado caso ele seja necess�rio ap�s
a fun��o ser chamada novamente.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
(cmd): tty

.in
.sp
.b ARQUIVOS
.in 5
/dev/*

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
