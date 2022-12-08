.bp 1
.he 'CRYPT (libc)'TROPIX: Manual de Refer�ncia'CRYPT (libc)'
.fo 'Atualizado em 19.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
crypt - encripta uma senha

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

char	*crypt (const char *key, const char *salt);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "crypt" encripta a senha "key", influenciada pela
cadeia de 2 caracteres apontada por "salt".

.sp
Quaisquer caracteres podem ser usados na cadeia apontada por "key",
da qual apenas os primeiros 14 caracteres s�o considerados.
Os 2 caracteres da cadeia apontada por "salt"
devem pertencer ao conjunto [./0-9A-Za-z].

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A fun��o devolve um ponteiro para uma cadeia de 13 caracteres
(terminada por um NULO) contendo a senha encriptada,
na qual os dois primeiros caracteres
s�o os pr�prios caracteres apontados por "salt".

.sp
Os caracteres da senha encriptada pertencem ao mesmo conjunto
dado acima.

.in
.sp
.b OBSERVA��ES
.in 5
A fun��o usa 7 transforma��es que encriptam sucessivamente um
vetor padronizado contendo apenas s�mbolos 0 e 1.
Estas transforma��es s�o "perturbadas" pelos caracteres da cadeia "salt".
A senha encriptada � uma permuta��o dos elementos do vetor.

.sp
A fun��o "crypt" devolve um ponteiro para uma �rea est�tica, e o
seu conte�do deve ser copiado caso ela seja chamada novamente.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
login, passwd
.br
.wo "(libc):"
getpass
.br
.wo "(fmt): "
passwd
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
