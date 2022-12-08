.bp
.he 'CLRTOEOL (curses)'TROPIX: Manual de Refer�ncia'CLRTOEOL (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Escreve espa�os
.sp
.wo "wclrtoeol -"
at� o fim da linha dada a janela
.br
.wo "wclrtobot -"
at� o fim da janela dada a janela
.br
.wo "clrtoeol  -"
at� o fim da linha na janela padr�o
.br
.wo "clrtobot  -"
at� o fim da janela na janela padr�o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

void wclrtoeol (WINDOW *janela);
void wclrtobot (WINDOW *janela);
void clrtoeol (void);
void clrtobot (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "wclrtoeol" escreve espa�os
da posi��o corrente at� o fim da linha corrente em "janela".

.sp
A rotina "wclrtobot" escreve espa�os
da posi��o corrente at� o fim (canto inferior direito) de "janela".

.sp
As macros "clrtoeol" e "clrtobot" s�o equivalentes
�s rotinas "wclrtoeol" e "wclrtobot" aplicadas � janela padr�o ("stdwin").


.in
.sp
.b OBSERVA��O
.in 5
A posi��o corrente permanece inalterada ap�s a chamada �s rotinas
"wclrtoeol" ou "wclrtobot".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses): "
wmove
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
