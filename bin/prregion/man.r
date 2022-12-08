.bp
.he 'PRREGION (cmd)'TROPIX: Manual de Refer�ncia'PRREGION (cmd)'
.fo �tualizado em 10.08.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "prregion -"
imprime as regi�es dos processos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
prregion [<pid> ...]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "prregion" imprime informa��es sobre as regi�es dos
diversos processos. Se forem dados <pid>s de processos, somente
ser�o dadas informa��es sobre estes processos; em caso contr�rio
ser�o dadas informa��es sobre todos processos.

.sp
S�o listadas informa��es das regi�es dos textos (programas residentes na mem�ria),
bibliotecas compartilhadas e dos diversos processos. Ao final � dada uma
lista de regi�es que n�o foram atribu�das a nenhum processo
(isto n�o implica necessariamente em erro, pois a leitura das diversas
tabelas do n�cleo do TROPIX se d� em paralelo com a execu��o do comando
"prregion").

.sp
As informa��es dadas sobre cada regi�o s�o as seguintes:

.in +3
.ip Tipo: 10
Tipo da regi�o: (TEXT, DATA ou STACK).

.ip regiong: 10
Endere�o da tabela da regi�o global.

.ip vaddr: 10
Endere�o virtual da regi�o.

.ip prot: 10
Prote��o da regi�o (RW para leitura/escrita e RO para apenas leitura).

.ip size: 10
Tamanho da regi�o em KB.

.ip caddr: 10
Endere�o da regi�o.

.ip count: 10
N�mero de refer�ncias � regi�o.

.ip nome: 10
Nome do processo que criou a regi�o (e N�O o que possui a regi�o).

.ip Tabela 10
Tabela de p�ginas (endere�o da tabela de p�ginas, n�mero de p�ginas e de entradas usadas).

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
ps, prsync
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
