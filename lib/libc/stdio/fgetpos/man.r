.bp
.he 'FGETPOS (libc)'TROPIX: Manual de Refer�ncia'FGETPOS (libc)'
.fo 'Atualizado em 08.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Manipula��o do ponteiro da posi��o corrente de arquivos: 
.sp
.wo "fgetpos -"
obt�m o ponteiro
.br
.wo "fsetpos -"
restaura o ponteiro
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>

int	fgetpos (FILE *fp, fpos_t *pos);
int	fsetpos (FILE *fp, const fpos_t *pos);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "fgetpos" armazena o valor do ponteiro da posi��o corrente
do arquivo "fp" no objeto apontado por "pos".

.sp
A fun��o "fsetpos" posiciona o valor do ponteiro da posi��o corrente
do arquivo "fp" de acordo com o objeto apontado por "pos".
Este objeto deve conter o valor obtido atrav�s de uma chamada anterior
de "fgetpos" para o mesmo arquivo.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Ambas fun��es devolvem ZERO em caso de sucesso.
Em caso contr�rio, devolvem -1 e indicam em "errno" a causa do erro.

.in
.sp
.b OBSERVA��ES
.in 5
Lembre-se que as fun��es "fgetpos" e "fsetpos" n�o podem ser usadas em
arquivos associados a terminais, nem a "pipes".

.sp
As fun��es "fgetpos" e "fsetpos" desfazem os efeitos de "ungetc".

.sp
Ap�s um "fsetpos" em um arquivo de atualiza��o, a pr�xima opera��o pode ser
de leitura ou escrita.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
ftell, fseek, rewind
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
