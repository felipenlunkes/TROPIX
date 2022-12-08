.bp 1
.he 'GAR (cmd)'TROPIX: Manual de Refer�ncia'GAR (cmd)'
.fo 'Atualizado em 20.07.06'Vers�o 4.9.0'Pag. %'

.b NOME
.in 5
gar - cria/atualiza cole��es de arquivos

.in
.sp
.b SINTAXE
.in 5
.(l
gar -i [-xtce] [-F <col>] [-rnvugfmd#] [-B <n>] <PAD>

gar -o [-Tngv#] [-F <col>] [-B <n>] <COMP> < <nomes>
gar -o [-Tnvd.#] [-F <col>] [-B <n>] <PAD> <COMP> <nome> ...

gar -a [-ngv#] [-F <col>] [-B <n>] <COMP> < <nomes>
gar -a [-nvd.#] [-F <col>] [-B <n>] <PAD> <COMP> <nome> ...

Valores de <PAD>: [-s] [-p "<p>"] [-P "<P>"]

Valores de <COMP>: [-D] [-b <b>] [-l <l>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "gar" � um utilit�rio gen�rico para guardar e recuperar arquivos
e/ou sistemas de arquivos, em/de fitas magn�ticas, disquetes,
arquivos em disco, ou outro meio f�sico qualquer.
O conjunto de arquivos no referido meio chamaremos de "cole��o".

.sp
O formato GAR cont�m c�digos de CRC para cada cabe�alho e cada bloco
(de 512 bytes) dos arquivos, e por este motivo � mais confi�vel
do que cole��es no formato TAR e CPIO.
Al�m disto, o comando processa todos os tipos de arquivos (regulares,
diret�rios, especiais de bloco/caractere, elos simb�licos e "fifo"s),
conservando os elos f�sicos entre arquivos (quando poss�vel).

.sp
Normalmente, "gar" comprime os arquivos regulares antes de
escrev�-los na cole��o.
Com isto � poss�vel um aumento substancial do aproveitamento do meio
f�sico (como um disquete, por exemplo).
Se a compress�o for utilizada, TODAS as opera��es descritas abaixo
se realizam do mesmo modo
(inclusive
.bc	/*************************************/
a compara��o r�pida de objetos (op��o "-q") e
.ec	/*************************************/
a continua��o da cole��o em mais um volume).
Veja a se��o "COMPRESS�O DE DADOS".

.sp
Nas opera��es de sa�da, o utilit�rio gera cole��es
no seu formato nativo GAR ou no formato TAR, segundo as op��es
e os argumentos descritos abaixo.
Nas opera��es de entrada, o comando l� (reconhecendo automaticamente)
cole��es nos formatos GAR, TAR, CPIO e CPIO reverso.
O formato CPIO reverso � um formato obtido quando geramos
uma cole��o com o utilit�rio "cpio" em um computador que
inverte os bytes de uma palavra.

.sp
O comando usualmente n�o grava nas cole��es
os "arquivos ocultos" (arquivos cujos <nomes>
cont�m algum componente que come�a com um ponto - veja a op��o "-.").

.sp
A a��o do comando � controlada por uma chave e (possivelmente)
um modificador, al�m de outras op��es e argumentos.

.sp
.(t
As chaves s�o:

.in +3
.ip -i
Entrada: � lida uma cole��o da entrada padr�o (veja as op��es "-#" e "-F")
reconhecendo automaticamente
os formatos GAR, TAR, CPIO e CPIO reverso.
.)t

.sp 1
A opera��o realizada depende do modificador utilizado,
que deve ser um dos seguintes:
.in +5

.ip -x
Extra��o de arquivos: os arquivos da cole��o s�o criados
no sistema de arquivos,
com o mesmo nome contido na cole��o (veja a op��o "-d").
Se forem dados <padr�es> (veja as op��es "-p", "-P" e "-s"),
s� ser�o criados os arquivos aceitos.
Se o arquivo j� existe no sistema de arquivos, o usu�rio �
consultado para decidir
se recria o arquivo a partir da cole��o,
ou se conserva a vers�o antiga (veja a op��o "-f").

.ip -t
Tabela de conte�do: � gerada (na sa�da padr�o)
uma tabela contendo os nomes dos arquivos
da cole��o. Se forem dados <padr�es>, a tabela s� conter�
nomes de arquivos aceitos. Se for dada a op��o "-v", a tabela 
conter� mais informa��es sobre cada arquivo.
Se ela for dada duas vezes ("-vv"), a tabela conter� ainda mais informa��es, 
e os nomes simb�licos dos donos dos arquivos s�o substitu�dos
pelas identifica��es num�ricas dos donos e dos grupos. 
Nenhum arquivo � criado.

.ip -c
Compara��o de arquivos:
esta opera��o � semelhante � extra��o ("-x"), mas ao inv�s de
criar os arquivos, � realizada uma compara��o entre os
arquivos da cole��o e os arquivos do disco.
As mensagens s�o dadas na ordem: cole��o, arquivo no disco.

.bc	/*************************************/
Caso os arquivos sejam m�dulos objeto (veja "a.out" (fmt)),
os campos n�o significativos do cabe�alho s�o mascarados
de tal modo que apenas os componentes realmente significativos
s�o levados em conta na compara��o.
.ec	/*************************************/

.sp
Durante uma compara��o, podemos gerar o arquivo "garfield",
que ir� facilitar uma subseq��nte extra��o dos arquivos diferentes 
(veja a op��o "-g").
Tamb�m durante uma compara��o, os arquivos diferentes podem
logo ser atualizados (veja a op��o "-u").

.ip -e
Pipe:
esta opera��o � semelhante � extra��o mas ao inv�s
dos arquivos serem criados no disco, eles s�o copiados
para a sa�da padr�o. Com isto podemos passar os arquivos para
um processo subsequente (como por ex. o "grep", ou "pr"), ou ainda
podemos simplesmente ver os arquivos na tela.
.in -5

.sp
.ip -o
Sa�da: � criada uma cole��o GAR (ou TAR, veja a op��o "-T") na sa�da padr�o
(veja as op��es "-#" e "-F") contendo arquivos cujos <nomes> s�o dados na
entrada padr�o (veja a op��o "-g"), um por linha, ou dados como argumentos.
Se <nome> for
.bc	/*************************************/
Nesta segunda forma, cada argumento dado, se for
.ec	/*************************************/
o nome de um diret�rio, ser� interpretado como sendo
a raiz de uma �rvore, e substitu�do pelos nomes de todos os arquivos da
�rvore (veja as op��es "-d" e "-.").

.sp
Se forem dados <padr�es> (veja as op��es "-p", "-P" e "-s")
os nomes obtidos s�o comparados com os <padr�es> e somente
os nomes aceitos s�o utilizados para serem inclu�dos na cole��o.

.ip -a
Acr�scimo:
Esta chave � an�loga � "sa�da" ("-o"), exceto que os arquivos s�o
adicionados ao final de uma cole��o GAR criada anteriormente.

.ep
.in -3
.sp
.(t
.lp
Al�m das chaves e dos modificadores, temos as seguintes op��es: 

.in +3
.ip -T
Gera a cole��o no formato TAR ao inv�s de GAR: Isto � �til para
o transporte de "software" para sistemas SOFIX que aceitam o
formato TAR, mas n�o GAR.
.)t

.ip -r
Verifica sempre os CRCs (apenas para o formato GAR):
Normalmente, durante uma opera��o de leitura, somente s�o verificados
os CRCs dos arquivos processados
(isto �, os arquivos que foram selecionados atrav�s dos <padr�es>,
confirmados em opera��es interativas, etc...).
Com esta op��o, os CRCs de todos os arquivos s�o sempre verificados.

.ip -n
Interativo:
para cada a��o a realizar (inclus�o de um arquivo na
cole��o ou cria��o/compara��o de um arquivo lido da cole��o)
o usu�rio � consultado para indicar se o arquivo
em quest�o deve ser processado ou n�o.

.sp
No caso da gera��o interativa de uma cole��o, 
a indica��o de que o usu�rio n�o deseja processar um diret�rio,
significa que toda a respectiva sub�rvore ser� pulada.

.ip -u
Atualiza��o:
Durante uma compara��o (modificador "-c"), para cada arquivo diferente,
o usu�rio � consultado se deseja logo atualizar o arquivo.
Isto s� � poss�vel se o conte�do do arquivo em quest�o (na cole��o)
puder ser lido novamente, o que de acordo com o dispositivo da
cole��o, pode n�o ser poss�vel.

.ip -v
"Verboso": esta op��o faz com que informa��es sejam
dadas sobre o andamento das opera��es.
No caso da impress�o da tabela, faz com que sejam dadas mais
informa��es sobre cada arquivo listado.

.ip -B
Blocagem: o tamanho do bloco da cole��o � determinada automaticamente,
embora possa ser dada explicitamente, na forma de <n> KB
(veja "VOLUMES DE CONTINUAC�O").

.bc	/*************************************/
.sp
Para a sa�da, caso n�o seja dada, a blocagem utilizada � de 5120 bytes
para dispositivos n�o estruturados ("raw") e 512 bytes
para dispositivos estruturados. 

.ip -C
Durante a cria��o de uma cole��o, comprime os arquivos regulares
com o m�todo de "Lempel-Ziv-Welch" (LZW).
Veja a se��o "COMPRESS�O DE DADOS".

.ip -b
Tamanho m�ximo do c�digo (em bits) usado na compress�o LZW.
Esta op��o deve ser utilizada apenas na cria��o da cole��o
(a cole��o j� cont�m o tamanho m�ximo a ser utilizado na expans�o).
Este valor deve ser dado na faixa de 9 a 16 bits
(se for omitido, ser� usado um tamanho m�ximo de 14 bits, que � um bom
compromisso entre o fator de compress�o e a mem�ria necess�ria para arquivos
de 30 Kb ou menores).
.ec	/*************************************/

.ip -D
Normalmente, durante a cria��o de uma cole��o,
os arquivos regulares s�o comprimidos. Com esta op��o, estes arquivos
ser�o gravados sem compress�o.
Veja a se��o "COMPRESS�O DE DADOS".

.ip -l
N�vel a ser utilizado na "defla��o".
Esta op��o deve ser utilizada apenas na cria��o da cole��o.
O n�vel <l> deve ser dado no intervalo de 
1 (menor compress�o, maior velocidade) at� 9 (maior compress�o,
menor velocidade). Se n�o for dado, o n�vel usado � 5. 

.ip -F
A cole��o ser� lida/escrita do/no dispositivo/arquivo <col>.

.sp
Se n�o for dada nenhuma das op��es "-F" nem "-#" (ver abaixo),
a cole��o ser� lida/escrita do/no entrada/sa�da padr�o.
Isto N�O pode ser usado para acr�scimos.

.ip -#
Esta op��o � uma abreviatura para nomes de dispositivos
freq�entemente utilizados: # = 0 ou 1 equivale a "-F /dev/fd#";
# = 2 ou 3 equivale a "-F /dev/rzip0" ou "-F /dev/rzip1",
respectivamente.

.ip -p
Padr�es de inclus�o:
tanto na entrada como na sa�da, podemos dar <padr�es>
(isto �, express�es regulares, como os
do "sh", formados com "*", "?", "!", "[...]") 
para a sele��o dos nomes dos arquivos desejados.
Repare que os <padr�es> s�o aplicados ao nome completo do arquivo,
de tal modo que podemos utilizar (por exemplo) um padr�o da forma "*/etc/*.c".
No momento podemos dar at� 20 <padr�es>, entre aspas, separados
por brancos ou tabula��es.

.ip -P
Padr�es de exclus�o:
Esta op��o � an�loga � op��o "-p", exceto que os padr�es s�o usados
para a exclus�o de arquivos. Todos os arquivos cujos nomes s�o
aceitos por estes padr�es n�o s�o processados, mesmo que tenham sido
aceitos pelos padr�es da op��o "-p" ou "-s".

.ip -s
Fontes em "C":
esta op��o � �til para o processamento de programas fontes
na linguagem "C", e � uma abreviatura para "-p '*[Mm]akefile *.[cshryv]'".
Padr�es adicionais podem ser dados com a op��o "-p".

.ip -d
Diret�rio corrente:
durante a extra��o ou compara��o de arquivos de uma cole��o,
cria/compara os arquivos no diret�rio corrente, ao inv�s de utilizar
o diret�rio indicado pelo nome completo. 
Com esta op��o, elos f�sicos n�o s�o processados.

.sp
Durante a gera��o de cole��es, esta op��o pode ser usada
para n�o incluir os diret�rios na cole��o.

.(t
.ip -f
For�a: durante a cria��o de uma cole��o ou extra��o de arquivos de uma cole��o,
se o arquivo destino j� existir, normalmente o usu�rio �
consultado para decidir
se atualiza o arquivo,
ou se conserva a vers�o antiga.
A op��o "-f" suprime esta consulta, atualizando o arquivo.
.)t

.sp
Analogamente, durante uma compara��o com atualiza��o (op��es "-icu"),
se for dada a op��o "-f", o arquivo � atualizado sem consulta.

.sp
Um outro m�todo de evitar as consultas ao usu�rio � a de responder com letras
ma�usculas: com a resposta "S" ou "Y" todas as perguntas seguintes
ser�o automaticamente respondidas afirmativamente, e (analogamente)
com a resposta "N" ser�o respondidadas negativamente
(veja "askyesno" (libc)).

.ip -m
Restaura o estado: durante a extra��o de arquivos de uma cole��o,
restaura os donos, grupos, prote��o e tempos originais do arquivo.
Esta op��o, s� ser� inteiramente eficaz se o usu�rio for o superusu�rio.

.ip -g
"garfield":
durante uma compara��o, cria o arquivo "garfield" no diret�rio
corrente, contendo os <nomes> dos arquivos que acusaram diferen�as. 
Durante uma subseq�ente extra��o (tamb�m com a op��o "-g"),
estes nomes ser�o usados para extrair apenas os arquivos diferentes.
Na extra��o podemos ainda utilizar o modo interativo ("-n")
e dar <padr�es> ("-s", "-p" ou "-P"), para termos ainda mais controle
sobre a escolha dos arquivos a extrair.

.sp
Durante uma opera��o de sa�da ou acr�scimo, a op��o "-g" pode ser
usada para ler os <nomes> dos arquivos de "garfield" ao
inv�s da entrada padr�o.
 
.bc	/*************************************/
.ip -q
Compara��o r�pida de m�dulos objeto:
se durante uma opera��o de compara��o de arquivos, o arquivo da
cole��o e o arquivo correspondente do sistema de arquivos forem
m�dulos objeto, considera os arquivos iguais,
se os tamanhos totais dos arquivos e
as datas contidas nos cabe�alhos forem iguais.
Esta compara��o � muito mais r�pida, e a probabilidade de indicar
uma igualdade falsa � extremamente baixa.
.ec	/*************************************/

.ip -.
"Arquivos ocultos":
Durante a gera��o de uma cole��o em que os <nomes> dos arquivos
s�o dados como argumentos do comando, arquivos cujos nomes
cont�m algum componente que comece com um ponto (exceto "..")
n�o s�o gravados (como por exemplo "/usr/src/sys/.old/rot.c").
A op��o "-." faz com que estes arquivos sejam tamb�m
inclu�dos na cole��o.
.bc	/*************************************/
Al�m disto, a op��o faz com que os diret�rios sejam gravados,
mesmo que seus nomes n�o sejam aceitos pelos <padr�es>.
Esta op��o pode ser importante para "dump/restore" de sistemas
de arquivos.
.ec	/*************************************/

.ep
.in -3

.sp 2
.in
.b "COMPRESS�O DE DADOS"
.in 5
Para a compress�o de dados, o comando "gar" utiliza
o m�todo da "defla��o" (utilizada pelos programas "gzip" (GNU) e PKZIP).

.sp
Com a compress�o da dados � poss�vel um aumento substancial do
aproveitamento do meio f�sico (como um disquete, por exemplo).
Com programas fontes, a capacidade de um meio f�sico tipicamente
mais do que dobra, chegando a triplicar ou at� a quadruplicar
quando os arquivos cont�m muita redund�ncia.

.bc	/*************************************/
.sp
Quando gravado com compress�o, os arquivos regulares cont�m uma
dupla verifica��o de CRC: al�m dos CRCs gravados normalmente em cada
bloco da cole��o para verificar a integridade da cole��o
no meio f�sico, cada arquivo recebe CRCs adicionais, para
verificar que o processo de expans�o est� de fato recuperando o arquivo
original.

.sp
Se a compress�o for utilizada, TODAS as opera��es descritas
se realizam do mesmo modo (inclusive a compara��o r�pida de objetos
(op��o "-q")) e continua��o da cole��o em mais um volume.
.ec	/*************************************/

.sp
Durante a leitura de uma cole��o,
"gar" identifica quais s�o os arquivos comprimidos,
e torna a descompress�o autom�tica e transparente.

.sp
Se um arquivo ficar maior na forma comprimida (o que � poss�vel para
arquivos muitos pequenos), "gar" identifica isto e grava o arquivo
na sua forma original. Podemos ter cole��es com arquivos comprimidos
e originais misturados (o que pode facilmente ocorrer com a op��o de
acr�scimo (chave "-a").

.bc	/*************************************/
.sp
Ao contr�rio do que se possa imaginar, nem sempre a cria��o/recupera��o
de cole��es comprimidas � mais lenta - com disquetes, por exemplo, a
compress�o/descompress�o � realizada em paralelo com a leitura/escrita,
e como lemos/escrevemos menos blocos do/no disquete, na realidade a opera��o �
normalmente at� mais r�pida!

.sp
Normalmente, o m�todo da "defla��o" obt�m compress�es maiores, embora
seja um pouco mais lento. Veja as op��es "-C", "-D", "-b" e "-l".

.sp
Para simplificar o uso, os par�metros de compress�o podem ser pr�-definidos no
ambiente (veja "environ" (fmt)) atrav�s da vari�vel "GAR",
cujo valor deve ter a forma:

.sp
.(l
		<m�todo>[,<n>]
.)l
.sp
onde <m�todo> pode ser "reduce", "compress" ou "lzw" para o m�todo LZW
e "deflate" ou "zip" para a defla��o. Se dado o valor num�rico <n>, ele ser�
interpretado como n�mero de bits ou n�vel de compress�o de acordo com o
<m�todo> dado.
.ec	/*************************************/

.sp 2
.in
.b "VOLUMES DE CONTINUA��O"
.in 5
O utilit�rio processa volumes de continua��o, isto �,
ele prev� o caso de uma cole��o n�o caber em um volume
(fita magn�tica ou disquete).
Isto � de particular interesse para disquetes, que podem conter
apenas pequena quantidade de informa��o.

.sp
Durante a gera��o da cole��o, ao verificar que um volume
chegou ao final, � emitida uma mensagem no terminal, pedindo
o nome do dispositivo aonde deve continuar a grava��o da cole��o.

.sp
Durante a leitura de uma cole��o, ao final de um volume,
o utilit�rio pede o nome do dispositivo de continua��o,
e verifica se o volume de continua��o realmente � o
correto.

.sp
Tanto na leitura como na escrita,
se o dispositivo de continua��o for o mesmo do volume inicial, e este n�o
for a entrada/sa�da padr�o, basta dar um <nl>.

.bc	/*************************************/
.sp
Para o funcionamento correto de volumes de continua��o,
� importante utilizar na leitura a mesma blocagem 
utilizada na gera��o da cole��o.
.ec	/*************************************/

.sp
Repare que uma cole��o pode ficar armazenada em diversos
meios, tal como
o come�o em disquete, a continua��o em uma fita
magn�tica e o final em um arquivo em disco.

.sp
.in
.b OBSERVA��ES
.in 5
.bc	/*************************************/
O utilit�rio � pr�prio para realizar "dump/restore" de sistemas
de arquivos. Neste caso, durante a cria��o da cole��o,
n�o esquecer os arquivos ocultos (op��o "-.")
e durante a recupera��o, n�o esquecer o estados originais dos
arquivos (op��o "-m").

.sp
No momento, a opera��o de "acr�scimo" ("-a") pode ser realizada
apenas em disquetes ou fita magn�tica n�o blocada. 
.ec	/*************************************/

Deve-se tomar cuidado na utiliza��o do arquivo "garfield"
("-g") com cole��es em que foram acrescentados arquivos
(opera��o "-a"), pois a cole��o pode conter arquivos repetidos.

.sp
O comando n�o realiza uma consist�ncia completa nas op��es.
Isto significa que em certos casos, op��es sup�rfluas s�o
ignoradas.

.sp
.in

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
reduce, gzip
.br
.wo "(libc):"
askyesno
.br
.wo "(fmt): "
gar
.br

.in
.sp
.b ARQUIVOS
.in 5
 /dev/fd?
 /dev/rzip?
 ./garfield

.in
.sp
.(t
.b EXEMPLOS
.in 5
Cria a cole��o "col" no diret�rio corrente, contendo o arquivo "abc.c"
e todos os arquivos da �rvore cuja raiz � "dir":
.sp
.nf
		gar -ov abc.c dir  >col
.fi
.)t

.sp 2
.(t
O arquivo "names" cont�m os nomes de diversos arquivos, um por linha.
Cria uma cole��o na unidade de disquete ("/dev/fd0"):
.sp
.nf
		gar -ov0 <names
.fi
.)t

.sp 2
Le uma cole��o de um disquete, e extrai para o disco todos os arquivos
contendo programas fontes em "C":
.sp
.nf
		gar -ixv0 -p "*.c"
.fi

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
