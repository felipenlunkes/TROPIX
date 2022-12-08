.bp
.he 'PAUSE (sys)'TROPIX: Manual de Refer�ncia'PAUSE (sys)'
.fo 'Atualizado em 17.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "pause -"
suspende o processo at� a ocorr�ncia de um sinal
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	pause (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "pause" suspende a execu��o do processo
at� que ele receba um sinal. O sinal tem que ser um
que atualmente n�o esteja programado para ser ignorado.

.sp
Se o sinal causar a termina��o do processo, "pause" n�o ir�
retornar.

.sp
Se o sinal foi programado para ser interceptado por uma fun��o,
e esta fun��o retornar, o processo ir� continuar ap�s
o "pause", com um valor de retorno de -1.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Se a chamada retornar,
ela devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
alarm, kill, signal, wait
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
