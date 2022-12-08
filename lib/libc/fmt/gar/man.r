.bp
.he 'GAR (fmt)'TROPIX: Manual de Refer�ncia'GAR (fmt)'
.fo 'Atualizado em 28.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "gar -"
formato das cole��es GAR
.br

.in
.sp
.b DESCRI��O
.in 5
O utilit�rio "gar" (cmd) processa habitualmente cole��es em seu
formato nativo, o formato GAR. Este texto descreve este formato. 

.sp
Uma cole��o no formato GAR tem uma s�rie de cabe�alhos (e outras
informa��es) intercaladas entre os conte�dos dos arquivos;
todos estes cabe�alhos s�o em ISO (isto �, n�o cont�m
n�meros em forma bin�ria), o que facilita o transporte para
outros computadores (que possivelmente tem ordena��o
diferente dos bytes dentro das palavras). 

.sp
As diversas partes da cole��o s�o cont�guas, isto �,
o formato n�o prev� nenhum byte de alinhamento:
qualquer cabe�alho ou conte�do pode estar posicionado
em qualquer endere�o (isto �, dist�ncia em bytes do in�cio)
do volume, inclusive �mpar.

.sp
Repare que n�o temos um cabe�alho de final de volume;
isto � indicado pelo final f�sico do volume (final da fita
magn�tica, ou do disquete).

.sp
Todos os n�meros s�o codificados como sequ�ncias de  d�gitos decimais.  
Todos os bytes n�o utilizados s�o preenchidos com <sp>, a n�o
ser o byte seguinte ao valor dos CRCs, que � preenchido com <nul>.
Todas as datas s�o codificadas na forma padr�o do TROPIX,
isto �, em segundos desde 00:00 de 1.1.1970 GMT. 

.sp
Todos os CRCs s�o calculados pelo polin�mio padr�o da CCITT
(ver "crc16" (libc)). Embora "gar" (cmd) gere/verifique todos os
CRCs, um outro utilit�rio particular n�o tem necessariamente de
fazer esta verifica��o para ler cole��es GAR em um outro computador.

.sp 2
.b "Cabe�alho de Volume:"

.sp
Uma cole��o pode se estender a um ou mais
volumes; cada volume cont�m no in�cio um cabe�alho de volume,
que tem o formato
da seguinte estrutura:

.sp 1
.nf
	typedef	struct
	{
		char	g_magic[12];	/* Cadeia m�gica */
		char	g_date[12];	/* Data de cria��o */
		char	g_vol[6];	/* No. do Volume */
		char	g_version[9];	/* Vers�o do GAR */
		char	g_vres[13];	/* Reservado */
		char	g_vcrc[8];	/* CRC */
	
	}	GVOL;
.fi
.sp 2

O valor da cadeia m�gica � "GAR VOLUME".

.sp
A data de cria��o � a da cole��o.

.sp
O n�mero do volume come�a de 0 e � incrementado de 1 para cada
novo volume de continua��o.

.sp
No volume 0, o cabe�alho do volume � seguido do cabe�alho do
primeiro arquivo da cole��o; nos volumes seguintes � seguido
da continua��o do conte�do da cole��o, que pode ter
sido seccionado em um ponto qualquer. 

.sp 3
.b "Cabe�alho de Arquivo:"

.sp
Uma cole��o pode ter um n�mero indefinido de arquivos;
o final da cole��o � indicado por um cabe�alho de final
de cole��o (ver adiante).
Cada arquivo cont�m no in�cio um cabe�alho de arquivo,
que tem o formato da seguinte estrutura:

.sp 2
.nf
	typedef	struct
	{
		char	g_magic[12];	/* Cadeia magica */
		char	g_dev[6];	/* Dispositivo */
		char	g_ino[6];	/* No. do Inode */
		char	g_mode[12];	/* Modo do arquivo */
		char	g_nlink[6];	/* No. de Links */
		char	g_uid[6];	/* Dono */
		char	g_gid[6];	/* Grupo */
		char	g_rdev[6];	/* Dispositivo Especial */
		char	g_size[12];	/* Tamanho */
		char	g_atime[12];	/* tempo de acesso */
		char	g_mtime[12];	/* tempo de modifica��o */
		char	g_ctime[12];	/* tempo de cria��o */
		char	g_namesz[6];	/* Tamanho do nome */
		char	g_linkflag[2];	/* Este nome � um Link */
		char	g_origsz[12];	/* Tamanho original */
		char	g_bits[3];	/* Bits (L), n�vel (Z) */
		char	g_compcrc[2];	/* Compress�o com CRC */
		char	g_method[3];	/* "C" (LZW), "D" (ZIP) */
		char	g_res[16];	/* Reservado */
		char	g_crc[8];	/* CRC */

	}	GHEAD;
