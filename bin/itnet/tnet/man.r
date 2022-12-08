.bp
.he 'TNET (cmd)'TROPIX: Manual de Refer�ncia'TNET (cmd)'
.fo 'Atualizado em 05.05.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
Compara��o/atualiza��o/c�pia de/para �rvores remotas:
.sp
.wo "tcmpto   -"
compara��o/atualiza��o caminhando �rvores locais
.br
.wo "tcmpfrom -"
compara��o/atualiza��o caminhando �rvores remotas
.br
.wo "tcpto    -"
c�pia caminhando �rvores locais
.br
.wo "tcpfrom  -"
c�pia caminhando �rvores remotas
.br
.wo "tpipe    -"
escreve arquivos remotos na sa�da padr�o
.br

.in
.sp
.b SINTAXE
.in 5
.(l
tcmpto   [-tfdgLFvm.N] <ENV> <PAD> [<�rvore> ...]
tcmpfrom [-tfdgLFvm.N] <ENV> <PAD> [<�rvore> ...]
tcpto    [-LFvm.N] <ENV> <PAD> [<�rvore> ...]
tcpfrom  [-LFvm.N] <ENV> <PAD> [<�rvore> ...]
tpipe    [-N] <ENV> [<�rvore> ...]

Valores de <ENV>: [-C] [-n <n�>] [-u <usu�rio>] [-D <rdir>]

Valores de <PAD>: [-s] [-p "<p>"] [-P "<P>"]
.)l

.in
.sp
.b DESCRI��O
.in 5
A fam�lia TNET de comandos destina-se � compara��o/atualiza��o ou
c�pia entre/de �rvores locais e �rvores correspondentes de um <n�>
remoto de uma rede. A fam�lia comp�e-se
dos utilit�rios "tcmpto", "tcmpfrom", "tcpto", "tcpfrom" e "tpipe".

.sp
O utilit�rio "tcmpto" caminha as <�rvore>s locais dadas, e compara
cada arquivo local com o arquivo correspondente do <n�> remoto.
Opcionalmente pode atualizar os arquivos da �rvore desejada
(local ou remota).

.sp
O utilit�rio "tcmpfrom" caminha as <�rvore>s remotas dadas, e compara
cada arquivo do <n�> remoto com o arquivo local correspondente.
Opcionalmente pode atualizar os arquivos da �rvore desejada
(local ou remota).

.sp
Repare que a diferen�a entre os utilit�rios "tcmpto" e "tcmpfrom" �
apenas o local das <�rvore>s que s�o caminhadas; quais das <�rvore>s
ser�o (opcionalmente) atualizadas � decidido por uma das op��es
"-t", "-f" ou "-d" (elas s�o mutuamente exclusivas, veja abaixo);
sem alguma destas op��es N�O s�o realizadas atualiza��es.

.sp
O utilit�rio "tcpto" caminha as <�rvore>s locais dadas, copiando
cada arquivo local para o <n�> remoto (deste modo reproduzindo as
<�rvore>s no <n�> remoto).

.sp
O utilit�rio "tcpfrom" caminha as <�rvore>s do <n�> remoto dadas,
copiando cada arquivo destas <�rvore>s remotas para o local correspondente
das <�rvore>s locais (deste modo reproduzindo as
<�rvore>s no <n�> local).

.sp
O utilit�rio "tpipe" caminha as <�rvore>s remotas dadas, escrevendo
todos os arquivos do <n�> remoto na sa�da padr�o.

.sp
.(t
As op��es do comando s�o:

.in +3
.ip -t
"To": Atualiza as �rvores do <n�> remoto:
remove/reescreve todos os arquivos necess�rios das �rvores do <n�> remoto,
para que elas fiquem iguais �s �rvores locais. 
Normalmente, � pedida a confirma��o do usu�rio para cada atualiza��o
a realizar (veja a op��o "-F", abaixo).
.)t

.ip -f
"From": Atualiza as �rvores locais:
remove/reescreve todos os arquivos necess�rios das �rvores locais,
para que elas fiquem iguais �s �rvores do <n�> remoto. 
Normalmente, � pedida a confirma��o do usu�rio para cada atualiza��o
a realizar (veja a op��o "-F", abaixo).

