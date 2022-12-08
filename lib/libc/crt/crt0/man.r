.bp 1
.he 'CRT0 (libc)'TROPIX: Manual de Refer�ncia'CRT0 (libc)'
.fo 'Atualizado em 26.09.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
crt0 - fun��o pr�logo para todos os programas em "C"
.sp

.in
.sp
.b DESCRI��O
.in 5
Esta fun��o � usada pelo sistema como pr�logo de
todos os programas escritos em linguagem "C". Ela trata
do manuseio dos parametros "argc" e "argv" junto com
a chamada ao sistema "exec".

.in
.sp
.b OBSERVA��O
.in 5
A fun��o "crt0" n�o foi concebida para ser chamada
por um programa de usu�rio.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
exec
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
