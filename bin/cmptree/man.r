.bp
.he 'CMPTREE (cmd)'TROPIX: Manual de Refer�ncia'CMPTREE (cmd)'
.fo 'Atualizado em 28.10.03'Vers�o 4.5.0'Pag. %'

.b NOME
.in 5
.wo "cmptree -"
compara �rvores
.br

.in
.sp
.b SINTAXE
.in 5
.(l
cmptree [-ufglrqmL.] <PAD> <fonte> <destino>

Valores de <PAD>: [-s] [-p "<p>"] [-P "<P>"]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "cmptree" compara a �rvore <fonte> com a �rvore <destino>.
Isto � realizado caminhando a �rvore <fonte>,
e comparando todos os arquivos da �rvore <fonte>
com os arquivos correspondentes da �rvore <destino>.

.sp
Se for encontrada alguma diferen�a entre as �rvores, ela � indicada,
e de acordo com a op��o "-u" (veja abaixo), a �rvore <destino> pode
ser atualizada.

.sp
O comando verifica/atualiza as rela��es de elos f�sicos da �rvore <destino>
encontradas na �rvore <fonte>.

.sp
Se os arquivos a serem comparados forem especiais ou FIFO,
s�o comparados/copiados os n�s-�ndice ao inv�s dos conte�dos dos arquivos.
Para o caso dos elos simb�licos, s�o comparados/copiados os seus conte�dos sem modifica��es, o que
pode criar refer�ncias inexistentes.


.sp
As op��es do comando s�o:

.in +3
.ip -u
Atualiza a �rvore destino:
remove/reescreve todos os arquivos necess�rios da �rvore <destino>,
para que ela fique igual � �rvore <fonte>. 
Normalmente, � pedida a confirma��o do usu�rio para cada atualiza��o
a realizar na �rvore <destino> (veja a op��o "-f", abaixo).
.bc	/*************************************/
Se for dada uma letra mai�scula na confirma��o ("S", "Y" ou "N"),
t�das as perguntas seguintes ser�o respondidas automaticamente
(veja "askyesno" (libc)).
.ec	/*************************************/
Se a confirma��o da atualiza��o de um arquivo (exceto diret�rio)
for negada (e n�o foi dada a op��o "-f"),
o usu�rio � consultado se deseja
remover o arquivo da �rvore <fonte>.
Se a confirma��o da atualiza��o de um diret�rio for negada, ser� pulada toda
a sub-�rvore definida pelo diret�rio.

.ip -f
"For�a": Normalmente, as atualiza��es/c�pias s�o realizadas
interativamente: o usu�rio � consultado sobre
cada atualiza��o/c�pia a realizar.
Com a op��o "-f", o usu�rio permite com que todas as
atualiza��es/c�pias sejam realizadas sem consultas posteriores.

.sp
Um outro m�todo de evitar as consultas � a de responder com letras
ma�usculas: com a resposta "S" ou "Y" todas as perguntas seguintes
ser�o automaticamente respondidas afirmativamente, e (analogamente)
com a resposta "N" ser�o respondidadas negativamente
(veja "askyesno" (libc)).

.bc	/*************************************/
Permiss�o expl�cita:
com esta op��o (juntamente com a op��o "-u"), o usu�rio d� ao
comando "cmptree" a permiss�o de realizar todas as modifica��es
necess�rias na �rvore <destino> para que ela fique igual
� �rvore <fonte>. 
.ec	/*************************************/

.ip -g
"garfield":
cria o arquivo "garfield" (no diret�rio
corrente), contendo os nomes dos arquivos diferentes.
Os nomes s�o referentes � �rvore <fonte>.
Este arquivo pode ser usado como documenta��o (uma lista dos arquivos
diferentes), como entrada para "gar" (cmd) criar uma cole��o com
estes arquivos, ou ...

.ip -l
Ao encontrar um caractere diferente entre os arquivos,
lista as linhas correspondente de cada arquivo.
Isto s� � realizado se nenhum dos arquivos for um m�dulo objeto.

.ip -r
Modo rigoroso:
normalmente, o dono, grupo, modo/prote��o e datas dos arquivos
n�o s�o comparados.
Com esta op��o, estes itens s�o comparados/atualizados
(esta op��o implica tamb�m a op��o "-m").
Isto s� � inteiramente poss�vel se o usu�rio do comando for superusu�rio. 

.ip -q
Compara��o r�pida para m�dulos objeto:
se os dois arquivos forem m�dulos objetos, os seus tamanhos totais
e as datas contidas nos seus cabe�alhos forem iguais, os arquivos
s�o considerados iguais.
Esta compara��o � muito mais r�pida, e a probabilidade de indicar
uma igualdade falsa � extremamente baixa.

.ip -m
Em caso de atualiza��o, normalmente o dono e o grupo dos arquivos
da �rvore <destino> s�o conservados caso �stes j� existam,
e s�o usados os do usu�rio do comando em caso contr�rio. 
Com a op��o "-m", s�o copiados o dono, grupo, modo/prote��o e datas dos arquivos
(exceto os elos simb�licos)
da �rvore <fonte> para o arquivos correspondentes da �rvore <destino>.
Isto s� � inteiramente poss�vel se o usu�rio do comando for superusu�rio. 

.ip -L
Compara apenas os arquivos do diret�rio <fonte> raiz;
n�o entra nos subdiret�rios.

.ip -d
Compara apenas os arquivos contidos no dispositivo da �rvore <fonte>;
n�o entra nos subdiret�rios contidos em outros dispositivos montados.
.bc	/*************************************/
n�o entra nos subdiret�rios montados em outros dispositivos.
.ec	/*************************************/

.ip "-."
compara tamb�m os arquivos ocultos:
arquivos "ocultos" s�o aqueles cujos nomes cont�m algum componente que
come�a com um ponto (exceto ".."), como por exemplo "/usr/src/sys/.old/rot.c".
Normalmente, arquivos ocultos s�o ignorados - esta op��o faz com que
estes arquivos sejam tamb�m considerados na compara��o/atualiza��o.
Esta op��o � impl�cita se o nome da �rvore <fonte> ou <destino>
tiver um componente come�ando com um ponto.

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

.ep
.in -3

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
O comando "cmptree" retorna 0 quando as duas �rvores s�o iguais ou ficaram
iguais ap�s a atualiza��o (op��o "-u"). Em caso contr�rio, retorna o
n�mero de arquivos diferentes. Repare que neste c�lculo s� s�o levados
em conta os arquivos selecionados pelos padr�es dados. 

.in
.sp
.b OBSERVA��ES
.in 5
O �nico caso em que "cmptree" n�o consegue atualizar inteiramente a �rvore
<destino>, � quando no ponto correspondente a um arquivo normal
da �rvore <fonte> est� um diret�rio (possivelmente uma sub�rvore)
da �rvore <destino>.
Isto exigiria a remo��o de toda esta sub�rvore, tarefa que "cmptree"
ainda n�o efetua.

.sp
Ao atualizar uma �rvore utilizando a op��o "-r", � poss�vel que
sejam necess�rios v�rios passos, pois a cria��o de um arquivo
implica na escrita em um diret�rio, alterando o seu tempo de
modifica��o.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sh, cmp, cmpobj, cptree, gar
.br
.wo "(libc):"
askyesno
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
