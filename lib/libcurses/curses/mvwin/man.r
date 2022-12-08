.bp
.he 'MVWIN (curses)'TROPIX: Manual de Refer�ncia'MVWIN (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
.wo "mvwin -"
movimento da janela
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

void mvwin (WINDOW *janela, int linha, int coluna);
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "mvwin" altera a posi��o de "janela" no v�deo do terminal.

.in
.sp
.b OBSERVA��O
.in 5
A rotina "mvwin" automaticamente atualiza todas as janelas
no terminal.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses): "
wmove, touchwin
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
