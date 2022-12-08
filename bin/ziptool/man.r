.bp
.he 'ZIPTOOL (cmd)'TROPIX: Manual de Refer�ncia'ZIPTOOL (cmd)'
.fo 'Atualizado em 23.12.03'Vers�o 4.5.0'Pag. %'

.b NOME
.in 5
.wo "ziptool -"
ferramenta para dispositivos Iomega ZIP
.br

.in
.sp
.b SINTAXE
.in 5
.(l
ziptool [-rpwqe] [-c <code>] [-23] [<dev>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "ziptool" executa algumas opera��es especiais dispon�veis
nas unidades ZIP da Iomega.

Estas unidades s�o acionadores de discos remov�veis de 100 MB,
conectados ao barramento IDE/ATAPI, SCSI ou � porta paralela.

.sp
Antes de poder utilizar as unidades ZIP, � necess�rio configur�-las
(veja abaixo em CONFIGURA��O).

.sp
Em cada execu��o de "ziptool" � executada a opera��o definida pela
op��o dada (veja abaixo); a opera��o � executada no dispositivo <dev>,
e caso este n�o seja dado, em "/dev/zip".

.sp
As op��es do comando s�o:

.in +3
.ip --
Imprime a prote��o atual. Sem op��es, o comando imprime o estado
da prote��o corrente do disco.

.ip -r
Altera a prote��o do disco para permitir apenas leituras
(sem senha).

.ip -p
Altera a prote��o do disco para permitir apenas leituras,
e atribui uma senha para posterior altera��o da prote��o.

.ip -w
Altera a prote��o para permitir leituras e escritas.
Se o disco estava protegido com uma senha, ela � pedida.

.ip -q
Altera a prote��o para permitir leituras e escritas,
por�m somente enquanto o disco n�o for retirado do dispositivo.

.sp
Esta altera��o n�o � poss�vel a partir do estado que
permite apenas leituras com senha.

.ip -e
Retira o disco do dispositivo.

.ip -c
Consulta ou altera o c�digo da parti��o do sistema de arquivos.
Se <code> for "-", o c�digo � escrito em sua forma hexadecimal
(0x00 a 0xFF). Para os valores 0x06, 0xA8 e 0xA9 s�o tamb�m
dados os valores simb�licos ("FAT", "V7" e "T1").

.sp
Se <code> tiver um valor num�rico ou um dos nomes simb�licos
acima, o c�digo da parti��o � alterado para o valor dado.
O c�digo da parti��o deve corresponder ao tipo do sistema de arquivos
contido no disco para que ele possa ser montado atrav�s do comando
"mount" (cmd".

.ip -2
Atribui o valor "/dev/zip0" a <dev>.

.ip -3
Atribui o valor "/dev/zip1" a <dev>.

.ep
.in -3

.in
.sp
.b OBSERVA��O
.in 5
H� um modo de prote��o em que n�o s�o permitidas
leituras nem escritas. Este modo N�O � suportado pelo TROPIX.

.sp
Os nomes "/dev/zip" e /dev/zip0" s�o sin�nimos.

.in
.sp
.b CONFIGURA��O
.in 5
Para a configura��o das unidades, execute as seguintes etapas:

.in +3
.ip 1. 3
Durante a carga do TROPIX, certifique-se de que a unidade ZIP est�
sendo reconhecida. Al�m disto, se for IDE/ATAPI ou SCSI, dever� ser impressa
uma mensagem relativo ao respectivo barramento.

.ip 2. 3
Se n�o for reconhecida (no caso da porta paralela),
experimente mudar o seu modo (EPP, PS2, NIBBLE, ...) na BIOS do computador.
Na presente vers�o, nem todas as pastilhas ("chips") de portas paralelas
s�o reconhecidas pelo TROPIX. H� uma chance da sua unidade ZIP n�o
poder ser usada.

.ip 3. 3
Uma vez detetado, ainda em mono-usu�rio, execute o comando
"mkdev" (veja o manual). Ele criar� quatro novos arquivos
(provavelmente) denominados "/dev/sda", "/dev/sda4",
"/dev/rsda" e "/dev/rsda4" (confira atrav�s do comando "prdisktb").

.ip 4. 3
Crie nomes convenientes atrav�s do comando "ln":

.sp
.(l
		ln /dev/sda4  /dev/zip
		ln /dev/rsda4 /dev/rzip
		ln /dev/sda4  /dev/zip0
		ln /dev/rsda4 /dev/rzip0
.)l

.ip 5. 3
Teste o dispositivo atrav�s do comando "ziptool".
No caso da porta paralela, se n�o conseguir acess�-lo corretamente,
experimente alterar na BIOS do PC o modo da porta paralela (EPP, PS2, NIBBLE, ...).

.ip 6. 3
Crie uma entrada adequada no arquivo "fstab" (fmt), como por exemplo:

.sp
.(l
		/dev/zip  /zip	noauto,user
.)l

.ip 7. 3
Pronto! Voc� j� poder� examinar/alterar a prote��o atrav�s do
comando "ziptool", montar discos ZIP DOS atrav�s de "dosmp",
criar cole��es GAR/TAR atrav�s de "gar", criar sistemas de
arquivos atrav�s de "mkfs", mont�-los atrav�s de "mount" ...
Se o barramento for IDE/ATAPI ou SCSI, voc� poder� gerenciar
a tabela de parti��es atrav�s de "fdisk" contido no "boot2".

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
fdisk, mount
.br
.wo "(fmt): "
fstab
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
