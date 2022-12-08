.bp
.he 'XTSET (xwin)'TROPIX: Manual de Refer�ncia'XTSET (xwin)'
.fo 'Escrito em 19.03.03'Vers�o 4.4.0'Pag. %'

.b NOME
.in 5
xtset - modifica caracter�sticas de uma janela XTERM

.in
.sp
.b SINTAXE
.in 5
.in 5
.(l
xtset [-b <cor_de_fundo>] <-f <cor_de_frente>] [-F <fonte>]
      [-g <ncol>x<nlin>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "xtset" permite ao usu�rio modificar algumas caracter�sticas
da janela "xterm" onde ele � invocado.
.sp

.in 5
As op��es dispon�veis s�o as seguintes:
.in 8

.ip "-b <cor_de_fundo>" 20
modifica a cor de fundo da janela "xterm".
Para maiores detalhes sobre especifica��es de cores, veja "X (xwin)".

.ip "-f <cor_de_frente>" 20
modifica a cor do texto da janela "xterm" e tamb�m a cor do cursor.
Para maiores detalhes sobre especifica��es de cores, veja "X (xwin)".

.ip "-F <fonte>" 20
modifica a fonte a ser utilizada.

.ip "-g <ncol>x<nlin>" 20
modifica o tamanho da janela, que passar� a ter <ncol> colunas e <nlin> linhas.
.ep

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(xwin): "
xterm
.br

.in
.sp
.b
EXEMPLOS
.r
.ip
xtset -b darkgreen -f white -F 7x13bold -g 90x30
.in 5
.ip
A janela "xterm" ter� fundo verde escuro, texto branco, 30
linhas, 90 colunas e usar� a fonte 7x13bold.
.in -5
.ep

.in
.sp
.b ESTADO
.in 5
Efetivo.
