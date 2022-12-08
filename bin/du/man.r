.bp
.he 'DU (cmd)'TROPIX: Manual de Refer�ncia'DU (cmd)'
.fo 'Atualizado em 27.10.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "du -"
informa sobre o uso de disco
.br

.in
.sp
.b SINTAXE
.in 5
.(l
du [-dam.sN] [-b <sz>] [-p "<p>"] [-P "<P>"] [<�rvore> ...]
.)l

.bc	/*************************************/
Op��es:	-d: Informa tamb�m para cada sub�rvore
	-a: Informa tamb�m para cada arquivo
	-m: Escreve os valores em MB (ao inv�s de KB)
	-.: Lista tamb�m arquivos ocultos (".old" ...)
	-s: Adiciona os padr�es dos fontes em "C"
	-N: L� os nomes das <�rvore>s de "stdin"
	-b: Use <sz> como o tamanho do bloco
	-p: Seleciona arquivos atrav�s dos padr�es <p> de inclus�o
	-P: Seleciona arquivos atrav�s dos padr�es <P> de exclus�o
.ec	/*************************************/

.in
.sp
.b DESCRI��O
.in 5
O comando "du" informa sobre o espa�o ocupado pelos arquivos e diret�rios
contidos em cada <�rvore> dada, no sistema de arquivos (em disco).

.sp
O espa�o � dado normalmente em KB (veja a op��o "-m" abaixo),
e N�O considera os arquivos "ocultos" (arquivos cujos "caminhos" cont�m
algum componente que come�a com um ponto - veja a op��o "-.").

.sp
Normalmente, <�rvore> � o nome de um diret�rio (a raiz) cujos arquivos
e subdiret�rios (recursivamente) definem a �rvore.
Se <�rvore> for o nome de um arquivo (e n�o de um diret�rio),
a �rvore consiste em apenas este arquivo.
Se n�o for dada nenhuma <�rvore>, ser� considerada a �rvore cuja raiz �
o diret�rio corrente.

.sp
Os tamanhos dos arquivos s�o arredondados para o tamanho do bloco
do sistema de arquivos nos quais est�o contidos, para dar um valor
representativo do espa�o efetivamente ocupado no meio (veja a op��o "-b" abaixo).

.sp
Sem op��es, o comando imprime uma linha para cada <�rvore> dada.
.bc	/*************************************/
e para cada um de seus subdiret�rios.
.ec	/*************************************/

.sp
As op��es do comando s�o:

.in +3
.ip -d
Imprime uma linha tamb�m para cada sub�rvore.

.ip -a
Imprime uma linha tamb�m para cada arquivo.

.ip -m
Imprime os resultados em MB (ao inv�s de KB).

.ip "-."
Seleciona tamb�m nomes de arquivos ocultos.
Normalmente, arquivos cujos nomes cont�m algum componente que
come�a com um ponto (exceto "..") n�o s�o selecionados
(como por exemplo "/usr/src/sys/.old/rot.c").
Esta op��o faz com que estes arquivos sejam tamb�m considerados.


.ip "-s"
Esta op��o � a abreviatura de
.sp
.nf
			-p "*[Mm]akefile *.[cshryv]"
.fi
.sp
e � �til para selecionar arquivos relacionados com a linguagem "C".
Padr�es adicionais podem ser dados com a op��o "-p" (veja abaixo).

.ip -N
L� os nomes das �rvores de "stdin".

.ip "-b"
Use <sz> como o tamanho do bloco para o arredondamento dos arquivos.
Podem ser usados os sufixos "c" ou "C" para especificar multiplica��o
por 2048, "k" ou "K" para especificar multiplica��o por 1024,
"b" ou "B" para especificar multiplica��o por 512.

.ip "-p"
Padr�es de inclus�o:
Seleciona apenas arquivos cujos nomes s�o aceitos por um dos <padr�es> dados.
Cada padr�o � uma express�o regular, como as do "sh" (cmd),
formada com "*", "?", "!", "[...]" (ver "patmatch" (libc)).
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
.b OBSERVA��ES
.in 5
Um arquivo com mais de um elo f�sico s� � considerado uma �nica vez.

.sp
No caso de elos simb�licos, s�o computados os espa�os ocupados
pelos pr�prios elos, e n�o pelos arquivos referenciados.

.sp
N�o s�o computados os blocos indiretos dos arquivos.

.sp
Arquivos com "buracos" (ver "lseek" (sys)) s�o computados incorretamente.

.in
.sp
.(t
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
df
.br
.wo "(sys): "
lseek
.br
.wo "(libc):"
patmatch
.br
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
