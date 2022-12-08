.bp

.sp 5

.nf
     *********************************************************
     *							     *
     *			    CAP�TULO 6			     *
     *							     *
     *	           CHAMADA � "SHELL" E AMBIENTE	             *
     *							     *
     *********************************************************

.fi

.sp 4


.pp
No TROPIX, ap�s o "login", a "shell" � invocada para ler
e executar comandos do usu�rio em um terminal espec�fico.
Poder� tamb�m ser chamada explicitamente pelo usu�rio, como qualquer
comando, ou implicitamente, como para a execu��o de um arquivo de
comandos ("script").


.sp 4
.b
6.1 - Chamada � "shell"
.r

.pp
A chamada � "shell" obedece � seguinte sintaxe:
.sp
.in +10
 [-]sh [-c <comando>] [-erv]
.in -10
.sp
 onde "cmdarq" � um comando ou um arquivo de comandos.


.pp
Se o primeiro caractere do argumento 0,
ou seja o nome do comando "sh", for precedido pelo caractere
"-", a "shell" executar� inicialmente o arquivo de comandos
"$HOME/.profile",
passando depois a receber os comandos normalmente. 


.pp
As op��es t�m os seguintes significados:
.in +5

.ip -c
executa o <comando> dado como argumento.

.ip "-e"
Termina a execu��o quando um comando retorna erro.

.ip "-r"
Verifica a reescrita de arquivos no redirecionamento.

.ip "-v"
Lista cada linha de comandos lida do arquivo de entrada.

.in -5
.lp


.sp 4
.b
6.2 - "Prompt"
.r

.pp
O uso mais comum da "shell" � o interativo.
A "shell" fornece um "prompt" (caractere ou cadeia de caracteres),
definido pela vari�vel "PS1", sempre que est� apto a receber comandos.
Se esse comando deve continuar em outra linha, � fornecido um "prompt"
secund�rio, definido pela vari�vel "PS2".
Os "prompt" podem ser modificados atrav�s
da atribui��o de um novo valor �s suas vari�veis.


.sp 4
.b
6.3 - Ambiente
.r


.pp
A "shell" quando chamada recebe o ambiente de execu��o,
que nada mais � do que uma lista
de vari�veis. Este ambiente � passado para os subprocessos criados por ela.

.pp
Por exemplo, as vari�veis "HOME", "PATH", "PS1" e "PS2"
usadas pela "shell" (ver 3.1) s�o passadas a ela atrav�s do ambiente.

.in +5
.sp
"PS1" e "PS2" s�o os "prompts" principal e secund�rio da "shell".

.sp
"HOME" � o diret�rio corrente, representado por "."
e usado na resolu��o de refer�ncias a arquivos que n�o come�am com "/".
O comando interno "cd" � usado para se mudar o diret�rio corrente.

.sp
"PATH" define os diret�rios onde os comandos a executar devem ser
procurados e a ordem desta procura.
Se n�o for especificado ser�, por omiss�o, o diret�rio corrente,
"/bin" e "/usr/bin", nessa ordem. Assume-se,
"PATH=.:/bin:/usr/bin",  onde o caractere ":" separa os nomes dos diret�rios.
Se o comando come�a com "/", o "PATH" n�o � usado.

.in -5

.pp
O usu�rio pode atribuir novos valores para essas vari�veis,
bem como criar outras.
Ent�o, os "prompts" podem ser escolhidos pelo usu�rio
e os valores das vari�veis "HOME" e "PATH" modificados sempre que necess�rio.

.pp
Essas modifica��es e adi��es de vari�veis s� s�o repassadas ao
ambiente atrav�s do comando interno "export". 
Assim, os processos criados pela "shell", para executar os comandos,
receber�o o ambiente da "shell", somente com as modifica��es
e adi��es explicitadas atrav�s do comando interno "export".


.sp 4
.b
6.4 - Sinais
.r


.pp
Os sinais do processo que inicia a "shell" s�o tamb�m passados
a ela no ambiente
e ser�o  repassados aos processos criados para executar os comandos,
com uma exce��o:
para os comandos terminados por "&", que dever�o ser executados em
"background", o sinal
"SIGINT"  � passado  com o valor "SIG_IGN", que far� com que eles
n�o possam ser interrompidos pelo terminal teclando o caractere "intr"
(usualmente <^C>).
