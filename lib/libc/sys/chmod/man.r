.bp
.he 'CHMOD (sys)'TROPIX: Manual de Refer�ncia'CHMOD (sys)'
.fo 'Atualizado em 12.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "chmod -"
modifica a permiss�o de acesso a um arquivo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>

int	chmod (const char *path, int mode);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "chmod" modifica a parte de  permiss�o de acesso
do modo do arquivo "path", de acordo com o padr�o de indicadores dado em
"mode".
.sp

O arquivo <sys/stat.h> cont�m a defini��o completa dos diversos indicadores
do modo de um arquivo.
A seguir damos os significados dos principais indicadores
de permiss�o de acesso:

.in 10
.ip S_ISUID 10
O UID efetivo do processo passa a ser igual ao
dono do arquivo quando o arquivo � executado como um programa
("set user ID"). 

.ip S_ISGID 10
O GID efetivo do processo passa a ser igual ao
grupo do arquivo quando o arquivo � executado como um programa
("set group ID"). 

.ip S_IMETX 10
Uma imagem do programa � guardada na mem�ria interna
ap�s a execu��o, mesmo que n�o haja mais usu�rios do programa.

.ip S_ISVTX 10
Uma imagem do programa � guardada na �rea de SWAP (em disco)
ap�s a execu��o, mesmo que n�o haja mais usu�rios do programa.

.ip S_IRUSR 10
Permiss�o de leitura pelo usu�rio.

.ip S_IWUSR 10
Permiss�o de escrita pelo usu�rio.

.ip S_IXUSR 10
Permiss�o de execu��o (busca, se diret�rio) pelo usu�rio.

.ip S_IRWXG 10
Permiss�o de leitura, escrita, execu��o (busca) pelo grupo. 

.ip S_IRWXO 10
Permiss�o de leitura, escrita, execu��o (busca) pelos outros.

.ep

.sp 1
.in 5
Para poder trocar 
a parte de permiss�o de acesso do modo de um arquivo,
o usu�rio efetivo do processo  
deve ser o dono do arquivo ou ent�o ser o superusu�rio.

.sp
Se o usu�rio efetivo do processo n�o for o superusu�rio,
os indicadores para guardar a imagem do programa ap�s a execu��o
(S_IMETX e S_ISVTX) s�o zerados.

.sp
Se o usu�rio efetivo do processo n�o for o superusu�rio,
e o grupo efetivo do processo n�o � o grupo do arquivo,
o indicador S_ISGID ("set group ID") � zerado.

.sp
Se um programa reentrante tem um dos indicadores para
guardar a imagem ap�s a execu��o ligado, o sistema
operacional conserva uma imagem do programa na �rea de SWAP
ou na mem�ria interna
quando o �ltimo usu�rio do programa termina.
Isto faz com que o programa j� esteja dispon�vel
quando o pr�ximo usu�rio executar o programa,
tornando sua execu��o mais r�pida.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A chamada ao sistema devolve zero se conseguiu alterar 
a permiss�o de acesso do arquivo.
No caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
chmod
.br
.wo "(sys): "
chown, creat, exec, fcntl, mknod, open, read, write 
.br

.in
.sp
.b ARQUIVOS
.in 5
/usr/include/sys/stat.h

.in
.sp
.b ESTADO
.in 5
Efetivo.
