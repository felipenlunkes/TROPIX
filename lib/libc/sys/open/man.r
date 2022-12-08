.bp 1
.he 'OPEN (sys)'TROPIX: Manual de Refer�ncia'OPEN (sys)'
.fo 'Atualizado em 17.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "open -"
abre um arquivo para leitura e/ou escrita
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	open (const char *path, int oflag, ...);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "open" abre para leitura e/ou escrita o arquivo
cujo nome � dado pela cadeia de caracteres apontada por "path".
Os indicadores do estado do arquivo s�o atribu�dos de acordo com "oflag".

.sp
O valor de "oflag" � constru�do a partir
de um out�rio dos indicadores da
lista abaixo (os tr�s primeiros s�o mutuamente exclusivos):

.in 8
.ip O_RDONLY 10
O arquivo � aberto apenas para leituras.

.ip O_WRONLY 10
O arquivo � aberto apenas para escritas.

.ip O_RDWR 10
O arquivo � aberto para leituras e escritas.

.ip O_NDELAY 10
Este indicador (cujo nome � O_NONBLOCK no padr�o POSIX),
afeta leituras e escritas
subsequentes (veja "read" e "write" (sys)).

.ip O_APPEND 10
Se este indicador estiver ligado, o ponteiro de posi��o do
arquivo � colocado no final do arquivo antes de cada escrita.

.ip O_CREAT 10
Se o arquivo j� existe, este indicador n�o tem efeito.
Em caso contr�rio, a chamada ao sistema espera o argumento adicional
"int mode"; o arquivo � criado, do mesmo modo do que a chamada
.sp
.nf
			"creat (path, mode)"

.fi
(veja "creat" (sys)).

.ip O_TRUNC 10
Se o arquivo j� existe, o seu tamanho � truncado a zero
(isto �, o seu conte�do � apagado), e o modo e dono/grupo
s�o conservados.

.ip O_EXCL 10
Se O_EXCL e O_CREAT est�o ligados, a chamada "open" ir�
falhar caso o arquivo j� exista. A fun��o deste indicador
� possibilitar executar a opera��o composta de "certificar-se
de que um arquivo n�o existe, e neste caso cri�-lo" de
maneira indivis�vel. 

.ip O_LOCK 10
Abra o arquivo de maneira exclusiva, isto �, enquanto este descritor
n�o for fechado, n�o ser� poss�vel um outro "open" neste arquivo.

.ep
.in 5
.sp 2
Alguns destes indicadores podem ser alterados posteriormente
ao "open" atrav�s da chamada "fcntl" (sys).

.sp
O ponteiro de posi��o do arquivo � colocado no in�cio do
arquivo.

.sp
O descritor de arquivos retornado ir� continuar
aberto atrav�s de chamadas
"exec" (veja "fcntl" (sys)).

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve o descritor do
arquivo, que deve ser usado em todas as opera��es com o arquivo.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
chmod, close, creat, dup, fcntl, intro, lseek, read
.br
.wo "        umask, write, signal"
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
