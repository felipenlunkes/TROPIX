.bp
.he 'SETVBUF (libc)'TROPIX: Manual de Modifica��es'SETVBUF (libc)'
.fo 'Atualizado em 04.02.91'Vers�o 2.3.1'Pag. %'

.b NOME
.in 5
.wo "setvbuf -"
atribui um "buffer" de tamanho vari�vel a um arquivo
.br

.in
.sp 2
.ip "01.04.87  1.0" 20
VERS�O CORRENTE
.sp

.ip "31.05.88  1.1.0" 20
Foi consertado o erro que ocorria quando n�o se dava o endere�o
do "buffer".
Agora, a fun��o aloca uma �rea atrav�s de "malloc".

.ip "04.02.91  2.3.1" 20
Agora, se "buf" n�o for dado, aproveita "_sio?buf".

.sp
Corrigido tamb�m um �rro da atribui��o de "buf" inexistente. 
