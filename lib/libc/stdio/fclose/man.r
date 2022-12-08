.bp
.he 'FCLOSE (libc)'TROPIX: Manual de Refer�ncia'FCLOSE (libc)'
.fo 'Atualizado em 08.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
T�rmino do processamento de um arquivo:
.sp
.wo "fclose  -"
fecha um arquivo
.br
.wo "fflush  -"
atualiza o conte�do do arquivo no disco
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>

int	fclose (FILE *fp);
int	fflush (FILE *fp);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "fclose" atualiza o conte�do do arquivo "fp" no disco,
e em seguida o fecha.

.sp
A fun��o "fflush" apenas atualiza o conte�do do arquivo "fp" no disco,
deixando-o aberto.
Se "fp" for um ponteiro NULO, atualiza o conte�do de todos os arquivos
abertos.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Estas fun��es retornam 0 no caso normal, e EOF caso
ocorra algum erro.

.in
.sp
.b OBSERVA��O
.in 5
A fun��o "fclose" � automaticamente chamada para todos os
arquivos abertos, quando um programa termina normalmente.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
close, exit
.br
.wo "(libc):"
fopen, setbuf, setvbuf
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
