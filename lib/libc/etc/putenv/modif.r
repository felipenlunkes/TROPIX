.bp 1
.he 'PUTENV (libc)'TROPIX: Manual de Modifica��es'PUTENV (libc)'
.fo 'Atualizado em 30.05.95'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
putenv - modifica ou acrescenta um valor ao ambiente

.in
.sp 2
.ip "30.04.89  2.1.0" 20
VERS�O CORRENTE
.sp

.ip "01.09.89  2.3.0" 20
Na compara��o, n�o era considerado o "=", de tal modo que a modifica��o
de uma vari�vel do tipo "CC" (por exemplo) iria modificar a primeira
vari�vel encontrada cujo prefixo fosse "CC" (tal como "CCC", "CCCCD", etc...). 

.ip "30.05.95  3.0.0" 20
A fun��o foi reescrita. Agora n�o h� mais limite no n�mero de vari�veis
no ambiente.
