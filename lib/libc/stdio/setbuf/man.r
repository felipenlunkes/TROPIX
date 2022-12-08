.bp 1
.he 'SETBUF (libc)'TROPIX: Manual de Refer�ncia'SETBUF (libc)'
.fo 'Atualizado em 10.07.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Atribui uma �rea de entrada/sa�da ("buffer") a um arquivo:
.sp
.wo "setbuf  -"
de tamanho impl�cito
.br
.wo "setvbuf -"
de tamanho dado
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdio.h>

void     setbuf (FILE *fp, char *buf);
int      setvbuf (FILE *fp, char *buf, int mode, size_t size);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "setbuf" pode ser usada depois que o arquivo foi aberto
mas antes que ele seja lido ou escrito.
Se o argumento "buf" n�o for um ponteiro NULO, a �rea apontada
por ele ser� utilizada como �rea de entrada/sa�da, ao inv�s de uma
�rea alocada automaticamente.
Este vetor deve ter o tamanho "BUFSIZ" (definido em <stdio.h>).
Se  "buf" for um ponteiro NULO, a entrada/sa�da ser� realizada
sem nenhuma �rea de entrada/sa�da (isto �, de caractere em caractere).

.sp
A fun��o "setvbuf" pode ser usada depois que o arquivo foi aberto
mas antes que ele tenha seja lido ou escrito.
O parametro "mode" determina a natureza da �rea de entrada/sa�da
do arquivo. Os valores que "mode"
pode assumir (definidos em <stdio.h>) s�o os seguintes:

.in +3
.ip _IOFBF 8
o arquivo ter� uma �rea de entrada/sa�da normal, ou seja,
a �rea s� ser� descarregada quando ela estiver cheia.

.ip _IOLBF 8
o arquivo ter� uma �rea de entrada/sa�da de linha, ou seja,
a �rea ser� descarregada quando ela estiver cheia,
for escrito um caracter <nl>, e em um caso particular que � o seguinte:
<stdout> e <stderr> s�o descarregados quando for pedida uma
entrada em <stdin>.

.ip _IONBF 8
o arquivo n�o ter� �rea de entrada/sa�da.

.ep
.in -3

.sp
Se o argumento "buf" n�o for um ponteiro NULO, a �rea apontada
por ele ser� utilizada como �rea de entrada/sa�da, ao inv�s de uma
�rea alocada automaticamente.
O argumento "size"  especifica o tamanho da �rea de entrada/sa�da.
Uma boa sugest�o � usar a constante "BUFSIZ" (definida em <stdio.h>).
Caso o arquivo seja definido sem �rea de entrada/sa�da, os argumentos
"buf" e "size" s�o ignorados.

.sp
A n�o ser que outra coisa seja especificada,
todo arquivo de sa�da para um terminal ter� uma �rea de entrada/sa�da
de linha e todos os outros arquivos ter�o �reas normais.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Caso o parametro "mode" ou "size" tenha um valor ilegal, 
ou o pedido n�o possa ser satisfeito, a fun��o "setvbuf"
devolve um n�mero n�o-zero. Caso contr�rio devolve zero.

.in
.sp
.b OBSERVA��ES
.in 5
 Aten��o para n�o chamar estas fun��es com um "buf" alocado em uma
�rea autom�tica, que ir� ser liberada quando a fun��o
que a chamou retornar. 

.sp
A fun��o "setbuf" � mais antiga e limitada do que "setvbuf",
e s� � mantida por quest�es de compatibilidade. 

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc):"
fopen, getc, malloc, putc, stdio
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
