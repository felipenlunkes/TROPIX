.bp
.he 'KERNEL (sys)'TROPIX: Manual de Modifica��es'KERNEL (sys)'
.fo 'Atualizado em 28.08.07'Vers�o 4.9.0'Pag. %'

.b NOME
.in 5
.wo "kernel -"
n�cleo do sistema operacional TROPIX
.br

.in
.sp 2
.nf
/*
 ******	PLURIX **************************************************
 */
.fi
.ip "13.7.87   1.0" 20
VERS�O CORRENTE
.sp

.ip "13.7.87   1.0.1" 20
Foi modificada a sincroniza��o do "ioctl" de terminais:
antes, o par SLEEPLOCK & FREE ficava parte no "driver" e parte em
"ttyctl.c"; agora fica todo no "driver".
.sp
Com isto, n�o � mais poss�vel escrever caracteres entre a modifica��o
da estrutura "termio" e a programa��o da pastilha, o que podia acontecer,
na vers�o anterior.

.ip "14.7.87   1.0.2" 20
Na rotina "ttyread" foi colocado um teste para o caso do evento
"t_inqnempty" estar ligado com um alarme falso. Isto pode ocorrer
no caso de interrup��es em locais inconvenientes, que poderiam
ser sanados com mais um sem�foro, mas a solu��o dada � mais simples.

.ip "27.7.87   1.0.3" 20
Foi consertado o problema da
rotina "pipe" que n�o estava zerando a �rea do inode referente ao
texto no close.
.sp
Foi consertado o problema da
rotina "sched" que n�o estava preparada para o fato de que um processo
SCORESLP pode ser transformar em SCORERDY durante a opera��o de swap.
Agora, um processo SCORESLP � transformado em SSWAPSLP antes do
in�cio da opera��o de swap.

.ip "28.7.87   1.0.4" 20
O endere�o da �rea de argumentos da chamada ao sistema "exec", que
ficava na stack do programa "exece" foi agora colocado na UPROC.
O motivo � permitir a desaloca��o desta �rea no caso do processo
receber um sinal fatal durante um "exec". Foram feitas modifica��es
em "sysexec.c", "sysfork.c" e "uproc.h".

.ip "31.7.87   1.0.5" 20
Foi ativada a escrita de "core" (modifica��o em "aux.c").
Foi colocado uma MSG (chaves = 18) para as chamadas ao sistema
"read" e "write" (modifica��o em "sysfio.c"). 

.ip "04.8.87   1.0.6" 20
Foram modificadas as rotinas "bflush" e "bumerase" para serem s�ncronas,
isto �, para s� retornarem depois de terminadas as escritas nos
dispositivos. Isto faz com que a chamada ao sistema "sync" seja
s�ncrona. 

.ip "19.8.87   1.0.7" 20
Foi acrescentado na UPROC o "frame-pointer" do usu�rio, para que ele
esteja dispon�vel ao "sdb" em um "core-dump" (modifica��o em "aux.c").

.ip "20.11.87  1.1.0" 20
Foi modificado o m�dulo "dev/si.c" para processar terminais virtuais.
.sp

.ip "09.12.87  1.1.1" 20
Foi modificado o m�dulo "dev/dis.c" para tentar recuperar �rros de
leitura/escrita de maneira mais eficiente, dando recalibrate entre
as diversas tentativas. 

.ip "12.12.87  1.1.2" 20
Foi consertado o problema do "cc[VMIN]" da estrutura "termio",
que ao ser alterado, faltava apagar o evento "inqnempty".
Foi alterado o m�dulo "ttyctl".

.ip "24.12.87  1.1.3" 20
Foram modificados os m�dulos "ttyctl" e "ttyread" para resolver
dois problemas: ficar preso no evento "outqstart" quando se passa
do modo cooked para raw e quando se
d� "intr" no final da p�gina do terminal.

.ip "05.01.88  1.1.4" 20
Foi alterada a
rotina "itocore" do m�dulo "ialloc",
para que o campo "rdev" do
inode na mem�ria agora cont�nha "0", se o arquivo n�o for especial. 

.sp
Foram alterados alguns "printf" em "prdev" do m�dulo "ialloc",
para tamb�m informar em qual dispositivo est� ocorrendo o problema.

.ip "07.01.88  1.1.5" 20
Foi consertado o esquecimento de desligar o evento "outqempty"
no caso do "eco" das linhas de comunica��o. Foram alteradas as
rotinas "ttyout" do m�dulo "ttyin" e a rotina "ttywrite" do
m�dulo "ttyread". 

.ip "08.01.88  1.1.6" 20
Foi consertado o FIFO, que agora (como o PIPE) funciona na mem�ria.
Foi inserida uma sincroniza��o,
para que o leitor (ou o escritor) espere pelo
"open" do seu parceiro. Foram alterados os m�dulos "pipe.c"
e "file.c".

