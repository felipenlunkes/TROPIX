.bp
.he 'GETOPT (libc)'TROPIX: Manual de Modifica��es'GETOPT (libc)'
.fo 'Atualizado em 13.7.88'Vers�o 2.1'Pag. %'

.b NOME
.in 5
.wo "getopt -"
Obt�m as informa��es dadas a um programa.
.br

.in
.sp 2
.ip "01.04.87  1.0" 20
VERS�O CORRENTE
.sp

.ip "13.07.88  1.0.1" 20
Agora quando ao fim da leitura das op��es,
"getopt" al�m de retornar EOF, se reinicializa
permitindo a leitura de op��es de um outro
vetor de argumentos.
