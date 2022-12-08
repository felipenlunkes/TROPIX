.bp
.he 'DELETELN (curses)'TROPIX: Manual de Refer�ncia'DELETELN (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Remo��o de uma linha
.sp
.wo "wdeleteln   -"
na posi��o corrente na janela dada
.br
.wo "deleteln    -"
na posi��o corrente na janela padr�o
.br
.wo "mvwdeleteln -"
dadas a janela e a posi��o
.br
.wo "mvdeleteln  -"
dada a posi��o na janela padr�o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

void wdeleteln (WINDOW *janela);
void deleteln (void);
void mvwdeleteln (WINDOW *janela, int linha);
void mvdeleteln (int linha);
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "wdeleteln" remove uma linha em "janela"
na posi��o corrente.
.sp
A macro "deleteln" remove uma linha na janela padr�o ("stdwin").
.sp
As macros "mvwdeleteln" e "mvdeleteln" equivalem respectivamente
� rotina "wdeleteln" e � macro "deleteln" precedidas da rotina "wmove",
que estabelece qual linha ser� removida.

.sp
A remo��o de uma determinada linha de uma janela
causa o deslocamento para cima de todas as linhas abaixo dela
e o surgimento de uma nova linha completamente em branco
na extremidade inferior da janela.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses):"
wdelch, winsertln
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
