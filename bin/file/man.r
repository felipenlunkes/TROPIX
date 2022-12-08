.bp
.he 'FILE (cmd)'TROPIX: Manual de Refer�ncia'FILE (cmd)'
.fo 'Atualizado em 24.04.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "file -"
tenta identificar o conte�do de um arquivo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
file [-vN] [<arquivo> ...]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "file" analisa cada um dos <arquivo>s dados, tentando
classific�-lo.

.sp
Se o <arquivo> for regular, examina os seus primeiros 1024 bytes
e tenta descobrir se se trata de um programa em alguma
linguagem conhecida ("C", pascal, fortran, basic, assembly),
ou um texto em um linguagem natural conhecida
(ingl�s, portugu�s, franc�s, alem�o).

.sp
Se o <arquivo> N�O for regular, d� o seu tipo (diret�rio, FIFO, especial
de blocos/caracteres).

.sp
As op��es do comando s�o:

.in +3
.ip -v
Indica o elemento l�xico que possibilitou a identifica��o.
Isto ajuda a avaliar se a classifica��o realizada pelo comando "file"
est� correta.

.ip -N
L� os nomes dos <arquivo>s de "stdin".
Esta op��o � impl�cita se n�o forem dados argumentos.

.ep
.in -3

.in
.sp
.b OBSERVA��O
.in 5
O comando "file" utiliza uma s�rie de heur�sticas para tentar classificar
o arquivo, que nem sempre alcan�am o sucesso.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
