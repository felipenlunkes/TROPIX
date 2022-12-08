.bp
.he 'LINKOPTIM (cmd)'TROPIX: Manual de Refer�ncia'LINKOPTIM (cmd)'
.fo 'Atualizado em 19.06.97'Vers�o 3.0.1'Pag. %'

.b NOME
.in 5
.wo "linkoptim -"
substitui arquivos duplicados por "link"s
.br

.in
.sp
.b SINTAXE
.in 5
.(l
linkoptim [-fvN] <�rvore> ...
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "linkoptim" caminha as <�rvore>s dadas,
� procura de pares de arquivos regulares
iguais com o objetivo de substituir um dos arquivos por um "link" ao outro.
Isto pode economizar um espa�o apreci�vel no sistema de arquivos.

.sp
As op��es do comando s�o:

.in +3
.ip -f
For�a: Normalmente, o usu�rio � consultado para confirmar que
realmente deseja substituir o arquivo por um "link" ao outro.
Com esta op��o, a substitui��o � realizada sem consulta.

.ip -v
Verboso.

.ip -N
L� os nomes das <�rvores>s da entrada padr�o.
Esta op��o � impl�cita se n�o forem dados argumentos

.ep
.in -3

.in
.sp
.b OBSERVA��ES
.in 5
A substitui��o de um arquivo por um "link" a outro
(mesmo de conte�do igual) poder� alterar as propriedades
do arquivo (tais como o dono, grupo, prote��o, datas, ...),
o que pode ter conseq��ncias indesej�veis
(como por exemplo, atrapalhar o funcionamento do comando "make").

.sp
O comando N�O considera arquivos vazios (de tamanho zero).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
make, cp, ln
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
