.bp
.he 'MKDEV (cmd)'TROPIX: Manual de Refer�ncia'MKDEV (cmd)'
.fo 'Atualizado em 30.07.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "mkdev -"
cria/atualiza os dispositivos de "/dev"
.br

.in
.sp
.b SINTAXE
.in 5
.(l
mkdev [-wufasv]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "mkdev" cria e/ou atualiza os dispositivos de "/dev"
(ou "/aroot/dev", veja a op��o "-a")
para que "/dev" fique consistente com a tabela de parti��es e
a tabela de dispositivos do n�cleo do TROPIX.

.sp
Os dispositivos envolvidos
nestas opera��es s�o todos os dispositivos especiais estruturados
(de blocos) e n�o-estruturados (de caracteres) associados a discos r�gidos,
discos remov�veis (com as suas respectivas parti��es), al�m
de todos os outros dispositivos n�o-estruturados
tais como linhas seriais, telas de modo texto, pseudo terminais,
dispositivos "ethernet", etc ...

.bc	/*************************************/
Em outras palavras, s�o os dispositivos com os nomes
"/dev/hd*", "/dev/rhd*", "/dev/sd*" e "/dev/rsd*".
.ec	/*************************************/

.sp
Al�m disto, s�o atualizados os dispositivos "/dev/root" e "/dev/swap".

.sp
Tamb�m s�o atualizados sin�nimos de dispositivos (isto �, dispositivos
que s�o elos f�sicos de dispositivos da tabela de parti��es).
Assim sendo, � mais interessante criar sin�nimos para
parti��es usando o comando "ln" ao inv�s de criar novos dispositivos
atrav�s do comando "mknod".

.sp
O comando tamb�m verifica se h� dispositivos "esp�rios", ou seja,
dispositivos presentes em "/dev", mas n�o mais presentes
na tabela de parti��es nem na tabela de dispositivos do n�cleo do TROPIX.

.sp
Normalmente, "mkdev" apenas indica as inconsist�ncias, sem alterar "/dev".

.sp
As op��es do comando s�o:

.in +3
.ip -w
Modifica "/dev", criando/atualizando/removendo os dispositivos em "/dev"
para que reflitam corretamente a tabela de parti��es/tabela de dispositivos.

.ip -u
Sin�nimo de "-w".

.ip -f
O comando normalmente pede permiss�o para cada modifica��o em "/dev"
a realizar. Com esta op��o, o usu�rio d� permiss�o a "mkdev" a realizar
todas as modifica��es necess�rias sem outras consultas.

.ip -a
Cria e/ou atualiza os dispositivos de "/aroot/dev" ao inv�s de "/dev".

.ip -s
Modo silencioso. N�o escreve as inconsist�ncias encontradas.
Implica "-f".

.ip -v
Verboso.

.ep
.in -3

.in
.sp
.b OBSERVA��O
.in 5
Este comando somente pode ser executado pelo superusu�rio.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
prdisktb, ln, mknod
.br
.wo "(fmt): "
parttb
.br

.in
.sp
.(t
.b ARQUIVOS
.in 5
/dev/*
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
