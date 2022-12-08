.bp
.he 'ADDCH (curses)'TROPIX: Manual de Refer�ncia'ADDCH (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Escreve um caractere:
.sp
.wo "waddch   -"
na posi��o corrente na janela dada
.br
.wo "addch    -"
na posi��o corrente na janela padr�o
.br
.wo "mvwaddch -"
dadas a posi��o e a janela
.br
.wo "mvaddch  -"
dada a posi��o na janela padr�o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

int waddch (WINDOW *janela, chtype ch);
int addch (chtype ch);
int mvwaddch (WINDOW *janela, int linha, int coluna, chtype ch);
int mvaddch (int linha, int coluna, chtype ch);
.)l

.sp
.in
.sp
.b DESCRI��O
.in 5
A rotina "waddch" escreve o caractere "ch" na posi��o corrente em "janela".
.sp
A macro "addch" escreve o caractere "ch" na janela padr�o ("stdwin").
.sp
As macros "mvwaddch" e "mvaddch" equivalem respectivamente
� rotina "waddch" e � macro "addch" precedidas da rotina "wmove",
estabelecendo a posi��o onde o caractere ser� escrito.

.sp
O tipo "chtype" engloba o caractere e seus atributos.
A rotina "waddch" escreve o caractere "ch" com seus atributos
e com os atributos correntemente habilitados para "janela"
(veja "wattrset" (curses)).

.sp
Normalmente os caracteres de controle t�m significado especial
para a rotina "waddch".
O caractere <nl> equivale a uma seq��ncia de espa�os
suficiente para preencher o restante da linha corrente.
O caractere <ht> � expandido em espa�os
at� que seja atingida a pr�xima coluna de tabula��o na janela.
Os caracteres <bs> e <cr> retrocedem a posi��o corrente
respectivamente para a coluna anterior
e para a primeira coluna na linha corrente.
Os demais caracteres de controle s�o escritos na forma "^X".
� poss�vel evitar a interpreta��o especial dos caracteres de controle
escrevendo-os diretamente na janela (veja "waddset" (curses)).

.sp
A rotina "waddch"
avan�a a posi��o corrente de acordo
com o espa�o ocupado pelo caractere escrito.
O avan�o da posi��o corrente � an�logo ao avan�o do cursor
na maioria dos terminais.
Dentro de uma linha a posi��o corrente avan�a
incrementando-se a coluna corrente,
ao final de uma linha passando-se para o in�cio da linha seguinte
e ao final da janela rolando-a.
Este comportamento pode ser alterado
(veja "waddset" (curses)).

.sp
Um conjunto de caracteres semigr�ficos est� dispon�vel
para escrita nas janelas.
Nos terminais que n�o suportam este caracteres,
eles ser�o atualizados com caracteres comuns,
tais como '-', '+', '|', etc...
Cada caractere semigr�fico pode ser referenciado
por uma vari�vel externa associada,
cujos nomes s�o prefixadas pela seq��ncia "ACS_".
A rela��o completa dos caracteres semigr�ficos
se encontra no arquivo para inclus�o "<curses.h>".

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
As seguintes situa��es causam erro:
chamada das rotinas e macros com par�metros inv�lidos
(por ex: janela nula ou posi��o fora da janela)
e a impossibilidade de escrever o caractere
devido � posi��o corrente ter ultrapassado o final da linha corrente
ou o final da janela (veja "waddset" (curses)).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses): "
waddset, waddstr, wattrset, winsch, wmove, wprintw,
.wo "          "
wscroll
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
