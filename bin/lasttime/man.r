.bp
.he 'LASTTIME (cmd)'TROPIX: Manual de Refer�ncia'LASTTIME (cmd)'
.fo 'Atualizado em 04.08.97'Vers�o 3.0.4'Pag. %'

.b NOME
.in 5
.wo "lasttime -"
lista os nomes de arquivos modificados recentemente
.br

.in
.sp
.b SINTAXE
.in 5
.(l
lasttime [-g.] [-r <n>] <PAD> <�rvore> ...

Valores de <PAD>: [-s] [-p "<p>"] [-P "<P>"]
.)l

.bc	/*************************************/
.(l
lasttime [-g.s] [-r <n>] [-n <max>] [-p <padr�es>] <�rvore> ...
.)l
.ec	/*************************************/

.in
.sp
.b DESCRI��O
.in 5
O comando "lasttime" caminha as diversas <�rvore>s, listando
os nomes dos arquivos modificados hoje (isto �, desde a �ltima meia-noite,
veja a op��o "-r"), 
juntamente com a data da sua �ltima modifica��o.

.sp
As op��es do comando s�o:

.in +3
.ip -g
"garfield": cria o arquivo "garfield" (no diret�rio corrente),
contendo os nomes dos arquivos modificados.
Este arquivo pode ser usado como documenta��o (uma lista dos arquivos
modificados), como entrada para "gar" (cmd) criar uma cole��o com
estes arquivos, ou ...

.ip "-."
compara tamb�m os arquivos ocultos:
arquivos "ocultos" s�o aqueles cujos nomes cont�m algum componente que
come�a com um ponto (exceto ".."), como por exemplo "/usr/src/sys/.old/rot.c".
Normalmente, arquivos ocultos s�o ignorados - esta op��o faz com que
estes arquivos sejam tamb�m considerados.

.ip -r
Imprime os arquivos modificados nos �ltimos <n> dias ao inv�s
de um dia (hoje).

.ip "-s"
Esta op��o � a abreviatura de
.sp
.nf
			-p "*[Mm]akefile *.[cshryv]"
.fi
.sp
e � �til para selecionar arquivos relacionados com a linguagem "C".
Padr�es adicionais podem ser dados com a op��o "-p" (veja abaixo).

.ip "-p"
Padr�es de inclus�o:
Seleciona apenas arquivos cujos nomes s�o aceitos por um dos <padr�es> dados.
Cada padr�o � uma express�o regular, como as do "sh" (cmd),
formada com "*", "?", "!", "[...]" (ver patmatch (libc)).
Os padr�es s�o aplicados ao nome completo do arquivo,
sem considerar o caractere "/" como especial.
Um caractere branco ou <ht> indica o final de um padr�o, de tal modo que
uma �nica op��o pode conter v�rios padr�es
(desde que venham entre aspas ou ap�strofes).
Ao total podemos ter at� 20 <padr�es>.

.ip -P
Padr�es de exclus�o:
Esta op��o � an�loga � op��o "-p", exceto que os padr�es s�o usados
para a exclus�o de arquivos (ao inv�s de inclus�o).
Todos os arquivos cujos nomes s�o
aceitos por estes padr�es n�o s�o selecionados, mesmo que tenham sido
aceitos pelos padr�es das op��es "-p" ou "-s".

.bc	/*************************************/
.ip -n
Normalmente, "lasttime" lista um m�ximo de 100 arquivos.
Com esta op��o, lista at� <max> arquivos.
.ec	/*************************************/

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
gar
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
