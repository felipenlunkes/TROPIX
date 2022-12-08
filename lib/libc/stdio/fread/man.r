.bp
.he 'FREAD (libc)'TROPIX: Manual de Refer�ncia'FREAD (libc)'
.fo 'Atualizado em 09.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Leitura/escrita sem convers�o:
.sp
.wo "fread  -"
leitura de registros
.br
.wo "fwrite -"
escrita de registros
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>

size_t fread (void *ptr, size_t size, size_t nregs, FILE *fp);
size_t fwrite (const void *ptr, size_t size,
					size_t nregs, FILE *fp);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "fread" l� "nregs" registros do arquivo "fp"
para a �rea de mem�ria apontada por "ptr".
Cada registro consiste de uma seq��ncia de "size" bytes
(N�O necessariamente terminado com um caractere NULO).
A fun��o n�o completa a leitura
se for detetado o final do arquivo (EOF),
ou ocorrer um erro.

.sp
A fun��o "fwrite" escreve  "nregs" registros apontados por 
"ptr" no arquivo  "fp".
A fun��o n�o completa a escrita se for detetado um erro.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Ambas as fun��es retornam o n�mero de itens lidos ou escritos
com sucesso.
Caso  "size" ou "nregs"
n�o for positivo, n�o ser� lido/escrito nenhum registro,
e ser� retornado zero.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
read, write
.br
.wo "(libc):"
fopen, getc, gets, printf, putc, puts, scanf, stdio
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
