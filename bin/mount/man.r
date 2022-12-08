.bp
.he 'MOUNT (cmd)'TROPIX: Manual de Refer�ncia'MOUNT (cmd)'
.fo 'Atualizado em 13.03.06'Vers�o 4.8.0'Pag. %'

.b NOME
.in 5
Monta e desmonta sistemas de arquivos:
.sp
.wo "mount  -"
monta sistemas de arquivos
.br
.wo "umount -"
desmonta sistemas de arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
mount [-rw] [-o <op��es>] <dispositivo> <diret�rio>
mount [-rw] [-o <op��es>] <dispositivo ou diret�rio>
mount [-rw] [-o <op��es>] -a
mount [-v]

umount [-o <op��es>] <dispositivo ou diret�rio> ...
umount [-o <op��es>] -a
.)l

.in
.sp
.b DESCRI��O
.in 5
Os comandos "mount" e "umount" alteram a �rvore que modela a estrutura
de arquivos do sistema operacional.

.sp
O comando "mount" incorpora uma ou mais sub�rvores de arquivos
� arvore principal do sistema.
Cada sub�rvore (indicada como <dispositivo> acima),
pode ser dada como um sistema de arquivos local
contido em um dispositivo (arquivo especial de blocos),
a imagem de um sistema de arquivos contida em um arquivo regular local
ou ainda (no caso de sistemas de arquivos NFS) de
um par da forma "servidor:/diret�rio", ver "nfs" (fmt).




.bc	/*************************************/
Cada sub�rvore consiste de um sistema de arquivos
contido em um dispositivo (arquivo especial de blocos)
ou um arquivo regular.

O comando "mount" incorpora uma ou mais sub�rvores de arquivos
(ou seja, sistemas de arquivos contidos em dispositivos ou imagens
de sistemas de arquivos contidos em arquivos regulares)
� arvore principal do sistema.
.ec	/*************************************/

.sp
O comando "umount" desfaz a a��o de "mount", desmontando um ou mais sistemas 
de arquivos da �rvore principal.

.sp
O arquivo "/etc/fstab" suplementa a execu��o de "mount" e "umount",
fornecendo informa��es que podem estar omitidas de algumas formas de "mount" e "umount",
em particular, as op��es de montagem.
Para ver o formato deste arquivo e quais s�o as op��es de montagem,
veja "fstab" (fmt) e "getmntent" (libc).

.sp
Normalmente, somente o superusu�rio pode montar/desmontar sistemas de arquivos.
No entanto, se uma linha do arquivo "/etc/fstab" contiver a op��o "user",
qualquer usu�rio poder� montar o sistema de arquivos correspondente.
Neste caso, somente o usu�rio que montou o sistema (ou o superusu�rio)
poder� desmont�-lo.

.sp
Em sua primeira forma,

.sp
.(l
	mount [-rw] [-o <op��es>] <dispositivo> <diret�rio>
.)l

.sp
o comando "mount" incorpora
a sub�rvore contida no <dispositivo> � arvore principal do sistema.
O <diret�rio> passa a ser a raiz desta sub�rvore.
Se, por acaso, o <diret�rio> era a raiz de uma sub�rvore antes da montagem,
esta sub�rvore fica oculta enquanto o sistema de arquivos estiver montado.
Esta � a �nica forma em que as op��es de montagem definidas em "/etc/fstab"
N�O s�o consultadas (as op��es usadas s�o as "default", possivelmente modificadas
pelas op��es "-r", "-w" ou "-o").

.sp
Na sua segunda forma,

.sp
.(l
	mount [-rw] [-o <op��es>] <dispositivo ou diret�rio>
.)l

.sp

basta dar o <dispositivo> ou o <diret�rio>, e a informa��o
completa � procurada no arquivo  "/etc/fstab".
As op��es de montagem usadas s�o as de "/etc/fstab", possivelmente modificadas
pelas op��es "-r", "-w" ou "-o".

.sp
Na sua terceira forma

.sp
.(l
	mount [-rw] [-o <op��es>] -a
.)l

.sp

s�o montados todos os
<dispositivo>s no respectivos <diret�rio>s dados no arquivo "/etc/fstab",
que possuem a op��o de montagem "auto".
As op��es de montagem usadas s�o as de "/etc/fstab", possivelmente modificadas
pelas op��es "-r", "-w" ou "-o".

.sp
Na sua quarta forma

.sp
.(l
	mount [-v]
.)l

.sp

o comando "mount" imprime uma tabela contendo os dispositivos mountados, respectivos
diret�rios, dados sobre o dispositivo e as op��es de montagem em uso (veja a op��o "-v", abaixo).

.sp
Se houver clientes remotos com sistemas arquivos NFS montados neste servidor,
isto ser� indicado ao final da listagem ap�s uma linha em branco.

.sp
Na atual vers�o do sistema TROPIX, podem ser montados <dispositivo>s
contendo sistemas de arquivos dos tipos TROPIX T1, TROPIX V7,
FAT12, FAT16, FAT32, CDROM (ISO 9660, Rock Ridge, Joliet), LINUX/EXT2,
NTFS (somente para leitura) e NFS (vers�o 2).
N�o � necess�rio dar o tipo: ele � descoberto automaticamente pelo
c�digo da entrada da tabela de parti��es (ver "prdisktb" (cmd)) ou pelo
superbloco do sistema de arquivos.

.sp
As op��es do comando "mount" s�o:

.in +3
.ip -o
Fornece uma lista das seguintes op��es separadas por v�rgula:
"default", "ro", "rw", "user", "nouser", "atime", "noatime", "dev", "nodev", "exec",
"noexec", "suid", "nosuid", "eject", "noeject", "case", "nocase",
"rock", "norock", "joliet", "nojoliet", "lfn", "nolfn",
"hard", "soft", "rsize", "wsize", "timeout" e "retrans".
Para o significado de cada uma destas op��es, veja "getmntopt" (libc).

.ip -r
Apenas leitura: equivalente a "-o ro".

.ip -w
Leitura e escrita: equivalente a "-o rw".

.ip -a
Monta todos os dispositivos que possuem a op��o de montagem "auto" no
arquivo "/etc/fstab".

.ip -v
Normalmente, "mount" somente imprime as op��es de montagem diferentes das "default".
Com a op��o "-v" imprime t�das as op��es que se aplicam a v�rios sistemas de arquivos;
Repetindo a op��o ("-vv") imprime t�das as op��es, mesmo as particulares de um �nico
sistema de arquivos.

.ep
.in -3

.sp 2
O comando "umount" desfaz a a��o de "mount", desmontando um ou mais sistemas 
de arquivos da �rvore principal, dados atrav�s dos <dispositivo ou diret�rio>s montados.

.sp
As op��es do comando "umount" s�o:

.in +3
.ip -o
Fornece uma lista de seguintes op��es separadas por v�rgula:
a lista � a mesma da op��o "-u", de "mount" (acima), no entanto,
atualmente apenas s�o consideradas as op��es "eject" e "noeject",
para modificar a a��o descrita no arquivo "/etc/fstab".

.ip -a
Tenta desmontar todos os dispositivos montados (exceto o dispositivo RAIZ e PIPE).
Isto s� ser� poss�vel para aqueles que n�o estejam em uso.

.ep
.in -3

.sp
.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd):  "
prdisktb
.br
.wo "(sys):  "
intro, mount, umount
.br
.wo "(libc): "
getmntent, getmntopt
.br
.wo "(fmt):  "
fstab, nfs
.br

.in
.sp
.b ARQUIVOS
.(l
/etc/fstab
.)l

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
