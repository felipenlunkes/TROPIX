.bp
.he 'PALLWD (cmd)'TROPIX: Manual de Refer�ncia'PALLWD (cmd)'
.fo �tualizado em 10.08.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "pallwd -"
imprime todos os diret�rios correntes
.br

.in
.sp
.b SINTAXE
.in 5
.(l
pallwd
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "pallwd" imprime informa��es sobre os diret�rios correntes
de todos os processos.
Este comando � reservado para o superusu�rio.

.sp
Os diversos processos s�o agrupados conforme o seu terminal/video
virtual/pseudo-terminal associado.
Para cada terminal, "pallwd" imprime uma (ou mais) linhas contendo
o usu�rio em sess�o no terminal, o nome do terminal, "<root>" se
o usu�rio tem privil�gios do superusu�rio, "<sys>" se o usu�rio pertence
ao grupo "sys", "<n>" se tem algum processo com a prioridade aumentada
(veja "nice" (sys)) e os diret�rios correntes dos diversos processos.

.sp
Finalmente, "pallwd" imprime mais dois grupos de linhas:
"<other tty>", relativo a processos associados a
terminais sem usu�rio em sess�o e
"<no tty>" relativo a processos sem terminais associados.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
ps
.br
.wo "(sys): "
nice
.br

.in
.sp
.b ARQUIVOS
.in 5
/etc/utmp

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
