.bp
.he 'XTERM (xwin)'TROPIX: Manual de Refer�ncia'XTERM (xwin)'
.fo 'Escrito em 18.03.05'Vers�o 4.8.0'Pag. %'

.b NOME
.in 5
xterm - emulador de terminal ANSI para o X-Window.

.in
.sp
.b SINTAXE
.in 5
xterm [op��es] [-e <comando> [<arg>...]]

.in
.sp
.b DESCRI��O
.in 5
O cliente "xterm" � uma vers�o simplificada do emulador de terminal "rxvt",
distribu�do como contribui��o ao X-Window.
Sua fun��o � criar, na tela gr�fica, uma janela de texto para que
um comando qualquer do TROPIX possa ser executado.
Normalmente, esse comando � o interpretador "shell" (veja "sh (cmd)").
.sp

.in 5
As op��es dispon�veis s�o as seguintes:
.in 8

.ip "-d <display>" 20
indica o servidor X a contactar. O default � o servidor local.

.ip "-D <desktop>" 20
especifica o n�mero do "desktop" em que a janela "xterm" ser�
criada.

.ip "-b <cor_de_fundo>" 20
modifica a cor de fundo da janela.
O default � branco.
Para maiores detalhes sobre especifica��es de cores, veja "X (xwin)".

.ip "-f <cor_de_frente>" 20
modifica a cor do texto da janela.
O default � preto.
Para maiores detalhes sobre especifica��es de cores, veja "X (xwin)".

.ip "-c <cor_do_cursor>" 20
modifica a cor do cursor.
O default � preto.
Para maiores detalhes sobre especifica��es de cores, veja "X (xwin)".

.ip "-F <fonte>" 20
especifica a fonte a ser utilizada.

.ip "-C" 20
captura as mensagens de erro provenientes do n�cleo do sistema.
A janela correspondente ter� t�tulo "Console (ptyc??)", diferenciando-a
das demais.
Se mais de um comando "xterm" especificar a op��o "-C", apenas um deles conseguir�
desviar as mensagens.

.ip "-g <geometria>" 20
especifica a geometria da janela, no formato [<lin>x<col>][<x><y>].
Para maiores detalhes sobre especifica��o de geometria, veja "X (xwin)".

.ip "-h <diret�rio>" 20
especifica o diret�rio inicial.

.ip "-i" 20
a janela "xterm" inicia na forma "iconificada".

.ip "-t <t�tulo>" 20
modifica o t�tulo da janela. O default � "xterm (ptyc??)",
onde ptyc?? indica o pseudo-terminal utilizado.
Para maiores detalhes sobre especifica��o de fontes, veja "X (xwin)".

.ip "-s <linhas>" 20
indica o n�mero de linhas que devem ser salvas para posterior
exame atrav�s da barra de rolamento. O default � 64 linhas.
Especificar o valor 0 implica a supress�o da barra de rolamento.

.ip "-e <comando> [<arg>...]" 20
executa <comando> na janela criada pelo "xterm". O default �
o interpretador de comandos shell ("/bin/sh").
Esta op��o deve obrigatoriamente ser a �ltima na chamada,
uma vez que o comando pode receber argumentos.

.ip "-color<n> <cor>" 20
altera o nome da cor b�sica <n> para <cor>, onde <n> pode variar
de 0 a 15, significando: 0 - preto, 1 - azul, 2 - verde, 3 - ciano,
4 - vermelho, 5 - magenta, 6 - marrom, 7 - branco sujo, 8 - preto,
9 - azul claro, 10 - verde claro, 11 - ciano claro, 12 - vermelho claro,
13 - magenta claro, 14 - marrom claro, 15 - branco.
.ep

.in
.sp
.b
COMPATIBILIDADE
.in 5
Por quest�o de compatibilidade com o emulador "xterm" original,
s�o aceitas op��es com nomes longos, a saber:
.sp
.nf
          -bg		equivale a	-b
          -background	equivale a	-b
	  -cr		equivale a	-c
	  -desktop	equivale a	-D
          -display	equivale a	-d
          -fg		equivale a	-f
          -foreground	equivale a	-f
          -fn		equivale a	-F
          -font		equivale a	-F
          -geometry	equivale a	-g
          -title	equivale a	-t
.fi
.sp
As op��es longas podem ser inclu�das no arquivo $HOME/.Xdefaults, de
modo que fiquem impl�citas a cada execu��o do "xterm". Por exemplo,
um arquivo $HOME/.Xdefaults contendo as seguintes linhas
.sp
.nf
          XTerm*background:     black
          XTerm*geometry:       80x44
          XTerm*color4:         orange
.fi
.sp
far� com que toda execu��o do "xterm" assuma o fundo preto, a geometria
de 44 linhas por 80 colunas e a cor vermelha (4) passe a ser laranja.


.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd):  "
sh
.br
.in 5
.wo "(fmt):  "
terminfo
.br
.in 5
.wo "(xwin): "
X, fvwm
.br

.in
.sp
.b
EXEMPLOS
.r
.ip
xterm -b darkgreen -f white -F 7x13bold
.in 5
.ip
A janela "xterm" ter� fundo verde escuro, texto branco e usar�
a fonte 7x13bold.
.in -5

.ip
xterm -C -g 80x13+30+100
.in 5
.ip
A janela "xterm" ter� 80 colunas e 13 linhas.
Se poss�vel, o gerenciador de janelas ("fvwm") posicionar� o
canto superior esquerdo da janela nas coordenadas (30, 100),
a partir do canto superior esquerdo do "desktop".
Nesta janela ser�o impressas as mensagens de erro do n�cleo do sistema,
se j� n�o houver outra com essa finalidade.
.in -5

.ip
xterm -g 80x30 -t Coremap -e coremap
.in 5
.ip
A janela "xterm" ter� 80 colunas, 30 linhas e t�tulo "Coremap (ptyc??)".
O comando a ser executado � "coremap", que mostra um
mapa de aloca��o de mem�ria (veja "coremap (cmd)").
.in -5
.ep

.in
.sp
.b ESTADO
.in 5
Efetivo.
