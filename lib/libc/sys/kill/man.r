.bp
.he 'KILL (sys)'TROPIX: Manual de Refer�ncia'KILL (sys)'
.fo 'Atualizado em 16.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "kill -"
envia um sinal para um processo ou grupo de processos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>
#include <signal.h>

int	kill (int pid, int sig);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "kill" envia um sinal para um processo ou
grupo de processos. O processo ou grupo de processos � especificado
por "pid". O sinal enviado � especificado por "sig",
e � um elemento da lista
dada em <signal.h>, ou zero (veja a observa��o).

.sp
No texto abaixo, chamaremos o processo que envia o sinal
(isto �, que chamou "kill") de "transmissor",
e o processo que recebe o sinal de "receptor".

.sp
O UID real ou efetivo do transmissor
deve ser igual ao UID real ou efetivo do
receptor, a n�o ser que o UID efetivo
do transmissor � o do superusu�rio.

.sp
Os processos cujas identifica��es v�o de "0" a "initpid" s�o processos
especiais; os demais s�o "processos regulares"
(veja "intro" (sys)).

.sp
Dependendo dos valores de "pid" e outros atributos,
o sinal � enviado para diversos
receptores:

.in +3
.ip 1. 3
.wo "PROCESSO INDIVIDUAL:"
se "pid" for maior do que zero, o sinal "sig" ser� enviado ao
processo de identifica��o "pid". Neste caso, "pid" pode ser igual
a "initpid".

.ip 2. 3
.wo "GRUPO DADO:"
se "pid" � negativo, mas n�o -1, "sig" ser� enviado a todos
processos que pertencem ao grupo de processos cuja identifica��o 
� o valor absoluto de "pid".

.ip 3. 3
.wo "GRUPO IMPL�CITO:"
se "pid" � 0, o sinal ser� enviado a todos processos regulares
que s�o membros do grupo de processos a que pertence o transmissor
(ou seja, cuja identifica��o do grupo de processos � igual
� identifica��o do grupo de processos do transmissor).

.ip 4. 3
.wo "DONO IMPL�CITO:"
se "pid" � -1 e o UID efetivo do transmissor N�O
� o superusu�rio, "sig" ser� enviado a todos os processos
regulares cujo UID REAL � igual ao UID EFETIVO do transmissor.

.ip 5. 3
.wo "UNIVERSAL:"
se "pid" � -1 e o UID efetivo do transmissor
� o superusu�rio, "sig" ser� enviado a todos os processos regulares.

.ep
.in -3

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
.b OBSERVA��ES
.in 5
Se "sig" for zero (o sinal NULO),
a consistencia de erros � realizada, mas nenhum sinal � enviado.
Isto pode ser utilizado para verificar a validade de "pid".
.sp
Processos podem enviar sinais para eles pr�prios.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
kill
.br
.wo "(sys): "
getpid, intro, setpgrp, signal
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
