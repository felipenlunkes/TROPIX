.bp
.he 'CURSES (curses)'TROPIX: Manual de Refer�ncia'CURSES (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
curses - biblioteca desenvolvimento de aplicativos interativos

.sp
.in
.b SINTAXE
.in 5
.(l
#include <curses.h>
.)l

.in
.sp
.b DESCRI��O
.in 5
A biblioteca "curses" cont�m rotinas e defini��es de macros
que facilitam a constru��o de interfaces programa-usu�rio
atrav�s da cria��o e manipula��o de janelas em terminais de v�deo.
Os programas que usam a "curses" independem dos tipos de terminais
em que s�o executados.

.sp
Janelas s�o estruturas bidimensionais de texto
que podem ser total ou parcialmente expostas no v�deo do terminal.
A forma de apresenta��o das janelas e o texto nelas contido
s�o definidos pelo programador atrav�s da execu��o de rotinas e macros,
enquanto que as a��es necess�rias para atualizar o v�deo do terminal
s�o realizadas pela "curses".

.sp
Cada rotina ou macro dispon�vel na biblioteca "curses"
realiza um dos seguintes tipos de fun��o:
.in 10
.sp
 (a) ativa��o da "curses",
 (b) manipula��o de janelas,
 (c) entrada e sa�da nas janelas e
 (d) configura��o da entrada e sa�da.
.in 5

.sp
As rotinas de ativa��o da "curses"
s�o usadas para iniciar e terminar a sua opera��o,
assim como para suspend�-la temporariamente
quando for desejado executar outros programas.
A biblioteca "curses" pode operar com um ou v�rios terminais.

.sp
A manipula��o de janelas
corresponde a opera��es que atingem a janela como um todo.
Dentre estas opera��es encontram-se
a cria��o  e remo��o de janelas
e a altera��o de caracter�sticas das janelas existentes,
tais como tamanho, localiza��o
e prioridade de visibilidade.

.sp
As opera��es de entrada e sa�da
s�o usadas pelo programador para definir o conte�do das janelas.
Estas opera��es sempre s�o realizadas
em uma posi��o no interior da janela, denominada posi��o corrente,
que pode ser modificada usando-se a rotina "wmove",
e s�o baseadas
nas rotinas "wgetch" (leitura de um caractere do teclado),
"waddch" (escrita de um caractere),
"winsch" (inser��o de um caractere) e
"wdelch" (remo��o de um caractere).
Estas rotinas avan�am a posi��o corrente
correspondendo aos caracteres lidos, escritos ou inseridos.
As janelas podem ainda ser demarcadas no v�deo
por um contorno (veja "wbox" (curses)).

.sp
O comportamento das opera��es de entrada e sa�da � configur�vel
independentemente para cada janela de modo a atender necessidades espec�ficas
de cada janela.
As op��es de configura��o s�o agrupadas de acordo suas funcionalidades em:
.in 10
.sp
 (a) modo de entrada de texto do teclado,
 (b) modo de escrita nas janelas,
 (c) modo de atualiza��o do v�deo e
 (d) conjunto de atributos correntes.
.in 5
.sp
Todas as janelas s�o criadas com a configura��o
que normalmente � a utilizada com maior freq��ncia
(veja "newwin" (curses)).

.sp
Uma janela � identificada por um ponteiro para uma estrutura do tipo "WINDOW".
O ponteiro correspondente a cada janela � obtido na sua cria��o
e a identifica nas opera��es seguintes.
A inicia��o da biblioteca "curses" (veja "incurses" (curses))
normalmente j� cria uma janela padr�o (denominada  "stdwin")
que � associada ao terminal correntemente em uso e ocupa todo o seu v�deo.
Um ponteiro nulo ("NOWINDOW") identifica uma janela inexistente.

.sp
As vari�veis externas "COLS" e "LINES", declaradas no arquivo "<curses.h>"
cont�m respectivamente o n�mero de colunas e de linhas no v�deo do terminal.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
As rotinas e macros da biblioteca retornam em sua maioria
um dentre os valores inteiros "OK" e "ERR" definidos no arquivo "<curses.h>",
indicando respectivamente uma opera��o bem sucedida ou a ocorr�ncia de um erro.

.in
.sp
.b OBSERVA��O
.in 5
Esta biblioteca, apesar da semelhan�a na forma de utiliza��o,
n�o � compat�vel com a biblioteca "curses" criada originalmente
na Universidade da California em Berkeley
nem com a vers�o da biblioteca "curses" dispon�vel no UNIX System V da AT&T.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd):   "
tic, tac
.br
.wo "(curses):"
incurses, newwin, wgetch, waddch, winsch, wdelch,
.wo "         "
wmove, wrefresh, touchwin, wbox
.br
.wo "(fmt):   "
terminfo
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
