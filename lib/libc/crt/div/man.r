.bp
.he 'DIV (libc)'TROPIX: Manual de Refer�ncia'DIV (libc)'
.fo 'Atualizado em 27.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Calcula o quociente e o resto:
.sp
.wo "div  -"
da divis�o de inteiros
.br
.wo "ldiv -"
da divis�o de longos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

div_t  div  (int numer,  int denom);
ldiv_t ldiv (long numer, long denom);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "div" calcula o quociente e o resto da divis�o do numerador
"numer" pelo denominador "denom".
Se a divis�o � inexata, o sinal do quociente resultante � o do quociente
alg�brico, e o m�dulo do quociente resultante � o maior inteiro menor
do que o m�dulo do quociente alg�brico.
Se o resultado n�o puder ser representado, o resultado � indefinido;
em caso contr�rio, "quot * denom + rem == numer". 

.sp
A fun��o "ldiv" � an�loga � "div", exceto que os argumentos e os valores de
retorno t�m o tipo "long int".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
As fun��es devolvem estruturas do tipo "div_t" e "ldiv_t" (respectivamente),
contendo o quociente e o resto nos membros "quot" e "rem".

.in
.sp
.b OBSERVA��ES
.in 5
Como normalmente as instru��es das CPUs para a divis�o fornecem
tamb�m o resto, a utiliza��o da fun��o "div" (ou "ldiv") � em geral mais
r�pida do que o c�lculo separado do quociente e do resto.

.sp
Como no TROPIX os inteiros s�o sempre longos (32 bites), as duas estruturas
e as duas fun��es s�o equivalentes entre si.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
