.bp
.he 'DELCH (curses)'TROPIX: Manual de Refer�ncia'DELCH (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Remove um caractere
.sp
.wo "wdelch   -"
na posi��o corrente na janela dada
.br
.wo "delch    -"
na posi��o corrente na janela padr�o
.br
.wo "mvwdelch -"
dadas a posi��o e a janela
.br
.wo "mvdelch  -"
dada a posi��o na janela padr�o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

void wdelch (WINDOW *janela);
void delch (void);
void mvwdelch (WINDOW *janela, int linha, int coluna);
void mvdelch (int linha, int coluna);
.)l


.in
.sp
.b DESCRI��O
.in 5
A rotina "wdelch" remove o caractere na posi��o corrente em "janela".

.sp
A macro "delch" remove um caractere na janela padr�o ("stdwin").

.sp
As macros "mvwdelch" e "mvdelch" equivalem respectivamente
� rotina "wdelch" e � macro "delch" precedidas da rotina "wmove",
estabelecendo qual caractere ser� removido.

.sp
Quando um caractere � removido todos os caracteres � direita
e na mesma linha s�o deslocados para a esquerda de uma coluna
e � escrito um espa�o na �ltima coluna.
A posi��o corrente permanece inalterada.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses): "
wdeleteln, wmove
.ep

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
