.bp
.he 'INSERTLN (curses)'TROPIX: Manual de Refer�ncia'INSERTLN (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Inser��o de uma linha:
.sp
.wo "winsertln   -"
na posi��o corrente da janela dada
.br
.wo "insertln    -"
na posi��o corrente da janela padr�o
.br
.wo "mvwinsertln -"
dadas a janela e a posi��o
.br
.wo "mvinsertln  -"
dada a posi��o na janela padr�o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

void winsertln (WINDOW *janela, char *str);
void insertln (char *str);
void mvwinsertln (WINDOW *janela, int linha, char *str);
void mvinsertln (int linha, char *str);
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "winsertln" insere a linha "str" em "janela"
na posi��o corrente.
.sp
A macro "insertln" insere uma linha na janela padr�o ("stdwin").

.sp
As macros "mvwinsertln" e "mvinsertln" equivalem respectivamente
� rotina "winsertln" e � macro "insertln" precedidas da rotina "wmove",
que estabelece qual linha ser� removida.

.sp
A inser��o de uma nova linha em uma janela
causa o deslocamento das linhas abaixo dela para baixo,
desaparecendo a linha antes existente na extremidade inferior da janela.
A nova linha � inserida completamente em branco.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses):"
winsch, wdeleteln
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
