.bp
.he 'LINK (sys)'TROPIX: Manual de Refer�ncia'LINK (sys)'
.fo 'Atualizado em 16.04.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "link -"
cria um novo nome para um arquivo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	link (const char *old_path, const char *new_path);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "link" cria um novo nome
(uma entrada em um diret�rio, "hard-link") para um arquivo j� existente.

.sp
O nome do arquivo � apontado por "old_path"
e o novo nome a ser criado � apontado por "new_path".

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
.b OBSERVA��ES
.in 5
Todos os nomes de um arquivo devem pertencer ao mesmo sistema
de arquivos.

.sp
Somente o superusu�rio pode criar mais um nome para um diret�rio.

.sp
Nem todos os sistemas de arquivos permitem a cria��o de novos nomes
para um arquivo.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
symlink, unlink
.br
.wo "(cmd): "
ln, rm
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
