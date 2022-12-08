.bp
.he 'DC (cmd)'TROPIX: Manual de Refer�ncia'DC (cmd)'
.fo 'Atualizado em 03.11.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "dc -"
Calculador de mesa com aritm�tica de m�meros inteiros
.br

.in
.sp
.b SINTAXE
.in 5
.(l
dc
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "dc" simula um calculador de mesa (muito simples) com
aritm�tica de m�meros inteiros.

.sp
Os n�meros podem ser dados
nas bases 10 (decimal), 16 (hexadecimal) ou 8 (octal),
conforme a sintaxe da linguagem "C":
(0x.... para hexadecimal e 0... para octal; os demais s�o considerados decimais).
Para o caso hexadecimal, somente s�o aceitas
as letras mai�sculas 'A' a 'F' para representar os d�gitos
10 a 15.
Um n�mero pode ser seguido das letras 'K', 'M' ou 'G',
o que far� com que seu valor seja multiplicado por
1024 (KB), 1024^2 (MB) ou 1024^3 (GB), respectivamente.

.sp
Est�o dispon�veis 26 vari�veis para conterem valores intermedi�rios,
cujos nomes s�o "a" a "z". Estas vari�veis s�o inicializadas com o
valor 0, mas no entanto, "dc" indica quando est� sendo usado o valor
de uma vari�vel ainda n�o atribu�da pelo usu�rio.

.sp
Os operadores dispon�veis s�o: "=", "+", "-", "*", "/", "\%", "&",
"|", "^", ">>", "<<", "~", "(" e ")", conforme a mesma nota��o da
linguagem "C".
As express�es s�o formadas usando os operadores
na forma infixa, tal como "a = b + 5".

.sp
Os resultados s�o dados em decimal e hexadecimal.

.sp
Um <^D> encerra o uso de "dc".

.bc	/*************************************/
.sp
As op��es do comando s�o:

.in +3
.ip -v
Verboso: (nesta vers�o sem fun��o).

.ep
.in -3
.ec	/*************************************/

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
fdc
.br

.in
.sp
.b EXEMPLO
.in 7
.(l
	a = 0x34
	b = 234
	c = (a - 4) * (b ^ 1)
.)l

.sp
ir� imprimir o valor 11280 (e atribu�-lo � vari�vel "c").

.in
.sp
.b ESTADO
.in 5
Efetivo.
