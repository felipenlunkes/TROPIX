.bp
.he 'LOGIN (cmd)'TROPIX: Manual de Modifica��es'LOGIN (cmd)'
.fo 'Atualizado em 22.01.98'Vers�o 3.0.5'Pag. %'

.b NOME
.in 5
login - entra em sess�o
.br

.in
.sp 2
.ip "01.12.87  1.1.0" 20
VERS�O CORRENTE
.sp

.ip "06.11.88  2.1.0" 20
Foi corrigido o problema do programa "login" permitir
a um usu�rio (erroneamente) entrar como supeusu�rio
quando a rotina "getpass" retornava com erro.

.ip "19.09.90  2.3.0" 20
Adicionado o segundo argumento (para "stty") na "initab".

.ip "21.10.91  2.3.1" 20
O segundo argumento da "initab" agora � processado diretamente com
"ioctl" ao inv�s de "fork" para "stty".

.ip "18.11.92  3.0.0" 20
Adaptado para funcionar tamb�m atrav�s de "rlogin" e "telnet".

.ip "29.04.93  3.0.1" 20
Incorporado o nome do n� da r�de.

.ip "16.02.97  3.0.2" 20
Retirado o "retype".

.ip "22.05.97  3.0.3" 20
Mais uma revis�o.

.ip "02.01.98  3.0.4" 20
Autualizada a mensagem de "correspond�ncia nova".

.ip "22.01.98  3.0.5" 20
Alterado os "ioctls" para usar o "lock". Incorporado o "modem".
