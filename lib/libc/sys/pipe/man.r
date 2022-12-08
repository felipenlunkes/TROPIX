.bp 1
.he 'PIPE (sys)'TROPIX: Manual de Refer�ncia'PIPE (sys)'
.fo 'Atualizado em 18.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "pipe -"
cria um canal entre processos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	pipe (int fd[]);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "pipe" cria um mecanismo de entrada/sa�da
entre dois processos chamado de canal ("pipe").
Ela recebe como argumento o ponteiro "fd" para um vetor de dois inteiros,
que s�o preenchidos por dois descritores de arquivos, "fd[0]" e "fd[1]".
O descritor "fd[0]" est� aberto para leituras e "fd[1]" para
escritas.

.sp
A �rea interna do canal comporta at� 5120 bytes de dados,
valor ap�s o qual o processo que est� escrevendo � bloqueado. 

.sp
O descritor de leituras "fd[0]" acessa os dados escritos em "fd[1]"
em um modo de fila ("FIFO").

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve zero.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b OBSERVA��O
.in 5
� poss�vel aguardar a disponibilidade de dados na leitura de um
"pipe" atrav�s da chamada ao sistema "attention" (sys).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sh
.br
.wo "(sys): "
read, write, attention
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