.ip -d
Data: Atualiza os arquivos diferentes das �rvores locais ou do
no <n�> remoto, dependendo das datas de modifica��o dos arquivos
(atualizando os arquivos mais antigos).
Normalmente, � pedida a confirma��o do usu�rio para cada atualiza��o
a realizar (veja a op��o "-F", abaixo).

.ip -g
"Garfield": Cria o arquivo "garfield" (no diret�rio corrente),
contendo os nomes dos arquivos diferentes.
Os nomes s�o referentes �s �rvores locais.
Este arquivo pode ser usado como documenta��o (uma lista dos arquivos
diferentes), como entrada para "tcpto/tcpfrom" atualizar a �rvore
posteriormente, como entrada para "gar" (cmd) criar uma cole��o com
estes arquivos, ou ainda ...

.ip -L
Compara apenas os arquivos do diret�rio raiz;
n�o entra nos subdiret�rios.

.ip -F
"For�a": Normalmente, as atualiza��es/c�pias s�o realizadas
interativamente: o usu�rio � consultado sobre
cada opera��o de atualiza��o/c�pia a realizar.
Com a op��o "-F", o usu�rio permite com que todas as
atualiza��es/c�pias sejam realizadas sem consultas posteriores.

.sp
Um outro m�todo de evitar as consultas � a de responder com letras
ma�usculas: com a resposta "S" ou "Y" todas as perguntas seguintes
ser�o automaticamente respondidas afirmativamente, e (analogamente)
com a resposta "N" ser�o respondidadas negativamente
(veja "askyesno" (libc)).

.bc	/*************************************/
.ip -i
"interativo": Normalmente, as atualiza��es s�o realizadas sem
consultar o usu�rio; com a op��o "-i", o usu�rio � consultado sobre
cada opera��o de atualiza��o a realizar.
Se a atualiza��o de um diret�rio for negada, ser� pulada toda
a sub-�rvore definida pelo diret�rio.
.ec	/*************************************/

.ip -v
Verboso: Imprime estat�sticas sobre as transfer�ncias dos arquivos
al�m de outras informa��es.

.ip -m
Em caso de atualiza��es, normalmente o dono e o grupo dos arquivos
da �rvore <destino> s�o conservados caso �stes j� existam,
e s�o usados os do usu�rio do comando em caso contr�rio. 
Com a op��o "-m", s�o copiados o dono, grupo, modo/prote��o e datas dos arquivos
da �rvore <fonte> para o arquivos correspondentes da �rvore <destino>.
Isto s� � inteiramente poss�vel se o usu�rio do comando for superusu�rio. 

.ip "-."
Compara tamb�m os arquivos ocultos:
arquivos "ocultos" s�o aqueles cujos nomes cont�m algum componente que
come�a com um ponto (exceto ".."), como por exemplo "/usr/src/sys/.old/rot.c".
Normalmente, arquivos ocultos s�o ignorados - esta op��o faz com que
estes arquivos sejam tamb�m considerados na compara��o/atualiza��o/c�pia.

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
.ip -p
Padr�es: Podemos dar <padr�es> (isto �, express�es regulares, como os
do "sh" (cmd), formados com "*", "?", "!", "[...]") 
para a sele��o dos arquivos desejados.
Repare que os <padr�es> s�o aplicados ao nome completo
do arquivo, de tal modo que
podemos utilizar (por exemplo) um padr�o da forma "*/etc/*.c".
Se forem dados v�rios padr�es, devem vir separados
pelos caracteres <sp> ou <ht>.

.ip -P
Padr�es de exclus�o:
Esta op��o � an�loga � op��o "-p", exceto que os padr�es s�o usados
para a exclus�o de arquivos. Todos os arquivos cujos nomes s�o
aceitos por estes padr�es n�o s�o processados, mesmo que tenham sido
aceitos pelos padr�es da op��o "-p" ou "-s".

.ip -s
Fontes em "C":
Esta op��o � �til para o processamento de programas fontes
na linguagem "C", e � uma abreviatura para "-p '*[Mm]akefile *.[cshryv]'".  
Padr�es adicionais podem ser dados com a op��o "-p".
.ec	/*************************************/

