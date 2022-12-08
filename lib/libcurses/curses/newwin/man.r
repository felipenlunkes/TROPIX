.bp
.he 'NEWWIN (curses)'TROPIX: Manual de Refer�ncia'NEWWIN (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
.wo "newwin -"
cria uma nova janela
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

WINDOW *newwin (int linhas, int colunas, int linhabase, int colunabase);
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "newwin" cria uma nova janela com tamanho dado
pelos par�metros "linhas" e "colunas"
e com o canto superior esquerdo localizado
no v�deo de acordo com os par�metros "linhabase" e "colunabase".

.sp
A contagem para as linhas e colunas do v�deo se inicia em zero
e segue de cima para baixo, no caso das linhas,
e da esquerda para a direita, no caso das colunas.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A rotina "newwin" normalmente retorna um ponteiro para uma estrutura "WINDOW"
que referenciar� a nova janela em todas as suas opera��es.
Em caso de erro, a rotina "newwin" retorna o ponteiro nulo "NOWINDOW".


.in
.sp
.b DIAGN�STICOS
.in 5
A cria��o de um nova janela n�o � poss�vel quando j� est�o excedidos
os limites de mem�ria determinados
pela implementa��o da biblioteca "curses".


.in
.sp
.b OBSERVA��O
.in 5
A exist�ncia de uma janela n�o implica em sua presen�a no v�deo;
para torn�-la vis�vel � necess�rio utilizar a rotina "touchwin".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses):"
delwin, touchwin, wbox
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
