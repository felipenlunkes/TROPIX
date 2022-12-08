.bp

.sp 5

.nf
     *********************************************************
     *							     *
     *			    CAP�TULO 2			     *
     *							     *
     *	     		     COMANDOS			     *
     *							     *
     *********************************************************

.fi

.sp 4


.pp
O usu�rio se comunica com o sistema operacional TROPIX por meio dos
comandos fornecidos � "shell". Sempre que a "shell" est� com o controle
do terminal, ela os interpreta e executa. A indica��o de que a "shell"
est� com o controle do terminal � dada pelo "prompt" escrito pela
"shell" no terminal. O "prompt" � um caractere ou seq��ncia de
caracteres definida pelo usu�rio. Por omiss�o, a seq��ncia "$ " �
utilizada.

.sp 4
.b
2.1 - Comandos simples
.r

.pp
Um comando simples � formado por palavras (seq��ncia de caracteres diferentes
de branco e dos metacaracteres apresentados no decorrer do texto), separadas 
pelos caracteres de espacejamento <sp> ou <ht> (branco ou tab).
A primeira palavra � o nome do comando a ser executado (o argumento 0)
e as demais s�o argumentos para o comando.
Por exemplo:

.sp
.in +5

$ date

.in -5
.sp
� um comando que fornece a data atual.

.sp
.in +5

$ ls -l

.in -5
.sp
lista os arquivos do diret�rio corrente. O argumento "-l" faz com que sejam
listadas tamb�m outras informa��es, como tamanho e data de cria��o de cada
arquivo.


.sp 4
.b
2.2 - Comandos em "background"
.r


.pp
Para executar um comando a "shell" normalmente cria um 
subprocesso e espera pelo seu t�rmino.
O caractere "&" evita a espera pelo t�rmino do comando:
a "shell" cria o subprocesso, escreve na tela sua identifica��o (PID)
e volta a ter o controle do terminal.

.sp
Assim, ao receber:

.sp
.in +5

$ cc prog.c &

.in -5
.sp
a "shell" invoca o compilador "C" para compilar "prog.c", fornece o
n�mero do  subprocesso e, imediatamente, escreve o "prompt".
Enquanto isso, a compila��o se processa concorrentemente e,
quando terminar, n�o dar� qualquer indica��o ao usu�rio.
Pelo n�mero do subprocesso, o usu�rio
poder� consultar o seu estado atrav�s do comando "ps".


.sp 4
.b
2.3 - Lista de comandos
.r


.pp
Os comandos simples podem vir em seq��ncia, formando uma lista de comandos,
desde que separados pelos s�mbolos ";", "&&" ou "||",
que s�o alguns dos metacaracteres da "shell" (um ou mais
caracteres que t�m significado especial para a "shell").


.pp
Os comandos (ou listas de comandos) separados por
";" s�o simplesmente executados em seq��ncia, como se fossem fornecidos em
linhas distintas.
O s�mbolo "||" separando dois comandos (ou duas listas de comandos) 
faz com que o segundo seja executado somente se o primeiro terminar
incorretamente.
Comandos (ou listas de comandos) separados por "&&" ser�o executados
seq�encialmente at� que um dos comandos termine incorretamente.


.pp
As listas de comandos tamb�m podem ser executadas em "background",
se terminadas por "&".


.pp
Os metacaracteres "||" e "&&" t�m a mesma preced�ncia, maior do que a de 
";" e "&", iguais entre si.

.sp
Por exemplo em:

.sp
.in +5

$ ls pg.h && cc -c pg1.c

.in -5
.sp
pg1.c ser� compilado apenas se pg.h (por exemplo contendo declara��es usadas
em pg1.c) existir.

.sp
E em

.sp
.in +5

$ cc -c src/pg1.c || cc -c fonte/pg1.c

.in -5
.sp
pg1.c do diret�rio "fonte" ser� compilado se, por exemplo, n�o existir
pg1.c no diret�rio "src".


.sp 4
.b
2.4 - Redirecionamento de entrada e sa�da
.r


