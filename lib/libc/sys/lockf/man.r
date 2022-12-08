.bp
.he 'LOCKF (sys)'TROPIX: Manual de Refer�ncia'LOCKF (sys)'
.fo 'Atualizado em 16.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "lockf -"
ger�ncia do uso exclusivo de regi�es de arquivos
.br

.in
.sp
.b SINTAXE
.(l
#include <sys/syscall.h>
#include <unistd.h>

int	lockf (int fd, int function, off_t size);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "lockf" permite o uso exclusivo de regi�es
de arquivos atrav�s da coloca��o de trancas nas regi�es desejadas.
A filosofia de implementa��o seguida pelo TROPIX � bastante pr�xima
das id�ias descritas no POSIX, ap�ndice "E".
As diferen�as mais significativas s�o as de que
as trancas s� podem ser aplicadas a arquivos regulares, e de que
sempre � realizado um teste de acesso
(independente dos atributos do arquivo)
durante as opera��es de leitura/escrita ("mandatory file record
locking" ou "enforcement mode record locks").

.sp
As trancas nas regi�es de um arquivo s�o possu�das pelo processo
que as criou, e elas s�o associadas ao arquivo, que deve estar aberto.
Se o processo fechar um arquivo do qual ele ainda possui trancas de regi�es,
elas s�o liberadas.
Analogamente,
se o processo terminar ainda com arquivos abertos dos quais possui
trancas,
todas as trancas s�o liberadas
como parte do procedimento autom�tico de fechamento dos seus arquivos.

.sp
Regi�es trancadas n�o s�o herdadas por processo filhos, mas s�o
conservadas atrav�s de uma chamada ao sistema "exec" (sys),
a n�o ser que o arquivo tenha sido fechado durante o "exec".

.sp
O par�metro "fd" � o descritor de um arquivo aberto,
obtido por uma das chamadas "creat", "open",
"dup" ou "fcntl".
� necess�rio que o descritor tenha permiss�o de escrita para que
o processo possa trancar uma regi�o.
Por outro lado, n�o h� distin��o entre trancas de leitura ou
escrita; uma vez trancada uma regi�o, um outro processo n�o
pode ler nem escrever naquela regi�o do arquivo.

.sp
O par�metro "function" controla a a��o a ser executada. 
Os valores v�lidos s�o definidos em <unistd.h>, e significam:

.in +5

.ip F_ULOCK: 10
Libera uma regi�o trancada.

.ip F_LOCK: 10
Tranca uma regi�o do arquivo.
Se a regi�o j� estiver trancada por outro processo, aguarda
a sua libera��o pelo outro processo.

.ip F_TLOCK: 10
Testa e tranca uma regi�o do arquivo.
Se a regi�o j� estiver trancada por outro processo,
retorne imediatamente com erro.

.ip F_TEST: 10
Testa se a regi�o tem trancas colocadas por outros processos.

.ep
.in -5

.sp
O par�metro "size" indica o tamanho (em bytes)
da regi�o a ser trancada/liberada.
O come�o da regi�o � dado pelo ponteiro de posi��o corrente do arquivo
(ver "lseek" (sys)), e se estende para a frente com "size" positivo
e para tr�s com "size" negativo.
Neste segundo caso, a regi�o termina no byte anterior � posi��o
corrente (mas n�o incluindo o byte apontado pelo ponteiro de posi��o).
Se "size" for NULO, a regi�o termina na posi��o indicada pelo
final de um arquivo de tamanho m�ximo poss�vel
(isto �, ela come�a na posi��o corrente e se estende at�
final do arquivo qualquer que seja seu tamanho, no presente ou futuro).
Uma regi�o n�o precisa estar efetivamente alocada ao arquivo
para poder ser trancada, e portanto podemos trancar regi�es
ap�s o final do arquivo.

.sp
Regi�es trancadas com "F_LOCK" ou F_TLOCK" podem incluir ou
serem inclu�das totalmente ou parcialmente por um regi�o
trancada previamente pelo mesmo processo.
Se isto ocorrer, ou haver regi�es adjacentes, elas s�o
combinadas em apenas uma regi�o.
Se uma a��o necessitar de mais uma entrada na tabela de
trancas ativas, e ela estar esgotada, a a��o n�o �
executada, e � retornado o erro "EDEADLK".

.sp
Cada a��o "F_ULOCK" pode liberar, integralmente ou em parte,
uma ou mais regi�es trancadas pelo processo. 
Quando uma regi�o n�o � liberada integralmente, as regi�es
remanescentes continuam trancadas pelo processo. A libera��o
do centro de uma regi�o necessita de uma entrada adicional
da tabela de trancas ativas, o que pode acarretar um erro,
como descrito acima.

.sp
Quando se tenta ler/escrever de um arquivo no qual se acessaria
uma regi�o trancada por um outro processo:
.sp
.in +5
Se O_NDELAY (veja "open" (sys)) estiver ligado,
a leitura/escrita retorna imediatamente
com o erro "EAGAIN".
.sp
Se O_NDELAY estiver desligado, a leitura/escrita � bloqueada at�
o processo liberar a regi�o.
.ep
.in -5

.sp
A chamada ao sistema "lockf" � uma fonte potencial de "deadlocks".
Isto pode ocorrer quando um processo, dono de uma regi�o trancada,
aguardar a libera��o de uma regi�o trancada por um outro processo.
Por este motivo, todas as chamadas ao sistema "read", "write"
e "lockf" tentam prever (e evitar) um "deadlock" antes de
aguardar a libera��o da regi�o trancada.
� importante salientar que esta previs�o 
deteta os casos usuais de "deadlock", mas n�o os mais
complexos, envolvendo recursos possu�dos por v�rios processos.

.sp
Processos aguardando a libera��o de trancas podem ser interrompidos
atrav�s de qualquer sinal, portanto a chamada ao sistema "alarm" (sys)
pode ser usado para providenciar uma interrup��o ap�s um tempo
limite de espera por um recurso.


.sp
Uma chamada ao sistema "creat" (sys) ou "open" (sys) com o indicador
"O_TRUNC" ligado retornar� com o erro "EAGAIN" se algum outro processo
tiver trancado parte do arquivo.

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
A chamada ao sistema "lockf" deve ser usada preferencialmente
com as chamadas "open", "read", "write", ... e n�o
"fopen", "fread", "fwrite", ... da "stdio".
Isto porque as rotinas da "stdio" cont�m "buffers" fora do controle
do sistema operacional, podendo ser lidos/escritos dados
que est�o contidos em regi�es trancadas
(caso em que ser�o manipulados dados desatualizados). 
Se for essencial usar estas rotinas, deve-se utiliz�-las sem
"buffers" (ver "setbuf" (libc)) ou ent�o descarreg�-los
ap�s cada opera��o (ver "fflush" (libc)).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
alarm, creat, dup, exec, fcntl, lseek, open 
.br
.wo "(libc):"
setbuf, fflush
.br

.in
.sp
.b
REFER�NCIAS
.r
.in 5
IEEE Trial-Use Standard Portable Operating System for
Computer Environments (POSIX), IEEE.

.in
.sp
.b EXEMPLOS
.in 7
A aplica��o usual da chamada ao sistema � feito da seguinte forma:
.sp 2
.(l
	lseek (...);		/* Posiciona no registro desejado */

	lockf (F_LOCK, ...);	/* Tranca a regi�o */

	read (...);		/* le o registro */

	lseek (...);		/* Se for necess�rio, atualiza */
	write (...);		/* o registro */

	lseek (...);		/* Libera a regi�o */
	lockf (F_ULOCK, ...);
.)l

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
