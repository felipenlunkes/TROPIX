.bp
.he 'GETPASS (libc)'TROPIX: Manual de Modifica��es'GETPASS (libc)'
.fo 'Atualizado em 22.01.98'Vers�o 3.0.3'Pag. %'

.b NOME
.in 5
getpass - l� uma senha do terminal
.br

.in
.sp 2
.ip "01.04.87  1.0" 20
VERS�O CORRENTE
.sp

.ip "19.03.88  2.0.0" 20
Nesta nova vers�o, em caso de erro,
podemos reler a senha toda, com o caractere "kill".

.ip "16.09.90  2.3.0" 20
Agora, desligando "ISIG".

.ip "16.11.92  3.0.0" 20
Ignorando <^S>, <^Q> e imprimindo o texto de uma s� vez.

.ip "07.07.95  3.0.1" 20
Adaptado para o PC.

.ip "03.06.97  3.0.2" 20
Aumentado o tamanho da senha.

.ip "19.01.98  3.0.3" 20
Agora, "tranca" e re-l� o "termio" antes de atribuir.
