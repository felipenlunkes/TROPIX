.bp
.he 'EJECT (cmd)'TROPIX: Manual de Refer�ncia'EJECT (cmd)'
.fo 'Atualizado em 01.10.02'Vers�o 4.3.0'Pag. %'

.b NOME
.in 5
.wo "eject -"
ejeta o meio remov�vel de um dispositivo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
eject [-23] [<dispositivo/diret�rio>]
.)l

.bc	/*************************************/
eject - ejeta o meio remov�vel de um dispositivo

Vers�o: 4.3.0, de 01.10.00

Sintaxe:
	eject [-23] [<dispositivo/diret�rio>]

Op��es:	-2: O dispositivo ser� "/dev/zip0"
	-3: O dispositivo ser� "/dev/zip1"

Obs.:	Se <dev> n�o for dado, ser� considerado "/dev/zip"
.ec	/*************************************/

.in
.sp
.b DESCRI��O
.in 5
O comando "eject" tenta ejetar o meio remov�vel de um dispositivo.
Isto nem sempre � poss�vel, pois nem todos os dispositivos oferecem esta possibilidade.

.sp
Pode ser dado o nome do dispositivo, ou do diret�rio em que ele � montado usualmente
(atrav�s de "/etc/fstab").

.sp
Sem argumento nem op��es, ejeta "/dev/zip".

.sp
Se o usu�rio do programa N�O for superusu�rio, verifica se o dispositivo tem a op��o
de montagem "user" em "/etc/fstab".

.sp
As op��es do comando s�o:

.in +3
.ip -2
O dispositivo ser� "/dev/zip0".

.ip -3
O dispositivo ser� "/dev/zip1".

.ep
.in -3


.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd):  "
mount, umount
.br
.wo "(libc): "
getmntent
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
