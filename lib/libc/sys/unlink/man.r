.bp
.he 'UNLINK (sys)'TROPIX: Manual de Refer�ncia'UNLINK (sys)'
.fo 'Atualizado em 23.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "unlink -"
remove uma entrada de um diret�rio
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	unlink (const char *path);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "unlink" remove uma refer�ncia a um arquivo,
ou seja, remove a entrada do diret�rio cujo nome � dado pela cadeia
de caracteres apontada por "path".

.sp
Quando todos as refer�ncias a um arquivo foram removidas,
e nenhum processo est� com o arquivo aberto, o espa�o ocupado
por ele � liberado e ele deixa de existir.

.sp
Se um ou mais processos
estiverem com o arquivo aberto quando a �ltima refer�ncia
for removida, a sua remo��o � adiada at� que todos os processos
fechem o arquivo.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve zero.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
rm
.br
.wo "(sys): "
close, link, open
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
