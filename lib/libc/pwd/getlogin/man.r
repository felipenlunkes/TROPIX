.bp 1
.he 'GETLOGIN (libc)'TROPIX: Manual de Refer�ncia'GETLOGIN (libc)'
.fo 'Atualizado em 07.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
getlogin - obt�m o nome do usu�rio dado no login

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/types.h>
#include <pwd.h>

char	*getlogin (void)
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "getlogin" retorna um ponteiro para o nome do usu�rio, como foi
dado no comando de "login", e est� registrado no arquivo "/etc/utmp". 
Pode ser usado conjuntamente com "getpwnam", para localizar
a entrada correta do arquivo de contas/senhas, quando v�rios
usu�rios tem a mesma identifica��o num�rica. 

.sp
A melhor maneira de obter o nome do usu�rio � chamar "getlogin",
e se falhar, chamar "getpwuid" (ou "pwcache").

.in
.sp
.b DIAGN�STICOS
.in 5
Devolve um ponteiro NULO se n�o conseguiu obter o nome do usu�rio.
Isto pode ocorrer (por exemplo) se "getlogin" � chamado por um
processo que n�o tem um terminal associado.

.in
.sp
.b OBSERVA��O
.in 5
A fun��o "getlogin" devolve um ponteiro para uma �rea est�tica, e o
seu conte�do deve ser copiado caso ele seja necess�rio ap�s
a fun��o ser chamada novamente.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
pwent, pwcache
.br
.wo "(fmt): "
utmp
.br

.in
.sp
.b ARQUIVOS
.in 5
/etc/utmp

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
