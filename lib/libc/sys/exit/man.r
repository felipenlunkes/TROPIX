.bp
.he 'EXIT (sys)'TROPIX: Manual de Refer�ncia'EXIT (sys)'
.fo 'Atualizado em 14.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Termina um processo:
.sp
.wo "exit  -"
processando "atexit" e atualizando a "stdio"
.br
.wo "_exit -"
sem processar "atexit" nem atualizar a "stdio"
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

void	exit (int status);
void	_exit (int status);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "exit" termina o processo com as seguintes
consequ�ncias:

.sp
.in 10
As fun��es registradas atrav�s de "atexit" (libc) s�o chamadas,
na ordem inversa em que foram registradas.

.sp
As �reas de sa�da da "stdio" s�o atualizadas atrav�s de "fflush" (libc).

.sp
Todos os descritores de arquivos abertos s�o fechados.

.sp
Se o processo pai utilizou a chamada ao sistema "sigchild" (sys),
� enviado o sinal "SIGCHLD" para o processo pai.

.sp
O processo pai deste processo �
notificado do t�rmino deste processo (atrav�s da chamada "wait"),
e os 8 bites de mais baixa ordem
de "status" s�o colocados � sua disposi��o. 

.sp
O novo pai dos filhos do processo passa a ser o processo "init"
(ver "intro" (sys)).

.sp
.in 5
A chamada ao sistema "_exit" � an�loga a "exit", exceto que 
as fun��es registradas por "atexit" n�o s�o chamadas, nem s�o
atualizados as �reas de sa�da da "stdio".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Nenhum; n�o pode haver um retorno destas chamadas.

.in
.sp
.b OBSERVA��O
.in 5
Um processo que termina, mas o seu processo pai n�o chama
"wait", permanece em um estado chamado "ZOMBIE", que
ocupa uma entrada da tabela de processos, o que �
indesej�vel.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
intro, signal, sigchild, wait
.br
.wo "(libc):"
atexit, fflush
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
