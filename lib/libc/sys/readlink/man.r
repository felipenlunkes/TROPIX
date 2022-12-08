.bp
.he 'READLINK (sys)'TROPIX: Manual de Refer�ncia'READLINK (sys)'
.fo 'Atualizado em 16.04.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "readlink -"
l� o valor de um elo simb�lico
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	readlink (const char *path, char *area, int count);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "readlink" armazena o conte�do do elo simb�lico
"path" na �rea "area", que cont�m o tamanho "count". Se o espa�o o
permitir, o conte�do � terminado com um caractere NULO.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A chamada ao sistema devolve o n�mero de caracteres armazenados
na �rea (inclu�ndo o poss�vel NULO final).
Em caso de �rro, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
ln
.br
.wo "(sys): "
stat, lstat, symlink
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
