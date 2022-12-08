.bp
.he 'EXECVP (sys)'TROPIX: Manual de Refer�ncia'EXECVP (sys)'
.fo 'Atualizado em 03.01.00'Vers�o 3.2.3'Pag. %'

.b NOME
.in 5
Executa um arquivo, utilizando os diret�rios do "PATH":
.sp
.wo "execlp  -"
dado um vetor de argumentos
.br
.wo "execvp  -"
dado um ponteiro para um vetor de argumentos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
int execlp (const char *arquivo, const char *arg0, ...);
int execvp (const char *arquivo, const char *argv[]);
.)l

.in
.sp
.b DESCRI��O
.in 5
As fun��es "execlp" e "execvp" s�o semelhantes respectivamente 
�s chamadas ao sistema "execl" e "execv" (ver "exec" (sys)),
com a diferen�a de que o arquivo dado � procurado nos v�rios
diret�rios dados pela vari�vel do ambiente "PATH" (ver "environ" (fmt)).

.sp
Repare que a lista de argumentos "arg0", "arg1", ... da fun��o
"execlp" deve ser terminada com um ponteiro NULO.

.sp
Se o nome do arquivo dado contiver um "/" (em qualquer posi��o),
este nome � considerado o nome definitivo, e a busca n�o � realizada.

.sp
Assim, se a vari�vel "PATH" contiver o valor ".:/bin:/usr/bin",
e o nome do arquivo for "ld", ser� tentada a execu��o dos
arquivos 

.sp
.in +8
 "ld"
 "/bin/ld"
 "/usr/bin/ld"
.in -8

.sp
(nesta ordem). Se o nome do arquivo for "/bin/ld" ou "old/ld", somente
estes nomes s�o tentados.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Se a chamada ao sistema retornou, � porque ocorreu um erro;
o valor de retorno � -1 e � indicada em "errno" a causa do erro.

.in
.sp
.b OBSERVA��ES
.in 5
N�o pode haver retorno de um "execlp" ou "execvp" com sucesso, pois o
processo � sobreposto pelo conte�do do novo arquivo execut�vel.

.sp
Nestas duas fun��es o ambiente � passado para o novo programa
execut�vel implicitamente, atrav�s da vari�vel externa "environ".

.sp
Se o ambinte n�o contiver a vari�vel "PATH", ser� utilizado 
o valor ".:/bin:/usr/bin".

.sp
Se um arquivo tem a permiss�o de acesso apropriada, mas n�o
se trata de um programa objeto execut�vel, automaticamente
� invocado o "sh" para executar o (poss�vel) arquivo
de comandos.

.in
.sp
.(t
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
exec
.br
.wo "(fmt): "
environ
.br
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.
