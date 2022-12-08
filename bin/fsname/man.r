.bp
.he 'FSNAME (cmd)'TROPIX: Manual de Refer�ncia'FSNAME (cmd)'
.fo 'Atualizado em 10.09.02'Vers�o 4.3.0'Pag. %'

.b NOME
.in 5
.wo "fsname -"
consulta/atualiza nomes de sistemas de arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
fsname   [-t]  <dispositivo> ...
fsname -s [-f] <dispositivo> <nome> [<volume>]
.)l

.in
.sp
.b DESCRI��O
.in 5
Cada sistema de arquivos T1 e V7 cont�m 2 nomes: o nome do pr�prio sistema de
arquivos ("nome"), e o nome do volume que o cont�m ("volume").
O comando "fsname" permite consultar e/ou atualizar
os nomes/volumes de sistemas de arquivos.
Estes nomes s�o tamb�m manipulados por outros comandos,
tais como "mkfs", "fsck" e "mount" (cmd).

.sp
A fun��o do programa depende da op��o dada:

.in +3
.ip -t
Imprime um tabela contendo os tipos (T1 ou V2), nomes e volumes
dos <dispositivo>s dados. Esta op��o � assumida, se n�o for dada nenhuma op��o.

.sp
Se "fsname" n�o conseguir identificar o sistema de arquivo, imprime
apenas um ponto (".") para o tipo.
Para <dispositivo>s montados, s�o reconhecidos outros tipos de sistemas
de arquivos. 

.ip -s
Altera o "nome" e (opcionalmente) o "volume" do sistema de arquivos
residente em <dispositivo> para <nome> e <volume>.

.bc	/*************************************/
Al�m disto, o "n�mero m�gico", que valida um sistema
de arquivos � verificado, e o usu�rio tem chance de corrig�-lo,
caso esteja errado.
.ec	/*************************************/

.sp
Se para o <nome> e/ou <volume> forem dados a cadeia "-", ser� atribu�do
um valor padr�o: para o "nome" a cadeia vazia, e para o "volume" o nome
do dispositivo contido na tabela de parti��es.

.sp
Se para o <nome> e/ou <volume> forem dados a cadeia ".", ou ainda se n�o
forem dados, os seus valores n�o ser�o alterados.

.ip -f
Normalmente, � pedida uma confirma��o do usu�rio para alterar
o nome/volume do sistema de arquivos. Com esta op��o, a confirma��o
� dispensada.

.ep
.in -3

.in
.sp
.b OBSERVA��O
.in 5
Este comando � reservado para o administrador
do sistema, e n�o deve ser utilizado em sistemas de arquivos
montados.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
mkfs, fsck, mount
.br
.wo "(sys): "
ustat
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
