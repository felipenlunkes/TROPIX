.bp 1
.he 'STTY (cmd)'TROPIX: Manual de Refer�ncia'STTY (cmd)'
.fo 'Atualizado em 09.07.97'Vers�o 3.0.1'Pag. %'

.b NOME
.in 5
.wo "stty -"
consulta/altera par�metros de terminais/v�deos
.br

.in
.sp
.b SINTAXE
.in 5
stty [-at] [<param> ou -<param> ...]
.sp
STTY [-at] [<param> ou -<param> ...]

.in
.sp
.b DESCRI��O
.in 5
O comando "stty" (ou "STTY") consulta/altera uma s�rie de par�metros
de terminais, pseudo-terminais, v�deos, linhas de comunica��o, impressoras,
etc ...

.sp
Se forem dados par�metros da forma <param> ou -<param>,
estes s�o respectivamente ativados ou desativados (veja a lista abaixo).
Em caso contr�rio, � impressa uma lista
resumida dos par�metros com os seus estados correntes (veja as op��es abaixo).

.sp
As op��es do comando s�o:

.in +3
.ip -a
Fornece a lista completa de par�metros ao inv�s de uma lista resumida.

.ip -t
Fornece a lista de cores dispon�veis para o par�metro "color", com
os respectivos c�digos num�ricos.

.ep
.in -3

.sp
Nas sess�es seguintes � dada uma lista completa dos par�metros.
Maiores detalhes sobre cada par�metro podem ser encontrados em
"termio" (fmt).

.sp 2
.b
Caracteres de controle:
.r

.sp
.in +5
Alguns caracteres t�m fun��o especial na entrada por terminal/v�deo;
eles s�o dados nesta sess�o, juntamente com alguns par�metros
que na realidade n�o s�o caracteres, mas s�o valores que
s�o armazenados em um byte.
O valor dado ap�s o nome do caractere (<c> ou <n>) passa a
ser o novo valor do caractere de controle.

.sp
O valor de <c> pode ser dado diretamente como um caracter, como por
exemplo <^C> ou ent�o na forma "^C", isto �, os 2 caracteres
"^" e "C". Neste segundo caso, os 2 caracteres devem vir entre
aspas ou ap�strofes.

.sp
O valor de <n> deve ser dado como um n�mero decimal, octal ou hexadecimal
(conforme a sintaxe de "strtol" (libc)).
Isto tamb�m � o caso dos valores de <f> e <b> para o caso de "color".

.ip "intr <c>" 16
Este caractere gera um sinal de interrup��o ("SIGINT"), 
que � enviado a todos os processos associados ao terminal/v�deo
de controle. Normalmente, estes processos terminam
ao receber este sinal, mas eles podem utilizar a chamada
ao sistema "signal" (sys) para ignor�-lo ou intercept�-lo.
O valor inicial deste caractere � <^C>. 

.ip "quit <c>" 16
Este caractere gera um sinal de "quit" ("SIGQUIT"), 
que � enviado a todos os processos associados ao terminal/v�deo
de controle. Normalmente, estes processos terminam com a grava��o
da imagem do processo no disco ("core-dump")
ao receber este sinal, mas eles podem utilizar a chamada
ao sistema "signal" (sys) para ignor�-lo ou intercept�-lo.
O valor inicial deste caractere � <^X>. 

.ip "erase <c>" 16
Este caractere apaga o caractere anterior; se estivermos
no come�o de uma linha, nada faz.
O valor inicial deste caractere � <del> ("^*"). 

.ip "kill <c>" 16
Este caractere apaga a linha inteira.
O valor inicial deste caractere � <^U>.

.ip "eof <c>" 16
Este caractere pode ser usado para gerar uma condi��o de 
fim de arquivo ("EOF") do terminal/v�deo. Quando recebido, todos os
caracteres da fila de entrada s�o passados imediatamente para
o programa, sem esperar um <nl>, e o caractere � ignorado.
Se n�o havia nenhum caractere na fila, zero caracteres s�o
passados para o programa, o que � a indica��o padr�o
de EOF. 
O valor inicial deste caractere � <^D>.

