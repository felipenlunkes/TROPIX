.bp
.he 'MVTREE (cmd)'TROPIX: Manual de Refer�ncia'MVTREE (cmd)'
.fo 'Atualizado em 26.04.02'Vers�o 4.2.0'Pag. %'


.b NOME
.in 5
.wo "mvtree -"
move (troca o nome) de uma �rvore/diret�rio
.br

.in
.sp
.b SINTAXE
.in 5
.(l
mvtree <�rvore1> <�rvore2>
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "mvtree" move (troca o nome) de �rvores (diret�rios).

.sp
Se o diret�rio <�rvore2> ainda n�o existe, o novo nome de <�rvore1>
ser� <�rvore2>. Em caso contr�rio, ser� <�rvore2>/<nome1>, onde
<nome1> � o �ltimo componente do caminho de <�rvore1>.

.sp
Se o nome antigo e o novo residirem em um mesmo sistema de arquivos,
ser� feita apenas uma mudan�a de nome. Em caso contr�rio, toda
a �rvore ser� copiada e em seguida a �rvore original ser� removida. 

.in
.sp
.b OBSERVA��ES
.in 5
Repare que ao mover uma �rvore, modificam-se os caminhos
de todos os arquivos nela contidos.

.sp
O comando tenta ser o mais geral poss�vel, processando
inclusive casos da forma
.sp
.ce
"mvtree  alpha/../../beta  gamma" 
e
.ce
"mvtree  alpha  ../..".

.sp
Os poucos casos n�o permitidos ocorrem quando o nome de <�rvore1> termina
por "/.", "/.." ou quando  <�rvore1> � um ancestral de <�rvore2>.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
mv, cptree, rmtree
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
