.bp
.he 'WC (cmd)'TROPIX: Manual de Refer�ncia'WC (cmd)'
.fo 'Atualizado em 30.12.04'Vers�o 4.7.0'Pag. %'

.b NOME
.in 5
.wo "wc -"
contador de p�ginas, linhas, palavras e caracteres
.br

.in
.sp
.b SINTAXE
.in 5
.(l
wc [-N] [-l <l>] [<arquivo> ...]
.)l
.bc	/*************************************/
.(l
wc [-plwcN] [-P <l>] [<arquivo> ...]
.)l
.ec	/*************************************/

.in
.sp
.b DESCRI��O
.in 5
O comando "wc" conta o n�mero de p�ginas, linhas, palavras
e caracteres dos <arquivo>s dados, imprimindo uma linha para
cada <arquivo>.
.bc	/*************************************/
O n�mero de p�ginas � o necess�rio pelo comando
"pr" (cmd) para imprimir o arquivo. 
.ec	/*************************************/

.sp
Uma palavra � uma seq��ncia de caracteres delimitada pelos
caracteres <sp>, <ht>, <nl> ou <np>.

.sp
Se for dado mais de um <arquivo>, ser� impressa tamb�m uma linha com
os totais acumulados.
Se n�o for dado nenhum nome de <arquivo> nem a op��o "-N" (veja abaixo),
ser� lida a entrada padr�o.

.sp
Normalmente, cada p�gina cont�m 75 linhas (veja a op��o "-l").

.sp
As op��es do comando s�o:

.in +3
.bc	/*************************************/
.ip -p 8
Imprime o n�mero de p�ginas.

.ip -l 8
Imprime o n�mero de linhas.

.ip -w 8
Imprime o n�mero de palavras.

.ip -c 8
Imprime o n�mero de caracteres.
.ec	/*************************************/

.ip -N 8
L� os nomes dos <arquivo>s de "stdin".

.ip '-l <l>' 8
A p�gina cont�m <l> linhas (ao inv�s de 75).
Para obter o n�mero de p�ginas
que um arquivo necessitar� ao ser impresso por "pr" (cmd), use
"-l 56".

.ep
.in -3

.bc	/*************************************/
.sp
As op��es "-p", "-l", "-w" e "-c" podem ser dadas em qualquer combina��o.
Se n�o for dada nenhuma delas, s�o impressos os 4 n�meros.
.ec	/*************************************/

.in
.sp
.b OBSERVA��ES
.in 5
Embora o comando "wc" tamb�m possa ser usado para m�dulos-objeto,
o seus n�meros de p�ginas, linhas e palavras n�o t�m qualquer sentido.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
pr
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
