.bp 1
.he 'PUTC (libc)'TROPIX: Manual de Refer�ncia'PUTC (libc)'
.fo 'Atualizado em 10.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Escreve um caractere ou uma palavra em um arquivo:
.sp
.wo "putc    -"
escreve um caractere em um arquivo dado
.br
.wo "putchar -"
escreve um caractere na sa�da padr�o ("stdout")
.br
.wo "fputc   -"
escreve um caractere em um arquivo dado (fun��o)
.br
.wo "putw    -"
escreve uma palavra em um arquivo dado
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>

int	putc (int c, FILE *fp);
int	putchar (int c);
int	fputc (int c, FILE *fp);
int	putw (int w, FILE *fp);
.)l

.in
.sp
.b DESCRI��O
.in 5
A macro "putc" escreve o caractere "c" no arquivo de sa�da "fp"
(na localiza��o dada pelo  ponteiro da posi��o do arquivo
se definido).

.sp
A macro  "putchar" � equivalente � "putc" com o segundo
argumento igual a "stdout".

.sp
A fun��o "fputc" � equivalente � macro "putc".
A fun��o � mais lenta do que a macro, 
mas cada chamada ocupa menos espa�o de mem�ria,
e o seu nome pode ser passado como um argumento
para uma fun��o.

.sp
A fun��o "putw" escreve uma palavra (ou seja um inteiro de 4 bytes)
no arquivo de sa�da "fp"
(na localiza��o dada pelo  ponteiro da posi��o do arquivo se definido).
A fun��o n�o exige nenhum tipo de alinhamento da palavra.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
As fun��es retornam o valor escrito e EOF em caso de erro
(exceto "putw", que retorna "ferror (fp)").
Um erro ocorre se o arquivo n�o for estiver aberto para
escrita ou o arquivo n�o possa mais crescer.

.in
.sp
.b OBSERVA��ES
.in 5
A fun��o "putw" � dependente de implementa��o, pois
nem todas as m�quinas tem o inteiro com 4 bytes, nem a ordem
dos bytes dentro da palavra � padronizada.
Isto significa que um arquivo escrito com "putw" em um computador
pode n�o ser lido corretamente com "getw" (libc) em outro computador.

.sp
� importante lembrar que "putc" e "putchar" s�o macros,
e portanto constru��es do tipo "putc (cp, *fp++)" podem n�o produzir
o efeito esperado. Deve-se utilizar "fputc" para estes casos.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
fclose, ferror, fopen, fread, printf, puts, setbuf,
.br
.wo "        stdio, getw"
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
