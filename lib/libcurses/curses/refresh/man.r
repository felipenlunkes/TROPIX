.bp
.he 'REFRESH (curses)'TROPIX: Manual de Refer�ncia'REFRESH (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Atualiza uma janela no v�deo:
.sp
.wo "wrefresh -"
uma janela dada
.br
.wo "refresh  -"
a janela padr�o ("stdwin")
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

void wrefresh (WINDOW *janela);
void refresh (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "wrefresh" atualiza "janela" no v�deo do terminal.
.sp
A macro "refresh" atualiza a janela padr�o ("stdwin").
.sp
O modo de atualiza��o de cada janela � configur�vel
(veja "wrefset" (curses)).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses): "
touchwin, wrefset
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
