.bp
.he 'MKFST1 (cmd)'TROPIX: Manual de Refer�ncia'MKFST1 (cmd)'
.fo 'Atualizado em 22.09.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "mkfst1 -"
gera um sistema de arquivos T1
.br

.in
.sp
.b SINTAXE
.in 5
.(l
mkfst1 [-rfv] <dev> [<fs> [<vn> [<pn>]]]
.)l

.in
.sp
.b DESCRI��O
.in 5
O  comando "mkfst1" cria um sistema de arquivos T1 no dispositivo
<dev>, no formato adequado para conter arquivos e
ser "montado" (veja "mount" (cmd)).

.sp
Tamb�m pode ser criado um sistema de arquivos T1 em um arquivo regular
(veja a op��o "r").

.sp
Um sistema de arquivos T1 � composto de uma ou mais zonas,
descritas por mapas de bits.
Cada zona compreende 8192 blocos de 4 KB, totalizando 32 MB.
Cada zona cont�m o seu mapa de bits no 3. bloco, e pode conter
blocos livres, de dados ou de n�s-�ndice.
A primeira zona � especial, pois cont�m 
o bloco de "boot" (o "boot1", na seq��ncia de carga do sistema)
e o Superbloco em seus blocos iniciais.

.sp
Para a cria��o do sistema de arquivos,
� necess�ria a defini��o de 3 par�metros.
Cada um dos par�metros pode ser dado:

.in +3
.ip 1. 3
Com um valor <val>: O valor <val> ser� utilizado.

.ip 2. 3
Na forma "-": Ser� utilizado um valor "padr�o", descrito abaixo,
em cada um dos par�metros.

.ip 3. 3
Na forma ".": Sup�e-se que <dev> j� contenha um sistema de arquivos,
e o valor ser� herdado do sistema existente.
Se <dev> N�O contiver um sistema de arquivos T1,
ser� utilizado o valor "padr�o".

.ip 4. 3
N�o ser dado: Como ".", acima.

.ep
.in -3

.sp
Os par�metros s�o:

.in +3
.ip <fs>
Tamanho do sistema. Especifica o tamanho total do
sistema de arquivos (normalmente em blocos de 512 bytes;
com o sufixo "k" ou "K" em KB e com o sufixo "m" ou "M" em MB).
O valor padr�o � o obtido da tabela de parti��es do disco
(veja "prdisktb" (cmd)).
Obviamente, se for dado um valor ele n�o pode ser maior
do que o espa�o total da parti��o.

.sp
Repare que o sistema de arquivos T1 possui blocos de 4 KB,
e podem ocorrer truncamentos na convers�o de 512 bytes para 4 KB.

.ip <vn>
Nome do Volume (at� 14 caracteres).
Este par�metro tem aspecto puramente documentacional,
e em geral � utilizado para descrever o conte�do do sistema
de arquivos.
Este nome � dado nas sa�das dos comandos "mount" e "fsname" (cmd).
O valor padr�o � igual a "???"
(ele pode ser alterado posteriormente atrav�s do comando "fsname").

.ip <pn>
Nome do Dispositivo F�sico (at� 14 caracteres).
Este par�metro tem aspecto puramente documentacional,
e em geral � utilizado para indicar o nome do dispositivo em
que reside o sistema de arquivos.
Este nome � dado nas sa�das dos comandos "mount" e "fsname" (cmd).
O valor padr�o � igual ao nome do dispositivo da tabela de parti��es
(ele pode ser alterado posteriormente atrav�s do comando "fsname").

.ep
.in -3

.sp
Normalmente, antes de iniciar a gera��o do sistema de arquivos T1,
"mkfst1" escreve todos os par�metros que ir� usar, pedindo ent�o
uma confirma��o do usu�rio para iniciar a gera��o (veja a op��o "-f").

.sp
As op��es do comando s�o:

.in +3
.ip -r
Arquivo regular. Caso o dispositivo <dev> n�o exista, cria um
arquivo regular com o sistema de arquivos T1.

.ip -f
For�a:
Como a gera��o de um sistema de arquivos destr�i todos os arquivos
que porventura j� existam em <dev>, "mkfst1" normalmente
pede a confirma��o do usu�rio, antes de iniciar a escrita em <dev>.
Com esta op��o, a confirma��o do usu�rio n�o � pedida.
Al�m disto, n�o � impressa a lista de par�metros utilizados
na gera��o.

.ip -v
Verboso. Esta op��o informa se o dispositivo j� tem um sistema de
arquivos T1 (dando os seus par�metros se for o caso).

.ep
.in -3

.sp
O comando "mkfst1" preenche o bloco de "boot" (primeiro bloco do
sistema de arquivos T1) com o arquivo "/etc/boot/t1.g.boot1" ou
"/etc/boot/t1.l.boot1", a n�o ser
para os disquetes de 1440 KB ("/dev/fd?"), em que utiliza o arquivo
"/etc/boot/t1.d.boot1". Este bloco pode posteriormente ser alterado
atrav�s do comando "edboot" ou "dd" (cmd).

.in
.sp
.b OBSERVA��ES
.in 5
Repare que, mesmo quando o sistema de arquivos T1 j� existe,
e os par�metros n�o s�o dados, N�O � herdado o bloco de
"boot".

.sp
Por raz�es de seguran�a e consist�ncia, o superbloco de um
sistema de arquivos T1 possui um campo que cont�m um "n�mero m�gico".
Deste modo o sistema operacional pode identificar
se naquele dispositivo existe realmente um sistema de arquivos
(por exemplo, em opera��es de "mount").

.sp
Antes de iniciar a cria��o do sistema de arquivos T1,
o comando "mkfst1" verifica se o dispositivo <dev> est�
est� montado sob algum diret�rio.
Se isto ocorrer, o novo sistema n�o ser�
criado, sendo enviada uma mensagem correspondente.
.bc	/*************************************/
Assim, sobre o dispositivo que for raiz ("root") do sistema no
momento, n�o poder� ser criado um sistema de arquivos.
.ec	/*************************************/

.sp
O comando gera automaticamente o diret�rio "lost+found",
utilizado pelo "fsckt1" ao reconectar arquivos T1.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
mount, fsname, fsckt1, dd, prdisktb, edboot
.br

.in
.sp
.b ARQUIVOS
.in 5
/etc/boot/*

.in
.sp
.(t
.b EXEMPLOS
.in 5
.(l
	mkfst1 /dev/hd2a
.)l
.)t

.sp
Se em "/dev/hd2a" j� existir um sistema de arquivos T1, ser�o
herdados todos os seus 3 par�metros. Em caso contr�rio, os
par�metros ser�o obtidos dos seguinte modo:
<fs> e <pn> da tabela de parti��es; <vn>: "???";

.sp
.(l
	mkfst1 /dev/sd3 10000
.)l

.sp
O sistema de arquivos T1 ter� 10000 blocos de 512 bytes.
Os demais par�metros ser�o herdados do sistema anterior, ou
caso o dispositivo ainda n�o possuir um sistema de arquivos,
o par�metro <vn> ter� o valor "???" e
<pn> ser� obtido da tabela de parti��es.

.sp
.(l
	mkfst1 /dev/hdb3c 30000 manuais -
.)l

.sp
O sistema de arquivos T1 ter� 30000 blocos de 512 bytes.
o par�metro <vn> ter� o valor "manuais" e
<pn> ser� obtido da tabela de parti��es.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
