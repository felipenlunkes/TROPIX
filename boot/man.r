.bp
.he 'BOOT (cmd)'TROPIX: Manual de Refer�ncia'BOOT (cmd)'
.fo 'Atualizado em 29.08.06'Vers�o 4.9.0'Pag. %'

.b NOME
.in 5
Carga do sistema operacional:
.sp
.wo "boot0 -"
Est�gio inicial
.br
.wo "boot1 -"
Est�gio intermedi�rio
.br
.wo "boot2 -"
Est�gio final
.br

.in
.sp
.b SINTAXE
.in 5
.(l
boot1:      > [-sSvV] [<boot2>]

boot2:  boot> [-x] [-v] [-<dev>] [<pgm>]
        boot>  -?  [-v]
.)l

.in
.sp
.b DESCRI��O
.in 5
O processo de carga do sistema operacional TROPIX � composto de
4 etapas: BIOS (em ROM), "boot0", "boot1" e "boot2".

.sp
O "boot0" e "boot1" operam ainda no modo de 16 bits, utilizando as chamadas
"INT 13" da BIOS para realizar a leitura dos blocos dos discos.
.bc	/*************************************/
O "boot0" tenta, automaticamente, utilizar as extens�es da INT 13, e
h� duas vers�es para o "boot1": "lboot1" (usando) e "hboot1" (sem usar)
as extens�es da INT 13. Se a BIOS do seu computador suportar estas
extens�es, voc� poder� carregar sistemas operacionais (pelo menos o TROPIX)
em parti��es acima do limite de 8 GB (n�meros de cilindro maiores do que 1024).
.ec	/*************************************/

.sp
Na �ltima fase de "boot", "boot2" o modo � passado para 32 bits, quando
ent�o a entrada/sa�da passa a ser realizada atrav�s de "drivers" inclu�dos
em "boot2". No momento, "boot2" cont�m "drivers" para disquete, discos IDE e
os controladores de discos SCSI Adaptec ISA 1542 e PCI 2940/29160.

.sp
Os diversos programas de "boot" tentam fornecer para a
etapa seguinte qual foi o dispositivo do qual foram lidos.
O objetivo consiste em escolher um dispositivo durante a segunda etapa
("boot0"), e este mesmo dispositivo ser usado para a leitura de "boot1",
"boot2", o n�cleo do TROPIX e finalmente ser usado como sistema de arquivos
"raiz" do sistema operacional.

.sp
Repare que, a partir da vers�o 4.3.0, h� dois tipos de sistemas de arquivos
nativos do TROPIX: o "antigo" (V7) com blocos de 512 bytes (em obsolesc�ncia)
e o "novo" (T1) com blocos de 4 KB.

.sp
A descri��o do processo de "boot" dada abaixo refere-se � carga atrav�s de
disco r�gido. Se for dado "boot" em um disquete com um sistema de arquivos
TROPIX (V7 ou T1), este conter� no primeiro bloco (de 512 bytes ou 4 KB)
o "boot1" (n�o havendo o "boot0").

.in
.sp
.b BIOS
.in 5
A BIOS do PC (ap�s diversos testes e inicializa��es), le o primeiro
bloco (de 512 bytes) de um disco ("/dev/hda" ou "/dev/sda") para a mem�ria,
e passa o controle para o programa contido neste bloco.

.in
.sp
.b BOOT0
.in 5
Este primeiro bloco cont�m o in�cio de "boot0", que por sua vez
le os seus blocos restantes do mesmo disco.
O "boot0" imprime uma tabela com as parti��es ativas dos diversos
discos encontrados no sistema, e pede o �ndice da parti��o desejada
para prosseguir o procedimento de carga.

.sp
S�o impressos tamb�m o �ndice "default" (valor por omiss�o), e o n�mero
de segundos remanescentes at� que seja carregada
(se nada for teclado)
a parti��o indicada pelo �ndice "default".
Este �ndice "default" pode ser alterado atrav�s de "edboot" (cmd).
Repare que, se o �ndice "default" for NULO, ele ser� substitu�do pela primeira
parti��o de tipo TROPIX (V7 ou T1) da tabela.

.sp
O "boot0" permite carregar diversos sistemas operacionais,
e j� foi testado com MS-DOS/Win3.1/Win95/Win98/WinNT/Win2000, Linux
e FreeBSD (al�m, naturalmente, do TROPIX).

