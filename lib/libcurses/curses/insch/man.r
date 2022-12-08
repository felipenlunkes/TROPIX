.bp
.he 'INSCH (curses)'TROPIX: Manual de Refer�ncia'INSCH (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Insere um caractere:
.sp
.wo "winsch   -"
na posi��o corrente na janela dada
.br
.wo "insch    -"
na posi��o corrente na janela padr�o
.br
.wo "mvwinsch -"
dadas a posi��o e a janela
.br
.wo "mvinsch  -"
dada a posi��o na janela padr�o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

int winsch (WINDOW *janela, chtype ch);
int insch (chtype ch);
int mvwinsch (WINDOW *janela, int linha, int coluna, chtype ch);
int mvinsch (int linha, int coluna, chtype ch);
.)l

.sp

.in
.sp
.b DESCRI��O
.in 5
A rotina "winsch" insere o caractere "ch" na posi��o corrente em "janela".

.sp
A macro "insch" insere o caractere "ch" na janela padr�o ("stdwin").

.sp
As macros "mvwinsch" e "mvinsch" equivalem respectivamente
� rotina "winsch" e � macro "insch" precedidas da rotina "wmove",
estabelecendo a posi��o onde o caractere ser� escrito.

.sp
A inser��o de um caractere desloca o caractere na posi��o corrente
e os caracteres a sua direita na linha corrente
para a direita de acordo com o espa�o ocupado pelo caractere inserido.
O caractere que ocupava a �ltima coluna na linha corrente � perdido.
A posi��o corrente � avan�ada de modo
a que a pr�xima inser��o seja realizada imediatamente � direita da atual.
A inser��o de uma cadeia � equivalente � inser��o de seus caracteres.

.sp
Alguns caracteres t�m significado especial na inser��o.
O caractere <nl> faz com que os caracteres a direita da posi��o corrente
sejam movidos para uma nova linha que � inserida
(veja "winsertln" (curses)) imediatamente abaixo
e a posi��o corrente passe para o in�cio desta nova linha.
O caractere <ht> � expandido em espa�os at� que seja atingida
a pr�xima coluna de tabula��o na janela.
Os caracteres de controle s�o inseridos na forma "^X".

.sp
O tipo "chtype" engloba o caractere e seus atributos.
A rotina "winsch" insere o caractere "ch" com seus atributos
e com os atributos correntemente habilitados para "janela"
(veja "wattrset" (curses)).

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
As rotinas e macros retornam as constantes inteiras "OK" (em caso normal)
ou "ERR" (em caso de erro).

.in
.sp
.b DIAGN�STICOS
.in 5
A rotina "winsch" retorna "ERR" quando
inserindo na extremidade direita
caracteres que ocupam mais de uma coluna
da janela se as op��es "A_WRAP" ou "A_SCROLL"
n�o estiverem habilitadas no modo de escrita da janela.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses):"
wattrset, winsstr, winsertln, wmove, wprintw

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
