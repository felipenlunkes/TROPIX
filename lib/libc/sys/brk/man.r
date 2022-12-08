.bp
.he 'BRK (sys)'TROPIX: Manual de Refer�ncia'BRK (sys)'
.fo 'Atualizado em 11.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Muda o tamanho do segmento de dados do processo:
.sp
.wo "brk  -"
dado o novo tamanho
.br
.wo "sbrk -"
dado um incremento/decremento
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	brk (const void *end_data);
void	*sbrk (int inc);

extern void	*_cbreak;
.)l

.in
.sp
.b DESCRI��O
.in 5
As chamadas ao sistema "brk" e "sbrk" s�o usadas para mudar din�micamente
a quantidade de mem�ria alocada ao segmento de dados do processo. 
Por defini��o, o valor de "break" � o primeiro endere�o
ap�s o final do segmento de dados.

.sp
A chamada "brk" altera a aloca��o de mem�ria de tal modo que o valor de "break"
seja igual a  "end_data".

.sp
A chamada "sbrk" adiciona "inc" bytes ao segmento de dados.
Como "inc" pode ser negativo, a quantidade de mem�ria alocada
pode ser reduzida.

.sp
A vari�vel "_cbreak" cont�m sempre o valor atual de "break".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema "brk" devolve zero,
e "sbrk" devolve o valor antigo de "break".
No caso contr�rio, elas devolvem -1 e indicam em "errno" a causa do erro.

.in
.sp
.b OBSERVA��ES
.in 5
Quando o segmento de dados aumenta, a nova regi�o alocada ao
processo � zerada.

.sp
Quando um processo � iniciado, o valor de "break" e "&end" tem o mesmo
valor, o que n�o ocorre depois da chamada de uma destas chamadas
ao sistema.

.sp
Recomenda-se utilizar a fun��o "malloc" (libc) para alocar
mem�ria. Repare no entanto, que programas usando "malloc"
ou a "stdio" n�o devem utilizar "brk" nem "sbrk".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
exec
.br
.wo "(libc):"
end
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
