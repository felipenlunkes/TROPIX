.bp 1
.he 'CPTREE (cmd)'TROPIX: Manual de Refer�ncia'CPTREE (cmd)'
.fo 'Atualizado em 22.09.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "cptree -"
copia uma �rvore
.br

.in
.sp
.b SINTAXE
.in 5
.(l
cptree [-ifvmlLe.] <PAD> <fonte> <destino>

Valores de <PAD>: [-s] [-p "<p>"] [-P "<P>"]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "cptree" copia a �rvore <fonte> para a �rvore <destino>.
Isto � realizado caminhando a �rvore <fonte> e copiando todos
os arquivos para a �rvore <destino> nos locais correspondentes.

.sp
O comando tenta reproduzir as rela��es dos elos f�sicos na �rvore <destino>
encontradas na �rvore <fonte>. No entanto, isto s� � inteiramente poss�vel
quando � realizada uma c�pia completa.

.sp
Se o arquivo a ser copiado for especial ou FIFO,
� copiado o n�-�ndice ao inv�s do conte�do do arquivo.
Para o caso do elo simb�lico, � copiado o seu conte�do sem modifica��es, o que
pode criar refer�ncias inexistentes.

.sp
As op��es do comando s�o:

.in +3
.ip -i
Modo interativo:
� pedida a confirma��o do usu�rio para cada arquivo a copiar.
Se a confirma��o de um diret�rio for negada, ser� pulada toda
a sub-�rvore definida pelo diret�rio.

.ip -f
Se algum arquivo correspondente na �rvore <destino> j� existir,
"cptree" normalmente pede permiss�o ao usu�rio para remov�-lo.
Com esta op��o, o arquivo � removido silenciosamente.

.sp
Um outro m�todo de evitar as consultas � a de responder com letras
ma�usculas: com a resposta "S" ou "Y" todas as perguntas seguintes
ser�o automaticamente respondidas afirmativamente, e (analogamente)
com a resposta "N" ser�o respondidadas negativamente
(veja "askyesno" (libc)).

.ip -v
Lista os nomes dos arquivos que est�o sendo copiados.

.ip -m
Copia os estados dos arquivos:
normalmente, o dono e o grupo dos arquivos da �rvore <destino> s�o conservados
caso �stes j� existam, e s�o usados os do usu�rio do comando em caso contr�rio. 
Com a op��o "-m", s�o copiados o dono, grupo, prote��o e datas dos arquivos
da �rvore <fonte> para o arquivos correspondentes da �rvore <destino>
(exceto elos simb�licos).
Isto s� � inteiramente poss�vel se o usu�rio do comando for superusu�rio. 

.ip -l
Copia apenas os arquivos do dispositivo da �rvore <fonte>;
n�o entra nos subdiret�rios montados.

.ip -L
Copia apenas os arquivos do diret�rio raiz;
n�o entra nos subdiret�rios.

.ip -e
Copia apenas os arquivos n�o existentes na �rvore <destino>.

.ip "-."
Copia tamb�m os arquivos ocultos.
Normalmente, arquivos cujos nomes cont�m algum componente que
come�a com um ponto (exceto "..") n�o s�o copiados
(como por exemplo "/usr/src/sys/.old/rot.c").
Esta op��o faz com que estes arquivos sejam tamb�m copiados.

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
Todos os arquivos cujos nomes s�o
aceitos por estes padr�es n�o s�o selecionados, mesmo que tenham sido
aceitos pelos padr�es das op��es "-p" ou "-s".

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
Ao copiar uma �rvore utilizando a op��o "-m", � poss�vel que
os tempos de modifica��o dos diret�rios n�o fiquem iguais,
pois a cria��o de um arquivo implica na escrita em um diret�rio,
alterando o seu tempo de modifica��o.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd):  "
sh, cp
.br
.wo "(libc): "
askyesno
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
