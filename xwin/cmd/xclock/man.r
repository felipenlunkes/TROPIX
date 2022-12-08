.bp
.he 'XCLOCK (xwin)'TROPIX: Manual de Refer�ncia'XCLOCK (xwin)'
.fo 'Escrito em 19.03.03'Vers�o 4.4.0'Pag. %'

.b NOME
.in 5
xclock - rel�gio anal�gico para o X-Window.

.in
.sp
.b SINTAXE
.in 5
xclock [op��es]

.in
.sp
.b DESCRI��O
.in 5
O cliente "xclock", al�m de exibir em uma janela um rel�gio
anal�gico, notifica ao usu�rio a chegada de correspond�ncia
em sua caixa postal.
.sp

A janela "xclock" possui como t�tulo a data atual.
.sp

.in 5
As op��es dispon�veis s�o as seguintes:
.in 8

.ip "-d <display>" 20
indica o servidor X a contactar. O default � o servidor local.

.ip "-D <desktop>" 20
especifica o n�mero do "desktop" em que a janela "xclock" ser�
criada.

.ip "-b <cor_de_fundo>" 20
modifica a cor de fundo da janela.
O default � branco, podendo ser alterado em $HOME/.Xdefaults.
Para maiores detalhes sobre especifica��es de cores, veja "X (xwin)".

.ip "-f <cor_de_frente>" 20
modifica a cor do mostrador do rel�gio (n�meros e ponteiros).
O default � preto, podendo ser alterado em $HOME/.Xdefaults.
Para maiores detalhes sobre especifica��es de cores, veja "X (xwin)".

.ip "-g <geometria>" 20
especifica a geometria da janela, no formato [<dx>x<dx>][<x><y>].
Para maiores detalhes sobre especifica��o de geometria, veja "X (xwin)".

.ip "-i" 20
a janela "xclock" inicia na forma "iconificada".

.ip "-u <segundos>" 20
especifica o per�odo de atualiza��o do rel�gio. O default
� a cada segundo. Se o per�odo especificado n�o for de 1 segundo,
o ponteiro dos segundos n�o � mostrado.

.ip "-m <segundos>" 20
especifica o per�odo de consulta � caixa postal do usu�rio. O default
� a cada minuto.

.ep

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(xwin): "
X, fvwm
.br

.in
.sp
.b
ARQUIVOS
.in 5
$HOME/.Xdefaults
.br
/var/mail/$USER

.in
.sp
.b
EXEMPLOS
.r
.ip
xclock -b darkgreen -f white
.in 5
.ip
A janela "xclock" ter� fundo verde escuro e mostrador branco.
.in -5

.ip
xclock -g 200x200+30+100 -u 60
.in 5
.ip
A janela "xclock" ter� 200x200 pixels.
Se poss�vel, o gerenciador de janelas ("fvwm") posicionar� o
canto superior esquerdo da janela nas coordenadas (30, 100),
a partir do canto superior esquerdo do "desktop".
O mostrador � atualizado a cada minuto e o ponteiro dos
segundos n�o � desenhado.
.in -5
.ep

.in
.sp
.b ESTADO
.in 5
Efetivo.
