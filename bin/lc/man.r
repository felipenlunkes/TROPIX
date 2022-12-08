.bp
.he 'LC (cmd)'TROPIX: Manual de Refer�ncia'LC (cmd)'
.fo 'Atualizado em 02.10.03'Vers�o 4.5.0'Pag. %'

.b NOME
.in 5
.wo "lc -"
lista o conte�do de diret�rios
.br

.in
.sp
.b SINTAXE
.in 5
.(l
lc [-rdbclfstaRN] [<diret�rio> ...]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "lc" lista o conte�do dos diret�rios dados.
Se n�o for dado nenhum <diret�rio> (nem a op��o "-N"),
"lc" lista o conte�do do diret�rio corrente.

.sp
A listagem de cada diret�rio � dividida em sess�es,
uma para cada tipo de arquivo, e disposta em 5 colunas.

.sp
Normalmente, s�o listados todos os tipos de arquivos.
Se isto n�o for desejado, podemos selecionar os tipos desejados
atrav�s das seguintes cinco op��es. Se uma ou mais destas op��es
forem dadas, somente ser�o listados os tipos selecionados.

.in +3
.ip -r
Arquivos regulares.

.ip -d
Diret�rios.

.ip -b
Arquivos especiais de blocos.

.ip -c
Arquivos especiais de caracteres.

.ip -l
Elos simb�licos.

.ip -f
Fifos.

.ep
.in -3

.sp
Temos ainda, as seguintes outras op��es:

.in +3
.ip -t
Ordena os arquivos pela data da �ltima modifica��o, ao inv�s de
alfabeticamente pelo nome do arquivo, como � usual.

.ip -a
Inclui tamb�m as entradas "." e ".." na listagem
(n�o pode ser usada em conjunto com a op��o "-R"). 

.ip -R
Lista os conte�dos dos subdiret�rios encontrados recursivamente.
Deste modo, podemos obter listar todos os diret�rios de uma �rvore
(n�o pode ser usada em conjunto com a op��o "-a"). 

.ip -N
L� os nomes dos <diret�rio>s da entrada padr�o.

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
ls
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
