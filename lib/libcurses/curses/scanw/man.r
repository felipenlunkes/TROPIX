.bp
.he 'SCANW (curses)'TROPIX: Manual de Refer�ncia'SCANW (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Leitura formatada do teclado:
.sp
.wo "wscanw -"
para uma janela dada
.br
.wo "scanw  -"
para a janela padr�o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

int wscanw (WINDOW *janela, const char *format, ...);
int scanw (const char *format, ...);
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "wscanw" l� uma linha do teclado,
que � interpretada de acordo com "formato",
e guarda os valores convertidos nas �reas de mem�ria
dadas pelos argumentos (ponteiros para vari�veis).

.sp
A rotina "scanw" corresponde � rotina "wscanw" aplicada � janela padr�o
("stdwin").

.sp
A especifica��o do formato para leitura e convers�o
segue as mesmas normas adotadas para a rotina "scanf" da biblioteca
padronizada de entrada e sa�da ("stdio").

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
As rotinas "wscanw" e "scanw" retornam o n�mero de �tens 
para os quais a convers�o foi bem sucedida.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):   "
scanf
.br
.wo "(curses): "
wprintw, wgetstr
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
