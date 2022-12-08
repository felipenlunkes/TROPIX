.bp
.he 'RMDIR (sys)'TROPIX: Manual de Refer�ncia'RMDIR (sys)'
.fo 'Atualizado em 18.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "rmdir -"
remove um diret�rio
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	rmdir (const char *path);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "rmdir" remove o diret�rio cujo nome �
a cadeia de caracteres apontada por "path".

.sp
O diret�rio deve estar vazio, isto �, s� deve conter as entradas
"." e "..".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve zero.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
rmdir
.br
.wo "(sys): "
unlink
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
