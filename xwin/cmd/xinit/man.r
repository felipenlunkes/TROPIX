.bp
.he 'XINIT (xwin)'TROPIX: Manual de Refer�ncia'XINIT (xwin)'
.fo 'Escrito em 21.10.03'Vers�o 4.5.0'Pag. %'

.b NOME
.in 5
xinit - executa o servidor X local e um cliente qualquer

.in
.sp
.b SINTAXE
.in 5
xinit [<cliente> <arg> ...] [-- <servidor> <arg>...]

.in
.sp
.b DESCRI��O
.in 5
O programa "xinit" executa simultaneamente o servidor X local
e um cliente qualquer do X-Window.
O "xinit" deve ser invocado pelo usu�rio ainda em modo texto.
.sp

.in 5
N�o h� argumentos pr�prios para o "xinit";
seus argumentos destinam-se diretamente ao servidor X 
(veja "X (xwin)") ou ao cliente a ser executado.
A utiliza��o mais comum n�o especifica nenhum argumento;
neste caso, o servidor e o cliente executados s�o, respectivamente,
"/usr/xwin/bin/xserver" e o gerenciador de janelas "fvwm".

.sp
Se existir o arquivo $HOME/.xinitrc (um "script" de "shell"),
o "xinit" dispara como cliente uma "shell" para execut�-lo.
Neste arquivo podem ser iniciados diversos
clientes para o X-Window, com a ressalva de que devem ser executados
em "background" caso n�o terminem brevemente.
O �ltimo cliente (normalmente o gerenciador de janelas "fvwm")
deve ser iniciado com o comando intr�nseco "exec" (veja "sh (cmd)"),
sobrepondo-se � "shell".

.sp
Caso n�o exista o arquivo $HOME/.xinitrc e o usu�rio n�o especifique
nenhum cliente, o gerenciador de janelas "fvwm" � executado.

.sp
No momento em que o cliente executado pelo "xinit" termina.
o servidor X tamb�m encerra suas atividades, provocando,
como conseq��ncia, o retorno ao modo texto.

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
.wo "(xwin): "
X, fvwm
.br

.in
.sp
.b
ARQUIVOS
.in 5
  $HOME/.xinitrc
  $HOME/.fvwmrc

.in
.sp
.b
EXEMPLOS
.ip
xinit xterm -g 80x40
.in 5
.ip
Executa o servidor "/usr/xwin/bin/xserver" e o cliente "xterm".
Na janela "xterm", que possuir� 40 linhas e 80 colunas,
executar� o interpretador de comandos "shell".
.in -5

.sp
.in 5
Eis uma possibilidade para o arquivo $HOME/.xinitrc:
.sp
.nf
          xpaint -R /usr/xwin/gifmaps/tropix.gif
          sysmap -g -0+300 -b green -f white &
          xclock -g -0+0 &
          xterm -C -g 80x13+0+0 &
          xterm -g 90x30+0+300 -b blue -f yellow &
          exec fvwm
.fi
.sp
.in 5
No exemplo acima, o cliente "xpaint" n�o precisa ser
executado em background, uma vez que, ap�s alterar o
fundo da janela-m�e (RootWindow), encerrar� sua execu��o.
O cliente "sysmap" mostra em uma janela a porcentagem
de utiliza��o de diversos recursos do sistema.
O rel�gio "xclock" � posicionado no canto superior direito
do "desktop".
Os "xterm"s executam "shell"s independentes.
Al�m disso, o primeiro deles captura as mensagens de erro
provenientes do n�cleo do TROPIX.
Finalmente, o "fvwm" sobrep�e-se � "shell" que executa o "script"
$HOME/.xinitrc, permanecendo como processo filho do "xinit".
.sp

O mesmo efeito poderia ser conseguido com a omiss�o do arquivo
$HOME/.xinitrc e a utiliza��o do comando "AddToFunc InitFunction",
no arquivo $HOME/.fvwmrc, que permite executar comandos
quando o gerenciador "fvwm" � iniciado. A sintaxe para este
exemplo seria:
.sp
.nf
          AddToFunc InitFunction "I" Nop
          +   "I" Exec xpaint -R /usr/xwin/gifmaps/tropix.gif
          +   "I" Exec sysmap -g -0+300 -b green -f white
          +   "I" Exec xclock -g -0+0
          +   "I" Exec xterm -C -g 80x13+0+0
          +   "I" Exec xterm -g 90x30+0+300 -b blue -f yellow
.fi
.in
.sp
.b ESTADO
.in 5
Efetivo.
