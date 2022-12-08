.bp 1
.he 'PS (cmd)'TROPIX: Manual de Refer�ncia'PS (cmd)'
.fo 'Atualizado em 10.08.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "ps -"
imprime informa��es sobre processos
.br

.in
.sp
.b SINTAXE
.in 5
ps [-axlk] [-t <tty>] [<pid> ...]

.in
.sp
.b DESCRI��O
.in 5
O comando "ps" fornece algumas informa��es sobre os processos ativos.

.sp
Sem op��es nem argumentos, s�o dadas informa��es apenas sobre os processos
do usu�rio que est� utilizando o comando "ps",
e que est�o associados a algum terminal.

.sp
Neste modo, � dada uma lista curta de informa��es, contendo apenas
a identifica��o do terminal ("TTY"),
a identifica��o do processo ("PID")
e o nome do comando com os respectivos argumentos ("CMD").

.sp
O conte�do da lista de informa��es pode ser modificado atrav�s das seguintes
op��es/argumentos:

.in +3
.ip -a 7
Fornece informa��es sobre todos os processos associados a algum terminal
(e n�o apenas sobre os processos do usu�rio que est� utilizando o comando "ps").
Esta op��o s� � permitida ao superusu�rio.

.ip -x 7
Fornece informa��es sobre todos os processos,
quer tenham um terminal associado ou n�o.
Esta op��o s� � permitida ao superusu�rio.

.ip -l 7
Fornece informa��es mais detalhadas  sobre cada processo: al�m das
informa��es da forma curta descrita acima ("TTY", "PID" e "CMD"),
d� tamb�m:

.in +9
.ip F 6
indicadores do processo (ver abaixo);

.ip S 6
estado do processo (ver abaixo);

.ip UID 6
dono do processo obtido a partir da vari�vel "USER" do ambiente do processo
(ou, se n�o encontrado, o nome do usu�rio obtido no arquivo "/etc/passwd");

.ip US 6
indica��o se o dono � superusu�rio ("SU") ou do grupo
do superusu�rio ("sys");

.ip PPID 6
identifica��o do  pai do processo;

.ip T 6
tipo do processo (reentrante ("n") ou n�o);

.ip PRI 6
prioridade do processo;

.ip NI 6
valor do "nice";

.ip UTIME 6
tempo total de CPU (em modo usu�rio) j� utilizado pelo processo;

.ip STIME 6
tempo total de CPU (em modo de sistema) j� utilizado pelo processo.

.ep
.in -9

.ip -ll 7
Com a op��o "-l" dada duas vezes, algumas das informa��es descritas acima
(em "-l") s�o substitu�das por:

.in +9
.ip RUID 6
nome do usu�rio obtido no arquivo "/etc/passwd";

.ip ADDR 6
endere�o da UPROC do processo na mem�ria/disco em KB;

.bc	/*************************************/
.ip SIZE 6
tamanho do processo em KB;
.ec	/*************************************/

.ip MSK 6
m�scara de execu��o (isto �, uma indica��o em quais CPUs
o processo pode ser executado);

.ip PGRP 6
identifica��o do processo l�der do grupo ao qual este
processo pertence;

.ip TGRP 6
identifica��o do grupo de terminais do processo;

.ip RCs 6
n�mero atual/m�ximo de recursos lentos que o processo
ocupa/ocupou.

.ep
.in -9

.ip -lll 7
Com a op��o "-l" dada tr�s vezes, algumas das informa��es descritas acima
(em "-l") s�o substitu�das por:

.in +9
.ip ADDR 7
endere�o da UPROC do processo na mem�ria/disco em KB;

.ip TSIZE 7
tamanho da regi�o TEXT do processo em KB;

.ip DSIZE 7
tamanho da regi�o DATA (que inclui o BSS) do processo em KB;

.ip SSIZE 7
tamanho da regi�o STACK do processo em KB;

.ip KFILE 7
n�mero atual de arquivos abertos do processo.

