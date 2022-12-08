.bp 1
.he 'LIB (fmt)'TROPIX: Manual de Refer�ncia'LIB (fmt)'
.fo 'Atualizado em 22.08.01'Vers�o 4.0.0'Pag. %'

.b NOME
.in 5
.wo "lib -"
formato da biblioteca de m�dulos objeto
.br

.in
.sp
.b DESCRI��O
.r
.in 5
Este documento descreve o formato adotado para organiza��o de bibliotecas
de m�dulos objeto n�o compartilhadas no sistema TROPIX.

.sp
Para obter informa��es sobre as bibliotecas compartilhadas, veja "mkshlib" (cmd).

.sp 2
.b
1. Estrutura das bibliotecas:
.r

.in +3
.sp
A organiza��o de bibliotecas no sistema TROPIX aproveita a estrutura
hier�rquica inerente ao sistema de arquivos do TROPIX. De maneira gen�rica,
uma biblioteca deve estar contida em uma �rvore.
Os m�dulos objeto podem estar na raiz desta �rvore ou em subdiret�rios.

.sp
Na raiz da biblioteca temos o "arquivo de sinopse", uma colet�nea de
informa��es sobre os m�dulos contidos na biblioteca.
Este arquivo tem o nome padr�o de ".LIBSYM".
Abaixo, vemos um exemplo de  organiza��o de biblioteca:

.sp 2
.(t
.nf
                          /lib/libx  (Diret�rio Raiz)
                               x
                               |
        +--------------+-------+-------+-------+-------+
        |              |               |               |
     .LIBSYM          dirm            dirn    ...     dirp
                       |               |               |
                 +---+---+---+   +---+---+---+   +---+---+---+
                 |   |  ...  |   |   |  ...  |   |   |  ...  |
                m1  m2      mi  n1  n2      nj  p1  p2      pk
.fi
.)t

.sp 2
A escolha deste formato trouxe uma grande vantagem do ponto de vista do
usu�rio: a antiga ordena��o, eminentemente topol�gica, que prevalecia
para as bibliotecas do sistema UNIX original, deixa de ser aqui necess�ria.
O usu�rio �, assim, liberado da preocupa��o de conhecer as
interdepend�ncias entre os m�dulos da biblioteca para poder construi-la
corretamente, evitando falhas no processo de "link-edi��o".

.in -3
.sp 1
.b
2. Estrutura do arquivo de sinopse de s�mbolos:
.r

.sp
.in +3
O arquivo de sinopse ".LIBSYM" � um arquivo de texto.
� composto de um cabe�alho, com um "n�mero m�gico", para que possa
ser identificado como um arquivo de sinopse.
Em seguida, consiste de uma linha para cada m�dulo, contendo o seu nome,
n�mero do seu n�-�ndice e a respectiva lista de s�mbolos definidos.


.sp
Como exemplo, damos abaixo o arquivo de sinopse da biblioteca "/lib/libm",
isto �, o arquivo "/lib/libm/.LIBSYM":
.sp
.nf
	   299792458
	   conv/fcvt.o,3001:__fcvt
	   conv/pottb.o,2999:__pottb
	   conv/strtod.o,2998:_strtod
	   float/fexcep.o,2996:__fgcr,__fgiar,__fgsr,__fscr, ...
	   float/fgman.o,2995:_HUGE_VAL,_faexp,_fgexp,_fgfra, ...
	   float/fixdfsi.o,2994:___fixdfsi
	   float/fixunsdfsi.o,2993:___fixunsdfsi
	   float/frexp.o,2992:_frexp,_ldexp,_modf
	   math/asin.o,2990:_acos,_asin
	   math/atan.o,2989:_atan,_atan2
	   math/exp.o,2988:_exp,_exp10,_exp2,_expb,_pow
	   math/floor.o,2987:_ceil,_fabs,_floor,_fmod
	   math/hypot.o,2986:_hypot
	   math/log.o,2985:_log,_log10,_log2,_logb
	   math/sin.o,2984:_cos,_sin
	   math/sinh.o,2983:_cosh,_sinh,_tanh
	   math/sqrt.o,2982:_sqrt
	   math/tan.o,2981:_tan
.fi

.in -3
.sp 1
.b
3. Outros detalhes
.r

.in +3
.ip a. 3
N�o h� limites nem na altura da �rvore, nem nos comprimentos dos nomes
dos m�dulos e s�mbolos.

.ip b. 3
A manipula��o de bibliotecas, envolvendo opera��es de inser��o,
remo��o e atualiza��o de m�dulos deve ser feita via o utilit�rio
"mklib" (cmd), especialmente projetado para esta finalidade. Qualquer outro
procedimento utilizado no sentido de alterar o conte�do de uma
biblioteca n�o mais garantir� a integridade estrutural da mesma.
Em particular, o utilit�rio "mklib" possui uma op��o em seu funcionamento
cuja finalidade � simplesmente a verifica��o desta integridade.

.ip c. 3
Se a �rvore de uma biblioteca for copiada, ser� necess�rio
reconstruir o arquivo de sinopse atrav�s de "mklib",
pois os n�s-�ndices ser�o outros.

.ep

.in
.sp
.b
ARQUIVOS
.r
.in 5
.wo ".../.LIBSYM"
.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
ld, mklib, mkshlib
.br
.wo "(sys): "
inopen
.br
.wo "(fmt): "
a.out
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
