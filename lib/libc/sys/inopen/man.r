.bp 1
.he 'INOPEN (sys)'TROPIX: Manual de Refer�ncia'INOPEN (sys)'
.fo 'Atualizado em 14.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "inopen -"
abre um arquivo dados dispositivo e n�-�ndice
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	inopen (int dev, int ino);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "inopen" abre um arquivo que � identificado
n�o pelo seu "caminho" como "open" (sys), mas sim pelo par
(dispositivo, n�-�ndice). Este par pode ser obtido atrav�s
de uma chamada "stat" ou "fstat" (sys).

.sp
Esta chamada verifica apenas
a prote��o do arquivo em si, e n�o do caminho que leva a ele,
e � destinada a utilit�rios especiais.

.sp
O arquivo � aberto apenas para leituras.

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
arquivo.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
open, chmod, close, creat, dup, fcntl, intro, lseek,
.br
.wo "        read, umask, write"
.br

.in
.sp
.b ESTADO
.in 5
Efetivo
.in
