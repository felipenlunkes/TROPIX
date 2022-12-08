.bp
.he 'TOUCHWIN (curses)'TROPIX: Manual de Refer�ncia'TOUCHWIN (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Altera a visibilidade de uma janela:
.sp
.wo "touchwin   -"
para m�xima prioridade
.br
.wo "untouchwin -"
para m�nima prioridade

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

void touchwin (WINDOW *janela);
void untouchwin (WINDOW *janela);
.)l

.in
.sp
.b DESCRI��O
.in 5
As rotinas "touchwin" e "untouchwin" p�em "janela"
no in�cio ou no fim, respectivamente,  da fila de visibilidade das janelas em um terminal.

.sp
A ordem de uma janela na fila de visibilidade determina
em cada posi��o do v�deo
correspondente a mais de uma janela
qual destas deve ser atualizada.
Assim a imagem final no v�deo sugere a superposi��o
das janelas mais priorit�rias sobre as de menor prioridade.

.sp
� necess�rio executar a rotina "touchwin"
pelo menos uma vez para cada janela criada,
de modo que ela possa ser efetivamente atualizada no v�deo.
O in�cio das atividades de "curses" (veja "incurses" (curses))
j� coloca a janela padr�o ("stdwin") no in�cio da fila de visibilidade.

.in
.sp
.b OBSERVA��O
.in 5
As rotinas "touchwin" e "untouchwin" automaticamente
atualizam o v�deo do terminal.
A rotina "touchwin" atualiza a janela referente ao seu argumento
e a rotina "untouchwin" atualiza todas as janelas vis�veis no terminal.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses): "
incurses, mvwin
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
