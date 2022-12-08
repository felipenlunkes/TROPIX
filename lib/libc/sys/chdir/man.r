.bp
.he 'CHDIR (sys)'TROPIX: Manual de Refer�ncia'CHDIR (sys)'
.fo 'Atualizado em 12.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "chdir -"
troca de diret�rio corrente
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	chdir (const char *path);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "chdir" faz com que o diret�rio corrente
passe a ser o diret�rio apontado por "path".

.sp
O diret�rio corrente � o ponto de partida para buscas de caminhos
que n�o come�am por "/".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A chamada ao sistema devolve zero se conseguiu trocar de diret�rio
corrente. 
No caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
chroot
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
