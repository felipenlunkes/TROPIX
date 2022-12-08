.bp
.he 'COMM (cmd)'TROPIX: Manual de Refer�ncia'COMM (cmd)'
.fo 'Atualizado em 10.04.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
.wo "comm -"
seleciona linhas comuns a dois arquivos ordenados
.br

.in
.sp
.b SINTAXE
.in 5
.(l
comm [-123] <arquivo1> <arquivo2>
.)l

.in
.sp
.b DESCRI��O
.in 5
O utilit�rio "comm" compara, linha a linha, os arquivos de entrada
<arquivo1> e <arquivo2>, que devem estar ordenados lexicograficamente
de acordo com o c�digo ISO (veja "sort" (cmd)).
O nome de um dos <arquivo>s pode ser "-" para indicar a entrada padr�o.

.sp
O utilit�rio produz, na sa�da padr�o,
linhas come�ando em tr�s colunas distintas: 

.sp
.in +3
- coluna 1: para linhas somente no <arquivo1>;
.sp
- coluna 2: para linhas somente no <arquivo2>;
.sp
- coluna 3: para linhas em ambos os arquivos.
.in -3

.sp 2
As op��es do comando s�o:

.in +3
.ip -1
Suprime a coluna 1;

.ip -2
Suprime a coluna 2;

.ip -3
Suprime a coluna 3;

.ep
.in +3

.in
.sp
.b OBSERVA��O
.in 5
Se forem dados as 3 op��es simultaneamente  ("comm -123 ...."),
o comando n�o ir� produzir nenhuma sa�da. 

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sort, cmp, diff, uniq
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
