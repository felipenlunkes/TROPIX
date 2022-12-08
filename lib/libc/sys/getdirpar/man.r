.bp
.he 'GETDIRPAR (sys)'TROPIX: Manual de Refer�ncia'GETDIRPAR (sys)'
.fo 'Atualizado em 02.11.05'Vers�o 4.8.0'Pag. %'

.b NOME
.in 5
.wo "getdirpar  -"
obtem informa��es sobre o pai de um diret�rio
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/types.h>
#include <sys/sysdirent.h>    (ou #include "dirent.h")

ino_t	getdirpar (dev_t dev, ino_t ino, DIRENT *dep);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "getdirpar" tenta obter informa��es
sobre o pai do diret�rio definido pelo par (dispositivo "dev", n�-�ndice "ino").

.sp
Se o diret�rio ("dev", "ino") for a pr�pria raiz dos sistemas de arquivos ("/"),
"getdirpar" retorna um valor NULO, sem informa��es adicionais.

.sp
Em caso contr�rio, retorna o n�-�ndice do pai do diret�rio, e preenche
os membros da estrutura apontada por "dep" do seguinte modo:

.sp
.(l
	d_name:		Nome do diret�rio
	d_namlen:	N�mero de caracteres do nome
	d_ino:		N�-�ndice do pr�prio diret�rio
	d_offset:	Dispositivo do pr�prio diret�rio
.)l

.sp
No caso particular do diret�rio dado ("dev", "ino")
for a raiz de um sistema de arquivos, os seguinte membros recebem:

.sp
.(l
	d_ino:		N�-�ndice do diret�rio montado
	d_offset:	Dispositivo deste diret�rio
.)l

.sp
N�o � necess�rio ter nenhuma permiss�o de leitura, escrita ou execu��o
do arquivo.

.sp
Esta chamada ao sistema � especialmente �til quando se caminha no
sistema de arquivos no sentido das folhas em dire��o � raiz
(inclusive ultrapassando os pontos de montagem), o que � �til para
a obten��o do caminho completo do diret�rio corrente.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve o n�mero do n�-�ndice
do diret�rio pai do diret�rio dado.
No caso particular do diret�rio dado ser "/", retorna NULO.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b OBSERVA��O
.in 5
Esta chamada ao sistema foi criada principalmente para facilitar
a fun��o da biblioteca "getcwd" (libc) (e portanto o utilit�rio "pwd" (cmd)).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd):  "
pwd
.br
.wo "(libc): "
getcwd
.br
.wo "(sys):  "
stat, instat
.br

.in
.sp
.b ESTADO
.in 5
Experimental
