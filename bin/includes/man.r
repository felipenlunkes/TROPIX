.bp
.he 'INCLUDES (cmd)'TROPIX: Manual de Refer�ncia'INCLUDES (cmd)'
.fo 'Atualizado em 03.05.97'Vers�o 1.0.0'Pag. %'

.b NOME
.in 5
.wo "includes -"
descobre arquivos inclu�dos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
includes [-vuN] [-I <dir>] ... [<caminho> ...]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "includes" lista, na sa�da padr�o, todos os arquivos inclu�dos
atrav�s da diretiva "#include" do pr�-processador C nos m�dulos
especificados como argumentos.
.sp
Podem ser especificados arquivos regulares ou diret�rios como argumentos
do programa.
No segundo caso, � realizada uma busca em �rvore.
.sp
O formato peculiar da listagem produzida destina-se a facilitar o
preenchimento de um "Makefile" que esteja sendo constru�do para os
m�dulos em quest�o.

.sp
As op��es do comando s�o:

.in +3
.ip -I
inclui o diret�rio <dir> na lista de diret�rios de busca.

.ip -v
Modo verboso.

.ip -N
L� os nomes dos <arquivo>s da entrada padr�o. Neste caso, n�o
devem ser dados argumentos.

.ip -u
Lista tamb�m os arquivos inclu�dos que forem encontrados no
diret�rio "/usr/include".

.ep
.in -3

.in
.sp
.b OBSERVA��ES
.in 5
Apenas arquivos com extens�es ".c" e ".h" s�o varridos � procura de
"includes".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
trcpp
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
