.bp
.he 'REFSET (curses)'TROPIX: Manual de Refer�ncia'REFSET (curses)'
.fo 'Atualizado em 11.04.89'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Controla o modo de atualiza��o do v�deo:
.sp
.wo "wrefset -"
estabelece o modo
.br
.wo "wrefon  -"
habilita algumas op��es do modo
.br
.wo "wrefoff -"
desabilita algumas op��es do modo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

void wrefset (WINDOW *janela, int modo);
void wrefon (WINDOW *janela, int op��es);
void wrefoff (WINDOW *janela, int op��es);
.)l

.in
.sp
.b DESCRI��O
.in 5
As macros "wrefset", "wrefon" e "wrefoff"
controlam o modo de atualiza��o do v�deo para cada janela.

.sp
A macro "wrefset" estabelece o modo de atualiza��o do v�deo,
enquanto que as macros "wrefon" e "wrefoff"
respectivamente habilitam e desabilitam algumas de suas op��es.

.sp
O modo de atualiza��o do v�deo
� estabelecido habilitando ou desabilitando suas op��es
de acordo com os seguintes indicadores:

.in +3
.ip "R_CLEAR:" 11
Limpar o v�deo antes de atualiz�-lo.
Esta op��o � desabilitada ap�s cada chamada � rotina "wrefresh",
ou seja ela s� � v�lida para a pr�xima chamada � "wrefresh".

.ip "R_CURSOR:" 11
Ap�s a atualiza��o de "janela",
posicionar o cursor na sua posi��o corrente.

.ip "R_INPUT:" 11
Atualizar a janela antes de cada entrada via teclado.
Para as janelas em que as opera��es de escrita s�o
seguidas de opera��es de entrada,
esta op��o
elimina a necessidade do programador explicitamente
chamar a rotina "wrefresh" para atualizar a janela.

.ip "R_INVIS:" 11
Manter o cursor invis�vel durante a atualiza��o.

.(t
.ip "R_WATCH:" 11
Observa��o do teclado.
Este indicador habilita
a interrup��o da atualiza��o em curso do v�deo do terminal
se um caractere for teclado.
A interrup��o da atualiza��o � �til em aplica��es
nas quais a entrada de cada caractere
pode determinar uma realimenta��o visual
que signifique uma grande altera��o no v�deo,
se for considerado que quando o usu�rio
tecla rapidamente uma sequ�ncia de caracteres,
ele n�o necessita realmente da realimenta��o visual
consequente a cada caractere, mas apenas ao �ltimo.
Neste caso, a interrup��o da atualiza��o
evita um processo longo de atualiza��o do v�deo
para uma s�rie de estados intermedi�rios,
melhorando o tempo de resposta ao usu�rio.
� garantido que a atualiza��o do v�deo
abranger� pelo menos
a atualiza��o da linha corrente
e o movimento final do cursor para a posi��o corrente
(no caso das janelas em que a perman�ncia do cursor
sobre a posi��o corrente ap�s a atualiza��o � obrigat�ria).
.)t

.ip "R_FORCE:" 11
Garantir o posicionamento do cursor antes da atualiza��o.

.ip "R_HOLD:" 11
Enviar efetivamente os caracteres correspondentes � pr�xima atualiza��o
apenas quando houver entrada do teclado.
Esta op��o � �til para ocasi�es
em que v�rias janelas s�o atualizadas em seq��ncia
e deseja-se, com o objetivo de tornar o programa mais eficiente,
atualiz�-las todas num �nico fluxo de caracteres para o terminal.

.in -3
.ep
.in 5
.sp
Estes indicadores podem ser combinados atrav�s do operador "|"
("ou" bit a bit).

.sp
O modo inicial de atualiza��o do v�deo de todas as janelas
inclui as op��es correspondentes ao indicador "R_CURSOR".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses):"
waddset, wattrset, wgetset, wrefresh
.br

.in
.sp
.b EXEMPLOS
.in 5
A chamada a seguir reestabelece a configura��o inicial de atualiza��o
na janela padr�o:
.in 10
.sp
wrefset (stdwin, R_CURSOR);

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