.pp
Os dados de entrada de um comando s�o em geral obtidos da entrada
padr�o que, normalmente, est� associada ao terminal.
Da mesma forma, os dados de sa�da s�o dirigidos para a
sa�da padr�o, tamb�m associada ao terminal.
� poss�vel, no entanto, redirecionar a entrada e/ou sa�da dos comandos
atrav�s de alguns metacaracteres da "shell".
As constru��es apresentadas a seguir podem aparecer em qualquer
lugar em um comando simples
que n�o ser�o passados como argumentos aos comandos invocados.
Note que a substitui��o de comandos e par�metros
� realizada antes que a nota��o a seguir seja analisada.

.in +5
.ip "< nome" 12
Usa o arquivo de nome dado como a entrada padr�o
(relativo ao descritor de arquivos 0).

.ip "> nome" 12
Usa o arquivo de nome dado como a sa�da padr�o
(relativo ao descritor de arquivos 1).
Se o arquivo n�o existe ele � criado; sen�o ele � truncado a zero
caracteres.

.ip ">> nome" 12
Usa o arquivo de nome dado como sa�da padr�o. Se o arquivo j� existe,
a sa�da � anexada a ele; caso contr�rio, o arquivo � criado.

.ip "<< nome" 12
A entrada da "shell" � lida at� a primeira linha que corresponda
literalmente ao "nome" resultante, ou at� um fim de arquivo.

.ip "<&n�mero" 12
Usa o arquivo associado com o descritor de arquivos dado pelo n�mero
como a entrada padr�o. Similarmente para a sa�da padr�o com ">&n�mero".

.ip "<&-" 12
Fecha a entrada  padr�o. Similarmente para a sa�da padr�o com ">&-".

.ep
.in -5

.pp
Se qualquer das cadeias acima for precedida por um n�mero, o descritor de
arquivos que ser� associado ao arquivo � aquele dado pelo n�mero (ao inv�s
dos assumidos por omiss�o 0 e 1). Por exemplo:
.sp
.in +12
 ... 2>&1
.sp
.in -12

associa o descritor de arquivos 2 ao arquivo correntemente associado
com o descritor de arquivos 1.

.pp
A ordem na qual as redire��es s�o especificadas � significante. A
"shell"
avalia as redire��es da esquerda para direita. Por exemplo:
.sp
.in +12
 ... 1> xxx 2>&1
.in -12

.pp
primeiro � associado o descritor de arquivos 1 com o arquivo "xxx".
Depois � associado o descritor de arquivos 2 com o arquivo associado
ao descritor de arquivos 1 (i. e. "xxx"). Se a ordem de redire��es
fosse reversa, o descritor de arquivos 2 seria associado com o
terminal (assumindo que o descritor de arquivos 1 tinha sido) e
depois o descritor de arquivos 1 seria associado ao arquivo "xxx".

.pp
Usando a terminologia introduzida anteriormente,
se um comando � composto de v�rios comandos simples, as redire��es
ser�o avaliadas para o comando como um todo, antes que seja avaliada
para cada comando simples. Isto � a "shell" avalia o redirecionamento
para a lista inteira, ent�o para cada "pipeline" dentro da lista e
ent�o para cada lista dentro de cada comando.

.pp
Se um comando � seguido por '&', a entrada padr�o assumida para o
comando � o arquivo vazio "/dev/null".

.pp
Exemplos:

.sp
.in +5

$ ls > file

.in -5
.sp
o arquivo "file" conter� os nomes dos arquivos do diret�rio corrente.

.sp
.in +5

$ wc < file

.in -5
.sp
o arquivo "file" ser� lido e ser�o listados o n�mero de caracteres, palavras
e linhas encontradas.


.sp 4
.b
2.5 - "Pipes"
.r


.pp
A sa�da de um comando pode ser concatenada � entrada de outro atrav�s do 
operador "|".

.sp
Assim,

.sp
.in +5

$ ls -l | wc

.in -5
.sp
tem efeito similar a

.sp
.in +5

$ ls -l > file ; wc < file

.in -5
.sp
com as vantagens de que o arquivo "file" n�o precisa ser especificado
e os dois comandos podem executados concorrentemente.

.pp
V�rios comandos podem ser concatenados atrav�s do "pipe".

.sp
Exemplo:

.sp
.in +5

$ ls | grep teste | wc -l

.in -5
.sp
listar� o n�mero de arquivos no diret�rio corrente que cont�m a palavra
"teste" em seu nome.


