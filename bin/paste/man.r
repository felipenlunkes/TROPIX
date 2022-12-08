.bp
.he 'PASTE (cmd)'TROPIX: Manual de Refer�ncia'PASTE (cmd)'
.fo 'Atualizado em 23.11.99'Vers�o 3.2.3'Pag. %'

.b NOME
.in 5
.wo "paste -"
concatena linhas de v�rios arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
paste [-d <delimitador>] <arquivo> ...
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "paste" concatena as linhas correspondentes de um ou mais <arquivo>s
de entrada, e escreve as linhas resultantes na sa�da padr�o.

.sp
Normalmente � usado o caratere <ht> como separador entre as colunas
resultantes (veja a op��o "-d", abaixo).

.sp
Se for dada a cadeia "-" como nome de um <arquivo>, ela representa a entrada
padr�o. Se isto ocorrer mais de uma vez, ser� lida uma linha da entrada padr�o,
circularmente, para cada ocorr�ncia de "-".

.sp
As op��es do comando s�o:

.in +3
.ip -d
Usa a cadeia <delimitador> como separador entre as v�rias colunas, ao
inv�s do caractere <ht>.

.ep
.in -3

.in
.sp
.b OBSERVA��O
.in 5
As linhas lidas e geradas est�o limitadas a 1024 bytes.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
cat
.br

.in
.sp
.b EXEMPLOS
.in 7
Imprimir 3 arquivos, em colunas separadas por " | ".
.sp
.nf
		paste -d " | " a b c
.fi

.sp
Listar um diret�rio em 5 colunas:
.sp
.nf
		ls | paste - - - - -
.fi

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
