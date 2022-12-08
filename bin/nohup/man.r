.bp
.he 'NOHUP (cmd)'TROPIX: Manual de Refer�ncia'NOHUP (cmd)'
.fo 'Atualizado em 15.04.00'Vers�o 3.2.3'Pag. %'

.b NOME
.in 5
.wo "nohup -"
executa um comando imune ao sinal SIGHUP
.br

.in
.sp
.b SINTAXE
.in 5
.(l
nohup <comando> [<op��es>] [<argumentos>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "nohup" executa o <comando> ignorando o sinal SIGHUP.
O objetivo � evitar o t�rmino do <comando> quando o usu�rio sai de sess�o
(isto �, quando termina o "login" (cmd), "rlogin" (cmd) ou "telnet" (cmd)).

.sp
Se as sa�das padr�o (normal e de erro) n�o foram rediredionadas, elas s�o
adicionadas ao final do arquivo "nohup.out". Se este arquivo n�o puder
ser escrito no diret�rio corrente, a sa�da � posta no arquivo "$HOME/nohup.out".

.in
.sp
.b OBSERVA��ES
.in 5
No caso de:

.sp
.(l
	nohup <comando1> ; <comando2>
.)l

.sp
a a��o de "nohup" aplica-se apenas ao <comando1>.

.sp
Para estes casos � recomendado criar um arquivo contendo a seq��ncia de comandos,
e execut�-la atrav�s de "sh" (cmd).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sh, login, rlogin, telnet
.br
.wo "(sys): "
signal
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in







.bc	/*************************************/
.bp
.he 'NICE (cmd)'TROPIX: Manual de Refer�ncia'NICE (cmd)'
.fo �scrito em 30.7.87'Vers�o 1.0'Pag. %'

.b NOME
.in 5
.wo "nice -"
executa um programa com prioridade alterada
.br

.in
.sp
.b SINTAXE
.in 5
nice [-p [+]incr] comando [argumentos]

.in
.sp
.b DESCRI��O
.in 5
O utilit�rio "nice" executa o "comando" com a prioridade alterada,
de acordo com o argumento "incr" (que normalmente � considerado
como um n�mero negativo, isto �, um decremento de prioridade). 
.sp
As prioridades v�o de -20 (m�nima) a +20 (m�xima). A prioridade
normal de um programa executado diretamente (isto �, sem o comando
"nice") � 0.
.sp
Utilizando o "nice" sem o argumento "incr", "comando" ser� executado
com prioridade -10. Se for dado "incr", ele ser� utilizado como
prioridade para o "comando".
.sp
Para o caso de superusu�rios, podemos utilizar o prefixo "+"
ao incremento, e neste caso ele ser� considerado positivo.

.in
.sp
.b OBSERVA��ES
.in 5
Repare que tanto no comando "nice" como no "ps", utilizamos a id�ia
intuitiva de utilizar n�meros positivos (ou maiores) para prioridades
melhores (que melhoram a escala��o do processo).
Isto n�o � o caso da chamada ao sistema "nice" cuja conven��o
� a inversa.
.sp
Atrav�s do comando "ps" podemos monitorar a prioridade do processo
em quest�o.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sh, ps
.br
.wo "(sys): "
nice
.br

.in
.sp
.b EXEMPLOS
.in 7
.sp
.nf
	          nice -p 5 sroff arq.r >arq &

     formata o arquivo "arg.r" em "background" com prioridade -5.
.fi

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
.ec	/*************************************/