.ip "13.01.88  1.1.7" 20
Foi colocado um teste (com #ifdef SEGURO) no m�dulo "fio/mount.c"
para verificar, depois de um "umount", se ainda sobraram
INODEs ou BUFFERs do dispositivo no kernel.

.sp
Agora, quando se d� o �ltimo "close" em um dispositivo especial
de blocos, s�o removidos todos os blocos remanescentes do
"cache". Deste modo, quando se troca de disquete (por exemplo),
n�o se fica com um bloco do disquete anterior na mem�ria. 
Foi inserido uma chamada a "bumerase" no m�dulo "fio/iread.c".

.ip "12.02.88  1.1.8" 20
Foi implementado a chamada ao sistema "ptrace". N�o foi necess�rio
inserir um estado novo; foi utilizado o estado SCORESLP/SSWAPSLP esperando
no evento "p_trace" para represent�-lo. 
Foram realizadas modifica��es em "proc.h", "excep.c", "signal.c",  
"sysent.c", "sysexec.c", "sysfork.c",
al�m de criar o m�dulo novo "systrace.c".

.ip "01.03.88  1.1.9" 20
Faltou desligar o bite de "trace" do SR quando se mandava executar
o programa em STOP com o comando "7"; alterado "sys/systrace.c".

.sp
No m�dulo "sysfork.c", a chamada ao sistema "wait", em caso de
estado STOP, estava retornando (na parte baixa)
o valor "0x3F" ao inv�s de "0x7F".

.sp
A chamada ao sistema "wait" foi extendida para devolver
em "_fpc", o "pc" do BUS ERROR e do ADDR ERROR.

.ip "10.03.88  1.1.10" 20
Faltou desligar o bite de "trace" do SR quando
vinha a exce��o do TRACE;
alterado "proc/excep.c".

.ip "08.04.88  1.1.11" 20
O M�dulo "excep.c" foi alterado para devolver em "fa"
a instru��o inv�lido no caso de SIGILL.

.sp
No caso de um sinal interceptado, agora � passado para o usu�rio
(atrav�s do "sigludium") o "pc" e "fa". Alterado o m�dulo "signal.c".

.ip "26.04.88  1.1.12" 20
Foi introduzido o processamento do indicador "NDELAY" para linhas
de comunica��o. Foram alterados os m�dulos
uproc.h, sysfio.c e ttyread.c.

.sp
Foi criado a nova chamada ao sistema "sigchild".
Alterados os m�dulos
sysent.c, sysfork.c e  sysproc.c.

.sp
Foi criado o modo de comunica��es para linhas de comunica��o.
Alterados
tty.h, ttyin.c, ttyctl.c e ttyread.c.

.sp
Foi finalmente descoberto e corrigido o erro que causava processos
ZUMBI sobrarem em certas condi��es.
Alterados
sysfork.c e signal.c.

.ip "06.05.88  1.1.13" 20
Foi acrescentado o "driver" do RAM disk.

.sp
Foi alterado a chamada ao sistema "sigchild" para enviar tamb�m
o sinal quando o filho entra no estado "STOP".

.ip "28.06.88  1.1.14" 20
Foi alterado o valor inicial de "eol" para <esc>.
Envolveu mudan�a em "tty.h" e "ttyread".

.ip "08.07.88  1.1.15" 20
Agora, a m�scara do hash de processos "nhpash" do SCB j� est� sendo
inicializada. Altera��o em "scb.c".

.ip "02.08.88  1.1.16" 20
Foram feitas diversas pequenas altera��es para compilar o
KERNEL com o compilador "plc".

.sp
Foi feito a chamada ao sistema "lockf".
Cria��o dos m�dulos "fio/lockf.c" e "h/lockf.h",
e altera��es em diversos m�dulos,
principalmente em "sys/sysfio.c". 

.sp
Foi alterada a aloca��o de textos para usarem as regi�es do
final da mem�ria, o que permite a maior compacta��o
da mem�ria. Alterado "fio/text.c".

.sp
Foram tirados os pontos de entrada "smul" e "usmul"
de "arit.s", pois o compilador "plc" n�o
gera c�digo chamando estas rotinas.

.sp
Foram retiradas as restaura��es dos PCWs do ICA.
Altera��es em "smove.s" e "umove.s"

.sp
Foi implantado a chamada ao sistema "lockf".
Criado "fio/lockf.c", "h/lockf.h" e alterados
"fio/file.c", "sys/sysfio.c".

.sp
Foi alterado "proc/core.c" para que um processo
verifique se h� mem�ria adjacente na parte inferior
quando h� necessidade de aumento do tamanho do processo.

.ip "12.08.88  2.0.00" 20
Foram inseridos os testes para sinais ("proc/signal.c")
e modo "raw" ("tty/ttyctl.c") para ser compat�vel
com os execut�veis da vers�o "1.1".

.ip "24.08.88  2.1.00" 20
Foi retirado o "bootcode" do "etc/init", e colocado
em um arquivo separado "iconf/boot.s", inserindo logo
a tentativa de executar "/etc/oinit".

.ip "10.09.88  2.1.02" 20
Foi alterado a inicializa��o do sistema, podendo-se
dar o nome do programa "init". Mudan�as em "iconf/boot.s"
e "etc/kinit.c".

.ip "22.09.88  2.1.03" 20
Foi alterada a programa��o das linhas de comunica��o
para gerararem o sinal "request to send".
Alterado "dev/si.c".

.ip "29.09.88  2.1.04" 20
Foi consertado o pequeno erro no c�lculo da convers�o do endere�o
virtual para f�sico no caso PEG. Alteradas as rotinas "uatopa"
e "satopa" do m�dulo "conf/smove.s".

.ip "01.11.88  2.1.05" 20
As linhas de comunica��o no modo "ICOMM" agora n�o s�o mais
fechadas, para evitar problemas no funcionamento com 5 fios.
Alterado o m�dulo "si.c".

.ip "03.12.88  2.1.06" 20
No m�dulo "tty/ttytl.c", a fun��o "TCSETNR" n�o estava dando
o "eventdone" em "outqstart".

.sp
Foi estendido a chamada ao sistema "kcntl" para a nova fun��o
"K_SEMAFREE", para liberar um recurso pelo qual um processo est� esperando.

.ip "21.01.89  2.1.07" 20
Foi consertado o "dev/si.c" para n�o mais considerar trocas
de tela no modo "ICOMM".

.ip "25.01.89  2.1.08" 20
Foi consertado o problema do offset para fita magn�tica raw.
Modificado "dev/physio.c", "dev/sasi.c", "dev/win.c", "dev/dis.c".

.ip "26.01.89  2.1.09" 20
Foi consertado o detalhe do "nice" ser com sinal, e deve ter o
tipo "schar". Modificado "common.h", "proc.h".

.ip "06.03.89  2.1.10" 20
Foi modificado o driver do winchester, para realizar opera��es
com m�ltiplos blocos em uma opera��o, al�m de utilizar uma
estrutura para acessar os registros do dispositivo.
Alterado "dev/win.c".

.sp
Foi modificado o driver do disquete, para utilizar uma
estrutura para acessar os registros do dispositivo.
Alterado "dev/dis.c".

.sp
Foi introduzido o conceito de "update gradual", em que ao esvaziar
a fila de pedidos de um driver (por exemplo, "win.c"), � chamada
a rotina "boneflush", que procura um block "DIRTY", e inicia a escrita. 
Alterados "bio/bread.c", "proc/excep.c", e os drivers.

.ip "01.04.89  2.1.11" 20
Foram alterados os drivers de disquetes para exercer "open" exclusivo
duplicando a id�ia do "O_LOCK", para que "/dev/d5a" e "/dev/rd5a"
tenham o "LOCK" em comum.

.ip "07.05.89  2.2.00" 20
Foi alterado a dete��o de erro de "dis.c" para reparar que o
disquete est� protegido para escritas.

.ip "21.07.89  2.2.01" 20
Foi criado o diret�rio "ica.ctl", e realizado uma pequena
reestrutura��o para modularizar mais o KERNEL, com vista
a atender v�rios clientes, com peculariedades pr�prias.

.ip "03.08.89  2.2.02" 20
Alterado o m�dulo "etc/prot.c" para aceitar "snf" coringa (== 0).

.sp
Feita uma redivis�o de diret�rios "conf" para que nestes diret�rios
fiquem todos os detalhes particulares das m�quinas personalizadas.

.ip "16.08.89  2.2.03" 20
Foram realizadas modifica��es nos m�dulos "proc/signal.c" e "umove.s"
para que os sinais "SIGBUS" e "SIGADDR" possam
ser interceptados corretamente.

.ip "20.08.89  2.2.04" 20
Foi modificada ligeiramente a "stack" de exce��o para possibilitar
a compatibilidade "plurix/tropix". Retirado o "rot" da "stack".
Modificados "h/reg.h", "ctl.s".

.sp
Foram alterados "dis.c" e "delay.dis.c" para s� imprimirem
mensagem de �rro ap�s a segunda tentativa.

.sp
Foi estendido o m�dulo "etc/scb.c" para imprimir a tabela do
disco como "display c".

.ip "04.09.89  2.3.00" 20
Agora, quando uma linha de comunica��es � aberta, o c�digo
de caracteres � "ISO". Alterado "dev/si.c".

.ip "28.11.89  2.3.01" 20
Fora colocados os controles do "cache" do 68020.
Alterados "ctl.s", "kinit.c" e "dispat.c".

.ip "04.12.89  2.3.02" 20
Foram feitas as altera��es para o controle de discos "winchester"
com controlador embutido. Alterados "disktb.h", "win.c", "scb.c".

.ip "15.12.89  2.3.03" 20
Foram introduzidas as extens�es (apenas ICA) para utilizar a resolu��o
de microsegundos do rel�gio interno. Alterados "aux.c", "ctl.s",
"excep.c", "kinit.c" e "systime.c".

.sp
Foi estendido a chamada ao sistema "kcntl" para fornecer os tamanhos do 
processo. Alterado "kcntl.h" e "sysctl.c".

.sp
Foram corrigidos "win.c", "dis.c" e "delay.dis.c" para n�o exigir
o "count" m�ltiplo de 512.  

.sp
Foram corrigidos "dis.c" e "delay.dis.c" para processar o "byte count"
correto.

.ip "15.03.90  2.3.04" 20
Foi alterado "si.c" para trabalhar tamb�m com 38400 baud.

.ip "11.04.90  2.3.05" 20
Foram alterados "win.c", "dis.c" e "delay.dis.c" para n�o
aceitarem leituras/escritas de tamanho n�o m�ltiplo de 512.

.sp
Foram alterados "ttyread" e "ttyctl" para serem mais ortodoxos e conservativos
na manipula��o do sem�foro "t_inqnempty".

.sp
Foram alterados "excep.c" e "l.s" para conterem os vetores de
exce��o do ponto flutuante.

.ip "08.08.90  2.3.06" 20
Foi introduzido um c�lculo do TTYPANIC para o modo de comunica��es,
em fun��o do tamanho da CLIST. Alterados "scb.c" e "ttyin.c".

.sp
Foi estendida a an�lise de "cputype" para o MC-68881, mudando a codifica��o
para bites. Alterados "common.h", "ctl.s", "kinit.c", "dispat.c" e "excep.c".

.sp
Foram introduzidas os novos ioctl's TCSETCTS e TCRESETCTS em "dev/si.c",
"h/tty.h" e <termio.h>.

.sp
Foram atualizados os prot�tipos ANSI nos <includes> do "h",
e em raz�o disto feitas pequenas altera��es em "sysuser.c",
"systree.c", "systime.c", "sysent.c",  "sysetc.c" e "stdio.c".

.sp
J� pode ser feito a formata��o de disquetes "on-line". Alterados
"dis.c" e "delay.dis.c".

.sp
Consertado "delay.dis.c" para n�o prender todo o sistema quando
se tenta ler/escrever, mas n�o h� disquete montado.

.sp
Foi introduzido o controle de sto/ld do MC 68881/68882 no kernel.
Alterados "ctl.s", "uproc.h", "common.h", "core.c", "dispat.c", 
"nproc.c", "excep.c", "systrace.c" e "sysexec.c".

.ip "15.09.90  2.3.07" 20
Foram feitas corre��es no controle de sto/ld do MC 68881/68882 no
kernel. Alterados "kinit.c" e "ctl.s".

.sp
Tentativa de evitar o "bloco residual" em "bumerase". Alterado
"bread.c".

.sp
Agora, pegando a tabela de discos da ROM. Alterado "c.c".

.sp
Inserido a op��o de "close sempre" para dispositivos de caracteres.
Alterados "iotab.h", "file.c" e "c.c".

.sp
Adicionado campo de "endpoint" para o TCP/IP. Alterado "file.h".

.sp
Foi criado o sinal "SIGREAD", com todas as suas (deliciosas) conseq��ncias.
Alterados "h/common.h", "h/tty.h", "h/uproc.h", "h/file.h",
"tty/ttyread.c", "tty/ttyin.c", "tty/ttyctl.c", "dev/term.c",
"dev/si.c" e "proc/signal.c".

.sp
Foi feita uma revis�o no "mmuunld". Alterados
"sys/sysetc.c", "fio/text.c", "etc/kinit.c", "etc/aux.c" e "proc/core.c".

.ip "20.12.90  2.3.8" 20
Alterado para trabalhar com s�mbolos externos de 31 caracteres.
Alterado "etc/aux.c", "sys/sysctl.c", "ica.ctl/smove.s".

.sp
Acertado o detalhe do ".const" do "boot.s".

.ip "10.02.91  2.3.9" 20
Criado e incorporado o driver de pseudo-terminal "dev/pty.c".
Alterados "etc/kinit.c", "h/tty.h" e "c.c".

.ip "02.05.91  2.3.10" 20
Incorporados controles de tamanho (5, 6, 7, 8) bits do caracter,
paridade e stop-bit. Alterado "dev/si.c".

.sp
Criado a chamada ao sistema "select". Alterados 
"h/ioctl.h", "h/tty.h", "h/proc.h",  "sys/sysent.c", "sys/sysetc.c",
"tty/ttyin.c", "tty/ttyread.c", "dev/si.c", "dev/pty.c".

.ip "18.06.91  2.3.11" 20
Foi trocado o nome da chamada ao sistema "select" por "attention".
Foi introduzido mais um argumento na chamada "attention" - o "timeout".
Alterados "sys/sysent.c" e "sys/sysetc.c".

.sp
Foi consertado um pequeno erro no "attention" de "dev/pty.c", para
o servidor.

.sp
Foi consertada a fun��o "toutreset", que esquecia de adicionar o tempo
da entrada retirada na entrada seguinte, e adicionado mais um argumento.
Alterados "proc/excep.c" e "dev/delay.dis.c". 

.ip "16.07.91  2.3.12" 20
Iniciada a inclus�o da "internet" no PLURIX.

.ip "07.10.91  ......" 20
Foi acrescentado o "\%P" em "etc/stdio.c".

.sp
Foi consertado um erro de "count" em "/dev/pty.c".

.in
.sp 2
.nf
/*
 ******	TROPIX Icarus *******************************************
 */
.fi
.ip "20.11.89   2.3.00" 20
VERS�O INICIAL

.sp
Foi separado o tratamento de exce��es como bus error, address error, etc
que continua no m�dulo "excep" do "tconf/ctl.s", do tratamento de chamadas ao
sistema, agora no "syscall" do "tconf/ctl.s, e do de interrup��o que est� no
"interrupt" do "tconf/ctl.s".

.sp
Foi alterada a rotina "siint" em "dev/si.c" para pegar o vetor de
interrup��o diretamente do lugar na stack onde ele foi colocado originalmente
pela pr�pria interrup��o. Como a maioria das rotinas de interrup��o n�o
precisam do vetor, n�o h� necessidade de coloc�-lo sempre na stack,
como era feito anteriormente, atrasando o atendimento de todas interrup��es. 

.sp
Foi criada a rotina "tickfra" em "tconf/ctl.s" para calcular o n�mero de
microssegundos dentro de um tick de rel�gio. Junto com a modifica��o
no m�dulo "clock" da "proc/excep.c" foi poss�vel implementar a chamada ao
sistema "mutime" em "sys/systime.c" com resolu��o de 3,2 microssegundos.

.sp
Foi criada a rotina "prmutime" em "etc/aux.c" para ser usada na instrumenta��o
do kernel para an�lise de desempenho. Esta rotina imprime o tempo em
segundos e microsegundos no formato "\%d, \%6d\n".

.sp
Foi criada a vari�vel "preemptionflag" em "tconf/ctl.s" para quando
estiver com valor zero impedir preemption de processo em modo supervisor.

.sp
Foi criada a vari�vel "bestpripid" em "tconf/ctl.s" que d� a identifica��o
do processo que tem a prioridade mais alta, i.e., aquele cuja prioridade 
est� em "bestpri".

.ip "02.12.89   2.3.01" 20

Foram modificados os m�dulos "etc/kinit.c", "fio/text.c", "proc/core.c",
"proc/dispat.c", "proc/swap.c", "proc/nproc.c", "sys/sysetc.c", 
"sys/sysexec.c" para ligar e desligar a vari�vel "preemptionflag" de forma
a impedir preemption em modo supervisor nas seguintes condi��es:

.sp
.in +5
1) Entre um "ctxtsto" e um "ctxtld" porque as �reas de salvamento n�o
s�o empilh�veis;
.sp
2) Durante a carga e descarga da MMU porque sen�o o contexto restaurado
ficaria incorreto pois a �rea da MMU � global e n�o pertence � pilha do
processo na "uproc";
.sp
3) Quando um processo n�o est� no estado SRUN. Isto ocorre
na cria��o, no t�rmino e nas transi��es de estado de processos quando
o mesmo, embora rodando, tem momentaneamente estados SNULL, SZOMBIE,
SCORERDY, etc. O problema se d� porque trocar um processo que est�
com o controle da UCP significa mudar o seu estado para SCORERDY e
quando ele volta a rodar o "dispatcher" muda o seu estado para SRUN.
Este problema pode ser contornado com uma modifica��o mais radical
dos estados e do "dispatcher". Ainda n�o foi feito.
.in -5