.ip -C
Compress�o: Com esta op��o � utilizada a compress�o LZW para a transfer�ncia
dos conte�dos dos arquivos, aumentando a sua velocidade.
Esta op��o pode tamb�m ser dada no ambiente (fmt), veja abaixo.

.ip -n
N� remoto: Define o <n�> remoto com o qual as compara��es/atualiza��es/c�pias
ser�o realizadas.
Esta op��o pode tamb�m ser dada no ambiente (fmt), veja abaixo.

.ip -u
Usu�rio do n� remoto: Define o nome do <usu�rio> no <n�> remoto. Se esta
op��o n�o for dada, o nome do <usu�rio> remoto � igual ao nome do usu�rio
local.
Se for necess�rio, � pedida a senha do <usu�rio> no <n�> remoto.
Esta op��o pode tamb�m ser dada no ambiente (fmt), veja abaixo.

.ip -D
.bc	/*************************************/
Nome para compor o diret�rio remoto:
.ec	/*************************************/
Define <rdir>, um nome
usado para compor o caminho completo das <�rvore>s remotas
.bc	/*************************************/
Se dado, define o "deslocamento" entre os diret�rios local e do
<n�> remoto
.ec	/*************************************/
(veja detalhes abaixo).
Esta op��o pode tamb�m ser dada no ambiente (fmt), veja abaixo.

.ip -N
Le os nomes das <�rvore>s da entrada padr�o, ao inv�s de obt�-los
como argumentos.
Esta op��o � impl�cita, se n�o forem dadas <�rvore>s.

.ep
.in -3

.in
.sp
.b 'RELA��O ENTRE O CAMINHOS DE UMA �RVORE LOCAL E DO <N�> REMOTO'
.in 5
A rela��o entre o caminho de uma �rvore local e o caminho da �rvore
correspondente do <n�> remoto depende do caminho da <�rvore> local e de
<rdir> dado atrav�s da op��o "-D":

.in +3
.(t
.ip 1. 3
Se o caminho da <�rvore> local for absoluto (isto �, come�a por '/'),
o caminho da �rvore remota ser� id�ntico ao caminho da <�rvore> local
(independente de <rdir>).  
.)t

.ip 2. 3
Se o caminho da <�rvore> local for relativo (isto �, N�O come�a por '/'),
o caminho da �rvore remota depende de <rdir> do seguinte modo:

.in +3
.ip a. 3
Se <rdir> N�O for dado, o caminho da �rvore remota
ser� formado pela concatena��o do diret�rio "HOME"
(do <usu�rio> no <n�> remoto)
com o caminho da <�rvore> local.

.ip b. 3
Se <rdir> for um caminho absoluto, o caminho da �rvore remota
ser� formado pela concatena��o de <rdir> com o caminho da <�rvore> local.

.ip c. 3
Se <rdir> for um caminho relativo,
o caminho da �rvore remota
ser� formado pela concatena��o do diret�rio corrente (local)
com <rdir> e com o caminho da <�rvore> local.

.ep
.in -6

.sp 2
Na tabela abaixo, <rhome> significa o diret�rio "HOME" do <usu�rio>
no <n�> remoto e <lcwd> representa o diret�rio corrente (local):

.sp
.(t
.nf
	+---------------+---------------+-----------------------+
	| Caminho local	| <rdir>	| Caminho remoto	|
	+---------------+---------------+-----------------------+
	|		|		|			|
	| /gamma	| (n�o importa)	| /gamma		|
	|		|		|			|
	| gamma		| (n�o dado)	| <rhome>/gamma		|
	|		|		|			|
	| .		| (n�o dado)	| <rhome>		|
	|		|		|			|
	| gamma		| /beta		| /beta/gamma		|
	|		|		|			|
	| .		| /beta		| /beta			|
	|		|		|			|
	| gamma		| beta		| <lcwd>/beta/gamma	|
	|		|		|			|
	| .		| beta		| <lcwd>/beta		|
	|		|		|			|
	| gamma		| .		| <lcwd>/gamma		|
	|		|		|			|
	| .		| .		| <lcwd>		|
	|		|		|			|
	+---------------+---------------+-----------------------+
.fi
.)t


