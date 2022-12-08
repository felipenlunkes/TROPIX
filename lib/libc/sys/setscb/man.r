.bp
.he 'SETSCB (sys)'TROPIX: Manual de Refer�ncia'SETSCB (sys)'
.fo 'Atualizado em 23.10.98'Vers�o 3.1'Pag. %'

.b NOME
.in 5
.wo "setscb -"
atualiza o bloco de controle do sistema operacional
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/common.h>
#include <sys/scb.h>
#include <sys/syscall.h>

int	setscb (SCB *sp);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "setscb" permite alterar (apenas alguns) campos
do bloco de controle do sistema operacional.
Este bloco cont�m diversas informa��es sobre o n�cleo
do sistema, que podem ser vistas em <sys/scb.h>.

.sp
No momento, apenas o campo "y_tzmin" pode ser alterado.

.sp
O modo usual da utiliza��o desta chamada ao sistema � a de
(inicialmente) obter o estado atual do bloco de controle
(atrav�s de "getscb" (sys)), alterar os campos desejados, e
finalmente chamar "setscb".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve 0.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b OBSERVA��O
.in 5
Esta chamada pode ser utilizada apenas por superusu�rios.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
getscb, gettzmin
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
