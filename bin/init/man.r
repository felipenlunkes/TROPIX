.bp
.he 'INIT (cmd)'TROPIX: Manual de Refer�ncia'INIT (cmd)'
.fo 'Atualizado em 08.05.97'Vers�o 3.0.2'Pag. %'

.b NOME
.in 5
.wo "init -"
inicializa��o da opera��o do sistema
.br

.in
.sp
.b SINTAXE
.in 5
/etc/init

.in
.sp
.b DESCRI��O
.in 5
O comando "init" � o programa que assume o controle durante
a inicializa��o da opera��o do sistema, e cria todo o cen�rio
necess�rio para a opera��o normal do sistema. A sua atividade
pode ser dividida em 3 partes:

.ip MONOUSU�RIO: 16
nesta primeira fase, o sistema � aberto apenas na console,
permitindo ao operador executar tarefas administrativas, tais
como verificar a integridade dos sistemas de arquivos, dar a
data ao sistema, etc... 

.ip "ARQUIVO rc:" 16
nesta fase, s�o executados os comandos constantes do arquivo
"/etc/rc", que se comp�e de comandos de inicializa��o tais
como a montagem de sistemas de arquivos, remo��o de arquivos
tempor�rios, etc....

.ip MULTIUSU�RIO: 16
nesta �ltima fase, em que ele permanece at� a pr�xima
carga do sistema, s�o criados
processos, um para cada terminal ativo, conforme indicados
no arquivo "/etc/initab". Cada um destes processos ir� executar
um comando "login", possibilitando a um usu�rio entrar em sess�o.
.ep
.sp

.in
.b OBSERVA��O
.in 5
Este comando especial n�o pode ser utilizado. A sua execu��o
� iniciada automaticamente durante o processo de inicializa��o
da opera��o do sistema.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
login, sh
.br
.wo "(fmt): "
rc
.br

.in
.sp
.b ARQUIVOS
.in 5
 /dev/console
 /etc/mtab
 /etc/utmp
 /etc/initab
 /etc/globalenv
 /etc/rc

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
