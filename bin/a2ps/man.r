.bp
.he 'A2PS (cmd)'TROPIX: Manual de Refer�ncia'A2PS (cmd)'
.fo 'Atualizado em 03.10.02'Vers�o 4.3.0'Pag. %'

.b NOME
.in 5
.wo "a2ps -"
converte arquivos texto para PostScript
.br

.in
.sp
.b SINTAXE
.in 5
.(l
a2ps [-bN] [-c <nc>] [-F <ps>] [-l <nl>] [-o <mar>]
     [-t <tab>] [<arquivo> ...]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "a2ps" converte o conte�do dos arquivos dados para PostScript,
gerando o resultado na sa�da padr�o.
Se n�o for dado nenhum <arquivo> (nem a op��o "-N"), a entrada padr�o
� assumida.

.sp
Temos ainda as seguintes outras op��es:

.in +3
.ip -b
Divide as linhas grandes em v�rias, ao inv�s de trunc�-las.

.ip -c
Utiliza <nc> caracteres como tamanho m�ximo de uma linha. Por omiss�o,
� assumido o valor 95.

.ip -F
Gera o resultado no arquivo <ps>, ao inv�s de utilizar a sa�da padr�o.

.ip -l
Produz p�ginas de <nl> linhas. Por omiss�o, � assumido o valor 74.

.ip -o
A margem esquerda ser� de <mar> caracteres. Por omiss�o, � assumido o valor 0.

.ip -t
O tabulador tem espa�amento de <tab> caracteres. Por omiss�o, � assumido
o valor 8.

.ip -N
L� os nomes dos <arquivo>s a processar da entrada padr�o.

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
pr
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
