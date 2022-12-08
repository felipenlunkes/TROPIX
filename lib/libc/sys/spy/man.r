.bp
.he 'SPY (sys)'TROPIX: Manual de Refer�ncia'SPY (sys)'
.fo 'Atualizado em 22.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "spy -"
chama a rotina de instrumenta��o do n�cleo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	spy (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "spy"
chama a rotina de instrumenta��o do n�cleo do sistema
operacional. Durante a utiliza��o desta rotina, todo
o processamento normal do sistema operacional fica suspenso.
.sp
Esta chamada s� � permitida para superusu�rios e � usada
somente para a depura��o do sistema operacional. 

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
.b ESTADO
.in 5
Efetivo.
.in
