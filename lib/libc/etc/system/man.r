.bp 1
.he 'SYSTEM (libc)'TROPIX: Manual de Refer�ncia'SYSTEM (libc)'
.fo 'Atualizado em 26.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "system  -"
executa um comando
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

int	system (const char *comando);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "system" entrega a cadeia "comando" para o interpretador
de comandos "sh" como se a linha tivesse sido dada no terminal.
A fun��o espera at� que o comando e o "sh" terminem, e devolve
o codigo de retorno do "sh".

.sp
Uma cadeia NULA para "comando" � considerada uma consulta
sobre a exist�ncia de um interpretador de comandos.

.in
.sp
.b DIAGN�STICOS
.in 5
A fun��o "system" executa as chamadas ao sistema "fork" e "exec" 
para executar o comando. Se uma delas falhar, "system" devolve
um valor negativo e um c�digo de erro em "errno". 

.sp
Para o caso de uma cadeia NULA, a fun��o retorna um valor n�o
NULO se existe um interpretador de comandos.
No nosso caso temos o interpretador de comandos "sh", e o valor
de retorno � 1.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sh
.br
.wo "(sys): "
exec, fork
.br

.in
.sp
.b
REFER�NCIAS
.r
.in 5
Kernighan, B. W.,
"UNIX I/O PROGRAMMING",
pg. 17.

.in
.sp
.b ARQUIVOS
.in 5
/bin/sh

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
