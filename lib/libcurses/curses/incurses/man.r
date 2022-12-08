.bp
.he 'INCURSES (curses)'TROPIX: Manual de Refer�ncia'INCURSES (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Entrada e sa�da de "curses":

.sp
.wo "incurses  -"
entrada de "curses"
.br
.wo "outcurses -"
sa�da de "curses"

.sp
.in
.b SINTAXE
.in 5
.(l
#include <curses.h>

int incurses (const char *pgname);
void outcurses (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "incurses" � usada para iniciar a opera��o de "curses"
em um terminal ou reinici�-la ap�s uma suspens�o tempor�ria.

.sp
A rotina "outcurses" � usada para terminar a opera��o de "curses"
ou para suspend�-la temporariamente.

.sp
O par�metro "pgname" deve apontar uma cadeia de caracteres
contendo o nome do programa.
Este nome � usado em mensagens explicativas em caso de erro
na inicia��o de "curses".

.sp
O in�cio da opera��o de "curses" envolve
a obten��o da descri��o do terminal em uso,
a cria��o de estruturas de dados correspondentes ao terminal
e a altera��o do modo de comunica��o da linha do terminal.

.sp
O tipo do terminal � identificado por um nome passado
para "curses" atrav�s do ambiente (vari�vel "TERM").

.sp
As estruturas de dados correspondentes ao terminal incluem
uma janela padr�o no tamanho do v�deo
e o seu n�mero de linhas e colunas,
respectivamente acessadas pelo programador pelas vari�veis externas
"stdwin", "LINES" e "COLS".
Al�m disso, s�o tamb�m atribuidos os valores corretos
�s vari�veis correspondentes
aos caracteres semigr�ficos (veja "waddch" (curses)).

.sp
Durante o funcionamento de "curses" a comunica��o com o terminal
n�o utiliza os servi�os de eco, de edi��o da entrada
e de processamento da sa�da
da interface de terminais do kernel.

.sp
A suspens�o ou t�rmino da opera��o de "curses"
retorna o modo de comunica��o original do programa,
rola o v�deo de uma linha
e posiciona o cursor na primeira coluna da �ltima linha.

.sp
Ap�s a inicia��o ou cada reinicia��o de "curses"
a primeira chamada � rotina "wrefresh"
limpa o v�deo do terminal.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A rotina "incurses" retorna uma dentre as constantes inteiras "OK" e "ERR",
indicando respectivamente sucesso ou insucesso na opera��o.

.in
.sp
.b DIAGN�STICOS
.in 5
Veja esta se��o em "newterm" (curses).

.in
.sp
.b OBSERVA��ES
.in 5
Programas que se preparam para interceptar os sinais "SIGQUIT" e "SIGINT"
devem faz�-lo antes de chamar a rotina "incurses" pela primeira vez.

.sp
A biblioteca "curses" pode manipular mais de um terminal
(veja "newterm" (curses)).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd):   "
tic, tac
.br
.wo "(curses):"
newterm, outcurses, setterm
.br

.in
.sp
.b ESTADO
.in 5
Efetivo

.in
