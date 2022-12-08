.bp
.he 'NEWTERM (curses)'TROPIX: Manual de Refer�ncia'NEWTERM (curses)'
.fo 'Atualizado em 18.11.88'Vers�o 2.3'Pag. %'

.b NOME
.in 5
Manipula��o de v�rios terminais:
.sp
.wo "newterm -"
prepara��o de um novo terminal
.br
.wo "setterm -"
estabelecimento do terminal corrente
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>
#include <curses.h>

int newterm (const char *nome, FILE *sa�da, FILE *entrada);
int setterm (int term);
.)l

.in
.sp
.b DESCRI��O
.in 5
A biblioteca "curses" pode manipular mais de um terminal
utilizando-se do conceito de terminal corrente.
Assim a cada instante "curses" est� trabalhando em apenas um terminal,
denominado terminal corrente.
Quando for desejado trabalhar com outro terminal,
basta estabelec�-lo como terminal corrente.

.sp
A rotina "newterm" prepara "curses" para trabalhar com mais um terminal,
cujo tipo � identificado pelo par�metro "nome"
e arquivos utilizados para escrita e leitura s�o respectivamente
"sa�da" e "entrada".
Quando o par�metro "nome" � nulo � utilizada
o valor da vari�vel "TERM" do ambiente.

.sp
A rotina "setterm" estabelece o terminal correntemente em uso.
O par�metro "term" � um descritor de terminal retornado
numa chamada bem sucedida � rotina "newterm".


.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A rotina "newterm" normalmente retorna um descritor para o novo terminal;
em caso de erro ela retorna um valor negativo.
.sp
A rotina "setterm" retorna o descritor do terminal corrente anterior
ou um valor negativo se o descritor de terminal fornecido for inv�lido.

.in
.sp
.b DIAGN�STICOS
.in 5
As seguintes situa��es causam erro na rotina "newterm":
.ip (1)
indisponibilidade de mem�ria,
.ip (2)
incapacidade de leitura das caracter�sticas do terminal,
.ip (3)
os arquivos de sa�da ou de entrada n�o representarem terminais e
.ip (4)
a vari�vel "TERM" n�o definida no ambiente
(para o caso do par�metro "nome" nulo).
.ep

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(curses): "
incurses
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
