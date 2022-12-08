.bp
.he 'TERMIO (fmt)'TROPIX: Manual de Refer�ncia'TERMIO (fmt)'
.fo 'Atualizado em 29.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "termio -"
interface geral de linhas de comuni��o
.br

.in
.sp
.b DESCRI��O
.in 5
Todas as linhas de comunica��o ass�ncronas
(usadas usualmente para terminais ou impressoras;
neste texto, terminal ser� usado como sin�nimo de linha de comunica��o)
usam a mesma interface,
independente dos dispositivos utilizados. Este texto descreve as
caracter�sticas comuns desta interface.

.sp
Um terminal pode ser aberto diretamente por um processo de usu�rio,
mas em geral o terminal � aberto pelo utilit�rio especial "init",
e ele se torna a entrada e sa�da padr�o e a sa�da de erro do processo. 
O primeiro terminal aberto por um processo ainda n�o associado
a um terminal se torna o "terminal de controle" do grupo de processos
formado pelo processo e seus descendentes
(ver "grupo de terminais" em "intro" (sys)).
Um terminal de controle desempenha um papel importante no tratamento
dos sinais "SIGINT" e "SIGQUIT", como descrito abaixo.

.sp
Um terminal associado a um destes arquivos opera normalmente
no modo "full-duplex". Caracteres podem ser teclados a qualquer
tempo, mesmo quando est� havendo sa�da no terminal, e somente
s�o perdidos se a �rea de entrada do sistema encher totalmente,
o que � raro, ou quando foi alcan�ado o
n�mero m�ximo de caracteres de entrada
ainda n�o lidos por nenhum processo.
Atualmente este limite � de 1124 caracteres. Quando este
limite � atingido,
a �rea � liberada, todos os caracteres s�o perdidos.

.sp
Normalmente, a entrada de terminais � processada em unidades de
linhas. Uma linha � delimitada por um <nl> ou um caractere
"eof" (normalmente <^D>, ver caracteres de controle).
Isto significa que um processo tentando ler ser� suspenso
at� que uma linha completa seja teclada. Portanto, independente
do n�mero de caracteres pedidos na leitura, no m�ximo uma
linha ser� devolvida. No entanto, n�o � necess�rio ler
a linha inteira de uma vez; qualquer n�mero de caracteres
pode ser pedido em uma leitura, mesmo apenas um, sem perda
de informa��o.

.sp
Durante a entrada, normalmente se realiza o processamento
dos caracteres "erase", "aerase" e "kill".
Os caracteres "erase" e "aerase", cujos valores normais
s�o <del> e <bs> apagam o �ltimo caractere teclado,
desde que haja pelo menos um caractere na linha.
O caractere "kill", cujo valor normal � <^U> apaga
a linha inteira.

.sp
Alguns caracteres t�m fun��o especial na entrada. As fun��es
e seus valores normais s�o dados a seguir:

.in +3
.ip "intr" 8
Este caractere gera um sinal de interrup��o ("SIGINT"), 
que � enviado a todos os processos associados ao terminal
de controle. Normalmente, estes processos terminam
ao receber este sinal, mas eles podem utilizar a chamada
ao sistema "signal" (sys) para ignor�-lo ou intercept�-lo.
O valor inicial deste caractere � <^C>. 

.ip "quit" 8
Este caractere gera um sinal de "quit" ("SIGQUIT"), 
que � enviado a todos os processos associados ao terminal
de controle. Normalmente, estes processos terminam com a grava��o
da imagem do processo no disco ("core-dump")
ao receber este sinal, mas eles podem utilizar a chamada
ao sistema "signal" (sys) para ignor�-lo ou intercept�-lo.
O valor inicial deste caractere � <^X>. 

.ip "switch" 8
O sistema operacional n�o trata este caractere;
ele est� reservado para as rotinas de gerenciamento de janelas
de terminais.
O valor inicial deste caractere � <nul>.

.ip "erase" 8
Este caractere apaga o caractere anterior; se estivermos
no come�o de uma linha, nada faz.
O valor inicial deste caractere � <del> ("^*"). 

