.bp
.he 'GETSTR (curses)'TROPIX: Manual de Refer�ncia'GETSTR (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Entrada de cadeias do teclado:
.sp
.wo "wgetstr   -"
na posi��o corrente na janela dada
.br
.wo "getstr    -"
na posi��o corrente na janela padr�o
.br
.wo "mvwgetstr -"
dadas a janela e a posi��o
.br
.wo "mvgetstr  -"
dada a posi��o na janela padr�o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

int wgetstr (WINDOW *janela, char *str);
int getstr (char *str);
int mvwgetstr (WINDOW *janela, int linha, int coluna, char *str);
int mvgetstr (int linha, int coluna, char *str);
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "wgetstr" faz a entrada de uma cadeia de caracteres
do teclado para "janela",
a partir da posi��o corrente, at� que seja encontrado um <nl>.

.sp
A macro "getstr" faz a entrada de uma cadeia para a janela padr�o ("stdwin").

.sp
As macros "mvwgetstr" e "mvgetstr" equivalem respectivamente
� rotina "wgetstr" e � macro "getstr" precedidas da rotina "wmove",
que estabelece onde a entrada ser� realizada.

.sp
O funcionamento da rotina "wgetstr" e suas macros associadas
envolve uma sequ�ncia de execu��es da rotina "wgetch"
at� que um caractere <nl> seja encontrado,
seja sinalizado um fim de arquivo
ou ocorra um erro.

.sp
.in
.b
VALOR DE RETORNO
.r
.in 5
A rotina "wgetstr" e as suas macros associadas
repassam o �ltimo valor retornado pela rotina "wgetch".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses):"
wgetch, wgetset, wmove
.br


.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
