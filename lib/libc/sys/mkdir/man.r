.bp
.he 'MKDIR (sys)'TROPIX: Manual de Refer�ncia'MKDIR (sys)'
.fo 'Atualizado em 17.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "mkdir -"
cria um diret�rio
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	mkdir (const char *path, int mode);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "mkdir" cria um novo diret�rio cujo nome
� dado pela cadeia de caracteres apontada por "path".

.sp
O UID/GID do diret�rio ser� o UID/GID efetivo do processo.

.sp
O modo do diret�rio � obtido a partir do valor de "mode",
por�m os 9 indicadores de mais baixa ordem (a prote��o) s�o
modificados pela m�scara de cria��o de arquivos do processo;
todos os indicadores ligados da m�scara s�o zerados (veja "umask" (sys)).

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
mkdir
.br
.wo "(sys): "
chmod, stat, umask
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
