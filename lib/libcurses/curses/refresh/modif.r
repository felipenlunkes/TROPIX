.bp
.he 'REFRESH (curses)'TROPIX: Manual de Modifica��es'REFRESH (curses)'
.fo 'Atualizado em 28.06.89'Vers�o 1.0'Pag. %'

.b NOME
.in 5
Atualiza uma janela no v�deo:
.sp
.wo "wrefresh -"
uma janela dada
.br
.wo "refresh  -"
a janela padr�o ("stdwin")
.br

.in
.sp 2
.ip "01.04.87  2.1" 20
VERS�O CORRENTE
.sp

.ip "28.06.89  2.2.1" 20
A rotina passou efetivamente a utilizar
os comandos para tornar o cursor invis�vel e retornar ao normal.

.ip "08.08.89  2.2.2" 20
Melhoria na utiliza��o das seq��ncias de campos com atributos.
A capacidade de defini��o de uma regi�o de rolamento
n�o abrangendo todo o v�deo passou a ser utilizada quando conveniente.

.ip "10.09.90  2.3.0" 20
Foram implementados os atributos "A_BLINK", "A_BOLD" e "A_STANDOUT".
