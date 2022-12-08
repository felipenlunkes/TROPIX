.bp
.he 'DUP (sys)'TROPIX: Manual de Refer�ncia'DUP (sys)'
.fo 'Atualizado em 13.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Duplica um descritor de arquivo:
.sp
.wo "dup  -"
com o mais baixo n�mero dispon�vel
.br
.wo "dup2 -"
dado o n�mero do novo descritor
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	dup (int fd1);
int	dup2 (int fd1, int fd2);
.)l

.in
.sp
.b DESCRI��O
.in 5
As chamadas ao sistema "dup" e "dup2" duplicam descritores de arquivos
abertos.
O descritor "fd1" �
obtido a partir de  uma chamada "creat", "dup", "dup2",
"open", "fcntl" ou "pipe".

.sp
Estas chamadas devolvem um novo descritor tendo as seguintes propriedades
em comum com "fd1":

.sp
.in 10
Mesmo arquivo aberto.
.sp
Mesmo ponteiro de posi��o do arquivo.
.sp
Mesmo modo de acesso (leitura, escrita ou leitura/escrita).

.sp
.in 5
A chamada ao sistema "dup" devolve um novo descritor cujo n�mero
� escolhido pelo
sistema operacional.
.sp
A chamada ao sistema "dup2" devolve um novo descritor cujo n�mero
� "fd2".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A chamada ao sistema devolve o valor do novo descritor (um n�mero
n�o negativo) em caso de sucesso. 
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b OBSERVA��ES
.in 5
A chamada "dup" devolve o descritor de n�mero mais baixo dispon�vel.

.sp
No caso de "dup2", se "fd2"
se referir a um arquivo aberto, ele � fechado
antes de se referir ao mesmo arquivo a que se refere "fd1".

.sp
As chamadas ao sistema "dup" e "dup2" s�o mantidas por raz�es
hist�ricas; os servi�os prestados s�o equivalentes � chamada
ao sistema "fcntl" (sys) com o comando "F_DUPFD".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
close, creat, exec, fcntl, open, pipe
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
