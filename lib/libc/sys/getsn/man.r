.bp
.he 'GETSN (sys)'TROPIX: Manual de Refer�ncia'GETSN (sys)'
.fo 'Atualizado em 14.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
getsn - obt�m o n�mero de s�rie

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

long	getsn (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "getsn" devolve o n�mero de s�rie do
computador.

.sp
O n�mero de s�rie do computador deve coincidir com o
n�mero de s�rie do sistema operacional. Caso isto n�o
ocorra, a chamada ao sistema "getsn" devolve -1.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
uname
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
