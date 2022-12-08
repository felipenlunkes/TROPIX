.bp
.he 'UPSTAT (sys)'TROPIX: Manual de Refer�ncia'UPSTAT (sys)'
.fo 'Atualizado em 24.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "upstat  -"
obtem o estado de um diret�rio montado
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/types.h>
#include <sys/syscall.h>
#include <stat.h>

int	upstat (dev_t dev, STAT *sp);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "upstat" obt�m o estado (isto �, uma s�rie de
informa��es) de um diret�rio oculto sob um ponto de montagem do
sistema de arquivos.

O diret�rio � identificado pelo n�mero do dispositivo "dev"
do sistema de arquivos nele montado.
O argumento "sp" � um ponteiro para uma estrutura "STAT", que
� preenchida com as informa��es sobre o arquivo
(que podem ser vistas em "stat" (sys)).

.sp
N�o � necess�rio ter nenhuma permiss�o de leitura, escrita ou execu��o
do arquivo.

.sp
Esta chamada ao sistema � especialmente �til quando se caminha no
sistema de arquivos no sentido das folhas em dire��o � raiz
(atrav�s de ".."), para ultrapassar um ponto de montagem.
Ao atingir um ponto de montagem, isto �, a raiz do sistema de arquivos
montado, pode-se usar "upstat" para obter o estado do diret�rio
oculto sob o ponto de montagem (em especial o seu n�-�ndice), e
o n� �ndice de seu diret�rio pai (que � o valor de retorno da chamada).
Lendo-se este diret�rio pai e procurando-se o n� �ndice do filho,
obtem-se o nome deste diret�rio oculto.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve o n�mero do n�-�ndice
do diret�rio pai do diret�rio oculto pela montagem.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b OBSERVA��O
.in 5
Esta chamada ao sistema foi criada principalmente para facilitar
a fun��o da biblioteca "getcwd" (libc) (e portanto o utilit�rio "pwd" (cmd)).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd):  "
pwd
.br
.wo "(libc): "
getcwd
.br
.wo "(sys):  "
stat, instat
.br

.in
.sp
.b ESTADO
.in 5
Experimental