.ip "09.12.89   2.3.02" 20

Foi modificado o m�dulo "newproc" da "proc/nproc.c" para n�o
haver mais mudan�a no ponteiro "u.u_proc" do pai para o filho
durante um "fork". Agora o pai continua no estado SRUN e insere o
valor correto do ponteiro "u.u_proc" diretamente na "UPROC" do
filho. Isto permite que se libere a "preemption" em modo supervisor
durante a c�pia do filho.

.sp
Verificou-se que o fato de os processos estarem em estados diferentes
de SRUN afeta pouqu�ssimo ou nada o tempo de troca de processos
quando se tem "preemption" em modo supervisor.
Por enquanto desistiu-se de implementar essas mudan�as.

.ip "31.12.89   2.3.03" 20

Foi corrigido o problema da troca de contexto quando se executava um
"pipe". O problema, na realidade, estava na "unicopy" que altera
atrav�s da "setr34" diretamente registros da MMU. Estes registros n�o
eram salvos durante uma troca de contexto. Foram alteradas as rotinas
"mmuld" e "mmuunld" para que esses registros tamb�m sejam salvos.

.sp
Foram criadas no m�dulo "etc/aux.c" duas rotinas para fazer
trace do kernel em mem�ria: "mktrace" e "prmktrace".
As rotinas usam um buffer "ktracearea" que � preenchido de forma circular.
A "prmktrace" imprime em hexa os dados (long) armazenados.