.sp
Dependendo do �ndice escohido, iremos carregar o TROPIX ou um
outro sistema operacional.
Se for escolhida a continua��o da carga do TROPIX, o "boot0" carrega
o "boot1", contido no in�cio da parti��o ativa escolhida.

.in
.sp
.(t
.b BOOT1
.in 5
O "boot1", por sua vez, aguarda que seja teclado o nome do arquivo
que cont�m o "boot2" (normalmente "/boot", que � o valor "default"
usado se for teclado <enter>).

.sp
Normalmente, o modo de v�deo usado a partir de "boot2" � o "svga"
(113 colunas e 48 linhas, 1024x768).
Isto pode ser modificado para todas as cargas do sistema atrav�s
de "edboot" (cmd), ou apenas para esta carga atrav�s de uma das op��es do "boot1":
"-v" ou "-V" para o modo "vga" (80 colunas e 24 linhas, 720x400) e
"-s" ou "-S" para o modo "svga"

.sp
Durante a carga, se o controlador de v�deo n�o possibilitar o modo
"svga", automaticamente ser� usado o "vga".

.sp
Em seguida, "boot1" le o "boot2" e passa o controle para ele.
.)t

.in
.sp
.b BOOT2
.in 5
A �ltima etapa, o "boot2", permite carregar o arquivo contendo o n�cleo 
do TROPIX, editar as tabelas de parti��es, al�m de outras fun��es.
V�rios comandos de "boot2" iniciam di�logos, pedindo informa��es sobre
o comando a ser executado. Neste caso, a qualquer momento, o comando pode
ser cancelado atrav�s de uma resposta "n".

.bc	/*************************************/
A �ltima etapa, o "boot2", permite escolher o nome do programa que
cont�m o n�cleo do TROPIX (normalmente "/tropix")
e tamb�m o dispositivo no qual ele deve ser procurado (normalmente a primeira
parti��o de tipo TROPIX encontrado durante a an�lise das v�rias parti��es
dos diversos discos). 
Tanto o nome do programa como o dispositivo "default" podem ser alterados
atrav�s de "edboot" (cmd).
.ec	/*************************************/

.in
.sp
.b "EXTENS�ES da INT 13"
.in 5
O "boot0" tenta, automaticamente, utilizar as extens�es da INT 13, e
para discos r�gidos, h� ao total 4 vers�es do "boot1" (veja a lista abaixo).
.sp
Se a BIOS do seu computador suportar estas
extens�es, voc� poder� carregar sistemas operacionais (pelo menos o TROPIX)
em parti��es acima do limite de 8 GB (n�meros de cilindro maiores do que 1024).

.in
.sp
.b 'COMANDOS de "BOOT2"'
.in 5
Os comandos aceitos por "boot2" s�o:

.in +3
.ip "[-x] [-<dev>] [<pgm>]" 3
.sp
Carrega (e executa) <pgm> (normalmente um n�cleo do TROPIX),
contido no dispositivo <dev>.
Tanto <dev> como <pgm> tem valores "defaults", que podem ser alterados
atrav�s de "edboot" (cmd). Se n�o foram alterados, estes valores
"default" s�o "a parti��o usada por boot1" e "/tropix".
.bc	/*************************************/
"a primeira parti��o de tipo TROPIX encontrada" e "/tropix".
.ec	/*************************************/

