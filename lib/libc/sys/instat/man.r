.bp
.he 'INSTAT (sys)'TROPIX: Manual de Refer�ncia'INSTAT (sys)'
.fo 'Atualizado em 14.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.bc	/*************************************/
.wo "instat  -"
obtem o estado de um arquivo dados "dev" e "ino"
.br
.ec	/*************************************/
.wo "instat  -"
obtem o estado de um arquivo dados o dispositivo e o
.br
.wo "          n�-�ndice"

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

int	instat (int dev, int ino, STAT  *sp);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "instat" obt�m o estado (isto �, uma s�rie de
informa��es) de um arquivo.
Com a chamada ao sistema "instat" o arquivo � identificado
n�o pelo seu "caminho" como em "stat" (sys), mas sim pelo par
(dispositivo, n�-�ndice).

.sp
N�o � necess�rio ter nenhuma permiss�o de leitura, escrita ou execu��o
do arquivo.
.bc	/*************************************/
� necess�rio ter no m�nimo uma das permiss�es para ler,
escrever ou executar o arquivo.
Esta chamada verifica apenas a prote��o do arquivo em si,
e n�o do caminho que leva a ele, e � destinada a utilit�rios especiais.
.ec	/*************************************/

.sp
O par (dispositivo, n�-�ndice) normalmente � obtido atr�ves de um "stat"
anterior de um diret�rio, de onde se obt�m o dispositivo "dev",
seguido da leitura deste diret�rio, de onde se obt�m o n�-�ndice
"ino" de cada um de seus filhos.

.sp
O argumento "sp" � um ponteiro para uma estrutura "STAT", que
� preenchida com as informa��es sobre o arquivo
(que podem ser vistas em "stat" (sys)).

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
.wo "(sys): "
stat, upstat
.br

.in
.sp
.b ESTADO
.in 5
Efetivo
