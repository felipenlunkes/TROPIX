.bp
.he 'DF (cmd)'TROPIX: Manual de Refer�ncia'DF (cmd)'
.fo 'Atualizado em 10.09.02'Vers�o 4.3.0'Pag. %'

.b NOME
.in 5
.wo "df -"
informa sobre o espa�o dispon�vel de sistemas de arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
df [-kbi] [<nome> ...]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "df" d� informa��es sobre o espa�o total, ocupado e livre 
de sistemas de arquivos (montados ou n�o).
Para sistemas desmontados, "df" somente fornece dados para os
tipos T1 e V7.

.sp
De acordo com as op��es (ver abaixo), "df" d� informa��es sobre
a regi�o do sistema de arquivos destinada a blocos de arquivos ou
sobre a regi�o destinada a n�s-�ndice.

.sp
Cada sistema de arquivos � dado atrav�s de um <nome>, que pode ser

.in +3
.ip 1. 3
um dispositivo: o arquivo especial de blocos ou de caracteres que cont�m
o sistema de arquivos (por exemplo, "/dev/rwe2");

.ip 2. 3
o diret�rio de montagem do sistema de arquivos (por exemplo, "/u");

.ip 3. 3
um outro arquivo qualquer (n�o especial) contido no sistema de arquivos
montado.

.ep
.in -3

.sp
As op��es do comando s�o:

.in +3
.ip --
Sem op��es, s�o dados o espa�o total, ocupado e livre em MB (al�m da
taxa de ocupa��o em \%) da regi�o do sistema de arquivos destinada
a blocos de arquivos.

.ip -k
Como acima, em KB.

.ip -b
Como acima, em blocos de 512 bytes.

.ip -i
S�o dados o n�mero total, ocupado e livre de n�s-�ndice (al�m da
taxa de ocupa��o em \%) do sistema de arquivos.

.ep
.in -3

.sp
Se n�o for dado nenhum <nome>, o comando informa sobre todos os sistemas
de arquivos montados, incluindo a raiz do sistema.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
mount
.br

.in
.sp
.b ARQUIVOS
.in 5
/etc/mtab

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
