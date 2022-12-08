.bp 1
.he 'FSEEK (libc)'TROPIX: Manual de Refer�ncia'FSEEK (libc)'
.fo 'Atualizado em 09.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Manipula��o do ponteiro da posi��o do arquivo:
.sp
.wo "fseek  -"
posiciona o ponteiro
.br
.wo "rewind -"
retorna o ponteiro ao in�cio
.br
.wo "ftell  -"
obtem o valor do ponteiro
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>

int	fseek (FILE *fp, long offset, int whence);
void	rewind (FILE *fp);
long	ftell (FILE *fp);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o  "fseek" posiciona o ponteiro do arquivo "fp"
para a pr�xima leitura ou escrita.
A nova posi��o do ponteiro ser�
� dist�ncia (com sinal) "offset"
do come�o, da posi��o corrente ou do final do arquivo,
conforme "whence" tenha respectivamente os valores
SEEK_SET, SEEK_CUR ou SEEK_END.

.sp
A fun��o "rewind" retorna ao in�cio o ponteiro de posi��o
do arquivo "fp". Ela  � equivalente a 
"fseek (fp, 0, SEEK_SET)", exceto que o indicador de erro tamb�m
� apagado.

.sp
A fun��o "ftell" devolve a posi��o corrente do ponteiro do 
arquivo "fp".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A fun��o  "fseek"
retorna um n�mero negativo
caso ocorra algum erro, caso contr�rio
retorna zero.
Lembre-se que "fseek" n�o pode ser usado em arquivos associados
a terminais, nem a "pipes".

.in
.sp
.b OBSERVA��ES
.in 5
As fun��es "fseek" e "rewind" desfazem os efeitos de "ungetc" e
apagam o indicador de "fim de arquivo".

.sp
Ap�s um "fseek" ou "rewind",
em um arquivo de atualiza��o, a pr�xima opera��o pode ser
de leitura ou escrita.

.sp
Como no sistema TROPIX n�o h� distin��o entre arquivos de texto ou
bin�rios, n�o h� restri��es no uso das fun��es "fseek" e "ftell".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
lseek
.br
.wo "(libc):"
fopen, popen, ungetc, fgetpos, fsetpos, feof
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
