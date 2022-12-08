.bp
.he 'SYMLINK (sys)'TROPIX: Manual de Refer�ncia'SYMLINK (sys)'
.fo 'Atualizado em 16.04.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "symlink -"
cria um elo simb�lico para um arquivo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	symlink (const char *old_path, const char *new_path);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "symlink" cria o elo simb�lico ("soft-link") "new_path"
apontando para o arquivo "old_path".

.sp
Os dois caminhos n�o precisam estar no mesmo sistema de arquivos.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A chamada ao sistema devolve zero em caso de sucesso.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b OBSERVA��O
.in 5
Nem todos os tipos de sistemas de arquivos suportam elos simb�licos.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
link, unlink
.br
.wo "(cmd): "
ln, rm
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
