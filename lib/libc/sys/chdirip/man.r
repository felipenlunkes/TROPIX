.bp 1
.he 'CHDIRIP (sys)'TROPIX: Manual de Refer�ncia'CHDIRIP (sys)'
.fo 'Atualizado em 12.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "chdirip -"
troca de diret�rio corrente (dado o ponteiro)
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/types.h>
#include <sys/inode.h>
#include <sys/syscall.h>

int	chdirip (const INODE *ip);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "chdirip" faz com que o diret�rio corrente
passe a ser o diret�rio cujo ponteiro para a estrutura
"INODE" � dado pelo argumento "ip". Este ponteiro deve ser
dado como um endere�o virtual do espa�o de endere�amento
do n�cleo do sistema operacional.

.sp
Esta chamada � reservada para superusu�rios, e � destinada
para utilit�rios sofisticados.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A chamada ao sistema devolve zero se conseguiu trocar de diret�rio
corrente. 
No caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
chdir
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
