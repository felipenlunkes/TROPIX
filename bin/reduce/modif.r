.bp
.he 'REDUCE (cmd)'TROPIX: Manual de Modifica��es'REDUCE (cmd)'
.fo 'Atualizado em 14.01.91'Vers�o 2.3.4'Pag. %'

.b NOME
.in 5
Comprime/expande um arquivo segundo o algoritmo LZW:
.sp
.wo "reduce -"
comprime ou expande, de acordo com as op��es
.br
.wo "rcat   -"
apenas expande
.br

.in
.sp 2
.ip "15.08.90  2.3.0" 20
VERS�O CORRENTE
.sp

.ip "28.09.90  2.3.1" 20
Foi resolvido o problema da emiss�o de "max_code" justamente quando
o tamanho do c�digo mudava.

.ip "21.11.90  2.3.2" 20
Novamente, foi resolvido o problema da emiss�o de "max_code"
justamente quando o tamanho do c�digo mudava, o que n�o foi o caso
na vers�o 2.3.1.

.ip "12.12.90  2.3.3" 20
Novamente, mais uma v�z foi resolvido o problema da emiss�o de "max_code"
justamente quando o tamanho do c�digo mudava, o que tamb�m n�o foi o caso
na vers�o 2.3.2.
Alterados todos os m�dulos.

.sp
A �rea de c�digos foi passada de "short" para "int".
Lembrei de alterar a compacta��o/descompacta��o de 16 bites em "fillcode" e
"flushcode".

.ip "14.01.91  2.3.4" 20
Foi acrescentada o teste "bit_sz < MAX_BIT_SZ" para certificar-se de que o
limite n�o � passado.
