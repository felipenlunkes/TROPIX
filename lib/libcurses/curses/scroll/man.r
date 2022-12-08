.bp
.he 'SCROLL (curses)'TROPIX: Manual de Refer�ncia'SCROLL (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Rolamento de uma janela:
.sp
.wo "wscroll -"
uma janela dada
.br
.wo "scroll  -"
a janela padr�o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

void wscroll (WINDOW *janela, int n);
void scroll (int n);
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "wscroll" realiza um rolamento de "n" linhas em "janela".
.sp
A rotina "scroll" equivale � rotina "wscroll" aplicada � janela padr�o.

.sp
De acordo com o sinal do n�mero "n",
o rolamento ser� para cima ("n" positivo) ou para baixo.
Em um rolamento para cima (baixo)
a primeira (�ltima) linha na janela � perdida,
as linhas restantes s�o deslocadas para cima (baixo)
e surge uma nova linha totalmente em branco
na extremidade inferior (superior) da janela.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses): "
addch, addset
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
