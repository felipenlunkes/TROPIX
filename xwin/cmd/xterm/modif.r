.bp
.he 'XTERM (xwin)'TROPIX: Manual de Modifica��es'XTERM (xwin)'
.fo 'Atualizado em 17.07.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "xterm -"
Emulador de Terminal ANSI para o X-Window
.br

.in
.sp 2
.ip "05.02.99  3.1.6" 20
VERS�O CORRENTE
.sp

.in
.ip "01.04.99  3.1.7" 20
Revistas/eliminadas algumas op��es na linha de comando.

.ip "27.05.99  3.2.0" 20
Introduzida a altera��o do tamanho da janela, atrav�s da
seq��ncia ESC]46;<ncol>x<nlin>BEL, enviada pelo "xtset".

.ip "14.10.01  4.2.0" 20
Revisto para a vers�o 4.1.0 do X-Window.

.ip "06.05.02  4.2.0" 20
Agora � poss�vel alterar os nomes das cores b�sicas.

.ip "11.11.02  4.4.0" 20
Removido o tratamento especial para a seta ascendente.
Alterado o m�dulo "src/command.c".

.ip "19.03.03  4.4.0" 20
O programa foi revisto para a vers�o 4.3.0 do X-Window.

.ip "18.06.03  4.5.0" 20
Introduzido o tratamento das teclas num�ricas no teclado auxiliar.
Alterado o m�dulo "src/command.c".

.ip "18.08.03  4.5.0" 20
Introduzida a op��o "-h". Modificados: "h/main.h", "src/xterm.c" e
"src/xdefaults.c".

.ip "11.12.03  4.5.0" 20
Introduzido o rolamento atrav�s da "rodinha" do camundongo.
Modificado: "src/command.c".

.ip "17.07.04  4.6.0" 20
Agora usando "getpty" e "initent".

.ip "18.03.05  4.8.0" 20
Pequena revis�o.
