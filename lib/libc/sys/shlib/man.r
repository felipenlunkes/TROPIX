.bp
.he 'SHLIB (sys)'TROPIX: Manual de Refer�ncia'SHLIB (sys)'
.fo 'Atualizado em 29.12.99'Vers�o 3.2.3'Pag. %'

.b NOME
.in 5
.wo "shlib -"
ger�ncia de bibliotecas compartilhadas
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/common.h>
#include <sys/shlib.h>

int	shlib (int op, ...);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "shlib" efetua diversas opera��es com bibliotecas compartilhadas.

.sp
Dependendo do argumento "op", a opera��o efetuada �:

.in +3
.ip 1. 3
SHLIB_LOAD: Carrega uma biblioteca compartilhada.

.sp
Neste caso, a chamada tem a forma

.sp
.(l
		int shlib (SHLIB_LOAD, const char *lib_nm);
.)l

.sp
A biblioteca compartihada "lib_nm" � carregada.
O �ndice � obtido do cabe�alho da pr�pria biblioteca.

.ip 2. 3
SHLIB_UNLOAD: Descarrega uma biblioteca compartilhada.

.sp
Neste caso, a chamada tem a forma

.sp
.(l
		int shlib (SHLIB_UNLOAD, int index);
.)l

.sp
A biblioteca compartihada de �ndice "index" � descarregada.

.ip 3. 3
SHLIB_TABLE: Preenche uma tabela com dados sobre as bibliotecas carregadas.

.sp
Neste caso, a chamada tem a forma

.sp
.(l
		int shlib (SHLIB_TABLE, SHLIB *ptr);
.)l

.sp
A �rea apontada por "ptr" � preenchida com NSHLIB estruturas SHLIB
fornecendo informa��es sobre as bibliotecas carregadas.
Esta estrutura est� definida no arquivo <sys/shlib.h>.

.ep
.in -3

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A fun��o devolve zero se conseguiu efetuar a opera��o.
No caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
