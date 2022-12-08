.bp
.he 'ERASE (curses)'TROPIX: Manual de Refer�ncia'ERASE (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Preenche totalmente uma janela com espa�os:
.sp
.wo "werase -"
uma janela dada
.br
.wo "erase  -"
a janela padr�o ("stdwin")
.br
.wo "wclear -"
uma janela dada com a op��o "R_CLEAR"
.br
.wo "clear  -"
a janela padr�o com a op��o "R_CLEAR"
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

void werase (WINDOW *janela);
void erase (void);
void wclear (WINDOW *janela);
void clear (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "werase" preenche "janela" com espa�os.

.sp
A macro "erase" equivale � rotina "werase" aplicada � janela padr�o ("stdwin").

.sp
As macros "wclear" e "clear" s�o respectivamente equivalentes
� rotina "werase" e � macro "erase" com a op��o de atualiza��o "R_CLEAR"
(veja "wrefset" (curses)).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses):"
wclrtoeol, wrefset
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
