.bp
.he 'LOCALE (libc)'TROPIX: Manual de Refer�ncia'LOCALE (libc)'
.fo 'Atualizado em 03.02.98'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
Localiza��o do comportamento de algumas fun��es da "libc":
.sp
.wo "setlocale  -"
controla a localiza��o
.br
.wo "localeconv -"
fornece informa��es para uma formata��o num�rica
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <locale.h>

const char *setlocale (int category, const char *locale);
const LCONV *localeconv (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
Estas fun��es gerenciam a localiza��o do comportamento de algumas
fun��es da "libc" em rela��o a convers�es de campos num�ricos, compara��o
de cadeias de caracteres e convers�es de tempos e datas.

.sp
A fun��o "setlocale" seleciona o comportamento das fun��es apropriadas
do programa, de ac�rdo com os argumentos "category" e "locale".
Esta fun��o pode ser usada para consultar e/ou alterar 
a localiza��o do comportamento de t�das as fun��es
(que permitem localiza��o) ou somente de algumas delas.

.sp
O argumento "category" pode assumir os seguintes valores:

.in +3
.ip "LC_ALL:" 13
Modifica simultaneamente o comportamente de t�das as fun��es
(que permitem localiza��o).
Uma chamada com este valor � equivalente a chamar a fun��o
"setlocale", uma vez com cada um dos valores abaixo.

.ip "LC_COLLATE:" 13
Modifica o comportamente das fun��es "strcoll" e "strxfrm"
(ainda N�O implementado).

.ip "LC_CTYPE:" 13
Modifica o comportamente das fun��es de manuseamento de caracteres
(ainda N�O implementado).

.ip "LC_MONETARY:" 13
Modifica a informa��o de formata��o monet�ria retornada pela fun��o
"localeconv"
(ainda N�O implementado).

.ip "LC_NUMERIC:" 13
Modifica o comportamente das convers�es num�ricas das fun��es de entrada/sa�da
formatada, assim como a informa��o de formata��o n�o-monet�ria retornada pela fun��o
"localeconv"
(ainda N�O implementado).

.ip "LC_TIME:" 13
Modifica o comportamente da fun��o "strftime".

.ep
.in -3

.sp
No momento, somente est�o definidos dois valores para "locale", que s�o
"P" (para portugu�s) e "E" (para ingl�s).
Os valores "" e "C" s�o equivalentes a "P".
Tamb�m pode ser dada uma cadeia NULA para "locale"
(veja o VALOR de RETORNO, abaixo).

.sp
Todos os programas sempre come�am como se tivesse sido realizada a chamada

.sp
.nf
		setlocale (LC_ALL, "P");
.fi

.sp
A fun��o "localeconv" retorna um ponteiro para uma estrutura de tipo "lconv"
contendo diversos valores �teis para a formata��o de quantidades num�ricas
(monet�rias ou n�o), de ac�rdo com a localiza��o corrente.
Consulte o arquivo de inclus�o "locale.h" para ver os membros da estrutura.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Se o argumento "locale" for um ponteiro n�o NULO, e
a cadeia apontada contiver um valor aceit�vel, a fun��o "setlocale" altera a
localiza��o e retorna um ponteiro para a nova cadeia associada
� categoria "category" especificada.
Se o valor N�O for aceit�vel, "setlocale" retorna um ponteiro NULO,
e a localiza��o n�o � alterada.

.sp
Se o argumento "locale" for um ponteiro NULO, a fun��o retorna
um ponteiro para a cadeia associada � categoria "category" especificada
(sem efetuar nenhuma altera��o).

.in
.sp
.b OBSERVA��O
.in 5
Como j� foi indicado acima, na presente vers�o do sistema, apenas
a fun��o "strftime" (libc) est� sendo afetada pelo "locale". 

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
strftime
.br

.in
.sp
.b ARQUIVOS
.in 5
/usr/include/locale.h

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
