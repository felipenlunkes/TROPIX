.bp
.he 'INSSTR (curses)'TROPIX: Manual de Refer�ncia'INSSTR (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Inser��o de uma cadeia:
.sp
.wo "winsstr   -"
na posi��o corrente da janela dada
.br
.wo "insstr    -"
na posi��o corrente da janela padr�o
.br
.wo "mvwinsstr -"
dadas a janela e a posi��o
.br
.wo "mvinsstr  -"
dada a posi��o na janela padr�o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

int winsstr (WINDOW *janela, char *str);
int insstr (char *str);
int mvwinsstr (WINDOW *janela, int linha, int coluna, char *str);
int mvinsstr (int linha, int coluna, char *str);
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "winsstr" escreve uma cadeia de caracteres em "janela"
a partir da posi��o corrente.
.sp
A macro "insstr" escreve a cadeia para a janela padr�o ("stdwin").

.sp
As macros "mvwinsstr" e "mvinsstr" equivalem respectivamente
� rotina "winsstr" e � macro "insstr" precedidas da rotina "wmove",
que estabelece onde a entrada ser� realizada.

.sp
O funcionamento da rotina "winsstr" e suas macros associadas
envolve a execu��o da rotina "winsch"
para cada caractere na cadeia apontada pelo par�metro "str".
.sp
.in
.b
VALOR DE RETORNO
.r
.in 5
A rotina "winsstr" e as suas macros associadas
repassam o valor retornado pela rotina "winsch"
quando chamada para o �ltimo caractere em "str".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses):"
wattrset, winsch, wmove
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
