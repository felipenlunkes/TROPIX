.bp
.he 'RENAME (sys)'TROPIX: Manual de Refer�ncia'RENAME (sys)'
.fo 'Atualizado em 16.04.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "rename -"
troca o nome de um arquivo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int rename (const char *old_path, const char *new_path);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "rename" troca o nome do arquivo (antes chamado por) "old_path"
para "new_path". Ambos caminhos devem se referir ao mesmo sistema de arquivos.

.sp
Se "old_path" for um elo simb�lico, este ter� o seu nome trocado, e N�O
o arquivo apontado.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A fun��o devolve zero se conseguiu trocar o nome do arquivo.
No caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
mv
.br
.wo "(sys): "
link, unlink
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
