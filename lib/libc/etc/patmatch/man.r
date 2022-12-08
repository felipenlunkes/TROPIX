.bp 1
.he 'PATMATCH (libc)'TROPIX: Manual de Refer�ncia'PATMATCH (libc)'
.fo 'Atualizado em 10.10.03'Vers�o 4.5.0'Pag. %'

.b NOME
.in 5
.wo "patmatch -"
reconhecedor de padr�es
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

int	patmatch (const char *str, const char *pattern);
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "patmatch" verifica se a cadeia de caracteres apontada
por "str" satisfaz o padr�o apontado por "pattern".

.sp
O padr�o "pattern" pode conter caracteres regulares, que
devem coincidir com os caracteres correspondentes de "str", e os
meta-caracteres "?", "*", "[", "]", "!", que devem corresponder
a zero ou mais caracteres de "str", segundo as regras dadas abaixo:

.in 8
.ip c 10 
Corresponde ao caractere "c" (supondo que "c" n�o � nenhum dos
meta-caracteres). 

.ip ? 10
Corresponde a (um) caractere qualquer.

.ip * 10
Corresponde a zero ou mais caracteres quaisquer.

.ip !c 10
Corresponde a qualquer caractere diferente de "c".

.ip [....] 10
Corresponde a um caractere igual a um dos caracteres entre os colchetes.
Podemos tamb�m ter
constru��es do tipo "x-y"
entre os colchetes,
que representa todos os caracteres de "x" a "y" (inclusive). 

.ip ![....] 10
Corresponde a um caractere que deve ser diferente de todos os caracteres
entre os colchetes. Assim como acima, "x-y" representa todos os
caracteres de "x" a "y".

.ip \c 10
Corresponde ao caractere "c". Esta constru��o � �til para desfazer
o efeito especial dos meta-caracteres.
.ep

.in 0
.sp
.b
VALOR DE RETORNO
.r
.in 5
A rotina devolve um valor positivo caso a cadeia tenha sido
aceita. Ela devolve zero se n�o foi aceita, ou se o padr�o cont�m
um erro de sintaxe.

.in
.sp
.b OBSERVA��O
.in 5
A implementa��o da rotina � eficiente, s� utilizando
recurs�o para o meta-caractere "*".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sh
.br

.in
.sp
.(t
.b EXEMPLOS
.in 5
O padr�o "*akefile" reconhece as cadeias "/src/cmd/Makefile" e
"/usr/lib/makefile", mas n�o a cadeia "makefile+"
.sp
O padr�o "?akefile" reconhece as cadeias "Makefile" e
"makefile", mas n�o a cadeia "/usr/man/makefile"
.sp
O padr�o "Make!gile" reconhece as cadeias "Makefile" e
"Makevile", mas n�o a cadeia "Makegile"
.sp
O padr�o "Make[afx-z]ile" reconhece as cadeias "Makeaile", "Makefile",
"Makeyile", mas n�o a cadeia "Makegile"
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
