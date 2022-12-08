.bp
.he 'UTIME (sys)'TROPIX: Manual de Refer�ncia'UTIME (sys)'
.fo 'Atualizado em 24.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "utime -"
modifica os tempos de um arquivo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/types.h>
#include <sys/syscall.h>

int	utime (const char *path, const time_t tp[]);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "utime" permite alterar os tempos de acesso,
modifica��o e cria��o do arquivo cujo nome � dado pela cadeia de
caracteres apontada por "path". O processo tem que ser o dono do arquivo
ou ser superusu�rio para poder utilizar esta chamada ao sistema.

.sp
Os tempos s�o medidos pelo n�mero de segundos decorridos
desde 00:00:00, do dia primeiro de janeiro de 1970, hor�rio UT
(Tempo Universal, antes chamado de GMT).

.sp
Se "tp" for um ponteiro NULO, os tempos de acesso e modifica��o
s�o alterados para o tempo corrente (o tempo de cria��o n�o �
alterado).
.sp

Se "tp" for um ponteiro n�o NULO, ele � interpretado como sendo
um ponteiro para um vetor de 3 elementos do tipo "time_t", contendo
os tempos de acesso, modifica��o e cria��o (nesta ordem) que
devem ser postos no arquivo.

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
.b OBSERVA��O
.in 5
Repare que no TROPIX, o arquivo possui o tempo de cria��o
(e n�o o tempo de modifica��o do n�-�ndice), e
esta chamada ao sistema pode modificar todos os tr�s tempos.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
stat
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
