.bp
.he 'LSEEK (sys)'TROPIX: Manual de Refer�ncia'LSEEK (sys)'
.fo 'Atualizado em 02.11.02'Vers�o 4.4.0'Pag. %'

.b NOME
.in 5
Move o ponteiro de posi��o de um arquivo:
.sp
.wo "lseek  -"
dado um deslocamento de 32 bits
.br
.wo "llseek -"
dado um deslocamento de 64 bits
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>
#include <unistd.h>

off_t lseek (int fd, off_t offset, int whence);

int llseek (int fd, loff_t offset, loff_t *result, int whence);
.)l

.in
.sp
.b DESCRI��O
.in 5
As chamada ao sistema "lseek" e "llseek" alteram o valor do ponteiro de posi��o
de leitura/escrita de um arquivo aberto. O argumento "fd" � um
descritor obtido atrav�s de uma chamada "creat", "open", "dup" ou
"fcntl".

.sp
Dependendo do valor de "whence", as chamadas alteram
o ponteiro de posi��o para:

.in +3
.ip L_SET: 9
o valor de "offset" dado.

.ip L_CUR: 9
o valor antigo do ponteiro acrescido de "offset".

.ip L_END: 9
o tamanho do arquivo acrescido de "offset".

.ep
.in -3

.sp
O valor do ponteiro de posi��o resultante do arquivo � retornado de modo diferente
em cada uma das chamadas ao sistema:
para o caso de "lseek", � o pr�prio retorno da fun��o;
para o caso de "llseek", ele � armazenado na vari�vel apontada pelo
ponteiro "result" (se ele for n�o NULO).

.sp
Repare que o valor de "offset" pode ser negativo (o que faz sentido apenas
para "whence" com os valores "L_CUR" ou L_END").

.sp
Alguns dispositivos s�o incapazes de alterar o seu ponteiro de posi��o.
Nestes casos, o valor do ponteiro associado � indefinido.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema "lseek" devolve o valor do ponteiro
de posi��o resultante, e "llseek" devolve um valor NULO.
Em caso contr�rio, as fun��es devolvem -1 e indicam em "errno" a causa do erro.

.in
.sp
.b OBSERVA��ES
.in 5
Movendo-se o ponteiro de posi��o para al�m do
final de um arquivo regular,
e em seguida escrevendo-se nele, cria-se um "buraco"
que n�o ocupa blocos f�sicos no disco, e � lido como ZEROs. 

.sp
Somente a chamada ao sistema "write" pode aumentar o tamanho
de um arquivo: "lseek" por si s�, n�o aumenta
o tamanho de um arquivo.

.sp
O padr�o POSIX definiu as constantes "SEEK_SET", "SEEK_CUR" e "SEEK_END"
como sin�nimos de "L_SET", L_CUR" e L_END", respectivamente.


.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
creat, dup, fcntl, open
.br

.in
.sp
.(t
.b ESTADO
.in 5
Efetivo.
.)t
