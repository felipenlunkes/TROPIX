.bp 1
.he 'PUTS (libc)'TROPIX: Manual de Refer�ncia'PUTS (libc)'
.fo 'Atualizado em 10.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Escreve uma cadeia em um arquivo:
.sp
.wo "puts   -"
escreve na sa�da padr�o ("stdout")
.br
.wo "fnputs -"
escreve em um arquivo dado inserindo um <nl>
.br
.wo "fputs  -"
escreve em um arquivo dado sem inserir um <nl>
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>

int	puts (const char *str);
int	fnputs (const char *str, FILE *fp);
int	fputs (const char *str, FILE *fp);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "puts" escreve a cadeia apontada por "str",
seguida de um <nl> na sa�da padr�o ("stdout").

.sp
A fun��o "fnputs" escreve a cadeia apontada por "str",
seguida de um <nl> no arquivo definido por "fp".

.sp
A fun��o "fputs" � an�loga � fun��o "fnputs", mas n�o escreve o <nl>.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Todas estas fun��es retornam ZERO em caso normal e EOF em caso de erro.
Este segundo caso ir� ocorrer no caso de se tentar escrever em um
arquivo que n�o est� aberto para a escrita.

.in
.sp
.b OBSERVA��O
.in 5
Nenhuma das fun��es acima escreve o caractere NULO
(que termina a cadeia) no arquivo.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
ferror, fopen, fread, printf, putc, stdio
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