.sp
Foi criada a rotina "ktrace" para fazer trace do kernel mas colocar os
dados no arquivo "ktrace" do root. A "ktrace" fica no m�dulo "etc/aux.c"
e foi acrescentada a entrada "K_KTRACE" na chamada ao sistema "kcntl"
para ligar e desligar o trace do kernel. Foi alterada tamb�m a "kcntl.h".

.ip "28.11.90   2.3.04" 20
Foram acrescentados eventos, sem�foros e mem�ria compartilhada.

.sp
Foram acrescentados "h/ipc.h" e "sync/ipc.c" que controlam
eventos, sem�foros e mem�ria compartilhada.

.sp
Foram modificados "h/file.h" e "h/inode.h" que agora cont�m mais
ponteiros para o manuseio de eventos, sem�foros e mem�ria compartilhada.

.sp
Foram modificados "fio/file.h" e "fio/iget.c" para liberarem as
�reas relativas a eventos, sem�foros e mem�ria compartilhada
quando arquivos s�o fechados.

.sp
Foi modificado "sys/sysent.c"  criado "sys/ipc.c"
para conter as novas chamadas relativas a 
eventos, sem�foros e mem�ria compartilhada.

.sp
Foram modificados "h/default.h" e "h/common.h" para definir novas estruturas.

.sp
Foram modificados "h/scb.h" e "etc/scb.c" para definir novos par�metros para
eventos, sem�foros e mem�ria compartilhada.

.sp
Foi modificado "etc/kinit.c" para innicializar as estruturas relativas a
eventos, sem�foros e mem�ria compartilhada.

.sp
Foi modificado "h/uproc.h" para conter um "short" que indica o no. total
de p�ginas utilizadas pelo processo em mem�ria compartilhada.

.ip "1992-1993  3.0.00" 20
Implementada a INTERNET.

.ip "13.08.93   3.0.02" 20
Foi acertado o detalhe da paridade opcional do UDP.
Decodificado o caso particular de "destination unreachable". 

.ip "21.08.93   3.0.03" 20
Adicionadas mensagens de erro ICMP para "protocolo" e "port" desconhecidos.

.ip "09.12.93   3.0.04" 20
Agora, os tempos dos arquivos ficam no INODE da mem�ria. Criadas as
novas chamadas ao sistema "instat" e "upstat". Alterados diversos
arquivos.

