.bp
.he 'SCB (fmt)'TROPIX: Manual de Refer�ncia'SCB (fmt)'
.fo 'Atualizado em 21.10.03'Vers�o 4.5.0'Pag. %'

.b NOME
.in 5
.wo "scb -"
par�metros do bloco de controle do n�cleo do TROPIX
.br

.in
.sp
.b DESCRI��O
.in 5
O n�cleo do sistema operacional TROPIX cont�m uma tabela com diversos
par�metros, cujo objetivo � definir a configura��o do sistema.
Alterando um (ou mais) destes par�metros podemos modificar v�rios
aspectos do sistema operacional,
e deste modo atender a diversos desejos e necessidades.

.sp
Esta tabela (chamada de SCB, ou seja "system control block") est� contida
na imagem do n�cleo do TROPIX em disco (normalmente o arquivo "/tropix"),
e � copiada para a mem�ria (de onde � consultada) durante o processo
de "boot" (ou seja, a carga do sistema operacional).

.sp
Sem argumentos, o comando "edscb" (cmd) imprime os valores dos par�metros do SCB
em uso efetivo no momento.
Durante a carga do sistema operacional �
poss�vel alterar os par�metros apenas para esta execu��o do sistema
(veja "boot" (sys)).
O mesmo comando "edscb" pode alterar os valores dos par�metros de modo definitivo,
isto �, at� uma nova execu��o de "edscb", alterando a tabela contida
na imagem do n�cleo do TROPIX em disco.

.in
.sp
.b "LISTA DE PAR�METROS"
.in 5
Damos a seguir uma lista dos par�metros do SCB.
O valor inicial (padr�o) dos par�metros � dado entre par�nteses:
.bc	/*************************************/
O valor inicial (padr�o) da maioria destes par�metros pode ser encontrada
no arquivo "/usr/include/sys/defaults.h".
.ec	/*************************************/

.in +3
.ip nproc 10
N�mero de entradas da tabela de processos (100).

.ip ninode 10
N�mero de entradas da tabela de n�s-�ndice (150).

.ip nbuf 10
N�mero de �reas de entrada/sa�da para dispositivos estruturados
("cache" de "buffers"). Se este valor for NULO, ele ser� computado
durante a carga do sistema operacional, em fun��o da mem�ria dispon�vel
(calculado em fun��o do total de mem�ria interna).

.ip nkfile 10
N�mero de entradas da tabela de arquivos abertos (150).

.ip nclist 10
N�mero de �reas de entrada/sa�da para terminais, v�deos, linhas de comunica��es
e pseudo-terminais (1024).

.ip nmap 10
N�mero de entradas da tabela de aloca��o da mem�ria interna (102).

.ip nhshlib 10
N�mero de entradas da tabela "hash" para os s�mbolos das bibliotecas
compartilhadas (10007).

.ip ntout 10
N�mero de entradas da tabela de "time-outs" (40).

.ip nlockf 10
N�mero de entradas da tabela de "trancas" para arquivos (100).

.ip neventl 10
N�mero de entradas da tabela de eventos de usu�rios (local) (50).

.ip neventg 10
N�mero de entradas da tabela de eventos de usu�rios (global) (25).

.ip nsemal 10
N�mero de entradas da tabela de sem�foros de usu�rios (local) (50).

.ip nsemag 10
N�mero de entradas da tabela de sem�foros de usu�rios (global) (25).

.ip nregionl 10
N�mero de entradas da tabela de regi�es locais
(no momento N�O sendo usada).

.ip nregiong 10
N�mero de entradas da tabela de regi�es globais (400).

.ip ndns 10
N�mero de entradas da tabela de nomes/endere�os de computadores
da INTERNET (200).

.ip nroute 10
N�mero de entradas da tabela de roteamento da INTERNET (20).

.ip nether 10
N�mero de entradas da tabela de endere�os l�gicos/f�sicos de controladores
"ethernet" (50).

.ip nrawep 10
N�mero de entradas da tabela de "endpoint" para o "modo-de-acesso-interno"
(veja "t_intro" (xti)) (20).

.ip nudpep 10
N�mero de entradas da tabela de "endpoint" para o "modo-sem-conex�o"
(veja "t_intro" (xti)) (20).

.ip ntcpep 10
N�mero de entradas da tabela de "endpoint" para o "modo-com-conex�o"
(veja "t_intro" (xti)) (64).

