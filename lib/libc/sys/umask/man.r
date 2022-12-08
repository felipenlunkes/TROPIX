.bp
.he 'UMASK (sys)'TROPIX: Manual de Refer�ncia'UMASK (sys)'
.fo 'Atualizado em 22.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "umask -"
obtem e modifica a m�scara de cria��o de arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/types.h>
#include <sys/syscall.h>
#include <stat.h>

int	umask (int cmask);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "umask" atribui o valor "cmask" � m�scara
de cria��o de arquivos do processo, e devolve o valor anterior
da m�scara.

.sp
Somente os 9 indicadores de mais baixa ordem s�o usados,
ou seja, a parte referente � prote��o do arquivo
(a descri��o completa dos indicadores � dado em <stat.h>).

.sp
A m�scara de cria��o do processo � utilizado durante as chamadas
ao sistema "open", "creat", "mknod". Indicadores presentes em "cmask"
s�o zerados no modo do arquivo criado.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
mkdir, sh
.br
.wo "(sys): "
chmod, creat, mknod, open
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
