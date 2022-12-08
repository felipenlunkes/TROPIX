.bp
.he 'GETCH (curses)'TROPIX: Manual de Refer�ncia'GETCH (curses)'
.fo 'Atualizado em 28.09.89'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Entrada de um caractere do teclado
.sp
.wo "wgetch   -"
na posi��o corrente na janela dada
.br
.wo "getch    -"
na posi��o corrente na janela padr�o
.br
.wo "mvwgetch -"
dadas a janela e a posi�ao
.br
.wo "mvgetch  -"
dada a posi��o na janela padr�o

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

int wgetch (WINDOW *janela);
int getch (void);
int mvwgetch (WINDOW *janela, int linha, int coluna);
int mvgetch (int linha, int coluna);
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "wgetch" faz a entrada de um caractere do teclado para "janela",
na posi��o corrente.

.sp
A macro "getch" faz a entrada de um caractere para a janela padr�o ("stdwin").

.sp
As macros "mvwgetch" e "mvgetch" equivalem respectivamente
� rotina "wgetch" e � macro "getch" precedidas da rotina "wmove",
que estabelece para onde a entrada ser� realizada.

.sp
Normalmente a entrada de texto do teclado � realizada no seguinte modo:
.in 8
.ip (a)
com eco, utilizando a rotina "waddch" na janela indicada,
.ip (b)
editada por linha, 
.ip (c)
com gera��o de caracteres acentuados se o teclado n�o for capaz de ger�-los,
.ip (d)
convertendo o caractere <cr> no caractere <nl> e
.ip (e)
sem reconhecimento de teclas especiais.
.lp
.in 5
Como a entrada de texto � editada por linha,
somente ap�s o t�rmino de uma linha os seus caracteres
se tornam dispon�veis ao programa.
O modo de entrada de texto de cada janela pode ser reconfigurado
(veja "wgetset" (curses)).

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A rotina "wgetch" e as suas macros associadas
normalmente retornam um caractere lido do teclado;
em alguns casos especiais elas podem retornar
constantes predefinidas no arquivo para inclus�o "<curses.h>".
.sp
Quando a edi��o da entrada est� habilitada
a linha pode ser terminada pelos caracteres
<nl>, "eol" ou "eof" (veja "termio" (fmt));
neste caso chamadas sucessivas � rotina "wgetch"
retornam cada um dos caracteres da linha
e a seguir, de acordo com o caractere de termina��o,
respectivamente <nl> ou as constantes "EOL" e "EOT".
.sp
De acordo com a configura��o do modo de entrada,
a constante "ERR" pode ser retornada
imediatamente ap�s a recep��o de um sinal
ou para indicar que no momento da chamada � rotina "wgetch"
n�o havia caracteres dispon�veis
(veja "wgetset" (curses)).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd):   "
stty
.br
.wo "(libc):  "
strerror, perror
.br
.wo "(curses):"
waddch, wgetset, wgetstr, wmove, wscanw
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