.in
.sp
.(t
.b 'OP��ES NO AMBIENTE'
.in 5
Para simplificar o uso dos utilit�rios, algumas das op��es podem
ser colocadas no ambiente (fmt).
A id�ia � a de colocar certos parametros (que ir�o permanecer constantes
nos pr�ximos usos dos utilit�rios, tal como o nome do <n�> remoto) no
ambiente apenas uma vez, ao inv�s de repet�-los em cada uso do utilit�rio.

.sp
A cadeia do ambiente deve ter a forma

.sp
.nf
		TNET=<argumento>, ...
.fi
.)t
.sp
.(t
onde os <argumento>s podem ser:

.in +3
.ip reduce 13
Compress�o: Equivalente a dar a op��o "-C".
.)t

.ip compress 13
Compress�o: Equivalente a dar a op��o "-C".

.ip node=<n�> 13
Define o n� remoto: Equivalente � op��o
.wo '"-n <n�>".'

.ip user=<user> 13
Define o usu�rio remoto: Equivalente � op��o "-u <user>".

.ip rdir=<rdir> 13
Define o nome usado para compor o caminho completo das <�rvore>s remotas:
Equivalente � op��o "-D <rdir>".

.ep
.in -3

.bc	/*************************************/
Usando a cadeia "TNET" no ambiente, podemos definir globalmente certas
op��es e us�-las automaticamente nos comandos s
.ec	/*************************************/

.bc	/*************************************/
Valores de <ENV>: [-C] [-n <n�>] [-u <usu�rio>] [-D <rdir>]
TNET=node=<node>,user=<user>,rdir=<rdir>,reduce,compreess,<n>
.ec	/*************************************/

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd):  "
sh, gar
.br
.wo "(libc): "
askyesno
.br
.wo "(fmt):  "
ambiente
.br

.in
.sp
.b ARQUIVOS
.in 5
garfield

.in
.sp
.b EXEMPLOS
.in 5
Compara os arquivos da �rvore cuja raiz � o diret�rio corrente
com os arquivos correspondentes da �rvore cuja raiz � o diret�rio
"HOME" do n� "abacate":
.sp
.nf
		tcmpto -n abacate .
.fi

.sp 2
Compara os arquivos da �rvore cuja raiz � o diret�rio "HOME"
do n� "abacate" com os arquivos correspondentes da �rvore
cuja raiz � o diret�rio corrente, copiando (interativamente)
para o n� local os arquivos diferentes:
.sp
.nf
		tcmpfrom -fvC -n abacate .
.fi

.sp 2
Copia os arquivos da �rvore cuja raiz � "/usr/etc/local" para
a �rvore de mesma raiz do n� "abacate" (sem consultas ao usu�rio):
.sp
.nf
		tcpto -vFC -n abacate /usr/etc/local
.fi
.sp 2
Supondo que o diret�rio corrente � "alpha",
compara os arquivos da �rvore cuja raiz � "gamma"
com os arquivos correspondentes da �rvore cuja raiz � o diret�rio
"alpha/gamma" do n� "abacate":
.sp
.nf
		tcmpto -vC -n abacate -D . gamma
.fi
.sp 2
Supondo que o diret�rio corrente � "alpha",
compara os arquivos da �rvore cuja raiz � "gamma"
com os arquivos correspondentes da �rvore cuja raiz � o diret�rio
"alpha/beta/gamma" do n� "abacate":
.sp
.nf
		tcmpto -vC -n abacate -D beta gamma
.fi
.sp 2
Analisando os dois �ltimos exemplos, podemos ver como <rdir>
pode ser usado como um deslocamento entre os diret�rios
local e do <n�> remoto.

.sp 2
No �ltimo exemplo, as op��es "-n", "-D" e "-C" podem ser definidas no
ambiente, e deste modo n�o precisam ser dadas nos comandos subseq��ntes:
.sp
.nf
		TNET=node=abacate,rdir=beta,reduce
		export TNET

		tcmpto -v gamma
.fi

.sp 2
Podemos fazer compara��es entre arquivos local e de um <n�> remoto atrav�s
de "tpipe":
.sp
.nf
	     tpipe -n abacate -C prog.c | diff -c - prog.c | show
.fi


.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