.ip "min <n>" 16
Este valor s� � utilizado no modos "raw" ou "comm",
e representa o n�mero m�nimo de caracteres
necess�rios na fila de entrada para que eles sejam passados
para o processo. Em outras palavras, o processo espera
at� que a fila de entrada contenha <n> caracteres.  
O valor inicial deste par�metro � 1.

.ip "eol <c>" 16
Este caractere � um delimitador adicional (como <nl>).
N�o � utilizado normalmente, e no momento n�o est� implementado.
O valor inicial deste par�metro � <nul> (<^@>).

.ip "time <n>" 16
Este valor s� � utilizado no modos "raw" ou "comm",
e representa um tempo utilizado para medir o tempo decorrido
para receber "min" caracteres.
No momento n�o est� implementado.
O valor inicial deste par�metro � 0.

.ip "res <c>" 16
Este caractere no momento n�o tem fun��o; est� reservado
para uso futuro.
O valor inicial deste par�metro � <nul> (<^@>).

.ip "switch <c>" 16
Este caractere � utilizado pelas rotinas de gerenciamento de janelas
de terminais.
O valor inicial deste par�metro � <nul> (<^@>).

.ip "page <n>" 16
Este valor representa o n�mero de linhas ap�s o qual a sa�da
no terminal/v�deo p�ra, aguardando um <^Q> (ou um caracter qualquer,
veja "ixany").
Isto � �til para terminais de v�deo para evitar que a sa�da
desapare�a da tela antes que possa ser lida.
Fazendo <n> igual a zero (ou usando "-page),
o controle n�o � realizado.
O valor inicial deste par�metro � 23.

.ip "aerase <c>" 16
Este caractere � an�logo ao "erase":
apaga o caractere anterior; se estivermos
no come�o de uma linha, nada faz.
O valor inicial deste caractere � <bs>.

.ip "retype <c>" 16
Este caractere re-imprime o a linha no terminal/v�deo.
� �til quando a linha sendo teclada � misturada com
mensagens de processos executando em "background".
O valor inicial deste caractere � <^R>.

.ip "word <c>" 16
Este caractere apaga a �ltima palavra teclada.
Uma palavra � definida como sendo um conjunto de caracteres
que n�o contenham <sp> nem <ht>.
O valor inicial deste caractere � <^W>.

.ip "color <f>[,<b>]" 16
Este caracter define a cor de frente e fundo definido respectivamente
pelos n�meros <f> e <b> (veja a op��o "-t").
Se a cor de fundo <b> for omitida, ser� assumido preta.
O valor inicial deste caractere � dependente do dispositivo.

.ip "nline <l>" 16
N�mero de linhas do terminal/v�deo.
O valor inicial deste caractere � dependente do dispositivo
(em geral 24).

.ip "ncol <c>" 16
N�mero de colunas do terminal/v�deo.
O valor inicial deste caractere � dependente do dispositivo
(em geral 80).

.ep
.in -5
.sp 2
.b
Modos de controle:
.r
.in +5

.ip "parenb" 10
Liga a gera��o/dete��o de paridade.

.ip "-parenb" 10
Desliga a gera��o/dete��o de paridade.

.ip "parodd" 10
Utiliza paridade �mpar.

.ip "-parodd" 10
Utiliza paridade par.

.ip "cs5" 10
Os caracteres tem 5 bites.

.ip "cs6" 10
Os caracteres tem 6 bites.

.ip "cs7" 10
Os caracteres tem 7 bites.

.ip "cs8" 10
Os caracteres tem 8 bites.

.ip "0" 10
Desconecta a linha imediatamente.

.ip "n" 10
A linha deve transmitir/receber a "n" baud.
O valor de "n" pode ser: 110, 134, 150, 200, 300, 600, 1200,
1800, 2400, 4800, 9600, 19200, 38400, 57600, 115200. Nem todas as interfaces
aceitam todas estas velocidades.
As velocidades acima de 1000 baud tem os sin�nimos 1.2, 1.8, 2.4, 4.8,
9.6, 19.2, 38.4, 57.6 e 115.2.

.ip "hupcl" 10
Desconecta a linha no �ltimo "close".

.ip "-hupcl" 10
N�o desconecta a linha no �ltimo "close".

.ip "cstop" 10
Utiliza dois bites de "stop" por caractere.

.ip "-cstop" 10
Utiliza um bite de "stop" por caractere.

.ip "cread" 10
Liga o receptor.

.ip "-cread" 10
Desliga o receptor.

.ip "clocal" 10
A linha n�o tem "modem" (n�o usa controle de fluxo por "hardware").

.ip "-clocal" 10
A linha tem "modem" (usa controle de fluxo por "hardware").

.ep
.in -5
.sp 2
.b
Modos de entrada:
.r
.in +5

.ip "ignbrk" 10
Ignora "break" na entrada.

.ip "-ignbrk" 10
N�o ignora "break" na entrada.

.ip "brkint" 10
Envia o sinal "SIGINT" com um "break".

.ip "-brkint" 10
N�o envia o sinal "SIGINT" com um "break".

.ip "ignpar" 10
Ignora erros de paridade.

.ip "-ignpar" 10
N�o ignora erros de paridade.

.ip "parmrk" 10
Marca erros de paridade.

.ip "-parmrk" 10
N�o marca erros de paridade.

.ip "inpck" 10
Liga a verifica��o de paridade.

.ip "-inpck" 10
Desliga a verifica��o de paridade.

.ip "istrip" 10
Remove o oitavo bite do caracter de entrada.

.ip "-istrip" 10
N�o remove o oitavo bite do caracter de entrada.

.ip "inlcr" 10
Converte <nl> em <cr> na entrada.

.ip "-inlcr" 10
N�o converte <nl> em <cr> na entrada.

.ip "igncr" 10
Ignora <cr> na entrada.

.ip "-igncr" 10
N�o ignora <cr> na entrada.

.ip "icrnl" 10
Converte <cr> em <nl> na entrada.

.ip "-icrnl" 10
N�o converte <cr> em <nl> na entrada.

.ip "iuclc" 10
Converte letras mai�sculas em min�sculas na entrada.

.ip "-iuclc" 10
N�o converte letras mai�sculas em min�sculas na entrada.

.ip "ixon" 10
Liga o controle de sa�da com <^Q>, <^S>.

.ip "-ixon" 10
Desliga o controle de sa�da com <^Q>, <^S>.

.ip "ixany" 10
Aceita qualquer caracter para a fun��o de <^Q>.

.ip "-ixany" 10
Aceita apenas o caracter <^Q>.

.ip "ixoff" 10
Envia os caracteres <^S>, <^Q> quando a fila de entrada
est� quase cheia/vazia.

.ip "-ixoff" 10
N�o envia os caracteres <^S>, <^Q> quando a fila de entrada
est� quase cheia/vazia.


.ep
.in -5
.sp 2
.(t
.b
Modos de sa�da:
.r
.in +5

.ip "opost" 10
Processa os caracteres de sa�da.
.)t

.ip "-opost" 10
N�o processa os caracteres de sa�da. Ignora todos
os modos de sa�da dados a seguir.

.ip "olcuc" 10
Converte letras min�sculas em mai�sculas na sa�da.

.ip "-olcuc" 10
N�o converte letras min�sculas em mai�sculas na sa�da.

.ip "onlcr" 10
Converte <nl> em <cr><nl> na sa�da.

.ip "-onlcr" 10
N�o converte <nl> em <cr><nl> na sa�da.

.ip "ocrnl" 10
Converte <cr> em <nl> na sa�da.

.ip "-ocrnl" 10
N�o converte <cr> em <nl> na sa�da.

.ip "onocr" 10
N�o escreve <cr>s no come�o da linha.

.ip "-onocr" 10
Escreve <cr>s no come�o da linha.

.ip "onlret" 10
No terminal/v�deo, o caractere <nl> faz a fun��o do <cr>. 

.ip "-onlret" 10
No terminal/v�deo, o caractere <nl> n�o faz a fun��o do <cr>. 

.ip "ofill" 10
Usa caracteres de "enchimento" para produzir atrasos.

.ip "-ofill" 10
Usa o rel�gio interno para produzir atrasos.

.ip "ofdel" 10
Os caracteres de "enchimento" s�o <del>s.

.ip "-ofdel" 10
Os caracteres de "enchimento" s�o <nul>s (<^@>)s.

.ip "cr[i]" 10
Seleciona o modo do atraso para <cr>s: cr0, cr1, cr2, cr3
(ver termio (fmt)).

.ip "nl[i]" 10
Seleciona o modo do atraso para <nl>s: nl0, nl1
(ver termio (fmt)).

.ip "tab[i]" 10
Seleciona o modo do atraso para <ht>s: tab0, tab1, tab2, tab3
(ver termio (fmt)).

.ip "bs[i]" 10
Seleciona o modo do atraso para <bs>s: bs0, bs1
(ver termio (fmt)).

.ip "ff[i]" 10
Seleciona o modo do atraso para <ff>s: ff0, ff1
(ver termio (fmt)).

.ip "vt[i]" 10
Seleciona o modo do atraso para <vt>s: vt0, vt1
(ver termio (fmt)).

.ep
.in -5
.sp 2
.b
Modos locais:
.r
.in +5

.ip "isig" 10
Processa os caracteres especiais "intr" e "quit".

.ip "-isig" 10
N�o processa os caracteres especiais "intr" e "quit".

.ip "icanon" 10
Processa os caracteres na entrada, aplicando os modos de entrada
escolhidos.

.ip "-icanon" 10
N�o processa os caracteres na entrada, os modos de entrada
s�o ignorados.

.ip "xcase" 10
Apresenta��o can�nica de mai�sculas/min�sculas. 

.ip "-xcase" 10
Apresenta��o n�o processada de mai�sculas/min�sculas. 

.ip "echo" 10
Ecoa todos os caracteres teclados.

.ip "-echo" 10
N�o ecoa os caracteres teclados.

.ip "echoe" 10
Ecoa os caracteres "erase" e "aerase" como <bs><sp><bs>.

.ip "-echoe" 10
Ecoa os caracteres "erase" e "aerase" como <bs>.

.ip "-echok" 10
Ecoa <nl> ap�s o caractere "kill".

.ip "echok" 10
N�o ecoa <nl> ap�s o caractere "kill".

.ip "echonl" 10
Ecoa <nl>.

.ip "-echonl" 10
N�o ecoa <nl>.

.ip "noflsh" 10
Esvazia as filas ap�s um "intr" ou "quit".

.ip "-noflsh" 10
N�o esvazia as filas ap�s um "intr" ou "quit".

.ip "cntrlx" 10
Converte os caracteres de controle na sa�da para a forma "^X". 

.ip "-cntrlx" 10
N�o converte os caracteres de controle.

.ip "isokey" 10
N�o converte pares de caracteres de entrada (acento, letra) na letra acentuada
correspondente.

.ip "-isokey" 10
Converte pares de caracteres de entrada (acento, letra) na letra acentuada
correspondente.

.ip "iso" 10
Informa a interface que o c�digo deste terminal/v�deo � ISO completo.

.ip "ascii" 10
Informa a interface que o c�digo deste terminal/v�deo � ASCII.

.ip "user1" 10
Informa a interface que o c�digo deste terminal/v�deo � o c�digo
"user1" (normalmente o c�digo ABICOMP, pode ser alterado
por "kcntl" (sys)).

.ip "user2" 10
Informa a interface que o c�digo deste terminal/v�deo � o c�digo
"user2" (normalmente o c�digo ISO, pode ser alterado
por "kcntl" (sys)).

.ip "video" 10
Informa a interface que o terminal � de v�deo,
e processe os caracteres "kill", "erase", "aerase", "retype"  
de acordo.

.ip "-video" 10
Informa a interface que o terminal n�o � de v�deo,
e processe os caracteres "kill", "erase", "aerase", "retype"  
de acordo.

.ip "icomm" 10
Habilita na entrada, o "modo de comunica��es", que �
equivalente a desligar "icanon", "isig", "opost" e "echo"
por�m mais eficiente. 

.ip "-icomm" 10
Desabilita na entrada, o "modo de comunica��es".

.ep
.in -5
.sp 2
.b
Macro argumentos:
.r
.in +5
.sp
Os macro argumentos s�o nomes simb�licos
para algumas combina��es dos modos dados acima.
Eles unem as combina��es mais usuais, e simplificam o uso
no caso normal.

.ip "evenp" 10
Habilita a paridade par:
liga "parenb" e "cs7"; desliga "parodd".

.ip "parity" 10
Como "evenp".

.ip "oddp" 10
Habilita a paridade �mpar:
liga "parenb", "cs7" e "parodd".

.ip "-parity" 10
Desabilita o processamento de paridade:
desliga "parenb"; liga "cs8".

.ip "-evenp" 10
Como "-parity".

.ip "-oddp" 10
Como "-parity".

.ip "cooked" 10
Habilita o processamento de caracteres na entrada e sa�da:
liga "opost" e "icanon".

.ip "-cooked" 10
Desabilita o processamento de caracteres na entrada e sa�da:
desliga "opost" e "icanon".

.ip "raw" 10
Como "-cooked".

.ip "-raw" 10
Como "cooked".

.ip "comm" 10
Habilita na entrada, o "modo de comunica��es", que � o modo
mais r�pido e transparente, para comunica��o m�quina/m�quina.
Este par�metro desliga todo e qualquer processamento de entrada, como
por ex. "isig" e "icanon", o processamento de  de sa�da "opost"
e o "echo" na sa�da.

.ip "-comm" 10
Como "cooked".

.ip "-nl" 10
Tratamento de <nl> e <cr> normal para terminais:
liga "icrnl" e "onlcr"; desliga "inlcr", "igncr", "ocrnl", "onlret".

.ip "nl" 10
Desabilita o tratamento de <nl> e <cr>:
desliga "icrnl" e "onlcr".

.ip "-lcase" 10
Tratamento normal de mai�sculas/min�sculas:
desliga "xcase", "iuclc", "olcuc".

.ip "-LCASE" 10
Como "-lcase".

.ip "lcase" 10
Tratamento para terminais que s� t�m letras ma�usculas:
liga "xcase", "iuclc", "olcuc".

.ip "LCASE" 10
Como "lcase".

.ip "tabs" 10
Preserva os caracteres de tabula��o:
liga "tab0".

.ip "-tabs" 10
Substitue os caracteres de tabula��o por brancos:
liga "tab3".

.ip "std" 10
Atribue valores "razo�veis" para todos os modos e caracteres.

.ip "sane" 10
Como "std".

.ip "ebc" 10
Realiza as seguintes fun��es de inicializa��o do terminal EBC-4020:
seleciona os acentos longos, atribui a data corrente,  e apaga as
duas linhas entre a parte inferior da tela e a linha da data.

.ep
.in
.sp
.(t
.b OBSERVA��ES
.in 5
Nem todos os dispositivos admitem todos os modos descritos acima.
.)t
.sp
Nem todas as combina��es dos modos descritos acima fazem
sentido.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
ioctl, kcntl
.br
.wo "(libc):"
strtol
.br
.wo "(fmt): "
termio
.br

.in
.sp
.b ARQUIVOS
.in 5
<termio.h>

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