.sp
Agora s� se pode dar um LOCK em um arquivo com i_count == 0.
Alterado "sys/sysfio.c".

.ip "28.01.94   3.0.05" 20
Realizadas altera��es para a incorpora��o do "name resolver".
Alterados muitos m�dulos do "itnet".

.ip "25.08.94   3.0.06" 20
Alterado "ksnd.c" para satisfazer o protocolo TCP d�bio do PC, que
envia o ACK_of_SIN e SIN no mesmo segmento.

.ip "20.09.94   3.0.07" 20
Consertado o problema da compara��o circular do TCP (alterados "ksnd.c",
"rcv.c" e "snd.c").
Simplificado o m�dulo "sysipc.c" para utilizar a compara��o circular.

.ip "18.10.94   3.0.08" 20
Tentativa de conserto do problema do recebimento da retransmiss�o de
segmentos ap�s perdas de segmentos. Alterado "rcv.c".

.sp
Mudado o tempo de "SILENCE" para estados N�O "ESTABLISHED". Alterado
"daemon.c".

.ip "14.01.95   3.0.09" 20
Colocado um teste em "mmuunldregion" verificando se o ponteiro
corresponde a uma regi�o inexistente.

.sp
Alterado "update" para operar para um "dev" dado, e esperar caso
o sem�foro "updlock" esteja ocupado.
Eliminado o sem�foro "bfreesema".

.ip "23.01.95   3.0.10" 20
Restaurado o local de onde o rel�gio � ligado, para permitir ao
disquete funcionar como ROOT.

.ip "02.02.95   3.0.11" 20
Estendida a func�o "GET_DEV_TB" de "kcntl" para fornecer tamb�m a tabela
toda.

.ip "08.04.95   3.0.12" 20
Agora, os datagramas das filas RAW s�o removidos depois de certo tempo.

.sp
Invertida a ordem de chamar "close" para dispositivos BLK em "fio/iread.c".

.ip "22.05.95   3.0.13" 20
Agora, os blocos para datagramas da INTERNET s�o alocados estaticamente,
no SCB. Alterados "etc/scb.c", "itnet/itn.c" e "itnet/itblock.c".

.in
.sp 2
.nf
/*
 ******	TROPIX PC ***********************************************
 */
.fi
.ip "01.04.96  3.0.1" 20
VERS�O CORRENTE
.sp

.ip "12.04.96  3.0.2" 20
Foi alterado o endere�o do pr�prio n� para "127.0.0.1".
Foi consertado "itnet/kaddr.c" para reconhecer os v�rios endere�os pr�prios.
O teclado passou para "spl1" para n�o atrapalhar o "siosplip".

.sp
Foi estendido o tempo da chamada ao sistema "mutime" para microsegundos.
Alterados "etc/kinit.c" e "sys/systime.c".

.ip "11.08.96  3.0.3" 20
Foi alterada a filosofia de aloca��o de �reas da ITNET. Agora temos 3
classes: IT_IN, IT_OUT_DATA e IT_OUT_CTL.

.sp
Foram inclu�das entradas de 3.5" na tabela de 5.25" dos disquettes,
para o caso de obter a informa��o errada do CMOS.

.sp
o TROPIX agora tem um "screen saver"! Alterados: "proc/clock.c", "etc/scb.c",
"dev/con.c" e criado "dev/screen_saver.c".

.sp
Consertado "ctl/vector.s": faltava a atualiza��o dos dos ICUs.

.ip "05.01.97  3.0.5" 20
Foi modificada a execu��o das fun��es da fila de "timeout"
(m�dulo "proc/clock.c") para que cada fun��o seja chamada com
a fila solta.

.sp
Feita a primeira vers�o do "driver" do ZIP paralelo.

.sp
Novo "pcntl": ENABLE_USER_IO e DISABLE_USER_IO.

.sp
Conserto do problema do ano bissexto em "etc/cmos_clock.c".

.sp
Primeira vers�o de "xcon.c".

.sp
Estendido "dev/hd.c" para usar transfer�ncias longas no PIO.

.sp
Revis�o de "dev/zip.c" para ficar de acordo com a vers�o "ppa3.42"
do FreeBSD.

.sp
Elaborada a base de tempo de 1 us, e a medi��o da velocidade da CPU.

.sp
Estendida a estrutura HDINFO para conter o campo "flags" no momento
usando 16/32 bits.

.sp
Alinhada a tabela DISKTB para ficar com 64 bytes, o que facilita o
c�lculo de endere�o.

.sp
Eliminadas as colunas finais de "conf/c.c", que n�o eram usadas.

.sp
Modificado a fun��o "iclose" para a fun��o "close" dos drivers
serem chamados a cada chamada de "close".

.sp
Atualizados todos os drivers de blocos para utilizarem corretamento
os contadores de "open" das entradas da DISKTB e do dispositivo.

.ip "20.03.97  3.0.6" 20
Unificado em "dev/scsi.c" e "h/scsi.h" todos os procedimentos
comuns aos diversos drivers SCSI.

.sp
Aumentado (e muito) o tamanho da CLIST.

.sp
Alterado o "PAGING" para controlar a sa�da da CLIST (ao inv�s da
entrada).

.sp
Agora, a sa�da de "printf" do KERNEL pode ser desviado para
um pseudo-terminal. Introduzidas os IOCTLs "TC_KERNEL_PTY_ON"
e "TC_KERNEL_PTY_OFF".

.sp
O m�dulo "dev/hd.c" foi estendido para controlar tamb�m o segundo
canal IDE. A tabela "bcb.h" foi alterada para conter informa��es
sobre os novos dois discos IDE. A estrutura "disktb" foi estendida
para conter tamb�m o "target".

.ip "04.04.97  3.0.7" 20
Em decorr�ncia da introdu��o do campo "p_target" na estrutura DISKTB, foi
realizada uma revis�o dos m�dulos que utilizam "p_unit".

.ip "25.04.97  3.0.8" 20
Foi introduzido o teste do teclado estar pronto na interrup��o
(em "dev/con.c").

.sp
Foi alterado o "timeout" de 1 s. para 60 ms. da espera pelo endere�o
ETHERNET (em "itnet/frame.").

.ip "14.05.97  3.0.9" 20
Foram feitos pequenos consertos em "dev/meta_dos" ("close" faltando
e trocada a ordem "swap/root").

.sp
Introduzida a id�ia de "NODEV" e "-" nas especifica��es de dispositivos
no boot do kernel.

.sp
Agora, se n�o tiver dispositivo de SWAP, os textos de " chmod -t"
simplesmente N�O s�o colocados no SWAP (ao inv�s de PANIC).

