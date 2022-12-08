.bp 1
.he 'FTW (libc)'TROPIX: Manual de Refer�ncia'FTW (libc)'
.fo 'Atualizado em 25.04.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
ftw - caminha em uma �rvore do sistema de arquivos

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/types.h> 

#include <stat.h> 
#include <ftw.h>

int	ftw (const char *caminho, int (*ftn) ());

int	ftn (const char *nome, STAT *sp, int n);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "ftw" caminha por profundidade em pr�-ordem a �rvore do sistema de arquivos
cuja raiz � "caminho".

.bc	/*************************************/
A fun��o "ftw" visita um diret�rio antes de qualquer um de seus descendentes.
.ec	/*************************************/

.sp
Para cada arquivo visitado da �rvore, "ftw" chama a fun��o "ftn"
(que deve ser fornecida pelo usu�rio), com 3 argumentos: 
uma cadeia contendo o nome completo do arquivo, um ponteiro para
uma estrutura "stat" (sys) contendo informa��es sobre o arquivo,
e um inteiro, classificando o arquivo em:

.in +5
.ip 'FTW_D' 9
diret�rio

.ip 'FTW_SL' 9
elo simb�lico

.ip 'FTW_F' 9
outro tipo de arquivo

.ip 'FTW_NS' 9
arquivo para o qual a chamada ao sistema "stat" n�o p�de ser executada

.ip 'FTW_DNR' 9
diret�rio que n�o p�de ser lido

.ep
.in -5

.bc	/*************************************/
.sp 2
Para o parametro "ordem" deve ser dado um dos valores "FTW_PRE"
ou "FTW_POST".
Se for dado "FTW_PRE", a �rvore ser� caminhada em "pr�-ordem",
isto �, a fun��o "ftn" ser� chamada para cada um dos diret�rios
antes dos seus descendentes.
Se for dado "FTW_POST", a �rvore ser� caminhada em "p�s-ordem",
isto �, a fun��o "ftn" ser� chamada para cada um dos diret�rios
ap�s todos os seus descendentes.
.ec	/*************************************/

.sp
A �rvore � caminhada at� que todos os seus arquivos sejam visitados,
a fun��o "ftn" devolva um valor n�o NULO (ver abaixo)
ou algum erro seja detetado por "ftw" (tal como um erro de E/S).

.sp
Se a raiz "caminho" for de um elo simb�lico, ser� considerado o arquivo
referenciado por este elo. No entanto, se durante a caminhada da �rvore
for encontrado um elo simb�lico, ser� considerado o pr�prio elo.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A fun��o "ftw" retorna:

.in +3
.ip 1. 3
Zero, se "ftw" caminhou a �rvore integralmente
(exceto sub�rvores explicitamente puladas, ver abaixo).

.ip 2. 3
Menos um (-1), se "ftw" detetou algum erro.

.ip 3. 3
Um valor negativo igual ao valor retornado por "ftn",
caso esta retorne um valor negativo (ver abaixo).

.ep
.in -3

.sp 2
A fun��o "ftn" deve retornar:
.in +3

.ip 1. 3
Zero, para que o processamento da �rvore continue normalmente.

.ip 2. 3
Um valor negativo,
para que "ftw" interrompa imediatamente 
o processamento da �rvore, e retorne o valor recebido de "ftn".

.ip 3. 3
Um valor positivo,
no caso de "nome" ser um diret�rio 
e n�o for desejado que a sub�rvore cuja ra�z � "nome"
seja caminhada.
Neste caso, o processamento continuar� nas sub�rvores seguintes.

.ep
.in -3

.in
.sp
.b OBSERVA��ES
.in 5
A fun��o "ftw" N�O processa os arquivos "." e "..", isto �,
a fun��o "ftn" N�O � chamada para estes nomes.

.sp
A implementa��o da fun��o � feita recursivamente,
mas n�o h� limite na altura da �rvore.
A fun��o "ftw" aloca todas as suas �reas de trabalho atrav�s
de "alloca" (libc).

.sp
Como a aloca��o de mem�ria � feita atrav�s de "alloca" (e N�O
"malloc"), as �reas de trabalho s�o desalocadas mesmo que
a fun��o "ftn" execute um "longjmp" (libc).

.bc	/*************************************/
A implementa��o da fun��o � feita atrav�s de listas (e n�o
recursivamente), de tal modo que a altura da �rvore
n�o � limitada pelo n�mero de diret�rios abertos simult�neamente.
.ec	/*************************************/

.sp
Os argumentos "nome" e "sp" da fun��o chamada "ftn" s�o ponteiros
para �reas vol�teis, e os seus conte�dos devem ser copiados caso
sejam necess�rios ap�s o retorno da chamada a "ftn".

.sp
No caso de "ftn" ser chamada com o valor "FTW_NS", o conte�do da
�rea STAT apontada por "sp" n�o � significativo.

.sp
Para interromper o processamento, recomenda-se n�o utilizar o valor
menos um (-1) como retorno de "ftn" porque poder� ser confundido
com uma condi��o de erro detetada por "ftw".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
stat
.br
.wo "(libc):"
alloca, longjmp
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
