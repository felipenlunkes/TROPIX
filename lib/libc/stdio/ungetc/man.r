.bp 1
.he 'UNGETC (libc)'TROPIX: Manual de Refer�ncia'UNGETC (libc)'
.fo 'Atualizado em 11.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
ungetc - insere um caractere na �rea de entrada/sa�da

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>

int	ungetc (int c, FILE *fp);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "ungetc" insere o caractere "c" na �rea de entrada/sa�da
associada ao arquivo de entrada "fp", de tal modo que este caractere
ser� retornado na pr�xima chamada a "getc".

.sp
A fun��o "ungetc" retorna "c" e n�o modifica o arquivo.

.sp
Se algum caractere j� foi lido do arquivo e o arquivo possui uma �rea
de entrada/sa�da, garante-se que pelo menos um caractere pode ser
inserido na �rea.

.sp
Se o valor de "c" for EOF, "ungetc" nada faz e EOF � retornado.

.in
.sp
.b
DIAGN�STICOS
.r
.in 5
A fun��o "ungetc" retorna EOF se n�o foi poss�vel inserir
o caractere na �rea de entrada/sa�da.

.in
.sp
.b OBSERVA��O
.in 5
A fun��o "fseek" desfaz todos os efeitos de "ungetc".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
fseek, getc, setbuf, stdio
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
