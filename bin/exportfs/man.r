.bp
.he 'EXPORTFS (cmd)'TROPIX: Manual de Refer�ncia'EXPORTFS (cmd)'
.fo 'Atualizado em 07.03.06'Vers�o 4.8.0'Pag. %'

.b NOME
.in 5
.wo "exportfs -"
lista/atualiza a tabela "exports" do NFS
.br

.in
.sp
.b SINTAXE
.in 5
.(l
exportfs [-eduf]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "exportfs" gerencia a tabela de sistemas de arquivos exportados
pelo NFS. O formato desta tabela pode ser visto em "exports" (fmt).

.sp
A tabela � contida no arquivo "/etc/exports", de onde � lida durante a inicializa��o
do sistema operacional, e copiada para o n�cleo. Esta c�pia da tabela no n�cleo � a que
efetivamente ir� decidir quais s�o os sistemas de arquivos exportados.

.sp
Atrav�s do comando "exportfs", podemos alterar dinamicamente a lista dos sistemas exportados.
Al�m disto, o comando lista as duas tabelas e indica as diferen�as entre elas.

.sp
As op��es do comando s�o:

.in +3
.ip --
Sem op��es, � listada a tabela "exports" do n�cleo
(a tabela efetiva no momento).

.ip -e
Lista a tabela "exports" do arquivo "/etc/exports".

.ip -d
Indica as diferen�as entre as duas tabelas.
Linhas adicionadas em "/etc/exports" s�o indicadas com um prefixo "+";
linhas removidas de "/etc/exports" s�o indicadas com um prefixo "-" e
linhas modificadas s�o indicadas com um prefixo "!".

.ip -u
Atualiza a tabela "exports" do n�cleo, a partir de "/etc/exports",
isto �, torna "/etc/exports" a tabela efetiva dinamicamente.

.ip -f
Normalmente, � pedida uma confirma��o da atualiza��o da tabela "exports"
do n�cleo. Com esta op��o, esta confirma��o � dispensada.

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(fmt): "
nfs, exports
.br

.in
.sp
.b ARQUIVOS
.in 5
/etc/exports

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
