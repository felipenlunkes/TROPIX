.bp
.he 'NFS (fmt)'TROPIX: Manual de Refer�ncia'NFS (fmt)'
.fo 'Atualizado em 05.03.06'Vers�o 4.8.0'Pag. %'

.b NOME
.in 5
.wo "nfs -"
o sistema de arquivos NFS
.br

.in
.sp
.b DESCRI��O
.in 5
O Sistema de Arquivos NFS (Network File System) permite o acesso a arquivos
de computadores remotos do mesmo modo do acesso a arquivos locais. Este acesso
a arquivos remotos � (quase) completamente transparente para o cliente,
e funciona atrav�s de uma variedade de arquitetura de servidores e computadores.

.sp
Um computador cliente pode montar um diret�rio (isto �, um sistema de arquivos)
de um computador remoto (servidor) em um
diret�rio local do mesmo modo do que monta um dispositivo f�sico (um sistema de
arquivos local). A sintaxe � quase a mesma, por�m cont�m tamb�m o nome do computador
remoto. Assim, por exemplo, para montar o diret�rio remoto "/src" do computador "beta"
no diret�rio "/beta/src" do computador (local) "alpha", deve-se usar um comando da forma

.sp
.nf
		mount beta:/src /beta/src
.fi

.sp
� primeira vista, a semelhan�a entre "beta:/src" e "/beta/src" pode parecer confusa,
mas "/beta/src" � o modo mais claro de nos referimos ao diret�rio "/src" do computador "beta".

.sp
O comando "mount" ir� tentar conectar o servidor NFS do computador "beta". Este por
sua vez, ir� checar se o computador "alpha" possui a permiss�o para acessar e montar
o diret�rio "/src", e se este for o caso, ir� retornar o sucesso da montagem.

.sp
Uma vez montado, os arquivos remotos podem ser acessados atrav�s do diret�rio (local)
"/beta/src". Como o protocolo NFS utiliza os UIDs e GIDs num�ricos locais para verificar as permiss�es
de acesso aos arquivos remotos, � interessante que estes n�meros sejam os mesmos no cliente e
servidor. Se este n�o for o caso, � poss�vel dar indica��es sobre o mapeamento dos
UIDs e GIDs no arquivo "/etc/exports" (fmt).

.sp
H� v�rias vers�es do protocolo NFS: 2, 3 e 4. Atualmente o TROPIX possui apenas a vers�o 2
implementada; isto no entanto, n�o � um problema grave, pois a maioria dos servidores
aceitam esta vers�o, tais como o FreeBSD e LINUX.
Al�m disto, o TROPIX permite a transfer�ncia de apenas 1 KB de dados em cada datagrama NFS, enquanto
que os servidores em geral preferem transferir 4 KB ou 8 KB. Mais adiante veremos como
configurar o FreeBSD e LINUX para usar datagramas de apenas 1 KB de dados.

.sp
O comando "mount" lista tanto os sistemas de arquivos NFS remotos montados por este
cliente, como os sistemas de arquivos NFS locais montados por clientes remotos
veja "mount" (cmd).

.in
.sp
.b "CONFIGURANDO O NFS"
.in 5
Para utilizar o NFS, s�o necess�rios 3 passos:

.in +3
.ip 1. 3
Certificar-se de que o cliente/servidor est� acess�vel. Isto n�o faz parte do protocolo NFS,
e deve ser consultado em "internet" (cmd) e "itnetdev" (fmt).

.ip 2. 3
Preparar uma entrada em "etc/fstab" (no cliente), como o exemplo abaixo:

.sp
.nf
		beta:/src    /beta/src    noauto,nofsck
.fi

.sp
Com esta entrada podemos usar apenas

.sp
.nf
		mount /beta/src
.fi

.sp
ao inv�s da linha mais acima. Se for desejado, pode ser usada a op��o "auto" para
que a montagem seja realizada automaticamente durante a inicializa��o.

.sp
Esta entrada n�o � obrigat�ria, mas
auxilia a execu��o do comando "mount", pois n�o ser� ent�o necess�rio dar as diversas
op��es de montagem.
Veja os detalhes em "fstab" (fmt) e "getmntopt" (libc).


.ip 3. 3
Preparar uma entrada em "etc/exports" (no servidor), como o exemplo abaixo:

.sp
.nf
		/src alpha.nce.ufrj.br(rw,async,no_root_squash)
.fi

.sp
Esta entrada � necess�ria.
Veja os detalhes em "exports" (fmt) e "exportfs" (cmd).

.sp
Repare que atrav�s do comando "exportfs" � poss�vel mudar dinamicamente
os diret�rios que podem ser montados remotamente.

.ep
.in -3


.in
.sp
.b "CONFIGURANDO O LINUX"
.in 5
Para um cliente LINUX acessar o servidor NFS do TROPIX, � necess�rio
lembrar que o TROPIX permite a transfer�ncia de apenas 1 KB de dados por datagrama.
Devemos pois usar um comando "mount" da forma:

.sp
.nf
	mount -o rsize=1024,wsize=1024 beta:/src /beta/src
