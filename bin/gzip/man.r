.bp
.he 'GZIP (cmd)'TROPIX: Manual de Refer�ncia'GZIP (cmd)'
.fo 'Escrito em 22.03.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
Comprime ou expande arquivos usando o algoritmo de Lempel-Ziv:
.sp
.wo "gzip   -"
comprime
.br
.wo "gunzip -"
expande
.br

.in
.sp
.b SINTAXE
.in 5
.(l
gzip [-cdfrRt1..9vN] [<arquivo> ...]
gunzip [-cfrRtvN] [<arquivo> ...]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "gzip" tenta reduzir o tamanho dos <arquivo>s dados
usando o m�todo de Lempel-Ziv (LZ77, veja abaixo).
Quando poss�vel, cada "<arquivo>" � substitu�do por "<arquivo>.gz"
comprimido, conservando o dono e os tempos de acesso/modifica��o.
O nome original do <arquivo> � armazenado no <arquivo> comprimido.
Se n�o for dado nenhum <arquivo> nem a op��o "-N" (veja abaixo),
a entrada padr�o � comprimida e posta na sa�da padr�o.
O comando "gzip" comprime apenas arquivos regulares.

.sp
O comando "gunzip" restaura os <arquivo>s de volta � sua forma original.

.sp
As op��es do comando s�o:

.in +3
.ip -c
Escreve na sa�da padr�o. N�o modifica os <arquivo>s originais.
Se forem dados v�rios <arquivo>s de entrada, a sa�da consiste de uma
seq��ncia de membros comprimidos independentemente. Para obter
uma taxa de compress�o melhor, concatene todos os <arquivo>s de
entrada antes da compress�o. 

.ip -d
Descomprime. Esta op��o � desnecess�ria se o nome do comando
usado for "gunzip".

.ip -f
Executa a compress�o/descompress�o mesmo que o <arquivo> tenha v�rios
nomes (links), ou o <arquivo> correspondente j� existe. Se esta op��o
n�o for dada e o comando n�o est� sendo executado em "background",
"gzip" consulta o usu�rio para decidir se um <arquivo> existente
deve ser reescrito.

.ip -r
Recursivo.
Para cada <arquivo> dado que for um diret�rio, comprime/descomprime
todos os arquivos da �rvore cuja raiz � o diret�rio.

.ip -R
Como "-r".

.ip -t
Teste. Verifica a integridade do <arquivo> comprimido.

.ip -#
N�vel de compress�o. Com as op��es "-1", "-2", ..., "-9" podemos
regular a efici�ncia do algoritmo de compress�o.
Com a op��o "-1" temos uma compress�o mais r�pida (por�m com taxa
de compress�o m�nima) e com "-9" temos uma compress�o mais lenta
(por�m com taxa de compress�o m�xima).
Se nenhuma destas op��es for dada, � usado o n�vel "-5".

.sp
O nivel de compress�o tamb�m pode ser dado no ambiente atrav�s da
vari�vel "GZIP". Para usar o nivel 8 (por exemplo) ela deve ter o
valor "8" ou "-8". Se for dado um n�vel de compress�o atrav�s da
vari�vel "GZIP" e outro em uma op��o do comando, prevalecer� o da
op��o do comando.

.ip -v
Verboso.

.ip -N
Le os nomes dos <arquivo>s da entrada padr�o.

.ep
.in -3

.in
.sp
.b OBSERVA��O
.in 5
Este � um programa originalmente desenvolvido pelo projeto GNU.
Copyright (C) 1989, 1991 Free Software Foundation, Inc.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
gar
.br
.wo "(fmt): "
ambiente
.br

.in
.sp
.b
REFER�NCIAS
.r
.in 5
[LZ77]: Ziv J., Lempel A., "A Universal Algorithm for Sequential Data
Compression", IEEE Transactions on Information Theory", Vol. 23, No. 3,
pp. 337-343.

.in
.sp
.b ESTADO
.in 5
Programa contribu�do.

.in
