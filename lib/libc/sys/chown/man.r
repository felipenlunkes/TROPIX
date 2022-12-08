.bp
.he 'CHOWN (sys)'TROPIX: Manual de Refer�ncia'CHOWN (sys)'
.fo 'Atualizado em 12.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "chown -"
modifica o dono e o grupo de um arquivo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	chown (const char *path, int owner, int group);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "chown" muda o dono e o grupo
do arquivo "path", atribuindo os novos valores num�ricos
"owner" e "group".

.sp
Somente processos com o usu�rio efetivo igual ao dono do arquivo
ou o superusu�rio podem trocar o dono/grupo de um arquivo.

.sp
Se a chamada ao sistema � utilizada por um usu�rio que n�o �
superusu�rio, os indicadores S_ISUID ("set user ID") e S_ISGID ("set group ID")
s�o zerados (ver "chmod" (sys)). 

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A chamada ao sistema devolve zero se conseguiu alterar 
o dono/grupo do arquivo.
No caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
chown
.br
.wo "(sys): "
chmod
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