.fi

.sp
ou melhor ainda, preparar uma entrada no arquivo "/etc/fstab" da forma:

.sp
.nf
	beta:/src /beta/src nfs noauto,rsize=1024,wsize=1024 0 0
.fi

.sp
N�o � necess�rio especificar a vers�o 2 do NFS, pois esta � a vers�o
"default" do LINUX. Para maiores detalhes, � claro, consulte a documenta��o
do LINUX.

.in
.sp
.b "CONFIGURANDO O FreeBSD"
.in 5
Assim como no caso do LINUX,  � necess�rio lembrar que o TROPIX permite
a transfer�ncia de apenas 1 KB de dados por datagrama.
Devemos pois usar um comando "mount" da forma:

.sp
.nf
	mount_nfs -2 -r 1024 -w 1024 beta:/src /beta/src
.fi

.sp
Com a op��o "-2" especificamos a vers�o 2 do NFS, pois a vers�o
"default" do FreeBSD � a 3.

.sp
No arquivo "/etc/exports", repare que o equivalente ao parametro "anonuid"
� "maproot". Assim, uma linha exemplo deste arquivo seria:

.sp
.nf
	/src -maproot=root alpha
.fi

.sp
Para maiores detalhes, � claro, consulte a documenta��o do FreeBSD.


.in
.sp
.b
.(t
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
internet, mount, exportfs
.br
.wo "(fmt): "
itnetdev, fstab, exports
.br
.)t

.in
.sp
.b ARQUIVOS
.in 5
 /etc/fstab
 /etc/exports

.in
.sp
.b ESTADO
.in 5
Efetivo.

.bc	/*************************************/

	LINUX

/dev/hda9        swap             swap        defaults         0   0
/dev/hda10       /                ext2        defaults         1   1
/dev/hda11       /home            ext2        defaults         1   2
/dev/hda1        /dos_c           vfat        defaults         1   0
/dev/hda5        /dos_d           vfat        defaults         1   0
/dev/hda6        /dos_e           vfat        defaults         1   0
/dev/hda7        /dos_f           vfat        defaults         1   0
/dev/hda8        /dos_g           vfat        defaults         1   0
/dev/cdrom       /mnt/cdrom       iso9660     noauto,owner,ro  0   0
/dev/fd0         /fd0             auto        noauto,owner     0   0
piano:/src	/piano/src	nfs	noauto,soft,rw,rsize=1024,wsize=1024	0	0
piano:/tmp	/piano/tmp	nfs	noauto,soft,rw,rsize=1024,wsize=1024	0	0
piano:/home/pedrosal /piano/home/pedrosal nfs noauto,soft,rw,rsize=1024,wsize=1024 0 0
piano:/home	/piano/home	nfs noauto,soft,rw,rsize=1024,wsize=1024 0 0
piano:/alia	/piano/alia	nfs noauto,soft,rw,rsize=1024,wsize=1024 0 0
grave:/src	/grave/src	nfs	noauto,soft,rw,rsize=1024,wsize=1024	0	0
grave:/tmp	/grave/tmp	nfs	noauto,soft,rw,rsize=1024,wsize=1024	0	0
grave:/home/pedrosal /grave/home/pedrosal nfs noauto,soft,rw,rsize=1024,wsize=1024 0 0
devpts           /dev/pts         devpts      gid=5,mode=620   0   0
proc             /proc            proc        defaults         0   0


# See exports(5) for a description.
# This file contains a list of all directories exported to other computers.
# It is used by rpc.nfsd and rpc.mountd.
#
/home/pedrosal		piano(rw,async,no_root_squash) grave(rw,async)




	FreeBSD


# Device		Mountpoint	FStype	Options		Dump	Pass#
/dev/ad0s3b		none		swap	sw		0	0
/dev/ad0s3a		/		ufs	rw		1	1
/dev/ad0s3e		/tmp		ufs	rw		2	2
/dev/ad0s3f		/usr		ufs	rw		2	2
/dev/ad0s3d		/var		ufs	rw		2	2
/dev/cd0		/cdrom		cd9660	ro,noauto	0	0
/dev/cd1		/cdrom1		cd9660	ro,noauto	0	0


#The following examples export /usr to 3 machines named after ducks,
#/usr/src and /usr/ports read-only to machines named after trouble makers
#/home and all directories under it to machines named after dead rock stars
#and, /a to a network of privileged machines allowed to write on it as root.
#/usr                   huey louie dewie
#/usr/src /usr/obj -ro  calvin hobbes
#/home   -alldirs       janice jimmy frank
#/a      -maproot=0  -network 10.0.1.0 -mask 255.255.248.0
#
# You should replace these lines with your actual exported filesystems.
# Note that BSD's export syntax is 'host-centric' vs. Sun's 'FS-centric' one.

/root    -maproot=root  piano.nce.ufrj.br
/usr/src -maproot=root  piano.nce.ufrj.br


mount_nfs -2 -r 1024 -w 1024 piano:/src /mnt






.ec	/*************************************/
