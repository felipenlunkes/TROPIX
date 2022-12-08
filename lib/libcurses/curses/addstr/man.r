.bp
.he 'ADDSTR (curses)'TROPIX: Manual de Refer�ncia'ADDSTR (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Entrada de cadeias do teclado:
.sp
.wo "waddstr   -"
na posi��o corrente na janela dada
.br
.wo "addstr    -"
na posi��o corrente na janela padr�o
.br
.wo "mvwaddstr -"
dadas a janela e a posi��o
.br
.wo "mvaddstr  -"
dada a posi��o na janela padr�o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

int waddstr (WINDOW *janela, char *str);
int addstr (char *str);
int mvwaddstr (WINDOW *janela, int linha, int coluna, char *str);
int mvaddstr (int linha, int coluna, char *str);
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "waddstr" escreve uma cadeia de caracteres em "janela"
a partir da posi��o corrente.
.sp
A macro "addstr" escreve a cadeia para a janela padr�o ("stdwin").
.sp
As macros "mvwaddstr" e "mvaddstr" equivalem respectivamente
� rotina "waddstr" e � macro "addstr" precedidas da rotina "wmove",
que estabelece onde a entrada ser� realizada.

.sp
O funcionamento da rotina "waddstr" e suas macros associadas
normalmente envolve a execu��o da rotina "waddch"
para cada caractere na cadeia apontada pelo par�metro "str".
Na ocorr�ncia de algum erro este procedimento � interrompido.

.sp
.in
.b
VALOR DE RETORNO
.r
.in 5
A rotina "waddstr" e as suas macros associadas
repassam o �ltimo valor retornado pela rotina "waddch".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses):"
waddch, waddset, wmove, wprintw
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
