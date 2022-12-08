.bp
.he 'FDC (cmd)'TROPIX: Manual de Refer�ncia'FDC (cmd)'
.fo 'Atualizado em 25.03.00'Vers�o 3.2.3'Pag. %'

.b NOME
.in 5
.wo "fdc -"
Calculador de mesa com aritm�tica de m�meros flutuantes
.br

.in
.sp
.b SINTAXE
.in 5
.(l
fdc
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "fdc" simula um calculador de mesa (muito simples) com
aritm�tica de m�meros flutuantes.

.sp
Os n�meros devem ser dados
conforme a sintaxe da linguagem "C":
veja "strtod" (libc).

.sp
Est�o dispon�veis 26 vari�veis para conterem valores intermedi�rios,
cujos nomes s�o "a" a "z". Estas vari�veis s�o inicializadas com o
valor 0.0, mas no entanto, "fdc" indica quando est� sendo usado o valor
de uma vari�vel ainda n�o atribu�da pelo usu�rio.

.sp
Os operadores dispon�veis s�o: "=", "+", "-", "*" e "/".
As express�es s�o formadas usando os operadores
na forma infixa, tal como "a = b + 5.0".

.sp
Um <^D> encerra o uso de "fdc".

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
dc
.br
.wo "(libc):"
strtod
.br

.in
.sp
.b EXEMPLO
.in 7
.(l
	a = 4.0e+12
	b = 23
	c = (a - 1.0e+12) * (b / 100)
.)l

.sp
ir� imprimir o valor 6.9e+11 (e atribu�-lo � vari�vel "c").

.in
.sp
.b ESTADO
.in 5
Efetivo.