.ip "aerase" 8
Este caractere � an�logo ao "erase":
apaga o caractere anterior; se estivermos
no come�o de uma linha, nada faz.
O valor inicial deste caractere � <bs>.

.ip "kill" 8
Este caractere apaga a linha inteira.
O valor inicial deste caractere � <^U>.

.ip "eof" 8
Este caractere pode ser usado para gerar uma condi��o de 
fim de arquivo ("EOF") do terminal. Quando recebido, todos os
caracteres da fila de entrada s�o passados imediatamente para
o programa, sem esperar um <nl>, e o caractere � ignorado.
Se n�o havia nenhum caractere na fila, zero caracteres s�o
passados para o programa, o que � a indica��o padr�o
de EOF. 
O valor inicial deste caractere � <^D>.

.ip "min" 8
Este valor s� � utilizado nos modos "raw" e "comm",
e representa o n�mero m�nimo de caracteres
necess�rios na fila de entrada para que eles sejam passados
para o processo. Em outras palavras, o processo espera
at� que a fila de entrada contenha "n" caracteres.  
O valor inicial deste par�metro � 1.

.ip "eol" 8
Este caractere � um delimitador adicional (como <nl>).
N�o � utilizado normalmente, e no momento n�o est� implementado.
O valor inicial deste par�metro � <nul>.

.ip "time" 8
Este valor s� � utilizado nos modos "raw" e "comm",
e representa um tempo utilizado para medir o tempo decorrido
para receber "min" caracteres.
No momento n�o est� implementado.
O valor inicial deste par�metro � 0.

.ip "res" 8
Este caractere no momento n�o t�m fun��o; est� reservado
para uso futuro.
O valor inicial deste par�metro � <nul>.

.ip "stop" 8
A fun��o deste caractere � de suspender temporariamente
a sa�da no terminal,
para evitar que a sa�da
desapare�a da tela antes que possa ser lida.
O valor deste caractere � <^S>, e n�o pode ser mudado.

.ip "start" 8
� utilizado para reiniciar a sa�da que foi suspensa por um
caractere "stop" ou foi alcan�ado o limite de linhas
de "page".
O valor deste caractere � <^Q>, e n�o pode ser mudado.

.ip "page" 8
Este valor representa o n�mero de linhas ap�s o qual a sa�da
no terminal p�ra, aguardando um "start" (ou um caractere qualquer,
veja "ixany").
Isto � �til em terminais de v�deo para evitar que a sa�da
desapare�a da tela antes que possa ser lida.
Fazendo "n" igual a zero, o controle n�o � realizado.
O valor inicial deste caractere de controle � 22.

.ip "retype" 8
Este caractere reimprime o a linha no terminal.
� �til quando a linha sendo teclada � misturada com
mensagens de processos executando em "back-ground".
O valor inicial deste caractere � <^R>.

.ip "word" 8
Este caractere apaga a �ltima palavra teclada.
Uma palavra � definida como sendo um conjunto de caracteres
que n�o contenham <sp> nem <ht>.
O valor inicial deste caractere � <^W>.

.ip "color" 8
Este caractere define as cores de frente e fundo dos terminais
coloridos (para terminais monocrom�ticos n�o tem fun��o).
O valor inicial (ou seja, as cores iniciais) variam de
acordo com o terminal.

.ip "nline" 8
Este caractere define o n�mero de linhas do terminal.
O valor inicial � 24.

.ip "ncol" 8
Este caractere define o n�mero de colunas do terminal.
O valor inicial � 80.

.in -3
.ep

.sp
.in 5
Normalmente, os caracteres de entrada s�o ecoados colocando-os
na fila de sa�da assim que s�o recebidos.
Se o um processo produz caracteres mais rapidamente do que
podem ser escritos no terminal, o processo � suspenso quando
a fila de sa�da excede certo limite. Quando a fila esvaziou
abaixo de certo valor, o processo retoma a sua execu��o. 

.sp
Diversos comandos da chamada ao sistema "ioctl" (sys) se aplicam
a terminais. Normalmente estes comandos utilizam a estrutura
dada abaixo, definida em <termio.h>:

