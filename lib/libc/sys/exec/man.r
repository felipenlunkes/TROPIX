.bp
.he 'EXEC (sys)'TROPIX: Manual de Refer�ncia'EXEC (sys)'
.fo 'Atualizado em 13.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Executa um arquivo:
.sp
.wo "execl  -"
dado um vetor de argumentos (e ambiente impl�cito)
.br
.wo "execle -"
dado um vetor de argumentos e um ambiente
.br
.wo "execv  -"
dado um ponteiro para um vetor de argumentos
.br
.wo "         (e ambiente impl�cito)"
.br
.wo "execve -"
dado um ponteiro para um vetor de argumentos
.br
.wo "         e um ambiente"
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	execl  (const char *path, const char *arg0, ...);
int	execle (const char *path, const char *arg0, ...);
int	execv  (const char *path, const char *argv[]);
int	execve (const char *path, const char *argv[],
					const char *envp[]);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "exec" em todas as suas formas substitui
o arquivo em execu��o (do processo que fez a chamada) por um novo
arquivo execut�vel. Este arquivo � composto de um cabe�alho,
um segmento de texto, e um segmento de dados. O segmento de dados
� composto de uma parte inicializada ("data") e uma parte n�o 
inicializada ("bss").

.sp
Embora o processo continue sendo o mesmo (com o mesmo PID (veja "intro"),
apenas o programa em execu��o foi substitu�do),
usaremos os nomes de "processo antigo"
e "processo novo" para simplificar a explica��o. O processo antigo
refere-se ao processo durante o momento da chamada,
e processo novo refere-se ao processo ap�s a troca do arquivo execut�vel.

.sp
Quando um programa em "C" � executado, ele recebe argumentos
na seguinte forma:

.sp
.(l
	extern const char	**environ;

	main (int argc, const char *argv[], const char *envp[])
.)l

.sp
.in 5
onde "argc" cont�m o n�mero de argumentos, "argv" � um ponteiro
para um vetor de ponteiros para as cadeias dos argumentos,
e "envp" � um  ponteiro para o vetor de ponteiros para as cadeias do ambiente
(ver "environ" (fmt)).
A vari�vel "environ" recebe uma c�pia de "envp".
O vetor "argv" tem sempre pelo menos um elemento:
o ponteiro para a cadeia com o nome do arquivo em execu��o
(ou o seu �ltimo componente do caminho).
Ambos vetores de ponteiros para as cadeias terminam com um ponteiro NULO.

.sp
A chamada ao sistema "execl" executa o arquivo apontado pelo argumento "path".
os argumentos "arg0", ... s�o ponteiros para cadeias que ir�o formar o vetor
de argumentos dispon�veis para o programa a executar ("argv[0]", ...).
Ap�s o �ltimo ponteiro,
deve ser adicionado um ponteiro NULO (para indicar o final da lista de
argumentos). Por conven��o, "arg0" deve apontar para
uma cadeia igual a "path" (ou ao seu �ltimo componente do caminho).
O ambiente recebido pelo programa a executar ser� o mesmo do que
o processo corrente (definido pela vari�vel externa "environ").

.sp
A chamada ao sistema "execle" executa o arquivo apontado pelo argumento "path".
Ela � similar � chamada ao sistema "execl", mas cont�m um argumento adicional
(ap�s o ponteiro NULO): um ponteiro para um vetor de ponteiros para cadeias
definindo o "ambiente"
(este vetor tamb�m deve ser terminado por um ponteiro NULO).
Deste modo, o ambiente recebido pelo programa a executar poder� ser
diferente do ambiente do processo corrente (definido por "environ").

.sp
A chamada ao sistema "execv" executa o arquivo apontado pelo argumento "path".
o argumento "argv" � um ponteiro para um vetor de ponteiros para cadeias
que ir�o formar o vetor de argumentos dispon�veis para o programa a executar
(este vetor deve ser terminado por um ponteiro NULO).
Por conven��o, o primeiro ponteiro deste vetor (que deve ter no m�nimo um
ponteiro n�o NULO) aponta para uma cadeia igual a "path"
(ou ao seu �ltimo componente do caminho).
O ambiente recebido pelo programa a executar ser� o mesmo do que
o processo corrente (definido por "environ").

.sp
A chamada ao sistema "execve" executa o arquivo apontado pelo argumento "path".
Ela � similar � chamada ao sistema "execv", mas cont�m o argumento adicional
"envp": um ponteiro para um vetor de ponteiros para cadeias
definindo o "ambiente".
Deste modo, o ambiente recebido pelo programa a executar poder� ser
diferente do ambiente do o processo corrente (definido por "environ").

.sp
Os descritores dos arquivos abertos continuam abertos 
no processo novo, exceto para os quais foi ligado o indicador
de "feche na execu��o" (veja "fcntl" (sys)). Para os arquivos que
permanecem abertos, o ponteiro de posi��o n�o � alterado. 

.sp
Sinais com disposi��o para terminarem o processo ou serem ignorados,
continuar�o neste estado no novo processo.
Sinais com disposi��o para serem interceptados s�o
alterados para terminarem o novo processo (veja "signal" (sys)). 

.sp
Se os indicadores S_ISUID  e/ou S_ISGID ("set user ID" e/ou "set group ID",
veja "chmod" (sys)) do arquivo do novo processo
est�o ligados, o UID/GID efetivo do novo processo ser�
o UID/GID do arquivo do novo processo.  O UID/GID real
n�o � alterado.

.sp
.(t
O novo processo tamb�m herda os seguintes atributos do processo antigo:

.sp
.in 10
Valor do "nice" (veja "nice" (sys)).
.)t

.sp
Identifica��o do processo, e de seu pai.

.sp
Identifica��o do grupo de processos e grupo de terminais (ver "intro" (sys)).

.sp
Indicador de "trace" (ver "ptrace" (sys)).

.sp
Tempo restante para um sinal do alarme do rel�gio (ver "alarm" (sys)).

.sp
Diret�rio corrente, e diret�rio raiz.

.sp
M�scara de cria��o de arquivos (ver "umask" (sys)).

.sp
Tempos de processamento do processo e de seus descendentes.

.sp
Tranca dos arquivos (ver "lockf" (sys)).

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Se a chamada ao sistema retornou, � porque ocorreu um erro;
o valor de retorno � -1 e � indicada em "errno" a causa do erro.

.in
.sp
.b OBSERVA��O
.in 5
N�o pode haver retorno de um "exec" com sucesso, pois o
processo � sobreposto pelo conte�do do novo arquivo execut�vel.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
alarm, exit, fcntl, fork, intro,  nice, signal, times,
.wo "        umask"
.br
.wo "(libc):"
execvp
.br
.wo "(fmt): "
a.out, environ
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
