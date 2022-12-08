.bp
.he 'NICE (cmd)'TROPIX: Manual de Refer�ncia'NICE (cmd)'
.fo 'Atualizado em 01.06.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
.wo "nice -"
executa um comando com prioridade modificada
.br

.in
.sp
.b SINTAXE
.in 5
.(l
nice [-p [+]<inc>] <comando> [<op��es>] [<argumentos>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "nice" executa o <comando> com a prioridade de escala��o
modificada (normalmente decrementada de 10, veja a op��o "-p").

.sp
As prioridades v�o de -20 (m�nima) a +20 (m�xima). A prioridade
normal de um programa executado diretamente (isto �, sem o comando
"nice") � 0.

.sp
As op��es do comando s�o:

.in +3
.ip '-p <inc>' 11
Decremento de prioridade:
Utilizando a op��o "-p" nesta forma, a prioridade ser� decrementada
de <inc> ao inv�s de 10.

.ip '-p +<inc>' 11
Incremento de prioridade:
Utilizando a op��o "-p" nesta forma, a prioridade ser� incrementada
de <inc>. Somente o superusu�rio pode incrementar a prioridade.

.ep
.in -3

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
