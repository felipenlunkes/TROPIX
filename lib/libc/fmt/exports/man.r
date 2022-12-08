.bp
.he 'EXPORTS (fmt)'TROPIX: Manual de Refer�ncia'EXPORTS (fmt)'
.fo 'Atualizado em 06.03.06'Vers�o 4.8.0'Pag. %'

.b NOME
.in 5
.wo "exports -"
tabela de diret�rios exportados do NFS
.br

.in
.sp
.b DESCRI��O
.in 5
A tabela "exports" � utilizada durante o processo de inicializa��o
da INTERNET para obter informa��es sobre os diret�rios "exportados",
isto �, os diret�rios que o servidor NFS deve disponibilizar para
os clientes NFS de outros computadores.

.sp
A tabela reside no arquivo "/etc/exports", e pode ser editada
diretamente pelo administrador do sistema atrav�s de "ed" (cmd)
ou "vi" (cmd).

.sp
Ap�s a inicializa��o do sistema, os diret�rios exportados podem ser
alterados atrav�s de "exportfs" (cmd).

.sp
As linhas deste arquivo tem o formato do exemplo abaixo:

.sp
.nf
		/src venus(rw,async,no_root_squash)
.fi

.sp
Cada linha define um par (diret�rio, computador cliente). Esta linha
autoriza o computador cliente "venus" a montar o diret�rio "/src".
Para permitir a montagem do mesmo diret�rio por outro cliente, ser� necess�ria outra linha.

.sp
O nome do cliente pode conter os caracteres "*" e "?" com o mesmo significado
da "sh". Por exemplo, "*.nce.ufrj.br" aceitar� todos os computadores do dom�nio "nce.ufrj.br".

.sp
Linhas em branco ou come�ando por "#" ser�o ignoradas.

.sp
O nome do cliente pode ser seguido de uma s�rie de op��es entre parenteses.
Estas op��es podem ter os seguintes valores:

.in +3
.ip secure 15
S� aceita datagramas NFS com a porta abaixo de 1024 (n�o implementado).

.ip insecure 15
Aceita datagramas NFS com qualquer porta (op��o "default").

.ip ro 15
Monta o diret�rio apenas para leituras (op��o "default").

.ip rw 15
Monta o diret�rio para leituras e escritas.

.ip sync 15
As escritas dos blocos dos arquivos ser� feita imediatamente, e s�
ap�s a conclus�o desta escrita ser� enviada a confirma��o para o cliente (n�o implementado).

.ip async 15
A confirma��o para o cliente � enviado imediatamente, mas
as escritas dos blocos dos arquivos ser� feita apenas de acordo 
com o algor�tmo do CACHE de blocos do servidor (op��o "default").

.ip hide 15
As sub�rvores dos sistemas de arquivos exportados que correspondem a um
outro dispositivo (isto �, a um outro sistema de arquivos montado em algum ponto
do sistema de arquivos exportado) s�o "invis�veis" para o cliente
(op��o "default").

.sp
Se alguma sub�rvore deste tipo deve ser exportada, ser� necess�rio
um outro ponto de montagem.

.ip nohide 15
As sub�rvores s�o "vis�veis" (veja acima, n�o implementado).
Esta op��o n�o � implementada, pois ir� implicar em n�meros de
n�s-�ndice duplicados na mesma montagem.

.ip root_squash 15
Este � um item de seguran�a que impede a um superusu�rio de um cliente
possuir acessos de superusu�rio neste servidor. Esta op��o mapeia
o UID 0 de superusu�rio do cliente em -2 no servidor (op��o "default").

.sp
Lembre-se que normalmente os UIDs dos outros usu�rios N�O � alterada (veja abaixo).

.ip no_root_squash 15
N�o altera o UID do superusu�rio (veja acima).
O superusu�rio de um cliente ir� possuir acessos de superusu�rio neste servidor.

.ip all_squash 15
Este � um item de seguran�a mais radical, que mapeia
o UID de todos os usu�rios do cliente em -2 no servidor.

.ip anonuid=uid 15
Mapeia o UID de todos os usu�rios do cliente em "uid" no servidor.
Esta op��o � �til para clientes com sistemas operacionais que n�o possuem o conceito
de UID.

.ip anongid=gid 15
Mapeia o GID de todos os usu�rios do cliente em "gid" no servidor.
Esta op��o � �til para clientes com sistemas operacionais que n�o possuem o conceito
de GID.

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
internet, exportfs, sh, vi, ed
.br
.wo "(fmt): "
nfs
.br

.in
.sp
.b ARQUIVOS
.in 5
/etc/exports

.bc	/*************************************/
.in
.sp
.b EXEMPLO
.nf
	#
	#	R�de dom�stica (pode haver linha discada)
	#
	127.0.0.1		jupiter.tropix.com.br

	192.168.0.3		marte.tropix.com.br
	192.168.0.4		venus.tropix.com.br

	146.164.8.7		barra.nce.ufrj.br
	146.164.8.3		vidigal.nce.ufrj.br
	146.164.8.2		rocinha.nce.ufrj.br

	/dev/ed0				192.168.0.2
	netmask=255.255.255.0

	name_server		200.17.63.121	146.164.10.2
.fi
.ec	/*************************************/

.in
.sp
.b ESTADO
.in 5
Efetivo.