.(t
.sp
.nf
	#define	NCC	15	/* No. de Carac. de Controle */

	typedef struct termio	TERMIO;

	struct	termio
	{
		ushort	c_iflag;	/* Modos de Entrada */
		ushort	c_oflag;	/* Modos de Saida */
		ushort	c_cflag;	/* Modos de Controle */
		ushort	c_lflag;	/* Modos locais */
		uchar	c_line;		/* Disciplina da Linha */
		uchar	c_cc[NCC];	/* Caracteres de Controle */
		char	c_name[16]; 	/* Nome da Linha */
		uchar	c_wc[4];	/* Controle da janela */
		long	c_res[4];	/* Reser. p/ uso Futuro */
	};
.fi
.)t

.sp 2
Os caracteres de controle est�o definidos nos vetores "c_cc" e "c_wc".
A posi��o relativa e valor inicial de cada caractere s�o os seguintes:

.sp
.nf
		0	VINTR		<^C>
		1	VQUIT		<^X>
		2	VERASE		<del>
		3	VKILL		<^U>
		4	VEOF		<^D>
		5	VMIN		1
		6	VEOL		<nul>
		7	VTIME		0
		8	VRES		0
		9	SWTCH		0
		10	VPAGE		22
		11	VAERASE		<bs>
		12	VRETYPE		<^R>
		13	VWORD		<^W>
		14	VCOLOR		(vari�vel)

		0	VNLINE		24
		1	VNCOL		80
.fi
.sp 2
O campo "c_iflag" descreve os modos de entrada do terminal:

.sp
.nf
	IGNBRK	0x0001	Ignore a Condicao de BREAK
	BRKINT	0x0002	Sinalize uma interrupcao no caso de BREAK
	IGNPAR	0x0004	Ignorar Caracteres com erro de Paridade
	PARMRK	0x0008	Marcar Erros de Paridade
	INPCK	0x0010	Habilitar Paridade na Entrada
	ISTRIP	0x0020	Mascara o Oitavo Bit
	INLCR	0x0040	Mapeie <nl> em <cr> na entrada
	IGNCR	0x0080	Ignore <cr>s
	ICRNL	0x0100	Mapeie <cr> em <nl>
	IUCLC	0x0200	Mapeie Maiusculas em minusculas
	IXON	0x0400	Habilite XON/XOFF na Saida
	IXANY	0x0800	Qualquer caracter recomeca a saida
	IXOFF	0x1000	Habilite XON/XOFF na Entrada
.fi

.sp
Se IGNBRK est� ligado, a condi��o de "break" (um erro de formato
de caractere com todos os bites em zero) � ignorado; em caso
contr�rio, se tamb�m BRKINT est� ligado, a condi��o de "break"
gera um sinal "SIGINT", e esvazia as filas de entrada
e de sa�da. Se IGNPAR est� ligado, caracteres com outros erros
de formato e de paridade s�o ignorados.

.sp
Se PARMRK est� ligado, um caractere com erro de formato ou
de paridade que n�o � ignorado, � lido como a seq�encia de
3 caracteres: <del>, "0", "x", onde "x" � o valor do caractere
recebido com erro. Para evitar ambiguidade neste caso,
um caractere v�lido <del> � lido como <del>, <del>.
Se PARMRK est� desligado, um erro de paridade ou de formato
que n�o � ignorado, � lido como o caractere <nul>.

.sp
Se INPCK est� ligado, a verifica��o de paridade da entrada 
� habilitada; em caso contr�rio a verifica��o � desabilitada.
Isto permite a gera��o de paridade na sa�da sem verifica��o
na entrada.

.sp
Se ISTRIP est� ligado, os caracteres de entradas t�m o seu
oitavo bit (de mais alta ordem) apagado; em caso contr�rio
os oito bites s�o processados. 

.sp
Se INCLR est� ligado, um caractere <nl> � convertido em
<cr>; se IGNCR est� ligado, um <nl> � ignorado; em caso
contr�rio, se ICRNL est� ligado, um <cr> � convertido
em <nl>.

