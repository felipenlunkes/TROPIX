.bp
.he 'TIC (cmd)'TROPIX: Manual de Refer�ncia'TIC (cmd)'
.fo 'Atualizado em 12.07.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
Compila e instala a descri��o de um terminal/v�deo

.in
.sp
.b SINTAXE
.in 5
.(l
tic [-f] [-n <nome>] <fonte>
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "tic" compila a descri��o fonte de um terminal/v�deo,
dada em "<fonte>",
e instala a descri��o objeto correspondente no arquivo apropriado,
de acordo com a vari�vel "TERMINFO" do ambiente,
e as op��es dadas para o programa.

.sp
A vari�vel "TERMINFO" do ambiente define o diret�rio no qual o
arquivo ser� instalado; se ela n�o for definida ser� utilizado
o diret�rio padr�o "/usr/lib/terminfo". 

.sp
As op��es definem o nome do arquivo dentro do diret�rio:

.ip "--" 10
Sem nenhuma op��o, "tic" instala a descri��o objeto com o nome "test".
Este modo � destinado a testes; pode-se testar a descri��o
ora compilada (sem alterar a descri��o do terminal/v�deo em uso)
atribuindo-se � variavel do ambiente "TERM"
o valor "test". 
 
.ip "-n <nome>" 10
Com a op��o "-n", a instala��o � realizada com o nome dado
"<nome>".

.ip "-f" 10
A op��o "-f" realiza a instala��o definitiva, utilizando-se
os nomes contidos no pr�prio arquivo de descri��o "<fonte>"
(exceto o �ltimo).

.ep

.in
.sp
.b OBSERVA��O
.in 5
O programa verifica se uma descri��o j� existe antes de instal�-la
para evitar a perda acidental de uma descri��o antiga. 

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
tac
.br

.in
.sp
.b ARQUIVOS
.in 5
/usr/lib/terminfo

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
