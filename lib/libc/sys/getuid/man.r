.bp
.he 'GETUID (sys)'TROPIX: Manual de Refer�ncia'GETUID (sys)'
.fo 'Atualizado em 14.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Obtem a identifica��o:
.sp
.wo "getuid  -"
real do usu�rio do processo
.br
.wo "geteuid -"
efetiva do usu�rio do processo
.br
.wo "getgid  -"
real do grupo do processo
.br
.wo "getegid -"
efetiva do grupo do processo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	getuid (void);
int	geteuid (void);
int	getgid (void);
int	getegid (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "getuid" devolve o UID real do processo.

.sp
A chamada ao sistema "geteuid" devolve o UID efetivo do processo.

.sp
A chamada ao sistema "getgid" devolve o GID real do processo.

.sp
A chamada ao sistema "getegid" devolve o GID efetivo do processo.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
intro, setuid
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
