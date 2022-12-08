.bp
.he 'EDBOOT (cmd)'TROPIX: Manual de Refer�ncia'EDBOOT (cmd)'
.fo 'Atualizado em 29.08.06'Vers�o 4.9.0'Pag. %'

.b NOME
.in 5
.wo "edboot -"
gerencia "boot0", "boot1" e "boot2"
.br

.in
.sp
.b SINTAXE
.in 5
.(l
edboot  -0 [-wfv] [-i <�ndice>] [<dispositivo>]
edboot  -1 [-wfv] [<dispositivo>]
edboot [-2] [-v] [-d <dev>] [-p <pgm>] [-V <v�deo>] [<arquivo>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O processo de carga do sistema operacional TROPIX � composto de
4 etapas: BIOS (em ROM), "boot0", "boot1" e "boot2".

.sp
A BIOS (ap�s diversos testes e inicializa��es), le o primeiro
bloco de um disco (em geral "/dev/hda" ou "/dev/sda") para a mem�ria, e passa o
controle para o programa contido neste bloco.

.sp
Este primeiro bloco cont�m o in�cio de "boot0", que por sua vez
le os seus blocos restantes do disco.
O "boot0" imprime uma tabela com as parti��es ativas dos diversos
discos encontrados no sistema, e pede o �ndice da parti��o desejado
para prosseguir o procedimento de carga.

.sp
� impresso tamb�m o
�ndice "default" (valor por omiss�o), que ser� utilizado se
for teclado apenas <nl> ou se for decorrido um certo tempo
(da ordem de dezenas de segundos) sem que seja teclado algo.

.sp
O "boot0" permite carregar diversos sistemas operacionais,
e j� foi testado com MS-DOS, Win3.1, Win95, Win98, WinNT, Win2000, WinXP, Linux
e FreeBSD (al�m, naturalmente, do TROPIX).

.sp
Dependendo do �ndice escohido, iremos carregar o TROPIX ou um
outro sistema operacional.
O programa "edboot" permite imprimir o valor
do �ndice "default" atual ou alter�-lo (veja a op��o "-i" abaixo).

.sp
Se for escolhido a continua��o da carga do TROPIX, o "boot0" carrega
o "boot1", que aguarda o nome do "boot2" (normalmente "boot").

.sp
A �ltima etapa, o "boot2", permite escolher o nome do programa que
cont�m o n�cleo do TROPIX (normalmente "tropix")
e tamb�m o dispositivo no qual ele deve ser procurado
(normalmente o mesmo dispositivo de onde foi lido "boot1").
.bc	/*************************************/
(normalmente a primeira
parti��o de tipo TROPIX encontrado durante a an�lise das v�rias parti��es
dos diversos discos).
.ec	/*************************************/
Tanto o nome do programa como o dispositivo podem ser consultados e/ou
modifica��es atrav�s de "edboot" (veja as op��es "-d" e "-p" abaixo).

.sp
Normalmente "edboot" procura o "boot0" em "/dev/hda" e "/dev/sda",
o "boot1" em "/dev/root" e o "boot2" em "/boot".
Os argumentos <dispositivo>/<arquivo> permitem alterar isto.

.sp
Sem op��es, o programa "edboot" imprime o nome do
programa (n�cleo do TROPIX) e dispositivo contidos em "/boot".

.sp
Nesta vers�o, os diversos programas de "boot" tentam fornecer para a
etapa seguinte qual foi o dispositivo do qual foram lidos.
O objetivo consiste em escolher um dispositivo durante a segunda etapa
("boot0"), e este mesmo dispositivo ser usado para a leitura de "boot1",
"boot2", o n�cleo do TROPIX e finalmente ser usado como sistema de arquivos
RAIZ do sistema operacional.

.sp
As op��es do comando s�o:

.bc	/*************************************/
edboot - gerencia "boot0", "boot1" e "boot2"

Vers�o:	4.9.0, de 29.08.06

Sintaxe:
	edboot  -0 [-wfv] [-i <�ndice>] [<dispositivo>]
	edboot  -1 [-wfv] [<dispositivo>]
	edboot [-2] [-v] [-d <dev>] [-p <pgm>] [-V <v�deo>] [<arquivo>]

Op��es:	-0: Instala/consulta/modifica o "boot0"
	-1: Instala/consulta o "boot1"
	-2: Consulta/modifica o "boot2"
	-w: Instala o "boot0"/"boot1" no <dispositivo>
	-f: Instala/modifica sem consultar o usu�rio
	-v: Verboso
	-i: A parti��o "default" do "boot0" ser� <�ndice>
	-d: O dispositivo "default" do "boot2" ser� <dev>
	-p: O programa "default" a executar do "boot2" ser� <pgm>
	-V: Usa o modo de <v�deo> dado no "boot2" (25x80, 113x48)

Obs.:	Sem op��es nem argumentos, s�o impressos os parametros de "/boot"
.ec	/*************************************/


.in +3
.ip -0
Instala/consulta/modifica "boot0".
Sem as op��es "-w" nem "-i", � dado o �ndice da parti��o "default" contido em "boot0".

.sp
Al�m disto, verifica se a vers�o instalada � a atual (contida no diret�rio "/etc/boot").

.ip -1
Instala/consulta o "boot1".
Sem a op��o "-w", verifica se a vers�o instalada � a atual (contida no diret�rio "/etc/boot").

.ip -2
Consulta/modifica "boot2" (op��o impl�cita).
Sem as op��es "-d", "-V" nem "-p", s�o dados o dispositivo e programa "default"s contidos em "boot2".

.ip -w
Instala o "boot0"/"boot1" no <dispositivo> dado.

.sp
O programa "boot0" � constru�do a partir do arquivo "/etc/boot/h.boot0"
e a tabela de parti��es existente no bloco 0 do <dispositivo>.
O bloco 0 original do <dispositivo> � guardado no arquivo "/etc/boot/mbr".

.sp
Se o "boot0" n�o funcionar adequadamente, o bloco 0 original deve ser novamente
recolocado atrav�s do comando

.sp
.nf
		cat /etc/boot/mbr ><dispositivo>
.fi

.sp
e a carga do TROPIX dever� ser feita atrav�s de disquete.

.sp
O programa "boot1" � obtido a partir do arquivo
"/etc/boot/t1.l.boot1", "/etc/boot/t1.g.boot1",
"/etc/boot/v7.l.boot1" ou "/etc/boot/v7.g.boot1",
de acordo com o tipo do sistema de arquivo (T1 ou V7)
e se o dispositivo suporta as extens�es da INT 13 da BIOS ou n�o.

.ip -f
N�o pede a confirma��o do usu�rio antes de instalar
o "boot0"/"boot1".

.ip -v
Verboso. Imprime outras informa��es, tais como as vers�es dos
programas.

.ip -i
Atribui o valor <�ndice> para a parti��o "default" do "boot0".
Se este valor for NULO, a parti��o "default" do "boot0"
ser� a primeira parti��o do tipo TROPIX (T1 ou V7) encontrado na tabela.

.ip -d
Atribui <dev> como o dispositivo "default" de "boot2".
O valor "NODEV" (ou "nodev") � interpretado como o dispositivo
usado para a leitura do "boot1", ou (na aus�ncia desta informa��o)
como a primeira parti��o de tipo TROPIX encontrada durante
a an�lise das v�rias parti��es dos diversos discos.

.ip -p
Atribui <pgm> como o programa "default" de "boot2".

.ip -V
Atribui <v�deo> como o modo de v�deo do "boot2". Podem ser dados os valores
"25x80" (ou "vga") para o modo 720x400 (normal) ou
"113x48" (ou "svga") para o modo 1024x768.
Durante a carga, se o controlador de v�deo n�o possibilitar o modo
"svga", automaticamente ser� usado o "vga".

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
boot, fdisk
.br
.wo "(ref): "
install
.br

.in
.sp
.b ARQUIVOS
.in 5
.(l
/dev/hd?
/dev/sd?
/dev/root
/etc/boot/d.boot0		Para testar, em disquete
/etc/boot/h.boot0		Para disco r�gido
/etc/boot/t1.d.boot1	Disquete 1.44 MB, T1
/etc/boot/t1.g.boot1	Disco r�gido, sem as extens�es, T1
/etc/boot/t1.l.boot1	Disco r�gido, com as extens�es, T1
/etc/boot/v7.d.boot1	Disquete 1.44 MB, V7
/etc/boot/v7.g.boot1	Disco r�gido, sem as extens�es, V7
/etc/boot/v7.l.boot1	Disco r�gido, com as extens�es, V7
/etc/boot/mbr		C�pia do primeiro setor do disco
				principal ("/dev/hda" ou "/dev/sda")
/boot			Vers�o �nica de "boot2"
.)l

.in
.sp
.b EXEMPLOS
.in 5
A execu��o de 
.nf

		edboot -0 -w

.fi
ir� instalar o "boot0" nos setores iniciais de "/dev/hda" (ou "/dev/sda").

.sp
A execu��o de 
.nf

		edboot -0 -i 3 /dev/sda

.fi
ir� alterar para 3 o �ndice do  "boot0"
contido no disco SCSI "/dev/sda".

.sp
A execu��o de 
.nf

		edboot -1 -v /dev/aroot

.fi
informa se a vers�o de "boot1" contida no primeiro bloco de "/dev/aroot" � a atual.

.sp
.(t
A execu��o de 
.nf

		edboot -2 -p new.tropix /new.boot

.fi
.)t
ir� alterar para "new.tropix" o n�cleo "default" do "boot2"
alternativo "/new.boot".

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