.sp
Se IUCLC est� ligado, uma letra mai�scula � convertida na
letra min�scula correspondente.

.sp
Se IXON est� ligado, o controle de "start/stop" da sa�da
� habilitado. Um caractere de entrada "stop" (<^S>) suspende a s�ida
e um caractere "start" (<^Q>) a reinicia. Todos os caracteres
de "start/stop" s�o ignorados para efeito de leitura.  
Se IXANY estiver ligado, qualquer caractere de entrada ir�
reiniciar a sa�da.

.sp
Se IXOFF est� ligado, o sistema transmite caracteres de "start/stop"
quando a fila de entrada est� quase vazia/cheia.


.sp 2
O campo "c_oflag" descreve os modos de sa�da do terminal:
.sp
.nf
	OPOST	0x0001	Processe a Saida (sa�da "cooked")
	OLCUC	0x0002	Mapeie Minusculo em Maiusculo
	ONLCR	0x0004	Mapeie <nl> em <cr><nl>
	OCRNL	0x0008	Mapeie <cr> em <nl>
	ONOCR	0x0010	Evite <cr> na Coluna 0
	ONLRET	0x0020	NL executa a funcao de <cr>
	OFILL	0x0040	Use caracteres de enchimento para atrasos
	OFDEL	0x0080	O enchimento � <del>, em caso cont. <nul>
	NLDLY	0x0100	Atrasos do <nl>:
	NL0	0x0000	Tipo 0
	NL1	0x0100	Tipo 1
	CRDLY	0x0600	Atrasos do <cr>:
	CR0	0x0000	Tipo 0
	CR1	0x0200	Tipo 1
	CR2	0x0400	Tipo 2
	CR3	0x0600	Tipo 3
	TABDLY	0x1800	Atrasos do <ht>:
	TAB0	0x0000	Tipo 0
	TAB1	0x0800	Tipo 1
	TAB2	0x1000	Tipo 2
	TAB3	0x1800	Tipo 3: Converta em brancos
	BSDLY	0x2000	Atrasos do <bs>: 
	BS0	0x0000	Tipo 0
	BS1	0x2000	Tipo 1
	VTDLY	0x4000	Atraso do <vt>:
	VT0	0x0000	Tipo 0
	VT1	0x4000	Tipo 1
	FFDLY	0x8000	Atraso do <ff>:
	FF0	0x0000	Tipo 0
	FF1	0x8000	Tipo 1
.fi

.sp
Se OPOST est� ligado, os caracteres de sa�da s�o processados,
de acordo com os indicadores abaixo; em caso contr�rio,
s�o transmitidos sem modifica��o.

.sp
Se OLCUC est� ligado, uma letra min�scula � convertida na
letra mai�scula correspondente. Esta fun��o em geral �
utilizada conjuntamente com IUCLC.

.sp
Se ONLCR est� ligado, o caractere <nl> � transmitido como o
par <cr><nl>. Se OCRNL est� ligado, <cr> � transmitido como
<nl>. Se ONOCR est� ligado, o <cr> n�o � transmitido
no come�o da linha. Se ONLRET est� ligado, assume-se que o caractere <nl>
realiza a fun��o de <cr>; o ponteiro da coluna � zerado,
e ser�o usados os atrasos especificados para o <cr>;
em caso contr�rio, o ponteiro de coluna permanecer� no lugar.
Este ponteiro tamb�m volta para a coluna zero se o <cr>
� realmente transmitido.

.sp
Os bites de atrasos especificam o tempo de interrup��o da
transmiss�o para permitir movimentos mec�nicos quando certos
caracteres s�o transmitidos para o terminal. Em todos os casos,
um valor de 0 indica "sem atraso". Se OFILL est� ligado,
caracteres de enchimento s�o transmitidos para realizar a fun��o
do atraso; isto � �til para terminais de grande velocidade
em que apenas s�o necess�rios atrasos m�nimos. Se OFDEL
est� ligado, o caractere de enchimento � <del>, em caso
contr�rio <nul>. As fun��es de atrasos n�o est�o
implementadas; a �nica fun��o dispon�vel � a TAB3,
com a qual <ht> � convertido no n�mero apropriado de brancos.

