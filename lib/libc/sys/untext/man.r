.bp
.he 'UNTEXT (sys)'TROPIX: Manual de Refer�ncia'UNTEXT (sys)'
.fo 'Atualizado em 23.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "untext -"
libera os recursos de um programa reentrante 
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	untext (const char *path);
.)l

.in
.sp
.b DESCRI��O
.in 5
Um programa reentrante ("text") ocupa uma s�rie de recursos do sistema
operacional, e em particular, mem�ria interna e espa�o na �rea de
"swap" no disco. Isto pode ocorrer, mesmo que no momento n�o haja nenhum
usu�rio do programa.

.sp
A chamada ao sistema "untext" libera os
recursos ocupados pelo programa reentrante cujo nome � dado pela cadeia
de caracteres apontados por "path"
(desde que no momento ele n�o esteja sendo utilizado).

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
untext, cc, ld (op��o "-n"), chmod (op��o "-m")
.br
.wo "(sys): "
chmod
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
