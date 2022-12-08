.bp
.he 'ACCESS (sys)'TROPIX: Manual de Refer�ncia'ACCESS (sys)'
.fo 'Atualizado em 11.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "access -"
informa sobre a permiss�o de acesso a um arquivo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>
#include <unistd.h>

int	access (const char *path, int mode);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "access" verifica a permiss�o de acesso ao arquivo cujo
nome � dado pela cadeia de caracteres apontada por "path".
O argumento "mode" indica o tipo de acesso desejado ao arquivo.

.sp
Esta verifica��o � realizada
utilizando-se as identifica��es do usu�rio real (UID real) e
do grupo real (GID real), ao inv�s das identifica��es efetivas
(UID efetivo e GID efetivo).

.sp
O argumento "mode" cont�m um ou mais indicadores,
formado a partir de um out�rio de:
.sp 1
.nf
		F_OK	testa a existencia do arquivo
		R_OK	leitura
		W_OK	escrita
		X_OK	execu��o (ou busca em diret�rio)
.fi
.sp 1
A chamada ao sistema s� anuncia permiss�o de acesso
se todos os indicadores dados forem satisfeitos.  

.sp
Para o dono do arquivo, as permiss�es s�o verificadas na parte do
"dono" do modo do arquivo; para membros do grupo do arquivo
(que n�o s�o o dono),  as permiss�es s�o verificadas na parte do
"grupo"; para os demais as permiss�es s�o verificadas na parte dos
"outros" (ver "intro" (sys)).

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A chamada ao sistema devolve zero se o acesso � permitido.
No caso contr�rio, devolve -1 e indica em "errno" a causa da
proibi��o de acesso.

.in
.sp
.b OBSERVA��ES
.in 5
Esta chamada ao sistema � especialmente �til para programas
que utilizam o indicador "set user/group ID", pois verificam o acesso
em rela��o ao UID/GID real, e n�o ao efetivo.

.sp
Mesmo que o usu�rio real for super-usu�rio,
existem tr�s casos em ele n�o pode escrever em um arquivo:
quando o arquivo est� em um sistema de arquivos montado
apenas para leitura; quando o arquivo � um programa reentrante
sendo executado no momento; quando o arquivo � um diret�rio.

.sp
Repare que apenas os indicadores s�o verificados; "access" pode
informar que podemos escrever em um certo diret�rio, mas a
tentativa de abri-lo para escrita ir� falhar, porque n�o �
permitido escrever diretamente em diret�rios;
um arquivo pode parecer execut�vel para "access", mas a chamada ao
sistema "exec" falhar porque o arquivo n�o tem o formato pr�prio.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
intro, chmod, stat
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
