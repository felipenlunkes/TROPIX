.bp
.he 'ADDSET (curses)'TROPIX: Manual de Refer�ncia'ADDSET (curses)'
.fo 'Atualizado em 29.01.89'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Controla o modo de escrita em uma janela:
.sp
.wo "waddset -"
estabelece o modo
.br
.wo "waddon  -"
habilita algumas op��es do modo
.br
.wo "waddoff -"
desabilita algumas op��es do modo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

void waddset (WINDOW *janela, int modo);
void waddon (WINDOW *janela, int op��es);
void waddoff (WINDOW *janela, int op��es);
.)l

.in
.sp
.b DESCRI��O
.in 5
As macros "waddset", "waddon" e "waddoff"
controlam o modo de escrita de cada janela.

.sp
A macro "waddset" estabelece o modo de escrita,
enquanto que as macros "waddon" e "waddoff"
habilitam e desabilitam, respectivamente, algumas de suas op��es.

.sp
O modo de escrita
� estabelecido habilitando ou desabilitando suas op��es
de acordo com os seguintes indicadores:

.in 10
.ip "A_WRAP:" 11
Permite a passagem para a primeira coluna da pr�xima linha
ap�s a �ltima coluna da linha corrente.

.ip "A_SCROLL:" 11
Rolamento da Janela.
Quando esta op��o est� habilitada 
a escrita ap�s o canto inferior direito da janela
causar� um rolamento na janela.

.ip "A_PAGE:" 11
Pagina��o.
Esta op��o tem o objetivo de evitar que o usu�rio perca informa��o
quando uma seq��ncia muito longa de linhas � escrita em uma janela
antes que a rotina "wrefresh" seja chamada.
Quando esta op��o est� habilitada,
logo antes da janela sofrer um rolamento
que oculte alguma linha ainda n�o mostrada ao usu�rio,
a janela � atualizada
e espera-se o usu�rio apertar alguma tecla
antes que a escrita na janela prossiga;
se a tecla for o caractere <esc> a op��o torna-se inoperante
at� a pr�xima atualiza��o da janela.

.ip "A_REAL:" 11
Os caracteres de controle s�o escritos diretamente na janela,
ou seja, sem serem transformados para a forma "^X" ou expandidos
em espa�os (para os caracteres de tabula��o).
.ep
.in 5
.sp
Estes indicadores podem ser combinados atrav�s do operador "|"
("ou" bit a bit).

.sp
O modo de escrita inicial de cada janela
� o estabelecido pela execu��o da macro "waddset"
com os indicadores "A_WRAP" e "A_SCROLL".
.ep

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses):"
waddch, winsch, wattrset, wgetset, wrefset
.br


.in
.sp
.b EXEMPLOS
.in 5
A chamada a seguir reestabelece a configura��o inicial de escrita
na janela padr�o:
.in 10
.sp
waddset (stdwin, A_WRAP|A_SCROLL);

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
