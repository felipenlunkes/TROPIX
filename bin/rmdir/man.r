.bp
.he 'RMDIR (cmd)'TROPIX: Manual de Refer�ncia'RMDIR (cmd)'
.fo 'Atualizado em 08.05.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "rmdir -"
remove diret�rios
.br

.in
.sp
.b SINTAXE
.in 5
.(l
rmdir [-vN] <diret�rio> ...
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "rmdir" remove os diret�rio dados, que devem estar vazios.

.sp
As op��es do comando s�o:

.in +3

.ip -v
Lista os nomes dos <diret�rio>s sendo removidos.
Isto � �til em conjunto com a op��o "-N".

.ip -N
L� os nomes dos arquivos da entrada padr�o.
Esta op��o � impl�cita se n�o forem dados <arquivo>s.

.ep
.in -3

.sp
Se algum dos diret�rios n�o estiver vazio, utilize o comando "rm" (cmd)
para remover os arquivos nele contidos ou ent�o o comando
"rmtree" (cmd) para remover a �rvore inteira. 

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
rmdir
.br
.wo "(cmd): "
rm, rmtree, emptydir
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
