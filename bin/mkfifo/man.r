.bp
.he 'MKFIFO (cmd)'TROPIX: Manual de Refer�ncia'MKFIFO (cmd)'
.fo 'Atualizado em 23.05.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
.wo "mkfifo -"
cria FIFOs
.br

.in
.sp
.b SINTAXE
.in 5
.(l
mkfifo <fifo> ...
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando  "mkfifo" cria os arquivos <fifo> ... do tipo "FIFO"
("First In, First Out").
Estes arquivos s�o de uso semelhante aos PIPEs, mas no entanto possuem nomes,
o que possibilita o seu uso por processos que n�o t�m ancendentes em comum. 

.in
.sp
.b OBSERVA��O
.in 5
O comando "mkfifo" cria os arquivos com permiss�o para escrita e leitura
apenas pelo usu�rio que os criou.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
mknod, rm
.br
.wo "(sys): "
mknod, pipe
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
