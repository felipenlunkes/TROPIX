.bp
.he 'MKNOD (sys)'TROPIX: Manual de Refer�ncia'MKNOD (sys)'
.fo 'Atualizado em 17.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "mknod -"
cria um arquivo de um tipo qualquer
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

int	mknod (const char *path, int mode, int dev);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "mknod" cria um novo arquivo cujo nome
� dado pela cadeia de caracteres apontada por "path".

.sp
O modo do arquivo � obtido atrav�s de "mode",
e � semelhante ao argumento "mode" utilizado na chamada ao sistema "chmod"
(sys), com a exce��o de que � necess�rio dar adicionalmente
o tipo do arquivo:

.sp
.in 12
.wo "S_IFREG:  "
Regular
.br
.wo "S_IFDIR:  "
Diret�rio
.br
.wo "S_IFIFO:  "
FIFO
.br
.wo "S_IFBLK:  "
Especial de Blocos
.br
.wo "S_IFCHR:  "
Especial de Caracteres

.sp
.in 5
O arquivo <stat.h> cont�m a defini��o completa dos diversos indicadores
do modo de um arquivo.

.sp
O UID do arquivo ser� o UID efetivo do processo, e o GID
do arquivo ser� o GID efetivo do processo.

.sp
Valores de tipos de arquivo n�o dados acima s�o indefinidos,
e n�o devem ser usados.

.sp
Os 9 indicadores de mais baixa ordem do "mode" (a prote��o) s�o
modificados pela m�scara de cria��o de arquivos do processo;
todos os indicadores ligados da m�scara s�o zerados (veja "umask" (sys)).

.sp
Se "mode" indica um arquivo especial de blocos ou caracteres,
o argumento "dev" indica a especifica��o de identifica��o
do dispositivo ("major" + "minor").
Se o arquivo n�o for especial de blocos ou caracteres,
"dev" � ignorado.

.sp
Esta chamada ao sistema s� pode ser usada por processos
n�o superusu�rios para a cria��o de FIFOs.

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
Para a cria��o de diret�rios, deve ser preferida a chamada ao sistema
"mkdir" (sys), pois "mknod" n�o cria as entradas "." e ".." necess�rias
para o funcionamento de um diret�rio.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
mkdir, chmod
.br
.wo "(sys): "
mkdir, chmod, exec, umask
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
