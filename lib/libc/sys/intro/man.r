.bp
.he 'INTRO (sys)'TROPIX: Manual de Refer�ncia'INTRO (sys)'
.fo 'Atualizado em 14.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "intro -"
introdu��o aos conceitos fundamentais do sistema
.br

.in
.sp
.b DESCRI��O
.in 5
Esta introdu��o define uma s�rie de conceitos importantes do
TROPIX, que ser�o utilizados em todos o sistema, e s�o de particular
import�ncia para a utiliza��o das chamadas ao sistema.

.ip " 1." 4
.b "PROCESSO:"
Um espa�o de endere�amento, um programa em execu��o neste espa�o
e seus recursos necess�rios do sistema.

.ip " 2." 4
.b "IDENTIFICA��O DO PROCESSO:"
Cada processo ativo do sistema � identificado univocamente por
um inteiro positivo, cujo valor m�ximo � 2147483647 (2 ** 31 - 1).
Repare que neste ponto o TROPIX difere do UNIX,
no qual as identifica��es s� v�o at� 30000.
Usualmente, abreviamos a identifica��o de um processo 
como "ID" do processo, ou simplesmente "PID".

.ip " 3." 4
.b "IDENTIFICA��O DO PAI DO PROCESSO:"
Um processo � criado por um processo ativo j� existente
(veja "fork" (sys)).
A identifica��o do pai do processo � o PID do criador do processo,
durante o tempo de vida do criador.
Ap�s o t�rmino do criador, a identifica��o do pai do processo
� o PID do processo especial "init" (ver abaixo).

.ip " 4." 4
.b "TEMPO DE VIDA DE UM PROCESSO:"
Ap�s a cria��o de um processo atrav�s da chamada "fork",
o processo � considerado ativo, e
o programa associado e espa�o de endere�amento existem
at� o seu t�rmino.
Ao terminar, o processo entra em um estado inativo
("SZOMBIE", ver "ps" (cmd)),
quando alguns de seus recursos s�o liberados, enquanto
que outros ainda s�o mantidos (como por exemplo o seu PID).
Quando um (outro) processo executa um "wait" (sys) para um processo
inativo, os recursos remanescentes s�o liberados, e o
processo deixa de existir. 

.ip " 5." 4
.b "GRUPO DE PROCESSOS:"
Cada processo ativo � membro de um grupo de processos
(que � identificado por um PID). 
Durante a cria��o de um processo, o novo processo passa
a pertencer ao grupo do qual o criador � um membro. 
O objetivo do conceito de grupo de processos � 
o envio de sinais para processos relacionados
(ver "kill" (sys)).

.ip " 6." 4
.b "IDENTIFICA��O DO GRUPO DE PROCESSOS:"
A identifica��o do grupo de processos � o PID do l�der do grupo
(ver abaixo).

.ip " 7." 4
.b "L�DER DO GRUPO DE PROCESSOS:"
O l�der de um grupo de processos � o criador do grupo.
O seu PID � igual ao PID do seu grupo de processos.
Qualquer processo pode desligar-se do seu grupo atual, e
tornar-se l�der de um novo grupo de processos atrav�s
da chamada ao sistema "setpgrp". 

.ip " 8." 4
.b "GRUPO DE TERMINAIS:"
Cada processo ativo pode ser membro de um grupo de processos
associado a um terminal.
Durante a cria��o de um processo, o novo processo passa
a pertencer ao grupo do qual o criador � um membro. 
O grupo � criado pelo processo que abriu o terminal.
O objetivo do conceito de grupo de processos associados a um terminal � 
o envio de sinais para todos os processos associados a um terminal,
como por exemplo, o "SIGINT" e "SIGQUIT" (ver "termio" (fmt)). 

.ip " 9." 4
.b "IDENTIFICA��O DO GRUPO DE TERMINAIS:"
A identifica��o do grupo de processos associados a um terminal
� o PID do processo que abriu o terminal.

.ip "10." 4
.b "IDENTIFICA��O DO US�RIO REAL E GRUPO REAL:"
Cada usu�rio do sistema � identificado por um inteiro positivo
(0 a 65535) chamado de identifica��o do usu�rio real (UID real).
Cada usu�rio � tamb�m membro de um grupo, que � tamb�m identificado
por um inteiro positivo chamado de identifica��o do grupo real (GID real).
Cada processo ativo t�m
um UID real e um GID real, que s�o herdados do processo 
criador deste processo.

.ip "11." 4
.b "IDENTIFICA��O DO US�RIO EFETIVO E GRUPO EFETIVO:"
Cada processo ativo t�m
um UID efetivo e um GID efetivo, que s�o utilizados para determinar
as permiss�es de acesso aos arquivos (ver adiante).
O UID efetivo e o GID efetivo s�o iguais, respectivamente,
ao UID real e GID real do processo, a n�o ser que o processo
(ou um de seus antecessores) seja a execu��o de um arquivo
que tem o indicador "set user ID" ou "set group ID" ligado
(veja "exec" (sys)).

