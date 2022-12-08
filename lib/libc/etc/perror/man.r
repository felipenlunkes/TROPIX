.bp 1
.he 'PERROR (libc)'TROPIX: Manual de Refer�ncia'PERROR (libc)'
.fo 'Atualizado em 23.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Obten��o das mensagens de erro das chamadas ao sistema:
.sp
.wo "perror      -"
imprime a mensagem de erro
.br
.wo "errno       -"
o n�mero do erro
.br
.wo "strerror    -"
obt�m uma cadeia com a mensagem de erro 
.br

.in
.sp
.b SINTAXE
.(l
#include <errno.h>

void	perror (const char *pgname);
extern int	errno;	

#include <string.h>

char	*strerror (int err);
.)l

.sp
.b DESCRI��O
.in 5
A fun��o "perror" escreve uma mensagem na sa�da de erro padr�o
(descritor de arquivos 2), descrevendo
o �ltimo erro ocorrido durante uma chamada ao sistema.

.sp
Em primeiro lugar � impressa  a cadeia
"pgname" (que em geral cont�m o nome do programa), seguida de
":" (dois pontos), um <sp>, a mensagem de erro e um <nl>.
O n�mero do erro � obtido da vari�vel "errno".

.sp
A vari�vel "errno" cont�m sempre o n�mero do �ltimo erro ocorrido
durante uma chamada ao sistema. Note que esta vari�vel N�O � zerada
quando � feita uma chamada ao sistema com sucesso.

.sp
A fun��o "strerror" devolve um ponteiro para uma cadeia contendo uma
descri��o correspondente ao c�digo num�rico "err" de um erro.
A cadeia n�o cont�m o <nl> de final de linha.

.in
.sp
.b DIAGN�STICOS
.in 5
A fun��o "strerror" devolve um ponteiro para as mensagens
"Erro Desconhecido" ou "Erro ZERO", caso o argumento "err" contenha,
respectivamente, um n�mero de erro inv�lido ou NOERR (zero).
Em situa��es an�logas, "perror" imprime estas mesmas mensagens.

.in
.sp
.b OBSERVA��O
.in 5
Os textos das mensagens de erro N�O est�o mais inclu�dos em m�dulos
da "libc", mas s�o obtidos do n�cleo do TROPIX atrav�s de uma chamada
ao sistema. Deste modo, as vari�veis "sys_errlist" e "sys_nerr" N�O
existem mais; sua funcionalidade foi assumida pela fun��o "strerror".

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
