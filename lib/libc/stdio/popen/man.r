.bp 1
.he 'POPEN (libc)'TROPIX: Manual de Refer�ncia'POPEN (libc)'
.fo 'Atualizado em 10.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
fun��es para entrada/sa�da de/para processos:
.sp
.wo "popen  -"
inicia uma comunica��o com um comando
.br
.wo "pclose -"
termina a comunica��o com um comando
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>

FILE	*popen	(const char *command, const char *mode);
int	pclose (FILE *fp);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "popen" cria um "pipe" (sys) entre o processo que a chamou
e o processo resultante da execu��o de "command"
retornando um ponteiro para a estrutura FILE associada ao "pipe".

.sp
A vari�vel "mode" define como o "pipe" � aberto
e deve ser "r" (para leitura) ou "w" (para escrita).
Um "pipe" de leitura (escrita) � uma forma de comunica��o em que
a sa�da (entrada) padr�o de "command" � desviada e pode ser lida (escrita)
pelo processo que o criou atrav�s de "fp".

.sp
Um "pipe" aberto por "popen" deve ser fechado por "pclose",
que espera o processo associado com o "pipe" terminar
e retorna o estado de t�rmino do comando.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A fun��o "popen", retorna um ponteiro NULO caso ocorra algum erro.
Neste caso, a vari�vel externa  "errno" cont�m  a raz�o do erro.

.sp
A fun��o "pclose" retorna -1 se "fp" n�o for associado
com um arquivo aberto por "popen".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
pipe
.br
.wo "(libc):"
system, stdio, perror
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
