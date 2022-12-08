.bp
.he 'UNAME (sys)'TROPIX: Manual de Refer�ncia'UNAME (sys)'
.fo 'Atualizado em 22.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "uname -"
obt�m a identifica��o do sistema
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/syscall.h>

int	uname (UTSNAME *name);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "uname" obt�m a identifica��o do sistema.
Ela preenche a estrutura "UTSNAME" apontada por "name", que
tem os seguintes campos:

.sp
.nf
	char	uts_sysname[16];	/* Nome do Sistema */
	char	uts_systype[16];	/* Tipo do Sistema */
	char	uts_nodename[16];	/* Nome do n� */
	char	uts_version[16];	/* Vers�o */
	char	uts_date[16];		/* Data da vers�o */
	char	uts_time[16];		/* Tempo */
	char	uts_machine[16];	/* Computador */
	char	uts_customer[16];	/* Nome do Cliente */
	char	uts_depto[16];		/* Nome do Departamento */
	char	uts_sysserno[16];	/* N�mero de S�rie do Sistema */
.fi
.sp

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
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
uname
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
