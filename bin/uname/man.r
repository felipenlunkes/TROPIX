.bp
.he 'UNAME (cmd)'TROPIX: Manual de Refer�ncia'UNAME (cmd)'
.fo 'Atualizado em 13.07.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
.wo "uname -"
imprime a identifica��o do sistema
.br

.in
.sp
.b SINTAXE
.in 5
.(l
uname [-v]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "uname" imprime a identifica��o do computador,
do sistema operacional em uso, e do cliente.

.sp
Na primeira linha, s�o impressos o nome do sistema operacional, seu tipo,
sua vers�o/modifica��o com data e hora de gera��o, o tipo do
computador e o nome simb�lico do n� nas redes nas quais est� conectado.

.sp
Na segunda linha, s�o impressos o n�mero de s�rie do sistema,
o nome do cliente, e o nome do departamento. 

.sp
As op��es do comando s�o:

.in +3
.ip -v
S�o impressas as mesmas informa��es mencionadas acima,
mas com o formato dos membros da estrutura "uts"
(ver o arquivo "/usr/include/sys/utsname.h")

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
uname
.br

.in
.sp
.b ARQUIVOS
.in 5
/usr/include/sys/utsname.h

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
