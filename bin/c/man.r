.bp
.he 'C (cmd)'TROPIX: Manual de Refer�ncia'C (cmd)'
.fo 'Atualizado em 12.07.02'Vers�o 4.3.0'Pag. %'

.b NOME
.in 5
.wo "c -"
escreve as linhas de um arquivo em v�rias colunas
.br

.in
.sp
.b SINTAXE
.in 5
.(l
c [-l <largura>] [-b <brancos>] [<arquivo>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "c" l� as linhas do arquivo de entrada <arquivo>
e as escreve alinhadas em v�rias colunas na sa�da padr�o. 
Se o <arquivo> n�o for dado, "c" l� da entrada padr�o.

.sp
O comando "c" usa como largura o n�mero de colunas do terminal/v�deo
usado para a sua sa�da. Se n�o conseguir este valor, usa
o valor padr�o de 80 caracteres.
Normalmente, as colunas s�o separadas por 2 brancos (veja as op��es abaixo).

.sp
O comando "c" tenta utilizar o maior poss�vel n�mero de colunas;
se o <arquivo> de entrada contiver linhas muito compridas,
pode ocorrer que o arquivo de sa�da
contenha apenas uma coluna
(isto �, seja igual ao arquivo de entrada).

.sp
As op��es do comando s�o:

.in +3
.ip -l
Escreve as linhas de sa�da com <largura> caracteres.

.ip -b
Separa as colunas da sa�da com <brancos> brancos ao inv�s de 2.

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
cat
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