.ip "12." 4
.b "SUPERUSU�RIO:"
Se o UID efetivo de um processo � "0" (zero), ele � considerado
um processo superusu�rio, e recebe previl�gios especiais, tais
como a permiss�o de acesso a qualquer arquivo. 

.ip "13." 4
.b "PROCESSOS ESPECIAIS:"
Supondo que o sistema tenha "n" CPUs, os processos de PID "0" a "n+1"
s�o processos especiais (os demais s�o regulares).
O processo "0" � o "scheduler"; os processos "1" a "n" s�o os
"dispatchers" das v�rias CPUs, e o processo "n+1" � o "init",
repons�vel pela inicializa��o do sistema, e pai de todos os processos
que se tornam �rf�os.
O PID do processo "init" � chamado de "initpid".

.ip "14." 4
.b "DESCRITORES DE ARQUIVOS:"
Um descritor de arquivo � um inteiro pequeno utilizado para realizar
opera��es de entrada/sa�da em arquivos.
Existe um limite de arquivos abertos simultaneamente
por um processo (no momento 20).
Um descritor de arquivos � obtido por chamadas ao sistema
tais como "open" ou "pipe" (sys), e pode ser usado como
argumento em chamadas ao sistema tais como "read", "write",
"ioctl" e "close" (sys).

.ip "15." 4
.b "NOMES DE ARQUIVOS:"
Nomes consistindo de at� 255 caracteres podem ser usados
para qualquer arquivo regular, especial, diret�rio ou FIFO. 
Podem ser usados quaisquer caracteres, exceto <nul> ('\0')
e '/'.
Repare no entanto, que n�o � aconselh�vel utilizar os caracteres
'*', '?', '!', '[' ou ']' como partes do nome de um arquivo,
em virtude do significado especial destes caracteres para o "sh" (cmd).
Tamb�m n�o � recomendado o uso de caracteres sem representa��o
gr�fica.

.ip "16." 4
.b "CAMINHOS:"
Um caminho ("pathname") � um cadeia de caracteres (terminada por <nul>),
come�ando por um '/' opcional, seguido de zero ou mais nomes de diret�rios
separados por '/', possivelmente seguido de um nome de arquivo.

.sp
Se um caminho come�a por '/', a busca do arquivo come�a da raiz
do sistema de arquivos. Em caso contr�rio, come�a do diret�rio corrente.

.sp
Um caracter '/' sozinho representa a raiz do sistema de arquivos. 

.ip "17." 4
.b "DIRET�RIOS:"
Diret�rios s�o arquivos destinados exclusivamente para dar nomes
aos arquivos. Cada entrada de um diret�rio cont�m um nome de
um arquivo (ou outro diret�rio) e um n�mero que identifica o
arquivo naquele sistema de arquivos.

.ip "18." 4
.b "DIRET�RIO CORRENTE:"
A cada processo � associado um diret�rio corrente, que �   
utilizado para a busca dos arquivos atrav�s do caminhos.
Ele pode ser mudado atrav�s da chamada ao sistema "chdir".

.ip "19." 4
.b "PERMISS�ES DE ACESSO AOS ARQUIVOS:"
Para que um processos possa ler, escrever
ou executar/caminhar em um arquivo
� necess�rio que uma ou mais das condi��es abaixo sejam v�lidas:

.sp
.in +5
O UID efetivo do processo � superusu�rio, e o processo deseja
ler, escrever em um arquivo
ou caminhar em um diret�rio.

.sp
O UID efetivo do processo � superusu�rio, e o processo deseja
executar um arquivo
e um dos 3 bites de execu��o est�o ligados. 

.sp
O UID efetivo do processo � igual ao UID do arquivo e o bite
adequado de permiss�o da parte do "dono" (0700) do modo do
arquivo est� ligado.

.sp
O UID efetivo do processo n�o � igual ao UID do arquivo,
mas o GID efetivo do processo � igual ao GID do arquivo,
e o bite
adequado de permiss�o da parte do "grupo" (0070) do modo do
arquivo est� ligado.

.sp
O UID efetivo do processo n�o � igual ao UID do arquivo,
o GID efetivo do processo n�o � igual ao GID do arquivo,
mas
o bite
adequado de permiss�o da parte dos "outros" (0007) do modo do
arquivo est� ligado.

.in -5
.sp
Em caso contr�rio, a permiss�o correspondente � negada.

.ip "20." 4
.b "ERROS:"
Cada chamada ao sistema devolve um valor, que pode indicar 
um poss�vel erro. Em geral, um valor de retorno NULO ou positivo
indica um chamada ao sistema sem erro, e um valor de retorno
negativo (em geral "-1") indica que ocorreu um erro.
Neste caso, a vari�vel externa "errno" cont�m o n�mero do erro
detetado. Esta vari�vel n�o � zerada por chamadas ao sistema
corretas, de tal modo que o seu valor s� deve ser consultado
se houver ocorrido um erro.

.sp
As fun��es "strerror" e "perror" (libc) podem ser usadas
para imprimir um texto explicativo do erro.

.ep

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
init
.br
.wo "(sys): "
fork, wait, setpgrp
.br

.in
