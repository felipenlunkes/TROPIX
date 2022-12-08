.bp
.he 'REMOVE (libc)'TROPIX: Manual de Refer�ncia'REMOVE (libc)'
.fo 'Atualizado em 26.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "remove -"
remove uma entrada de um diret�rio
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>

int	remove (const char *filenm)
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "remove" remove um ponteiro para um arquivo,
ou seja, remove a entrada do diret�rio cujo nome � dado por "filenm".

.sp
Quando todos os ponteiros para um arquivo foram removidos,
e nenhum processo est� com o arquivo aberto, o espa�o ocupado
por ele � liberado e o arquivo deixa de existir.

.sp
Se um ou mais processos estiverem com o arquivo aberto
quando o �ltimo ponteiro for removido, a sua remo��o
� adiada at� que todos os processos fechem o arquivo.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a fun��o devolve zero.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
rm
.br
.wo "(sys): "
close, unlink, open
.br
.wo "(libc):"
fclose, fopen
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
