.bp
.he 'GETCH (curses)'TROPIX: Manual de Modifica��es'GETCH (curses)'
.fo 'Atualizado em x.2.87'Vers�o 1.0'Pag. %'

.b NOME
.in 5
Entrada de um caractere do teclado
.sp
.wo "wgetch   -"
na posi��o corrente na janela dada
.br
.wo "getch    -"
na posi��o corrente na janela padr�o
.br
.wo "mvwgetch -"
dadas a janela e a posi�ao
.br
.wo "mvgetch  -"
dada a posi��o na janela padr�o

.in
.sp 2
.ip "01.04.89  2.1" 20
VERS�O CORRENTE
.sp

.ip "29.06.89  2.2.1" 20
Corrigido o n�o funcionamento da op��o "R_INPUT".

.ip "08.05.90  2.3.0" 20
Corrigido erro no funcionamento da op��o "G_TOISO".
No caso do �ltimo caractere teclado ser um acento,
a sua remo��o n�o cancelava a forma��o de um caractere acentuado.

.ip "04.06.90  2.3.1" 20
Funcionamento completo do reconhecimento de teclas especiais.

.ip "18.04.91  2.3.2" 20
Os caracteres XON e XOFF s�o ignorados
no caso dos terminais que usam o protocolo XON/XOFF.

.ip "24.06.91  2.3.3" 20
Consertado erro no salvamento de contexto
ativado pelo caractere "switch"
atrav�s da inclus�o de um par�metro adicional para a rotina "doswitch"
indicando se a fila de caracteres lidos est� em uso.