.ip rootdev 10
C�digo interno ("major" + "minor") do dispositivo raiz de sistema de
arquivos. Se o seu valor for NODEV, o dispositivo ser� determinado
durante a carga do sistema operacional, baseado na tabela de parti��es.

.ip pipedev 10
C�digo interno ("major" + "minor") do dispositivo onde ser�o alocados
os n�s-�ndice para a cria��o de "pipe"s.
Se o seu valor for NODEV, o dispositivo ser� determinado
durante a carga do sistema operacional, baseado na tabela de parti��es.

.ip swapdev 10
C�digo interno ("major" + "minor") do dispositivo onde ser� alocada a
�rea de "swap".
Se o seu valor for NODEV, o dispositivo ser� determinado
durante a carga do sistema operacional, baseado na tabela de parti��es.

.ip swaplow 10
Deslocamento (em blocos de 512 bytes) do in�cio da �rea de "swap" no
dispositivo "swapdev" (0).

.ip nswap 10
Tamanho (em blocos de 512 bytes) da �rea de "swap" no
dispositivo "swapdev".
Se o seu valor for NULO, ele ser� determinado
durante a carga do sistema operacional, baseado na tabela de parti��es.

.ip ramd0sz 10
Tamanho (em KB) da �rea de mem�ria alocada para simular
a unidade de disco "0" na mem�ria interna (512 KB).

.ip ramd1sz 10
Tamanho (em KB) da �rea de mem�ria alocada para simular
a unidade de disco "1" na mem�ria interna (0 KB).

.ip tslice 10
Intervalo de tempo ("time-slice") entre os rec�lculos
das prioridades dos diversos processos.
Este intervalo de tempo � dado em "ticks" do rel�gio (que s�o normalmente
de 10 ms.); portanto um valor de "10" significa 100 ms (10 ms).

.ip incpri 10
N�mero com o qual s�o incrementadas as prioridades dos processos
prontos para a execu��o (mas N�O executando) a cada "time-slice" (10).

.ip decpri 10
N�mero com o qual s�o decrementadas as prioridades dos processos
em execu��o a cada "time-slice" (10).

.ip ttyinc 10
Tempo (em segundos) com o qual � incrementado o tempo de resid�ncia
no "swap" de processos que estavam aguardando entrada de teclado e
foram acordados (16).

.ip nfactor 10
N�mero que indica o grau de influ�ncia dos valores do "nice"
na prioridade dos processos (veja "nice" (cmd)) (10).

.ip nswapin 10
N�mero que determina o grau de influ�ncia do "nice" na opera��o de
trazer processos do "swap" para a mem�ria interna (1).

.ip nswapout 10
N�mero que determina o grau de influ�ncia do "nice" na opera��o de
levar processos da mem�ria interna para o "swap" (1).

.ip inage 10
Tempo (em segundos) que determina se um processo j� est� tempo suficiente
na mem�ria interna para lev�-lo para o "swap" (2).

.ip outage 10
Tempo (em segundos) que determina se um processo j� est� tempo suficiente
no "swap" para traze-lo de volta para a mem�ria interna (3).

.ip maxppu 10
Determina o n�mero m�ximo de processos por usu�rio
(no momento N�O sendo controlado) (10).

.ip maxpsz 10
Determina o tamanho m�ximo de um processo, em KB (4 MB).

.ip umask 10
M�scara global de cria��o de arquivos, em octal.
Cada usu�rio pode posteriormente mudar este valor atrav�s do comando
"umask" do "sh" (cmd) ou da chamada ao sistema "umask" (sys) (007).

.ip ncexec 10
N�mero m�ximo de caracteres alocados pelo n�cleo do TROPIX
para a passagem de argumentos e cadeias do ambiente durante a
execu��o de um programa (8 KB).

.ip stksz 10
N�mero de bytes alocados inicialmente na pilha de execu��o de um programa (3 KB).

.ip stkincr 10
N�mero de bytes alocados adicionalmente na pilha de execu��o de um programa,
cada vez que o espa�o alocado se esgota (4 KB).

.ip nmount 10
N�mero m�ximos de dispositivos que podem ser montados
(al�m do dispositivo "raiz"). Veja "mount" (cmd) (16).

.ip hz 10
Freq��ncia de interrup��o do rel�gio principal do sistema, em interrup��es
por segundo (hertz) (100).

