.bp
.he 'UMOUNT (sys)'TROPIX: Manual de Refer�ncia'UMOUNT (sys)'
.fo 'Atualizado em 05.10.02'Vers�o 4.3.0'Pag. %'

.b NOME
.in 5
.wo "umount -"
desmonta um sistema de arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	umount (const char *dev, int flags);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "umount" faz com que o sistema de arquivos
contido no arquivo especial de blocos "dev" seja desmontado.

.sp
Ap�s a desmontagem deste sistema de arquivos, o diret�rio
sobre o qual o sistema estava montado volta a ter o seu significado
normal.

.sp
A vari�vel "flags" cont�m indicadores contendo v�rias op��es de montagem.
A defini��o dos v�rios indicadores est� no arquivo <sys/sb.h>,
e uma explica��o est� em "getmntopt" (libc).

.sp
Se "flags" dado for diferente de "-1", ser�o usados os indicadores dados
nesta vari�vel; em caso contr�rio ser�o usados os indicadores dados
na montagem (pela chamada ao sistema "mount" (sys).
Na presente vers�o, somente � relevante o indicador SB_EJECT.

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
.b OBSERVA��O
.in 5
Esta chamada ao sistema pode ser utilizada apenas por superusu�rios,
e � reservada para o utilit�rio "umount" (cmd).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
umount
.br
.wo "(sys): "
mount
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