.sp 2
O campo "c_cflag" descreve os modos de controle do terminal:
.sp
.nf
	CBAUD	0x000F	Velocidade da Linha:
	B0	0x0000	Desconecte
	B50	0x0001	50 Baud
	B75	0x0002	75 Baud
	B110	0x0003	110 Baud
	B134	0x0004	134.5 Baud
	B150	0x0005	150 Baud
	B200	0x0006	200 Baud
	B300	0x0007	300 Baud
	B600	0x0008	600 Baud
	B1200	0x0009	1200 Baud
	B1800	0x000A	1800 Baud
	B2400	0x000B	2400 Baud
	B4800	0x000C	4800 Baud
	B9600	0x000D	9600 Baud
	B19200	0x000E	19200 Baud
	B38400	0x000F	38400 Baud
	CSIZE	0x0030	Tamanho do Caracter:
	CS5	0x0000	5 Bits
	CS6	0x0010	6 Bits
	CS7	0x0020	7 Bits
	CS8	0x0030	8 Bits
	CSTOPB	0x0040	Envie 2 Bits de Stop, em caso contrario 1
	CREAD	0x0080	Habilite a Leitura
	PARENB	0x0100	Habilite a Paridade
	PARODD	0x0200	Paridade Impar, em caso contrario par
	HUPCL	0x0400	Desconecte no ultimo close
	CLOCAL	0x0800	Linha local, em caso contrario discada
	LOBLK	0x1000	Block layer Output
.fi

.sp
Os bites CBAUD especificam a velocidade do terminal. A velocidade
nula, B0 � utilizada para desfazer a conec��o.
Nem todos os dispositivos aceitam todas as velocidades;
mudan�as para velocidades inv�lidas s�o ignoradas.
.sp

Os bites CSIZE especificam o tamanho do caractere (em bites) para
transmiss�o e recep��o. Este tamanho n�o inclui o (poss�vel)
bit de
paridade. Se CSTOB est� ligado, 2 bites de "stop" s�o utilizados;
em caso contr�rio � utilizado apenas um.

.sp
Se PARENB est� ligado, gera��o e dete��o de paridade � habilitada,
e um bite de paridade � acrescentado a cada caractere. Se ela
est� habilitada, o bite PARODD especifica paridade �mpar; em caso
contr�rio paridade par.

.sp
Se CREAD est� ligado, o receptor est� habilitado; em caso contr�rio
n�o h� recep��o de caracteres.

.sp
Se HUPCL est� ligado, a linha � desconectada quando o �ltimo
processo fecha a linha ou termina.

.sp
Se CLOCAL est� ligado, a linha � considerada local, isto �,
sem modem; em caso contr�rio � assumido que cont�m um modem.

.sp
Se LOBLK est� ligado, a sa�da de um n�vel de controle
de "job"s ser� bloqueado quando este n�o � o n�vel corrente;
em caso contr�rio, a sa�da gerada por aquele n�vel ser�
multiplexado no n�vel corrente. 


.sp 2
O campo "c_lflag" descreve os modos locais do terminal:
.sp
.nf
	ISIG	0x0001	Habilite Sinais
	ICANON	0x0002	Processe a Entrada (entrada "cooked")
	XCASE	0x0004	Processamento de Maiu/Min com '\'
	ECHO	0x0008	Habilite o eco
	ECHOE	0x0010	Ecoe "erase" como <bs><sp><bs>
	ECHOK	0x0020	Ecoe <nl> apos "kill"
	ECHONL	0x0040	Ecoe <nl>
	NOFLSH	0x0080	Deshabilite "flush" apos inter. ou quit

	ISOKEY	0x0200  Teclado ISO
	CODE	0x0C00	Codigo de Caracteres:
	ISO	0x0000	 ISO
	ASCII	0x0400	 ASCII
	USER1	0x0800	 USER1
	USER2	0x0C00	 USER2 
	CNTRLX	0x1000	Caracteres de controle na forma '^X'
	VIDEO	0x2000	O terminal e' de Video
	ICOMM	0x8000	Modo de comunica��es na entrada
