.bp
.he 'TAC (cmd)'TROPIX: Manual de Refer�ncia'TAC (cmd)'
.fo 'Atualizado em 12.07.95'Vers�o 3.0.1'Pag. %'

.b NOME
.in 5
.wo "tac -"
descompila a descri��o instalada de um terminal/v�deo

.in
.sp
.b SINTAXE
.in 5
.(l
tac [<term> [<fonte>]]
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "tac" descompila a descri��o objeto instalada
de um terminal/v�deo de nome <term>
e escreve um fonte correspondente no arquivo <fonte>.

.sp
Se <term> n�o for dado, ou for dado como "-" ser� considerado
o terminal/v�deo "$TERM" do ambiente.

.sp
Se <fonte> n�o for dado, escreve na sa�da padr�o.

.sp
O nome do terminal/v�deo deve ser dado sem o prefixo
(normalmente "/usr/lib/terminfo").
O arquivo contendo a descri��o objeto instalada
� procurado no diret�rio dado pela vari�vel "$TERMINFO" do ambiente;
Se ela n�o estiver definida
� utilizado o diret�rio padr�o "/usr/lib/terminfo". 

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
tic
.br

.in
.sp
.b ARQUIVOS
.in 5
/usr/lib/terminfo/*

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