.ep
.in -9

.ip -llll 7
Com a op��o "-l" dada quatro vezes, algumas das informa��es descritas acima
(em "-l") s�o substitu�das por:

.in +9
.ip ALARM 8
n�mero de segundos faltando antes de enviar o sinal SIGALRM para o processo;

.ip SIGALRM 8
estado do sinal SIGALRM: (D) para SIG_DFL, (I) para SIG_IGN e um endere�o
em hexadecimal para indicar a fun��o de usu�rio que ser� chamada.

.ep
.in -9

.ip -lllll 7
Com a op��o "-l" dada cinco vezes, algumas das informa��es descritas acima
(em "-l") s�o substitu�das por:

.in +9
.ip KERNEL 8
O tamanho (em bytes) da parte da pilha de modo de supervisor do processo que
j� foi usada.

.ip STACK 8
A percentagem correspondente ao uso da pilha (veja acima).

.ep
.in -9

.ip -k 8
Envia o sinal "SIGTERM", interativamente, para os processos desejados.
Se a op��o for dada duas vezes ("-kk"), envia o sinal "SIGTERM".

.ip "-t" 8
Fornece informa��es apenas sobre processos associados ao terminal <tty>.
O nome do terminal pode ser dado com ou sem o prefixo "tty"
(como por exemplo "tty002" ou simplesmente "002").
Se <tty> for "?" , ser�o dadas
informa��es apenas sobre processos sem terminal associado. 

.ip "<pid>" 8
Fornece informa��es apenas sobre processos cujas
identifica��es s�o dadas pelos <pid>s.

.ep
.in -3

.in
.sp
.b "ESTADOS DOS PROCESSOS"
.in 5
Os v�rios estados dos processos s�o dados abaixo pelos c�digos e
seus respectivos nomes simb�licos:

.in 8
.ip r 4
SSWAPRDY: pronto para executar, por�m no disco;
.ip R 4
SCORERDY: pronto para executar, e na mem�ria interna;
.ip s 4
SSWAPSLP: esperando alguma recurso, no disco;
.ip S 4
SCORESLP: esperando alguma recurso, na mem�ria interna;
.ip i 4
SRUN:	executando na CPU "i";
.ip Z 4
SZOMBIE: o processo j� terminou, mas o pai ainda n�o chamou "wait".
.ep

.in
.sp
.b "INDICADORES DOS PROCESSOS"
.in 5
Os indicadores dos processos d�o informa��es auxiliares sobre o processo.
Os v�rios indicadores s�o dados abaixo em hexadecimal, juntamente
com seus nomes simb�licos:

.in 8
.ip 0x01 8
SSYS: processo especial;
.ip 0x02 8
SLOCK:	deve ficar sempre na mem�ria principal;
.ip 0x04 8
SSCTXT:	o estado est� em uma �rea alternativa;
.ip 0x08 8
SULOCK:	processo regular que deve ficar sempre na mem�ria principal;
.ip 0x10 8
SIGWAKE: foi acordado sem esperar o recurso;
.ip 0x20 8
STRACE: processo em trace;
.ip 0x40 8
SWAITED: a informa��o de trace j� foi dada;
.ip 0x80 8
SIGEXIT: envia o sinal "SIGHILD".
.ep

.in
.sp
.b OBSERVA��ES
.in 5
Um sistema operacional, juntamente com seus usu�rios e processos,
formam uma atividade din�mica, e como a tarefa de coletar as diversas
informa��es sobre os  processos n�o � instant�nea,
o comando "ps" pode fornecer informa��es possivelmente desatualizadas.

.sp
Algumas informa��es impressas para processos defuntos
(estado SZOMBIE) podem ser irrelevantes.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
kill, nice
.br
.wo "(sys): "
intro, nice
.br

.in
.sp
.b ARQUIVOS
.in 5
/dev/console
 /dev/tty*
 /dev/ptyc*
 /dev/video*
 /dev/swap
 /etc/passwd

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