.ip nflush 10
N�mero m�ximo de �reas de entrada/sa�da do "cache" de "buffers"
que devem ser atualizados a cada segundo
(no momento N�O sendo usada).

.ip nitblock 10
N�mero de �reas para entrada/sa�da de datagramas da INTERNET (120).

.ip scrsaver 10
N�mero de segundos esperados at� a ativa��o do "screen-saver" (300).

.ip preempt 10
Realiza troca de processos mesmo quando est� em modo supervisor
(0xFF, permitindo).

.ip tzmin 10
Fuso hor�rio: n�mero de minutos que devem ser somados ao tempo universal
(UT, antes chamado de GMT) para obtermos o tempo local (-180).

.ip utclock 10
Diferente de zero caso o rel�gio do computador est� com o hor�rio UT, zero em caso
contr�rio (hor�rio local) (0).

.ip dmaenable 10
Diferente de zero caso deva ser habilitado o uso de DMA dos dispositivos ATA (IDE) (1).

.ip dma 10
Como "dmaenable", acima.

.ip key 10
C�digo da tabelas de teclado: 0 para teclado norte-americano (US) e
1 para teclado brasileiro ABNT-2 (0).

.ip dmesgsz 10
Tamanho da �rea em que ser�o armazenadas as mensagens da carga do sistema, e que
posteriormente poder�o ser lidas atrav�s do programa "dmesg" (3072).

.ip synctime 10
Intervalo de tempo em segundos entre c�pias consecutivas dos n�s-�ndices e Superblocos
dos sistemas de arquivos para o "cache" de blocos (31).

.ip blocktime 10
Intervalo de tempo em segundos entre escritas consecutivas de at� "maxflush" (ver abaixo)
blocos do "cache" de blocos para os dispositivos f�sicos (5).

.ip dirtytime 10
Tempo m�ximo permitido entre a �ltima modifica��o de um bloco do
"cache" de blocos e a sua escrita no dispositivo f�sico (30).

.ip maxflush 10
N�mero m�ximo de blocos escritos a cada escrita de blocos do cache nos dispositivos f�sicos (40).

.ip sioport? 10
N�mero da porta dos portas seriais 0 a 7, correspondem aos dispositivos "/dev/tty00?".
As portas seriais 0 a 3 correspondem respectivamente �s portas MS-DOS COM1 a COM4.
Os dispositivos seriais PCI s�o configurados automaticamente
(0x3F8, 0x2F8, 0x3E8, 0x2E8).

.ip sioirq? 10
N�mero da interrup��o dos portas seriais 0 a 7 (4, 3, 4, 3).

.ip lpport? 10
N�mero da porta dos portas paralelas 0 a 3 (0x378, 0x278, 0x3BC, 0).

.ip lpirq? 10
N�mero da interrup��o dos portas paralelas 0 a 3.
O n�mero 0 significa porta paralela operando por estado (7, 0, 0, 0).

.ip edport? 10
N�mero da porta dos dispositivos "ethernet" 0 a 3.
Os dispositivos "ethernet" PCI s�o configurados automaticamente (0, 0, 0, 0).

.ip edirq? 10
N�mero da interrup��o dos dispositivos "ethernet" 0 a 3 (0, 0, 0, 0).

.ip usb? 10
Igual a 1 caso deva ser habilitado o controlador "usb" 0 a 7 (1, 0, 0, 0, 0, 0, 0, 0).

.ip sysname 10
Nome do sistema operacional. Se o valor n�o for dado, o sistema assume
"TROPIX".

.ip systype 10
Variante do sistema operacional.
Se o valor n�o for dado, o sistema assume "INTEL 386/486".

.ip nodename 10
Nome do computador.

.ip version 10
Vers�o do sistema operacional TROPIX.

.ip date 10
Data de gera��o deste n�cleo do sistema operacional TROPIX.

.ip time 10
Hora de gera��o deste n�cleo do sistema operacional TROPIX.

.ip machine 10
Tipo do computador.
Se o valor n�o for dado, o sistema assume "PC".

.ip customer 10
Cliente do sistema operacional TROPIX.

.ip depto 10
Departamento de instala��o do sistema operacional TROPIX.

.ip sysserno 10
N�mero de s�rie deste exemplar do sistema operacional TROPIX.

.ep
.in -3

