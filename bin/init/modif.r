.bp
.he 'INIT (cmd)'TROPIX: Manual de Modifica��es'INIT (cmd)'
.fo 'Atualizado em 17.07.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "init -"
inicializa��o da opera��o do sistema
.br

.in
.sp 2
.ip "01.12.87  1.1.0" 20
VERS�O CORRENTE
.sp

.ip "06.11.88  2.1.0" 20
Foi alterado o nome do arquivo "/etc/profile" para "/etc/globalenv",
e agora as suas linhas s�o testadas para verificar se possuem '='.

.sp
Agora, a escrita da data � feita ap�s
a mensagem do nome
do "sh".

.ip "23.10.89  2.3.0" 20
Foi criada a id�ia do "PRINT_CHILD_STATUS".

.ip "01.10.91  2.3.1" 20
Foi tornada autom�tica a obten��o do nome do sistema atrav�s de "uname".

.ip "21.10.91  2.3.2" 20
Agora � colocado a vari�vel "SYS" no ambiente.

.ip "16.11.92  3.0.0" 20
Agora s� ativa as linhas com estado == '*'.

.ip "16.02.97  3.0.1" 20
Trocado "boot" por "root" na busca da senha.

.ip "08.05.97  3.0.2" 20
Uma pequena revis�o.

.ip "20.06.97  3.0.3" 20
Acertando o modo de "utmp" e "mtab".

.ip "31.01.99  3.1.6" 20
O modo mono-usu�rio agora entra como superusu�rio.

.ip "08.12.99  3.3.3" 20
Obtendo o nome do "sh" do SCB.

.ip "17.07.04  4.6.0" 20
Usando as fun��es de "initent" para acessar "/etc/initab".