.fi

.sp 2
O valor da cadeia m�gica � "GAR HEADER", a n�o ser
se trate de um "link" (ver adiante).

.sp
Os valores de "dev", "ino", "mode", "nlink", "uid", "gid", "rdev",
"atime", "mtime", e "ctime" s�o as informa��es habituais
sobre o arquivo, que s�o obtidas atrav�s de "stat" (sys).  

.sp
O se o arquivo estiver comprimido, o campo "size" cont�m o tamanho
do arquivo e o campo "origsz" cont�m zero; em caso contr�rio,
"size" cont�m o tamanho comprimido e "origsz" o tamanho real do
arquivo.

.sp
O campo "g_linkflag" cont�m um <sp> a n�o ser que se trate de
um "link", caso no qual cont�m um "*".

.sp
Se o arquivo estiver comprimido, o campo "bits" cont�m o n�mero
m�ximo de bits utilizado (m�todo LZW) ou o n�vel de compress�o
usado (m�todo ZIP (defla��o)), o campo "compcrc" cont�m "R" se
� usado um CRC adicional antes de comprimir o arquivo e o campo
"method" cont�m "C" para o m�todo LSW e "D0" para o m�todo ZIP.

Se o arquivo N�O estiver comprimido, estes campos n�o s�o usados.

.sp 3
.b "Nome de Arquivo:"

.sp
Ap�s este cabe�alho segue o nome do arquivo com o seu respectivo
CRC, com o formato da estrutura abaixo:  

.sp 2
.nf
	typedef	struct
	{
		char	g_name[size];	/* Nome do arquivo */
		char	g_crc[8];	/* CRC */

	}	GNAME;
.fi

.sp 2
O tamanho do nome "size" � obtido atrav�s de "namesz" do cabe�alho.

.sp 3
.b "Conte�do do Arquivo:"

.sp
Em seguida, se o arquivo for regular, temos o conte�do do arquivo
(a n�o ser que se trate de
um "link" - ver adiante).
Cada bloco do arquivo tem o formato da estrutura dada abaixo, exceto
o bloco final, que pode ter menos de 512 bytes.

.sp 2
.nf
	typedef	struct
	{
		char	g_block[512];	/* Bloco do arquivo */
		char	g_crc[8];	/* CRC */

	}	GBLOCK;
.fi

.sp 3
.(t
.b "Arquivo \"link\"ado:"

.sp
Se o arquivo � um "link" de um arquivo anterior, 
n�o temos o conte�do do arquivo; ao nome do arquivo segue-se
outro cabe�alho de arquivo com a cadeia m�gica "GAR LINK",
e outro nome de arquivo, conforme as respectivas partes.
A grande parte das informa��es deste segundo cabe�alho
� ignorada, pois importa apenas o nome do "link".
.)t

.sp
.(t
.in 5
Resumindo, temos a seguinte sequ�ncia para arquivos regulares:

.sp
.nf
	+---------------+-------+-------------------------------+
	|		|	|				|
	|   cabe�alho	| nome	|      c o n t e � d o		|
	|   de arquivo	|	|				|
	|		|	|				|
	+---------------+-------+-------------------------------+
.fi
.)t

.sp 2
.(t
.in 5
Para arquivos n�o regulares:

.sp
.nf
	+---------------+-------+
	|		|	|
	|   cabe�alho	| nome	|
	|   de arquivo	|	|
	|		|	|
	+---------------+-------+
.fi
.)t
.sp 2

.(t
.in 5
Para "link" de arquivos (regulares ou n�o):
.sp

.nf
	+---------------+-------+---------------+-------+
	|		|	|		|	|
	|   cabe�alho	| nome	|   cabe�alho	| nome	|
	|   de arquivo	|	|   de "link"	|	|
	|		|	|		|	|
	+---------------+-------+---------------+-------+
.fi
.)t
.sp 2

.b "Cabe�alho de Final de Cole��o:"
.sp
O final da cole��o � indicada por um cabe�alho de final de cole��o,
que � simplesmente a cadeia "GAR TRAILER". O restante do bloco
da cole��o � preenchido com <sp>.

.in
.sp

.b
OBSERVA��O
.r
.in 5
N�o confunda "final de volume" com "final de cole��o".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
gar
.br
.wo "(sys): "
stat
.br
.wo "(libc):"
crc16
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
