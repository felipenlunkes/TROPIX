.bp
.he 'GETSCB (sys)'TROPIX: Manual de Refer�ncia'GETSCB (sys)'
.fo 'Atualizado em 14.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "getscb -"
obtem o bloco de controle do sistema operacional
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/common.h>
#include <sys/scb.h>
#include <sys/syscall.h>

SCB	*getscb (SCB *sp);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "getscb" obt�m o bloco de controle do sistema
operacional. Este bloco cont�m diversas informa��es sobre o n�cleo
do sistema, que podem ser vistas em <sys/scb.h>.

.sp
A chamada ao sistema devolve o endere�o virtual do
bloco de controle do sistema, no espa�o de endere�amento do n�cleo,
que pode ser usado por "phys" (sys) para acessar o bloco.

.sp
Al�m disto, se "sp" for um ponteiro n�o NULO,
a chamada copia o bloco de controle
para a �rea apontada por "sp".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve o endere�o do
bloco de controle do sistema.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b OBSERVA��O
.in 5
Esta chamada pode ser utilizada por qualquer usu�rio, e � pr�pria
para utilit�rios consultarem algumas informa��es do n�cleo.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
phys
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
