.bp
.he 'GETTZMIN (sys)'TROPIX: Manual de Refer�ncia'GETTZMIN (sys)'
.fo 'Atualizado em 27.01.99'Vers�o 3.1.6'Pag. %'

.b NOME
.in 5
.wo "gettzmin -"
Obt�m o fuso hor�rio
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	gettzmin (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "gettzmin" retorna o valor do fuso hor�rio em minutos.
Este valor indica o tempo que deve ser acrescido ao Tempo Universal (UT, antes
chamado de GMT) para obter-se o tempo local.

.sp
No Rio de Janeiro, este valor
� de -180 exceto durante o hor�rio de ver�o, quando passa para -120.

.in
.sp
.b OBSERVA��O
.in 5
Repare que o valor de retorno � dado em minutos, e que em geral ser�
necess�rio multiplicar por 60 antes de somar/subtrair com os
diversos tempos do sistema (que s�o dados em segundos).

.in
.sp
.b ESTADO
.in 5
Efetivo.