.pp
Numa lista de comandos, "pipes" podem ser especificados e, neste
caso, a preced�ncia do metacaractere "|" �
maior que a dos metacaracteres "||", "&&", ";" e "&".


.sp 4
.b
2.6 - Valor de Retorno
.r

.pp
Atrav�s da chamada ao sistema "exit", os comandos retornam � "shell" um
valor inteiro, indicando seu estado de t�rmino.
O valor 0 significa que o programa terminou normalmente;
qualquer valor distinto de 0 indica t�rmino anormal.
Numa lista de comandos ou numa linha de "pipes", o valor que a "shell"
finalmente retorna � o do �ltimo comando executado.

.sp 4
.b
2.7 - Resumo
.r

.pp
Os comandos interpretados pela "shell" devem obedecer � seguinte sintaxe:

.sp
CMD [delim CMD] ...

.sp
onde:

.sp
CMD = cmd [arg] ... [<ent] [>sai]

.in +2

.ip cmd 6
nome do comando

.ip arg 6
argumento para o comando

.ip ent 6
arquivo de entrada

.ip sai 6
arquivo de sa�da

.lp


.sp 2

.in -2 
delim = |  ;  &  &&  ||

.ip 'CM1 ; CM2    ' 13
CM1 e CM2 s�o executados seq�encialmente.

.ip 'CM1 | CM2    ' 13
As execu��es de CM1 e CM2 s�o iniciadas simultaneamente.
A sa�da de CM1 � a entrada de CM2.
A "shell" espera CM2 terminar. ("Pipe")

.ip 'CMD &        ' 13
A execu��o de CMD � iniciada, mas seu t�rmino n�o �
esperado. ("Background")

.ip 'CM1 && CM2   ' 13
CM2 � executado se CM1 terminar corretamente. ("And")

.ip 'CM1 || CM2   ' 13
CM2 � executado se CM1 nao terminar corretamente. ("Or")

.lp


.sp 2
A preced�ncia dos metacaracteres �:

.sp
.in +5
|
.sp
|| &&

.sp
| ;

.in -5

.sp 4
.b
2.8 - Arquivos de Comandos
.r


.pp
Em uso interativo, os comandos s�o lidos do terminal e executados.
Entretanto, esses comandos podem ser provenientes de um arquivo de
comandos ("script"), previamente editado.
Assim, se o arquivo "arq" contem comandos para a "shell",

.sp
.in +5
$ sh arq

.in -5
.sp
criar� um subprocesso em que uma "shell" filha da original 
ler� os comandos de "arq" e os executar�.

.pp
Se esse arquivo de comandos tiver o atributo de modo indicando
que ele � execut�vel (veja "chmod(cmd)") a chamada

.sp
.in +5
$ arq

.in -5
.sp
ser� equivalente � anterior. Em qualquer hip�tese, � criado um
subprocesso que executa uma "shell" filha.

.pp
O comando interno "." evita a cria��o de um subprocesso. Assim

.sp
.in +5
$ . arq

.in -5
.sp
os comandos s�o executados diretamente pelo "shell".

.pp
Erros detectados pela "shell", quando da execu��o
de um arquivo de comandos, causam o t�rmino da execu��o desse arquivo.


.bp
.b
2.9 - Coment�rios e Linhas de Continua��o
.r

.pp
O metacaractere "#" inicia um coment�rio, que se estende at� o final da linha.
� �til em arquivos de comandos.

.pp
Quando for necess�rio usar varias linhas para a entrada de um
comando, as linhas que t�m continua��o dever�o ser terminadas
pela seq��ncia "\<nl>" (barra invertida seguida de <nl>). (Ver 3.3).

.sp 4
.b
2.10 - Comandos Internos
.r

.pp
Alguns comandos especiais n�o causam a cria��o de um subprocesso para
sua execu��o, sendo esta realizada internamente pela pr�pria "shell".
S�o eles:

.sp
":", ".", "cd", "eh", "eval", "exec", "exit", "export", "false", "gh",
"h", "login",  "read", "readonly", "rehash", "set", "shid", "shift",
"time", "times", "trap", "true", "umask", "unset", "wait" e "xh".


.pp
A utilidade de alguns desses comandos ser� apontada no decorrer do texto e uma
explica��o mais detalhada pode ser encontrada no Cap�tulo 4.
