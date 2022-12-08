.bp
.he 'GETCTLCH (curses)'TROPIX: Manual de Refer�ncia'GETCTLCH (curses)'
.fo 'Atualizado em 14.02.89'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Obten��o e altera��o de caracteres de controle:
.sp
getctlch - obt�m um caractere de controle.
.br
setctlch - altera um caractere de controle.
.br

.in
.sp
.b SINTAXE
.(l
#include <curses.h>

int getctlch (int fun��o);
void setctlch (int fun��o, int caractere);
.)l

.sp
.in
.sp
.b DESCRI��O
.in 5
A rotina "getctlch" retorna o caractere controle
associado a "fun��o" na entrada do teclado.

.sp
A rotina "setctlch" altera o caractere associado � "fun��o" para "caractere".

.sp
A tabela abaixo mostra os valores para "fun��o"
correspondentes a todos os caracteres de controle
com os nomes pelos quais eles s�o apresentados e reconhecidos
pelo comando "stty":
.sp
.ts
center
allbox;
c c.
Fun��o	Nome para o comando "stty"
C_INTR	intr
C_QUIT	quit
C_SWITCH	switch
C_ERASE	erase
C_AERASE	aerase
C_WORD	word
C_KILL	kill
C_RETYPE	retype
C_EOF	eof
.te

.sp
Veja em "wgetset" (curses)
o significado de cada um dos caracteres de controle acima.

.in
.sp
.b
OBSERVA��ES
.r
.in 5
As fun��es C_ERASE, C_AERASE, C_WORD, C_KILL, C_RETYPE e C_EOF
s� est�o ativas nas janelas em que a edi��o da entrada est� habilitada
(veja "wgetset" (curses)).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses): "
wgetset
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
