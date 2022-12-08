.bp
.he 'CHROOT (sys)'TROPIX: Manual de Refer�ncia'CHROOT (sys)'
.fo 'Atualizado em 12.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "chroot -"
troca de diret�rio raiz
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	chroot (const char *path);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "chroot" muda o diret�rio raiz, para 
o diret�rio apontando por "path". O diret�rio raiz � o diret�rio que
� usado como ponto inicial de busca para caminhos que
come�am com "/".

.sp
O diret�rio corrente do processo n�o � modificado.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A chamada ao sistema devolve zero se conseguiu mudar o diret�rio raiz. 
No caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b OBSERVA��ES
.in 5
Apenas processos cujo usu�rio efetivo � o superusu�rio
podem utilizar esta chamada ao sistema.

.sp
A entrada ".." do diret�rio raiz � interpretado como
o pr�prio diret�rio raiz. Portanto, ".." n�o pode ser usado
para acessar arquivos fora da sub�rvore cuja raiz � o diret�rio
raiz.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
chdir
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
