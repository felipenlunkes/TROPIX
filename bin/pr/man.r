.bp
.he 'PR (cmd)'TROPIX: Manual de Refer�ncia'PR (cmd)'
.fo 'Atualizado em 30.12.04'Vers�o 4.7.0'Pag. %'


.b NOME
.in 5
.wo "pr -"
imprime arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
pr [-o <o>] [-p <p>] [-e <e>] [-h "<h>"] [-l <l>]
					       [-N] [<arquivo> ...]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "pr" edita um ou mais arquivos para um formato pr�prio de
impress�o, pondo o resultado na sa�da padr�o.

.sp
A sa�da de "pr" � separada em p�ginas incluindo um cabe�alho que cont�m
a data/hora, nome do arquivo (ou um t�tulo dado pelo usu�rio,
veja a op��o "-h") e o n�mero da p�gina.

.sp
Se n�o for dado o nome de nenhum <arquivo>, nem a op��o "-N", ser� editado
o arquivo lido da entrada padr�o.
Podemos tamb�m especificar a entrada padr�o atrav�s de "-".


.sp
As op��es do comando s�o:

.in +3
.ip -o
Imprime <o> brancos antes do in�cio de cada linha.
Isto � �til quando n�o podemos mover lateralmente o papel da impressora.
Lembre-se no entanto, de que se <o> n�o for m�ltiplo de 8, as tabula��es
podem se modificar.

.ip -p
Come�a a imprimir cada <arquivo> a partir da p�gina <p>
(ao inv�s do seu in�cio).

.ip -e
Imprime somente at� a p�gina <e>. Utilizando as op��es "-p" e "-e"
podemos especificar quais s�o as p�ginas de cada <arquivo> que desejamos
imprimir. Repare que estas op��es se aplicam a todos os <arquivo>s.

.ip -h
Utiliza a cadeia de caracteres <h> como cabe�alho das p�ginas
(ao inv�s dos nomes dos respectivos <arquivo>s).

.ip -l
Usa a p�gina com <l> linhas (ao inv�s de 75).
Repare que 10 linhas s�o sempre reservadas para o cabe�alho, espa�os, etc...,
de tal modo que normalmente s�o impressas apenas 56 linhas do arquivo por
p�gina.

.ip -N
Os nomes dos <arquivo>s s�o lidos da entrada padr�o.

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
cat
.bc	/*************************************/
cat, lpr
.ec	/*************************************/
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