.ip "07.06.97  3.0.10" 20
Altera��es em "dev/pty.c": Nome agora sempre do cliente, confere melhor
"kernel_pty_tp", servidor pode dar IOCTL.

.sp
Introduzido "max_wait" e "max_silence" em "t_optmgmt".

.sp
No boot, analisa qual o disquete de 3�.

.ip "16.06.97  3.0.11" 20
Retirado os sem�foros "t_outqstart" e "t_olock" da interface de terminais.
Al�m disto, retirado o estado PAGING (agora � TTYSTOP).

.ip "24.06.97  3.0.12" 20
Introduzido o "/dev/grave" e o seu respectivo ATTENTION.

.ip "26.06.97  3.0.13" 20
Desligando as "l�mpadas" de IDLE e INTR quando entra no X-Window.

.ip "19.07.97  3.0.14" 20
Agora descartando os segmentos DATA da entrada quando d� "t_sndrel".

.ip "22.07.97  3.0.15" 20
Criado o ATTENTION para PIPEs.

.ip "28.07.97  3.0.16" 20
Acrescentado o "_attention_index".

.ip "05.08.97  3.0.17" 20
Retirado o nome do evento das mensagens da XTI.

.ip "12.08.97  3.0.18" 20
Consertado o URGENT do TCP.

.ip "02.09.97  3.0.19" 20
Criada a chamada ao sistema "boot".
Simplificadas as mensagens durante o BOOT.

.ip "04.09.97  3.0.20" 20
Colocado no SCB as vari�veis "preemption_mask" e "CSW".

.ip "23.10.97  3.0.21" 20
Inicializando agora o teclado em "dev/con.c".
Alterado o DELAY de todos os m�dulos para usar a fun��o de 1 us.

.ip "18.11.97  3.0.22" 20
Usando o novo "vector.s" simplificado.
A estrura "vecdef" � agora inteiramente inicializada dinamicamente.

.ip "23.11.97  3.0.23" 20
Foi estendida a pesquisa do ROOT durante o "boot"; agora se o n�mero
m�gico n�o � v�lido, continua procurando.

.ip "30.11.97  3.0.24" 20
Revis�o na parte de DNS para aceitar servidores de "mail" e "alias".

.ip "18.12.97  3.0.25" 20
Conserto no "unbind" para voltar corretamente ao estado anterior.

.ip "23.12.97  3.0.26" 20
Acrescentadas as fun��es F1-F12, setas, page up, down, ..., para o teclado.

.ip "11.01.98  3.0.27" 20
Revis�o no "...nopen" e "...lock" dos v�rios dispositivos.

.ip "22.01.98  3.0.28" 20
Pequeno acerto no TCSETNR (agora espera a fila de sa�da esvaziar) e
"ttychars" (agora inicializando todos os campo).
Novos ioctls: TCLOCK e TCFREE.

.ip "21.02.98  3.0.29" 20
A chamada ao sistema "phys" foi interamente refeita; agora podem ser
alocados at� 16 MB em regi�es de tamanhos sem limites.

.ip "24.02.98  3.0.30" 20
Agora, podemos ter at� 16 MB por regi�o!

.ip "28.02.98  3.0.31" 20
Agora a "attention" est� desarmando as chamadas. Dispositivo de "pipe"
n�o est� mais sendo for�ado a ser igual ao "root". O dispositivo "swap"
n�o pode mais ser de tipo LINUX.

.ip "06.03.98  3.0.32" 20
Iniciado o conserto da INTERNET: 1. Dois "attentions" faltando para
"tp_inq_nempty"; 2. Blocos sendo perdidos (problema do "last").

.ip "11.03.98  3.0.33" 20
Continua��o do conserto da INTERNET: 3. Paradas repentinas (causadas
pela atualiza��o n�o simult�nea de "snd_una" e "snd_wnd").
4. Agora mandando segmentos de teste de 1 byte quando a janela fecha.

.ip "17.03.98  3.0.34" 20
Colocado um SPINLOCK em "tp_inq_lock" no m�dulo "itnet/snd.c".
Transformado "off_t" em "unsigned long".

.ip "14.07.98  3.1.0" 20
Reforma da INTERNET para usar a fila circular (RND).
Consertado o esquecimento de fechar o dispositivo em "mount".

.ip "20.07.98  3.1.1" 20
Acrescentado o PCI ED.
Consertado o detalhe do DELIM de "ttyread".
Alterados os DELAYs de "zip.c".

.ip "27.07.98  3.1.2" 20
Adicionado o c�digo para uso dos discos e PPP ("sysmap").

.ip "28.07.98  3.1.3" 20
Alterado o "kaddr.c" para usar apenas letras min�sculas no
nome DNS, n�o reescrever entradas ainda v�lidas e n�o realocar entradas
do "/etc/itnetdev".

.sp
Adicionado o c�digo para uso do ETHERNET ("sysmap").

.ip "25.08.98  3.1.4" 20
Colocado o "pgname" na tabela de processos. Tiradas algumas
vari�veis n�o usadas da UPROC.

.sp
Reforma das regi�es (1a. parte): usando p�ginas de MMU
exclusivas para o processo.

.ip "05.12.98  3.1.5" 20
Reformado o PHYS para tamb�m usar as 
p�ginas de MMU exclusivas para o processo.

.sp
Reformado o SHMEM para tamb�m usar as 
p�ginas de MMU exclusivas para o processo
(al�m de colocar o REGIONL no KFILE e s� permitir
uma regi�o por arquivo).

.ip "21.01.99  3.1.6" 20
Reformado a parte de "text": unificado "xalloc" com "xget" e
"xrelease" com "xput".

.sp
Consertado o problema dos servidores de correio sem endere�o
e/ou mesma preced�ncia.

.sp
Reformulada a ger�ncia de mem�ria: agora cada processo tem
diret�rios e tabelas de p�ginas exclusivos.
Agora o registro "cr3" s� � recarregado quando estritamente
necess�rio ("mmu_dirty").

.sp
Foram revistos o "phys" e a mem�ria compartilhada.
Foram unificadas as regi�es regulares com as "phys"
e mem�ria compartilhada.

.sp
Refeitas as estruturas KFILE e INODE com uni�es.

.sp
Retirado todo o c�digo do SWAP.

.sp
Colocada a mensagem de "tentando ROOT ..." durante o "boot".

.sp
Revis�o em "ed.c".

.sp
Revis�o "itnet/kaddr.c", para retransmitir o pedido de DNS.

.ip "09.02.99  3.1.7" 20
Consertado o problema da falta de SWAP.

.sp
Em revis�o as cores do "video.c".

.sp
O "screen saver" � suspenso para que sejam escritas
as mensagens de erro do kernel. Alterados: "etc/printf.c" e "dev/con.c".

