.bp 1
.he 'DELENV (libc)'TROPIX: Manual de Refer�ncia'DELENV (libc)'
.fo 'Atualizado em 30.05.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
delenv - remove uma vari�vel do ambiente

.in
.sp
.b SINTAXE
.in 5
.(l
int	delenv (const char *name);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "delenv" pesquisa o ambiente ("environment"),
procurando uma cadeia da forma "name=value".

.sp
Se a cadeia for encontrada ela � removida e "delenv" retorna 0.
No caso contr�rio, a fun��o retorna -1.

.in
.sp
.b OBSERVA��ES
.in 5
O espa�o (do vetor de ponteiros) liberado pela remo��o de uma cadeia
do ambiente � reaproveitado por uma futura chamada a "putenv" (libc).

.sp
A cadeia da forma "name=value" n�o � mais referenciada pelo
ambiente, e o seu espa�o pode ser usado para outros fins.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
exec
.br
.wo "(libc):"
putenv, getenv
.br
.wo "(fmt): "
environ
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