.fi

.sp
Se ISIG est� ligado, cada caractere de entrada � comparado com os
caracteres de controle "intr" e "quit". Se o caractere confere,
a fun��o associada a �le � executada; caso contr�rio n�o �
(ver ICOMM).

.sp
se ICANON est� ligado, o processamento dos caracteres de entrada
� realizado. Isto habilita as fun��es de "erase" e "kill",
e a montagem de caracteres de entrada em linhas delimitadas
por <nl> e "eof". Se ICANON n�o est� ligado, as leituras s�o
realizadas diretamente da fila de entrada
(ver ICOMM).

.sp
Se XCASE est� ligado, e ICANON est� ligado, uma letra ma�uscula
� aceita na entrada precedendo-a pelo caractere "\", e � colocada
na sa�da na mesma forma. Neste modo, as seguintes sequ�ncias
s�o geradas na sa�da e aceitas na entrada:

.sp
.(t
.nf
	  ao inv�s de:	     utilize:

		`		\`
		|		\!
		~		\^
		{		\(
		}		\)
		\		\\
.fi
.)t

.sp
Se ECHO estiver ligado, os caracteres s�o ecoados assim que
recebidos.

.sp
Quando ICANON est� ligado, as seguintes fun��es de eco s�o poss�veis:
Se ECHOE est� ligado, 
ecoa "erase" como <bs><sp><bs>.
Se ECHOK est� ligado, 
ecoa <nl> apos "kill".
Se ECHONL est� ligado, 
ecoa <nl> mesmo com ECHO desligado.

.sp
Se NOFLSH est� ligado, a descarga normal das �reas de entrada e
sa�da associadas ao "intr" e "quit" n�o s�o realizadas.

.sp
Se CNTRLX est� ligado, 
os caracteres de controle na sa�da ser�o convertidos na forma "^X";
em caso contr�rio ser�o escritos sem modifica��o.

.sp
Se ISOKEY est� desligado, sup�e-se que o teclado do terminal
n�o processa acentos; a interface converte pares de caracteres
da entrada
nos caracteres acentuados correspondentes. Os pares definidos
s�o "," seguido de "c" ou "C" (representando "c"-cedilha),
":" seguido de vogal (representando a vogal com trema) e os
acentos "'", "`", "^" e "~" seguidos de vogais, representando
as vogais com acentos. Para evitar a uni�o dos pares de caracteres,
basta colocar um "\" entre eles (como por ex. ",\c" para gerar ",c").
Se ISOKEY est� ligado, sup�e-se que o teclado j� gere os
caracteres com acentos, e o procedimento acima descrito n�o �
realizado. 

.sp
A cada linha est� associada uma tabela de convers�o de caracteres.
O valor de CODE normal � ISO, indicando que n�o ser� feita
convers�o de c�digo. Com o valor ASCII, ser� feita a convers�o
para o c�digo "ascii", com o mapeamento de vogais acentuadas
em vogais sem acentos, e outras modifica��es.
Com os valores USER1 e USER2 ser�o utilizadas as tabelas
"user1" e "user2", cujos valores normais s�o ABICOMP e ISO,
mas que podem ser modificadas atrav�s de "kcntl" (sys).

.sp
Se VIDEO est� ligado, o terminal � considerado de v�deo:
para o processamento de "kill", apaga a linha inteira,
e para o processamento de "word", apaga a �ltima palavra;
se estiver desligado, para o processamento de "kill"
imprime o caractere de controle
e pula de linha, e n�o processa o "word".

.sp
Se ICOMM est� ligado, a entrada de caracteres ser� realizada
no modo de comunica��es, que � um modo especialmente adequado
para comunica��o m�quina/m�quina, pois � o mais eficiente.
Ligar ICOMM � equivalente a desligar ISIG, ICANON e ECHO, mas
a interface utiliza outro trecho de c�digo, que � mais r�pido. 

.sp 2
Os comandos principais dispon�veis da chamada ao sistema "ioctl" (sys)
referentes �s linhas de comunica��o
t�m a forma:

.sp
.nf
		#include <sys/types.h>
		#include <termio.h>

		int ioctl (int fd, int cmd, TERMIO *arg);
.fi

.sp

Os comandos utilizando esta forma s�o:
.in +3

.ip TCGETS 11
Obtenha os par�metros associados com o terminal e guarde-os
na estrutura apontada por "arg".

.ip TCSETS 11
Atribua os par�metros do terminal com os valores da estrutura
apontada por "arg". A mudan�a � imediata.

.ip TCSETAW 11
Espere at� que a file de sa�da esteja vazia antes de atribuir
os novos par�metros. Esta forma deve ser usada quando mudar
par�metros que ir�o afetar a sa�da.

.ip TCSETAF 11
Espere at� que a file de sa�da esteja vazia,
em seguida descarregue
a fila de entrada e s� ent�o atribua os novos par�metros.

.ip TCSETNR 11
Este modo de atribuir os par�metros pode ser usado quando
se deseja modificar par�metros apenas da interface de terminais
(por exemplo, passar do modo "raw" para "cooked" ou vice-versa),
e N�O modificar par�metros de "hardware" (tal como a velocidade
de transmiss�o).
Quando este for o caso, �ste � o modo mais indicado para a
mudan�a, pois N�O � dado "reset" nos dispositivos de "hardware",
nem s�o modificadas as filas de entrada/sa�da. 
� de responsabilidade do usu�rio certificar-se de que
n�o est�o sendo modicados par�metros de "hardware".

.ep
.in -3

.in 5
.sp 2
Comandos adicionais da chamada ao sistema "ioctl" (sys)
t�m a forma:

.sp
.nf
		int ioctl (int fd, int cmd, int arg);
.fi

.sp
Os comandos utilizando esta forma s�o:

.in +3
.ip TCSBRK 11
Espere a fila de sa�da esvaziar.

.ip TCXONC 11
Controle de "start/stop". Se "arg" � 0, suspenda a sa�da; se �
1, reinicie a sa�da.

.ip TCFLSH 11
Se "arg" � 0, descarregue a fila de entrada; se � 1, descarregue
a fila de sa�da; se � 2, descarregue ambas. 

.ip TCNREAD 11
Devolva o n�mero de caracteres dispon�veis na fila de entrada.

.ip TCISATTY 11
Devolva 1 se o descritor de arquivos se refere a um terminal, e   
0 se n�o.

.ip TCGETCTS 11
Devolve um valor n�o nulo se o sinal CTS ("clear to send") est�
sendo recebido no dispositivo serial.

.ip TCSETRTS 11
Envie o sinal RTS ("request to send") atrav�s do dispositivo serial.

.ip TCRESETRTS 11
N�o envie o sinal RTS ("request to send") atrav�s do dispositivo serial.

.ip TCINTERNET 11
Devolve um valor n�o nulo se o dispositivo pode ser usado como meio de
tranmiss�o/recep��o de datagramas da INTERNET.

.ip TCFIFOSZ 11
Ajusta o tamanho a ser usado do FIFO de sa�da. Isto s� pode ser
utilizado em alguns dispositivos, como por exemplo NS-16550.

.ep
.in -3

.in

.sp
.b OBSERVA��ES
.in 5
Os seguintes bites dos v�rios modos (e respectivas fun��es)
n�o est�o implementados: IGNBRK, BRKINT, IGNPAR, PARMRK,
INPCK, IXOFF, CSIZE, CSTOPB, CREAD, PARENB, HUPCL, CLOCAL, LOBLK,

.sp
Tamb�m n�o est�o implementados os atrasos dos diversos caracteres.

.in

.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
intro
.br
.wo "(cmd): "
stty
.br
.wo "(sys): "
ioctl, kcntl, signal
.br

.in
.sp
.b ARQUIVOS
.in 5
 /dev/console
 /dev/tty*
 /dev/ptys*
 /dev/ptyc*
 /dev/slip*

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
