.bp
.he 'GETDIRENT (sys)'TROPIX: Manual de Refer�ncia'GETDIRENT (sys)'
.fo 'Atualizado em 05.08.01'Vers�o 4.0.0'Pag. %'

.b NOME
.in 5
.wo "getdirent -"
l� um vetor de entradas de um diret�rio
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/types.h>
#include <sys/sysdirent.h>

int	getdirent (int fd, DIRENT *area, int count);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "getdirent" tenta ler "count" bytes do diret�rio
associado ao descritor "fd" na �rea apontada por "area".
O descritor "fd" � obtido por uma das chamadas "open", "inopen",
"dup" ou "fcntl" (sys).

.sp
A �rea � preenchida com entradas do diret�rio em um formato 
independente do sistema de arquivo
(veja o arquivo <sys/sysdirent.h>),
e cada entrada cont�m os seguintes membros:

.in +3
.ip d_offset: 10
O deslocamento da entrada no diret�rio original.
Este valor pode ser usado para reler uma entrada
j� lida anteriormente (atrav�s de "lseek" (sys)).

.ip d_ino: 10
O n�mero do n�-�ndice.

.ip d_namlen: 10
O tamanho do identificador.

.ip d_name: 10
O identificador, cujo tamanho m�ximo � de MAXNAMLEN caracteres, al�m
do NULO terminal.

.ep
.in -3


.sp
A leitura � feita a partir da posi��o dada pelo ponteiro associado a "fd".
Ap�s a leitura, o ponteiro � incrementado do valor de bytes
realmente lidos.

.sp
Se a opera��o � realizada com sucesso, "getdirent" retorna o n�mero
de bytes lidos e colocados na �rea.
Sempre s�o retornadas entradas completas; se o
tamanho "count" n�o for um m�ltiplo do tamanho da estrutura DIRENT,
o valor residual ser� ignorado.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve um inteiro
n�o negativo, indicando o n�mero de bytes efetivamente lidos. 
Um valor NULO indica o final do arquivo.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
dup, fcntl, open, inopen, lseek
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
