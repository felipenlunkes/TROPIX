.bp
.he 'MKNOD (cmd)'TROPIX: Manual de Refer�ncia'MKNOD (cmd)'
.fo 'Atualizado em 30.05.97'Vers�o 3.0.1'Pag. %'

.b NOME
.in 5
.wo "mknod -"
cria um arquivo especial
.br

.in
.sp
.b SINTAXE
.in 5
.(l
/etc/mknod <nome> <tipo> <major> <minor>
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "mknod" cria o arquivo especial <nome>.

.sp
O argumento <tipo> d� o tipo do arquivo:
"b" para arquivo especial de blocos (estruturado) ou
"c" para arquivo especial de caracteres (n�o-estruturado).

.sp
Os argumentos <major> e <minor> d�o a identifica��o num�rica
do arquivo especial.

.in
.sp
.b OBSERVA��O
.in 5
Este comando � reservado para o administrador do sistema;
ele poder� obter as identifica��es num�ricas dos arquivos especiais
em determinadas tabelas do sistema operacional.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
mkfifo
.br
.wo "(sys): "
mknod
.br

.in
.sp
.b EXEMPLO
.in 11
/etc/mknod /dev/tty006 c 4 6
.sp
.in 5
cria o arquivo "/dev/tty006" como um dispositivo especial de 
caracteres com <major> 4 e <minor> 6.


.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
