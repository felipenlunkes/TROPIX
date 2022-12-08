.bp 1
.he 'GETENV (libc)'TROPIX: Manual de Refer�ncia'GETENV (libc)'
.fo 'Atualizado em 01.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
getenv - obt�m o valor de uma vari�vel do ambiente

.in
.sp
.b SINTAXE
.in 5
.(l
const char	*getenv (const char *name);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "getenv" pesquisa o ambiente ("environment"),
procurando uma cadeia da forma
"name=value".

.sp
Devolve um ponteiro para "valor" caso 
encontre a cadeia, ou um ponteiro NULO em caso contr�rio.

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
putenv, delenv
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