.sp
Alterado "dev/fd.c" para continuar eternamente, no caso de erro de "overrun".

.ip "14.04.99  3.1.8" 20
Adicionado o FAT32 na tabela.

.ip "10.06.99  3.2.0" 20
Adicionado o FAT32 no arquivos "meta_dos.c".

.sp
Criado o "driver" da SB16.

.ip "02.07.99  3.2.1" 20
Revis�o no DNS, para aceitar um computador e dom�nio com o mesmo nome.

.sp
Revis�o no DNS, para fazer a busca reversa (nome do computador a partir do endere�o).

.ip "24.07.99  3.2.2" 20
Colocado um teste de fragmenta��o em "ip.c".

.ip "23.10.99  3.2.3" 20
Instalado a nova vers�o das fun��es de "timeout" (em "proc/clock.c").

.ip "04.11.99" 20
Instalado a nova vers�o das fun��es de "malloc" (em "mem/malloc.c").

.ip "08.12.99" 20
Carregando "/lib/libt.o".

.sp
Postas no SCB dialog os nomes do "init", "sh" e "libt.o".

.sp
Agora, um processo poder ter regi�o DATA de tamanho NULO.

.ip "13.02.00" 20
Introduzido o tratamento de dispositivos ATAPI.

.ip "13.03.00" 20
Introduzido o tratamento de bibliotecas compartilhadas.

.ip "13.04.00" 20
Alterado os tempos de "timeout" de "dev/fd.c".

.ip "17.04.00" 20
Consertado um pequeno problema do "timeout" (found) e
alterados os TIMEOUTs do "/dev/fd.c".

.ip "04.05.00" 20
Inserido o JAZ.

.ip "08.05.00" 20
Inserido o driver para a placa "ethernet" RealTek 100 Mbs.

.ip "06.06.00  4.0.0" 20
Atualizados os nomes das parti��es.

.ip "29.06.00" 20
O n�cleo agora herda o valor de DELAY do "boot2".
A vers�o do BCB � conferida.

.ip "14.07.00" 20
Consertado o erro "Tipo inv�lido de exce��o na pilha", na recep��o
de sinais. Alterado "ctl/vector.s".

.ip "18.07.00" 20
Introduzido o uso do DMA para discos IDE.

.ip "01.08.00" 20
Adicionado a tabela ABNT para os teclados.
.sp
Adicionado o m�dulo para o reconhecimento de dispositivos PnP.

.ip "10.08.00" 20
Adicionado a convers�o de endere�o IP dos endere�os do pr�prio
computador.

.ip "14.08.00" 20
Agora, o redirecionamento de datagramas IP j� decrementa o TTL.

.ip "17.08.00" 20
Adicionado o endere�o do pr�prio computador nas estruturas TCP, UDP e RAW.
Atualizado tamb�m no envio do ICMP ECHO.

.ip "12.10.00" 20
Introduzido o uso da instru��o "invlpg" para invalidar entradas na TLB quando
regi�es de um processo mudam de tamanho.
.sp
A troca de contexto foi agilizada, evitando recarregar sempre a ger�ncia de
mem�ria.

.ip "03.09.01  4.1.0" 20
Novo "driver" para Adaptec 29160.

.sp
Novo formato da tabela de s�mbolos SYM.

.sp
Nova chamada ao sistema "getdirent".

.sp
Consertado o problema dos "buracos" NULOs em diret�rios.

.ip "10.10.01  4.2.0" 20
Criada a chamada ao sistema "select".

.ip "20.11.01" 20
Mudan�a do "cache" de blocos para 4 KB.

.ip "20.12.01" 20
Constru��o da camada de INODEs virtuais.

.ip "20.01.02" 20
Elabora��o do sistema de arquivos FAT12/16/32.

.ip "20.03.02" 20
Elabora��o do sistema de arquivos CD-ROM.

.ip "20.04.02" 20
Elabora��o dos elos simb�licos.

.ip "05.06.02  4.3.0" 20
Nova vers�o das bibliotecas compartilhadas, com resolu��o
din�mica das refer�ncias externas.

.ip "16.06.02" 20
Pequena modifica��o na decis�o de usar LFN ou n�o nos nomes da FAT.

.ip "11.07.02" 20
O c�digo para os dispositivos ATA/ATAPI foi integralmente reescrito.

.ip "15.08.02" 20
In�cio do uso do sistema de arquivos T1.

.ip "03.09.02" 20
Reformulado o PIPE, com um novo sistema de arquivos.

.ip "05.09.02" 20
Introduzida na parte de 16 bits, a mudan�a de algumas cores.
Revis�o na parte das cores do v�deo em modo texto.

.ip "28.10.02  4.4.0" 20
Adicionado o sistema de arquivos EXT2 LINUX, somente para leituras.

.sp
Iniciado a chamada ao sistema "llseek".

.ip "09.11.02" 20
Completado o sistema de arquivos EXT2 LINUX, tamb�m para escritas.

.sp
Chamada ao sistema "llseek" terminada h� muito tempo.

.ip "30.12.02" 20
Corre��o no TCP "snd" para colocar PUSH no segmento que
coincidiu de ficar igual ao tamanho de segmento m�ximo.

.ip "02.04.03" 20
Pequena corre��o no "rcvconnect" (c�digo de erro).

.ip "03.04.03" 20
Corre��o em "sysexec.c" para o caso dos arquivos antigo e novo
serem o mesmo.

.ip "05.05.03" 20
Introduzidos os s�mbolos INTR_PATTERN e IDLE_PATTERN, nos m�dulos
"ctl/common.s", "ctl/intr.s", "ctl/vector.s" e "ctl/idle.s",
que permitem habilitar/desabilitar a impress�o de padr�es
("lampadinhas") no modo texto.

.ip "19.05.03  4.5.0" 20
Modificada a chamada ao sistema "unlink" para que n�o remova mais
diret�rios.

.ip "26.05.03" 20
Modificada ligeiramente a interrup��o de "dev/rtl.c".

.ip "28.05.03" 20
Agora as conex�es remotas ficam no in�cio da fila TCP, antes das
conex�es locais.

.ip "02.06.03" 20
Criado o campo "tp_snd_fin" para verificar o ACK do FIN.

.ip "09.06.03" 20
Alterados v�rios arquivos para possibilitar o compartilhamento das
interrup��es.

.ip "01.10.03" 20
Para a montagem com o sistema de arquivos FAT, cria os nomes DOS de at�
"....~99" para o caso LFN.

.ip "03.10.03" 20
Para a montagem com SB_USER no sistema de arquivos T1, usa os "uid/gid"

.ip "10.10.03" 20
Introduzido o erro ENOTMNT.

.ip "21.10.03" 20
Introduzido o DMESG.

