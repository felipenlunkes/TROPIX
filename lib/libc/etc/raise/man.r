.bp
.he 'RAISE (libc)'TROPIX: Manual de Refer�ncia'RAISE (libc)'
.fo 'Atualizado em 23.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "raise -"
envia um sinal para o pr�prio processo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <signal.h>

int	raise (int sig);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "raise" envia o sinal "sig" para o pr�prio programa em execu��o.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A fun��o retorna zero em caso de sucesso.
No caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
kill
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