.sp
Ap�s a carga de <pgm> (e antes de sua execu��o) ainda � pedida uma
confirma��o para a execu��o. No caso de uma resposta negativa, o
"boot2" ret�m o controle, e pode ser executada qualquer uma das fun��es
aqui descritas (inclusive, por exemplo, carregar outro <pgm>.

.ip -t 3
Imprime a tabela de parti��es em uso, com uma linha por parti��o.
A tabela cont�m as seguintes colunas:

.in +5
.ip 1. 3
O nome da parti��o. Durante o funcionamento do TROPIX, cada parti��o � associada a
um dispositivo com o prefixo "/dev/" anteposto ao nome da parti��o.
Assim, por exemplo, a parti��o de nome "hda1" corresponder� ao dispositivo
"/dev/hda1".

.ip 2. 3
Um asterisco se a parti��o est� "ativa", isto �, se � poss�vel carregar
um sistema operacional desta parti��o. Durante o processo de "boot", o
est�gio inicial "boot0" s� considera parti��es "ativas".

.ip 3. 3
N�mero do bloco (de 512 bytes) inicial da parti��o.

.ip 4. 3
Tamanho da parti��o em blocos.

.ip 5. 3
Tamanho da parti��o em MB.

.ip 6. 3
C�digo num�rico do dispositivo associado � parti��o. Este c�digo � composto
de duas partes chamadas de "major" e "minor".

.ip 7. 3
N�mero da unidade e alvo f�sicos do dispositivo.

.ip 8. 3
Nome simb�lico do tipo da parti��o.

.ep
.in -5

.ip -f 3
Executa o editor de tabelas de parti��es "fdisk" (cmd).

.bc	/*************************************/
.ip -l 3
Imprime o conte�do de um diret�rio.
O nome do dispositivo e o nome do diret�rio s�o pedidos atrav�s de um
di�logo.
.ec	/*************************************/

.ip -d 3
Imprime uma listagem em hexadecimal e caracteres de um dispositivo.
O nome do dispositivo e o endere�o inicial s�o pedidos atrav�s de um
di�logo.

.ip -m 3
Imprime uma listagem em hexadecimal e caracteres da mem�ria.
O endere�o inicial � pedido atrav�s de um di�logo.

.ip "-r [-<dev>] [<arq>]" 3
.sp
Descompata  <arq> (normalmente a imagem comprimida de um sistema de arquivos
T1 contendo uma RAIZ), contido no dispositivo <dev> para uma �rea de RAMD.
O dispositivo <dev> tem um valor "default", que � "a parti��o usada por
"boot1", mas pode ser alterado atrav�s de "edboot" (cmd).
O valor "default" de <arq> � "boot.dsk.gz".

.sp
Ap�s esta carga, deve-se utilizar o comando "-x" com o dispositivo "ramd0",
para executar o n�cleo do TROPIX, com a RAIZ no RAMD.

.ip -i 3
Inicia uma instala��o ou conserto de sistemas de arquivos.
� equivalente a "-r -fd0 boot.dsk.gz" seguido de "-x -ramd0 tropix".
Isto decompacta uma imagem comprimida de uma RAIZ de um disquete
para o RAMD, e em seguida executa o TROPIX, com a RAIZ no RAMD.


.bc	/*************************************/
.ip -c 3
Copia um dispositivo ou arquivo regular para um dispositivo.
A c�pia � feita inicialmente para a mem�ria, e desta para o dispositivo de
sa�da.
O nome do dispositivo/arquivo de entrada, deslocamento da entrada,
nome do dispositivo de sa�da, deslocamento da sa�da
e o n�mero de blocos a copiar s�o pedidos atrav�s
de um di�logo.

.ip -r 3
Copia um dispositivo para uma �rea de RAMD.
O nome do dispositivo de entrada � pedido atrav�s de um
di�logo (se n�o for dado, � usado "fd0"). 
� copiado a imagem inteira do dispositivo no final da mem�ria f�sica.
.ec	/*************************************/

.ip -s 3
Reavalia a velocidade da CPU.
Com isto, s�o recalculados a freq��ncia da CPU (MHz) e o valor
adequado para DELAY (a fun��o que permite esperas a n�vel de microsegundos).
Ao final, s�o impressas 10 mensagens com intervalos de um segundo,
para verificar se o valor de DELAY est� correto.

.bc	/*************************************/
.ip -p 3
Imprime os par�metros dos discos IDE.
S�o impressos a geometria real e a utilizada pela BIOS dos discos IDE
(Esta �ltima apenas para os discos do primeiro controlador).
.ec	/*************************************/

.ip -v 3
Verboso.

.ip -? 3
Imprime um resumo dos comandos.

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
edboot, fdisk
.br
.wo "(ref): "
install
.br

.in
.sp
.b ARQUIVOS
.in 5
.(l
/etc/boot/d.boot0		Para testar, em disquete
/etc/boot/h.boot0		Para disco r�gido
/etc/boot/t1.d.boot1	Disquete 1.44 MB, T1
/etc/boot/t1.g.boot1	Disco r�gido, sem as extens�es, T1
/etc/boot/t1.l.boot1	Disco r�gido, com as extens�es, T1
/etc/boot/cd.boot1		Disco compacto (CD)
/etc/boot/v7.d.boot1	Disquete 1.44 MB, V7
/etc/boot/v7.g.boot1	Disco r�gido, sem as extens�es, V7
/etc/boot/v7.l.boot1	Disco r�gido, com as extens�es, V7
/boot			Vers�o �nica de "boot2"
.)l

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
