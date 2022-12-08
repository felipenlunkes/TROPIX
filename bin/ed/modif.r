.bp
.he 'ED (cmd)'TROPIX: Manual de Modifica��es'ED (cmd)'
.fo 'Atualizado em 26.04.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
ed - editor de textos orientado por linhas
.br

.in
.sp 2
.ip "01.04.87  1.0.0" 20
VERS�O CORRENTE
.sp

.ip "10.08.87  1.0.1" 20
Devido a um erro no compilador (na fase de otimiza��o de c�digo),
a remo��o completa do arquivo (por exemplo atrav�s do comando "1,$d")
causava um "BUS ERROR".

.sp
O erro do compilador ocorre na inicializa��o de vari�veis longas (4 bytes)
com o valor zero, quando realizada ap�s a inicializa��o de uma vari�vel menor
(de 1 ou 2 bytes) tamb�m com valor nulo.
Esta situa��o ocorria no m�dulo "src/list.c" na fun��o "txt_remove";
o problema foi solucionado alterando-se o tipo da vari�vel "new_Root" de "char"
para "int".

.in
.sp 2
.ip "01.01.88  1.1.0" 20
VERS�O CORRENTE
.sp

.ip "26.04.97  3.0.0" 20
O programa sofreu (ou deliciou-se com) uma revis�o global.
