.bp 1
.he 'GETPASS (libc)'TROPIX: Manual de Refer�ncia'GETPASS (libc)'
.fo 'Atualizado em 03.06.97'Vers�o 3.0.2'Pag. %'

.b NOME
.in 5
getpass - l� uma senha do terminal

.in
.sp
.b SINTAXE
.(l
#include <sys/types.h>
#include <pwd.h>

char	*getpass (const char *prompt);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "getpass" l� uma senha do terminal associado ao processo, ap�s
escrever o "prompt" dado.

.sp
A senha pode ter at� 80 caracteres
(repare no entanto, que a fun��o "crypt" (libc), somente
considera os 14 primeiros caracteres).

.sp
A senha pode incluir quaisquer caracteres do c�digo ISO
exceto <^S>, <^Q>, <nl>,  <cr> e o caractere "kill"
(normalmente <^U>, ver "termio" (fmt)).

.sp
O caractere "kill" pode ser usado em caso de erro, para
ler novamente a senha completa.
Repare que os demais caracteres de "termio"
(tais como "erase", "aerase", "intr", "eof", etc ...)
n�o s�o processados, podendo fazer parte de uma senha.

.sp
Se o processo n�o tiver terminal associado, devolve um ponteiro NULO.

.in
.sp
.b OBSERVA��O
.in 5
A fun��o "getpass" devolve um ponteiro para uma �rea est�tica, e o
seu conte�do deve ser copiado caso ele seja necess�rio ap�s
a fun��o ser chamada novamente.

.in
.sp
.b ARQUIVOS
.in 5
/dev/tty

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
crypt
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
