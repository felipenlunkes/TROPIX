.bp
.he 'MOUNT (sys)'TROPIX: Manual de Refer�ncia'MOUNT (sys)'
.fo 'Atualizado em 04.10.02'Vers�o 4.3.0'Pag. %'

.b NOME
.in 5
.wo "mount -"
monta um sistema de arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/common.h>
#include <sys/sync.h>
#include <sys/sb.h>
#include <sys/syscall.h>

int mount (const char *dev, const char *dir, int flags);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "mount" faz com que um sistema de arquivos
contido no arquivo especial de blocos "dev" seja
montado no diret�rio identificado por "dir". Tanto "dev" como
"dir" s�o ponteiros para cadeias de caracteres contendo caminhos. 

.sp
A chamada ao sistema "mount" tenta identificar automaticamente o
tipo do sistema de arquivos. Se houver um c�digo correspondente na entrada
da tabela de parti��es, este � usado, e em caso contr�rio s�o tentados
todos os tipos suportados atualmente: TROPIX V7, TROPIX T1, FAT 12/16/32
e CDROM.

.sp
A vari�vel "flags" cont�m indicadores contendo v�rias op��es de montagem.
A defini��o dos v�rios indicadores est� no arquivo <sys/sb.h>,
e uma explica��o est� em "getmntopt" (libc).

.sp
Se a montagem foi efetuada com sucesso, as referencias a "dir"
ir�o se referir � raiz do sistema montado. Toda a sub�rvore
cuja raiz � "dir" (que era acess�vel antes da montagem) fica oculta.

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
.b OBSERVA��ES
.in 5
Esta chamada ao sistema pode apenas ser utilizada pelo superusu�rio,
e � reservada para o utilit�rio "mount" (cmd).

.sp
Sistemas de arquivos em fita magn�tica ou em dispositivos
com prote��o de escrita devem ser montados sempre
com permiss�o apenas de leitura.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd):  "
mount
.br
.wo "(sys):  "
umount
.br
.wo "(libc): "
getmntopt
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
