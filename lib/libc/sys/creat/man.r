.bp
.he 'CREAT (sys)'TROPIX: Manual de Refer�ncia'CREAT (sys)'
.fo 'Atualizado em 12.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "creat -"
cria um arquivo ou reescreve em um antigo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

int	creat (const char *path, int mode);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "creat" cria um arquivo novo ou prepara para
a reescrita em um arquivo j� existente. Em ambos casos, o nome
do arquivo � dado pela cadeia de caracteres apontada por "path".

.sp
Se o arquivo j� existe, o tamanho � truncado a zero (isto �,
o seu conte�do � apagado), mas o modo e UID/GID s�o conservados.

.sp
Em caso contr�rio, o UID/GID do arquivo ser� o UID/GID
efetivo do processo, e o modo do arquivo
(exceto o seu tipo "S_IFMT", ver <sys/stat.h>),
� obtido a partir do valor de "mode", com as seguintes
modifica��es:

.sp 1
.in 10
Todos os indicadores ligados da m�scara de cria��o de arquivos
s�o zerados (ver "umask" (sys)). 

.sp
Os indicadores para guardar a imagem dos programas reentrantes
("S_ISUID" e "S_ISGID", ver "chmod" (sys)),
s�o zerados.

.sp 1
.in 5
Ap�s um "creat" com sucesso, a chamada devolve um descritor de arquivos
que permite apenas escritas, mesmo que o modo dado n�o permita escritas.

.sp
O ponteiro do arquivo est� apontando
para o come�o do arquivo.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A chamada ao sistema devolve o descritor do arquivo (um n�mero
n�o negativo) se
conseguiu criar o arquivo novo ou preparar
a reescrita em um arquivo j� existente.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b OBSERVA��ES
.in 5
Um arquivo novo pode ser criado com um modo que pro�ba a escrita.

.sp
O descritor do arquivo � programado para que o arquivo
permane�a aberto atrav�s das chamadas ao sistema "exec".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
chmod, close, dup, fcntl, lseek, open, read, umask,
.br
.wo "        write"
.br

.in
.sp
.(t
.b ESTADO
.in 5
Efetivo.
.)t

.in
