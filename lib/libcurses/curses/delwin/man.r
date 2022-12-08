.bp
.he 'DELWIN (curses)'TROPIX: Manual de Refer�ncia'DELWIN (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
.wo "delwin -"
remove uma janela
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <curses.h>

void delwin (WINDOW *janela);
.)l

.in
.sp
.b DESCRI��O
.in 5
A rotina "delwin" remove "janela",
retirando a sua imagem do v�deo e
liberando todos os recursos alocados.

.sp
Ap�s a remo��o de uma janela,
o v�deo do terminal � atualizado
de modo a refletir a nova disposi��o
apenas com as janelas restantes.

.in
.sp
.b OBSERVA��O
.in 5
A janela padr�o ("stdwin") n�o pode ser removida.
.sp
A rotina "delwin" atualiza todas as janelas vis�veis no terminal.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses): "
werase, newwin
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
