.bp 1
.he 'GETENV (libc)'TROPIX: Manual de Modifica��es'GETENV (libc)'
.fo 'Atualizado em 01.09.89'Vers�o 2.3.0'Pag. %'

.b NOME
.in 5
getenv - obt�m o valor de uma vari�vel do ambiente

.in
.sp 2
.ip "30.04.89  2.1.0" 20
VERS�O CORRENTE
.sp

.ip "01.09.89  2.3.0" 20
Na compara��o, n�o era considerado o "=", de tal modo que a busca
de uma vari�vel do tipo "CC" (por exemplo) iria devolver a primeira
vari�vel encontrada cujo prefixo fosse "CC" (tal como "CCC", "CCCCD", etc...). 
