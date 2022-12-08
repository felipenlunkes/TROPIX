.bp
.he 'SETTGRP (sys)'TROPIX: Manual de Refer�ncia'SETTGRP (sys)'
.fo 'Atualizado em 28.10.95'Vers�o'3.0 Pag. %'

.b NOME
.in 5
.wo "settgrp -"
altera o terminal associado a um processo
.bc	/*************************************/
gerencia grupos de processos associados a um terminal
.ec	/*************************************/
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	settgrp (int flag);
.)l

.in
.sp
.b DESCRI��O
.in 5
Cada processo ativo pode ser membro de um grupo de processos
associado a um terminal.
A identifica��o deste grupo de processos associados a um terminal
� o PID do processo que abriu o terminal (ver "intro" (sys)).

.sp
Se for chamada com o argumento "flag" igual a zero,
"settgrp" zera a identifica��o do grupo ao qual o processo pertence.
Deste modo o processo passa a n�o pertencer mais a nenhum grupo de
processos associados a um terminal.

.sp
Se for chamada com o argumento "flag" igual a um,
"settgrp" faz com que seja criado um novo grupo de processos associados
a um terminal.
Este novo grupo consiste inicialmente do processo
que chamou "settgrp", e ir� futuramente conter os seus filhos.
Neste caso, o processo j� dever� ter um terminal aberto.

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
.b OBSERVA��O
.in 5
Esta chamada ao sistema somente pode ser utilizada pelo superusu�rio.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
intro
.br
.wo "(cmd): "
stty
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
