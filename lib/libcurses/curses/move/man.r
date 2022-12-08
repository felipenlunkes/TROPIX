.bp
.he 'MOVE (curses)'TROPIX: Manual de Refer�ncia'MOVE (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Posi��o corrente em uma janela:
.sp
.wo "wmove  -"
estabelece posi��o na janela dada
.br
.wo "move   -"
estabelece posi��o na janela padr�o
.br
.wo "wgetyx -"
informa posi��o corrente dada a janela

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

int wmove (WINDOW *janela, int linha, int coluna);
int move (int linha, int coluna);
void wgetyx (WINDOW *janela, int linha, int coluna);
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "wmove" estabelece a posi��o corrente em "janela"
em "linha" e "coluna".
A macro "move" equivale � rotina "wmove" aplicada � janela padr�o ("stdwin").

.sp
A rotina "wgetyx" atribui �s vari�veis apontadas por "linha" e "coluna"
a posi��o corrente em "janela".

.sp
A contagem das linhas e das colunas come�a em zero
e � limitada pelo tamanho da janela.
As primeiras e �ltimas linhas e colunas n�o s�o acess�veis
quando a janela tem contorno (veja "wbox (curses)").

.sp
A cria��o de uma janela estabelece como posi��o corrente
as primeiras linha e coluna.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A rotina "wmove" e a macro "move" retornam "OK" ou "ERR".

.in
.sp
.b DIAGN�STICOS
.in 5
A rotina "wmove" retorna "ERR" quando a posi��o fornecida
est� fora dos limites da janela.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses):"
wbox
.br


.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