.ip "23.10.03" 20
Adicionado a busca de ALIAS do pr�prio computador em "itnet/kaddr.c".

.ip "05.11.03" 20
Corre��o da tabela do teclado ABNT.

.ip "27.11.03" 20
Primeiro dia do funcionamento triunfal do camundongo USB.

.ip "02.01.04" 20
Primeira revis�o no driver do USB.

.ip "13.01.04" 20
Adicionado o driver para controladores USB do tipo OHCI.

.ip "26.01.04" 20
Adicionado o driver provis�rio para controladores USB do tipo EHCI.

.sp
Eliminado o "use_polling" na inicializa��o do USB.

.ip "27.01.04" 20
Modificada a cria��o de processos: agora as threads do processo 0
compartilham com o pai o diret�rio de p�ginas.
Alterados "proc/nproc.c" e "etc/main.c".

.ip "10.04.04" 20
Pequena corre�ao na cria��o de diret�rios FAT.

.ip "14.05.04" 20
Acrescentado o c�lculo correto do tamanho de um CD multisess�o.

.sp
Acrescentada a obten��o de nome do volume durante a montagem de uma
parti��o FAT.

.ip "22.05.04" 20
Pequena corre��o na compara��o dos nomes de CD ("_" igual a ".").

.ip "16.06.04" 20
Aumentado o valor de NUFILE para 32.

.ip "17.06.04" 20
Acrescentado o "KFILE" em mon.

.ip "05.07.04" 20
Come�ando a funcionar o sistema de arquivos NTFS.
.sp
Colocado o "0" no formato num�rico de "printf" para usar como prefixo
o "0" ao inv�s de branco.

.ip "19.07.04" 20
Acrescentada a fun��o "vprintf".

.ip "02.08.04" 20
Revis�o dos MAJORs, deixando um intervalo.

.ip "06.08.04" 20
Montagem de imagens de sistemas de arquivos ("pseudo device").

.ip "16.08.04" 20
Revis�o nos endere�os virtuais, com o n�cleo em 2 GB.

.ip "23.08.04" 20
Tabela din�mica dos pseudo terminais (no SCB).

.ip "02.09.04" 20
O "driver" para discos (de mem�ria) USB come�ou a funcionar.

.ip "04.09.04" 20
O n�cleo atualiza os dispositivos de "/dev" a partir de distktb.

.ip "10.09.04" 20
Consertado detalhe do NTFS (nem sempre "ntfs_ntvattrget" considera
um erro o fato de N�O encontrar um atributo).

.ip "16.09.04" 20
Consertado o "pseudo_dev.c".

.ip "19.09.04" 20
Agora, os novos blocos T1 alocados N�O s�o mais zerados (isto deve
ser feito por quem chama "t1_block_map".

.ip "27.09.04" 20
Anexa��o/desanexa��o din�mica de dispositivos USB come�ou a funcionar.

.ip "02.10.04" 20
Criada a fun��o "realloc_byte".

.sp
O sistema de arquivos FAT agora tem um vetor com os valores da FAT.

.ip "05.10.04" 20
Acrescentado o campo "fs_rel_inode_attr" na tabela DIRENT.

.ip "06.10.04" 20
Tamb�m s�o consideradas parti��es l�gicas na cria��o din�mica de tabelas
de parti��es.

.ip "10.10.04" 20
Criados os novos caracteres de convers�o "\%v", "\%r" e "\%m" para "printf".

.sp
Foram substitu�dos todas as refer�ncias a "id" para "str".

.ip "11.10.04" 20
Criado os novo caractere de convers�o "\%g" para "printf".

.sp
Substitu�das todas as referencias a "prpgnm" por "\%g".

.ip "08.11.04" 20
Agora o n�cleo recebe o "dmesg" do "boot2".

.ip "02.12.04  4.7.0" 20
Corrigido o travamento do TCP/IP na desconex�o (corrigido
"itnet/ksnd.c").

.ip "15.12.04" 20
Corrigido o erro de escrita dos diret�rios do LINUX
(NULO ao final dos nomes), "ext2fs/ext2dir.c".

.ip "23.12.04" 20
Alterado o local do conte�do do bloco para o final de ITBLOCK.

.ip "20.01.05  4.8.0" 20
Consertada a montagem de CDROMs (problema do "nojoliet,norock"),
e estendida para aceitar sess�es com SUPERBLOCOs inv�lidos.

.sp
Introduzida a op��o "lfn/nolfn" para sistemas de arquivos FAT.

.ip "10.03.05" 20
Consertado o problema do "timeout" para o comando IDENTIFY em
"ata-all.c".

.sp
Alterado o c�lculo do cilindro na tripla geom�trica da tabela de 
parti��o (1023).

.ip "29.06.05" 20
Acrescentado o tipo de parti��o PAR_DOS_EXT_L a "h/disktb.h"
e "dev/disktb.c".

.ip "01.07.05" 20
Ligado o "#ifdef" dos nomes dos dispositivos em "usb/usb_subr.c" (USB_KNOWNDEV).

.sp
Atualizado o c�lculo da geometria, em "dev/disktb.c".

.ip "06.07.05" 20
Atualizado o m�dulo USB para ler um "hub" filho de outro "hub" ("usb/bus.c")
e aceitar discos com protocolo ATAPI ("usb/ud.c").

.ip "22.08.05" 20
Alterado "ohci.c" para encontrar adequadamente o endere�o da porta.

.sp
In�cio dos trabalhos do protocolo NFS, vers�o 2.

.ip "02.09.05" 20
Nova convers�o dos tempos da FAT.

.ip "30.11.05" 20
As filas HASH dos INODEs e BHEADs agora est�o usando SPINLOCK.

.ip "21.12.05" 20
Foi retirado o SPINLOCK da fila da "cput" para tentar resolver o
problema do travamento dos "pty"s. Vamos ver ser resolve.

.ip "31.12.05" 20
Foram retirados os SPINFREE e SPINLOCK de "event.c", "sema.c" e "sleep.c", de tal
modo que durante a inser��o na CORERDY o sem�foro da fila HASH continua trancado.

.ip "01.07.06  4.9.0" 20
Implementa��o do modo texto SVGA (1024x768).

.ip "21.08.06" 20
Revista a fila "listen" TCP para remover entradas "esquecidas".

.ip "22.08.06" 20
Criado a nova op��o "max_client_conn" da XTI e TCP.

.ip "30.08.06" 20
Vers�o preliminar do protocolo DHCP.

.ip "04.10.06" 20
Introduzido o INODE dirty count.

.ip "16.08.07" 20
T�rmino da revis�o do USB. Introduzido o suporte a controladores EHCI.

.ip "28.08.07" 20
Revis�o da obten��o dos caracteres 8.3 (em "fatfs/fatlfn.c").