.sp 2
Finalmente, damos alguns par�metros adicionais
impressos pelo comando "edscb":

.in +3
.ip ncpu 10
N�mero de CPUs ativas encontradas. Embora o sistema operacional
TROPIX seja multiprocessado, no momento, para PCs apenas um
processador � utilizado.

.ip initpid 10
N�mero (identifica��o, PID) do processo "/etc/init".
Este processo � o pai de todos os processos, e o seu PID � dependente
do n�mero de CPUs ativas.

.ip cputype 10
O tipo da CPU: INTEL 386, 486 ou PENTIUM.

.ip pgsz 10
O tamanho da p�gina em bytes.

.ip nblkdev 10
N�mero de dispositivos estruturados (de blocos) encontrados.

.ip nchrdev 10
N�mero de dispositivos n�o-estruturados (de caracteres) encontrados.

.ip endkernel 10
Endere�o (em KB) do final da mem�ria utilizada pelo n�cleo do TROPIX
(incluindo todas as tabelas alocadas din�micamente).

.ip ucore 10
Endere�o (em KB) do in�cio da mem�ria dispon�vel para processos do usu�rio.

.ip enducore 10
Endere�o (em KB) do final da mem�ria dispon�vel para processos do usu�rio.

.ip endpmem 10
Endere�o (em KB) do final da mem�ria f�sica do computador.

.ip ramd1 10
Endere�o (em KB) do in�cio da �rea de mem�ria alocada para simular
a unidade de disco "1" na mem�ria interna.

.ip endramd1 10
Endere�o (em KB) do final da �rea de mem�ria alocada para simular
a unidade de disco "1" na mem�ria interna.

.ip ramd0 10
Endere�o (em KB) do in�cio da �rea de mem�ria alocada para simular
a unidade de disco "0" na mem�ria interna.

.ip endramd0 10
Endere�o (em KB) do final da �rea de mem�ria alocada para simular
a unidade de disco "0" na mem�ria interna.

.ip debug 10
Liga/desliga a depura��o do n�cleo.
A lista das op��es de depura��o � dada abaixo:

.in +11
.ip ' 0: ' 5
Depura��o desligada.
.ip ' 1: ' 5
Sincronismo.
.ip ' 2: ' 5
Chamadas ao sistema.
.ip ' 3: ' 5
Informa��es sobre exce��es de endere�amento e acesso � mem�ria.
.ip ' 4: ' 5
Leitura adiantada de blocos ("readahead").
.ip ' 5: ' 5
Atividade de SWAP.
.ip ' 6: ' 5
Update, bflush.
.ip ' 7: ' 5
Open, creat, close, ....
.ip ' 8: ' 5
Chamadas obsoletas (iname, ioctl, ...).
.ip ' 9: ' 5
Desliga synccheck.
.ip '10: ' 5
Discos IDE.
.ip '11: ' 5
Terminais PEGASUS (ti).
.ip '12: ' 5
Iget, iput, ....
.ip '13: ' 5
Residual de entrada/saida.
.ip '14: ' 5
Deadlocks evitatos.
.ip '15: ' 5
Sinais.
.ip '16: ' 5
�rea de data de um text lido da memoria.
.ip '17: ' 5
Atividade de timeout.
.ip '18: ' 5
Read/write.
.ip '19: ' 5
Lockf.
.ip '20: ' 5
Trace.
.ip '21: ' 5
Aumento do processo na parte inferior.
.ip '22: ' 5
Disquete.
.ip '23: ' 5
TCP/IP.
.ip '24: ' 5
IPC (eventos, semaforos e shmem).
.ip '25: ' 5
Regi�es de mem�ria.
.ip '26: ' 5
Preemption do Kernel (escreve @).
.ip '27: ' 5
Fast Read: escreve os segmentos lidos.
.ip '28: ' 5
Exec.
.ip '29: ' 5
Ethernet.
.ip '30: ' 5
PPP.
.ip '31: ' 5
Physio.
.ip '32: ' 5
Zip.

.ep
.in -11

.ep
.in -3

.in
.sp
.(t
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
edscb, boot, chmod, nice, sh, mount
.br
.wo "(sys): "
umask
.br
.wo "(xti): "
t_intro
.br
.)t

.in
.sp
.b ARQUIVOS
.in 5
/tropix
 /usr/include/stat.h
 /usr/include/sys/default.h

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
