.bp
.he 'FSTAB (fmt)'TROPIX: Manual de Refer�ncia'FSTAB (fmt)'
.fo 'Atualizado em 05.19.02'Vers�o 4.3.0'Pag. %'

.b NOME
.in 5
.wo "fstab -"
tabela de informa��es sobre sistemas de arquivos
.br

.in
.sp
.b DESCRI��O
.in 5
O arquivo "/etc/fstab" cont�m informa��es sobre diversos
sistemas de arquivos e � consultado por diversos
programas, entre os quais "mount", "umount", "fsck", "eject" (cmd).

.sp
Cada linha refere-se a um sistema de arquivos, e cont�m 3 campos
(separados por espa�os ou <ht>), como no exemplo:

.sp
.(l
		/dev/zip   /zip   noauto,user,noexec
.)l

.sp
O primeiro campo d� o nome do dispositivo especial estruturado
(de blocos) a ser montado, o segundo campo d� o nome do diret�rio
no qual o dispositivo deve ser montado, e o terceiro campo d� uma
lista de op��es de montagem separadas por v�rgulas.

.sp
A ordem das linhas � importante, pois os comandos "mount" e "fsck"
(entre outros) processam as linhas seq�encialmente.

.sp
Para ver a lista de op��es de montagem, veja "getmntopt" (libc).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd):  "
mount, umount, fsck, eject
.br
.wo "(libc): "
getmntent, getmntopt
.br

.in
.sp
.b ARQUIVOS
.in 5
/etc/fstab

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
