.bp
.sp 5

.nf
     *********************************************************
     *							     *
     *			    CAP�TULO 5			     *
     *							     *
     *	       A SHELL COMO LINGUAGEM DE PROGRAMA��O	     *
     *							     *
     *********************************************************

.fi

.sp 4

.pp
Al�m de seu uso como um interpretador interativo de comandos,
a "shell" pode ser usada tamb�m como linguagem de programa��o.
Duas de suas caracter�sticas como linguagem de programa��o j� foram
abordadas: arquivos de comandos e vari�veis.
Outras facilidades como as estruturas de controle tradicionais est�o
dispon�veis, possibilitando a cria��o de arquivos de comandos
("scripts"), que desempenham tarefas complexas. Estas caracter�sticas
incluem o seguinte:

.in +5
.ip "-"
Arquivos de comandos: um arquivo pode conter uma seq��ncia de comandos
para a execu��o posterior.

.ip "-"
Vari�veis:
um arquivo de comandos pode ter declara��es, atribui��es e
expans�es de vari�veis.

.ip "-"
Argumentos:
um arquivo de comandos pode receber os argumentos passados
na linha de comando de sua evoca��o.

.ip "-"
Execu��o condicional:
a seq��ncia de comandos a executar pode variar,
podendo ser definida por condi��es externas (comandos if..then..else..elif).

.ip "-"
Sele��o de casos:
uma entre v�rias seq��ncias de comandos pode ser
selecionada para a execu��o, dependendo de condi��es externas.

.ip "-"
Repeti��o enumerada:
� poss�vel a repeti��o da execu��o de uma
seq��ncia de comandos, enumerando-se os valores de uma vari�vel
de controle do la�o.

.ip "-"
Repeti��o condicional:
� poss�vel a repeti��o de uma seq��ncia de
comandos, enquanto persistir uma condi��o, ou at� ocorrer uma
condi��o.

.ip "-"
Blocos de comandos:
uma seq��ncia de comandos pode ser agrupada e assim as mesmas condi��es
de execu��o podem ser especificadas para toda a seq��ncia.

.ip "-"
Tratamento de Exce��es:
� poss�vel explicitar quais a��es devem ser realizadas quando
da ocorr�ncia de uma exce��o.

.ip "-"
Coment�rios:
textos explicativos podem ser inseridos como coment�rios em um
arquivo de comandos.

.ep

.in -5

.pp
Os comandos de programa��o e os blocos de comandos a serem
vistos a seguir, podem substituir comandos simples em uma lista de
comandos, podem sofrer redirecionamentos de entrada e sa�da como
um comando simples, ou podem ser executados em "background" como
um comando simples. Quando n�o especificado o valor de retorno
de um bloco de comandos ou de um comando de programa��o � o do
ultimo comando simples executado.


.sp 4

.b
5.1 - Passagem de Argumentos
.r

.pp
Como j� visto em "Comandos" (cap�tulo 2), a chamada de um
comando � constitu�da por uma ou mais seq��ncias de caracteres.
A primeira indica o nome do comando a ser evocado, as pr�ximas,
desde que iniciadas pelo caractere '-', indicam op��es de
funcionamento do comando, ou seja o "modo" de execu��o do comando,
e as �ltimas indicam os objetos sobre os quais o comando vai agir.
Todas estas seq��ncias de caracteres posteriores ao nome do
comando s�o consideradas como argumentos do comando.

.pp
A "shell" permite que um arquivo de comandos
que precisa ser interpretado por uma "shell" para executar,
seja externamente indistingu�vel de um comando tradicional com um
programa objeto execut�vel diretamente. Seguindo este objetivo
a "shell" passa os argumentos dados para um arquivo com comandos,
que pode acess�-los atrav�s dos par�metros posicionais $0, $1, $2, ..., $9.
Os nomes dessas vari�veis foram inspirados pelo vetor de argumentos
"argv" passados a primeira fun��o a executar de um programa na
linguagem de programa��o "C".

.pp
Os par�metros posicionais podem ser redefinidos pelo
comando interno "set" e reordenados pelo comando interno "shift" (cap�tulo 4).

.sp 4

.b
5.2 - Execu��o Condicional
.r

.pp
A determina��o da execu��o ou n�o de listas de comandos pode ser
realizada a tempo de execu��o. Para tanto existem os comandos de
programa��o "if", "else", "elif" e "fi". A sua sintaxe �:

.sp
.b if
lista 
.b then
lista [

.b elif
lista 
.b then
lista]... [
.b else
lista]
.b fi
.br

.pp
A lista seguinte ao
.b if
� executada e, se ela tiver um valor de retorno igual a zero,
ent�o a lista ap�s o
.b then
� executada. Sen�o a lista ap�s o
.b elif
se dada � executada e se o seu valor de retorno for zero a lista ap�s o
pr�ximo
.b then
� executada. Falhando a lista do 
.b elif
, a lista ap�s o
.b else
� executada. Se nenhuma lista associada a um
.b then
ou a um
.b else
for executada o valor de retorno do
.b if
ser� zero.

.sp 4

.b
5.3 - Sele��o de Casos
.r

.pp
Para a sele��o de uma lista de comandos entre v�rias para
a execu��o a "shell" tem o comando "case". Sua sintaxe �:

.sp
.b case
palavra 
.b in
[padr�o [|padr�o] ...) lista ;;]
.b esac
.br

.pp
O comando
.b case
executa a lista associada ao primeiro padr�o que
tenha correspond�ncia com a palavra dada. A forma dos padr�es
� a mesma que � usada para a gera��o de nomes de arquivos
exceto que uma barra ('/'),
um ponto ('.') inicial, ou um ponto ('.') imediatamente ap�s
uma barra ('/') n�o precisam ser explicitados.

.sp 4

.b
5.4 - Repeti��o Enumerada
.r

.pp
A repeti��o enumerada permite a execu��o de uma lista de comandos
para cada um de uma lista de nomes dados. A cada itera��o a vari�vel
de controle assume um dos nomes dados e assim os comandos da lista
podem realizar uma determinada opera��o sobre ele. A sintaxe do
comando de repeti��o enumerada �:

.sp
.b for
nome [
.b in
palavra ...]
.b do
lista
.b done
.br

.pp
Este comando faz a repeti��o da execu��o da lista
dada, por um n�mero de vezes definido a priori. A cada repeti��o
� vari�vel identificada por "nome" � atribu�do como valor a palavra
cuja posi��o entre as palavras dadas corresponde ao n�mero da
itera��o corrente. Se a parte "
.b in
palavra ..." n�o for dada ser� assumido como palavras dadas
os par�metros posicionais (veja
.b
"Substitui��o de Par�metros"
.r
adiante). A execu��o deste comando termina quando � "nome"
j� houver sido atribu�do todas as palavras dadas.


.sp 4

.b
5.5 - Repeti��o Condicional
.r

.pp
A "shell" tem constru��es de controle para a repeti��o de uma
lista de comandos enquanto persistir uma condi��o ("while"), ou
at� que ocorra uma condi��o. Sua sintaxe �:

.sp

.b while
lista
.b do
lista
.b done
.br

.pp
Um comando
.b while
executa repetidamente a primeira e a segunda lista. Se o valor
de retorno do �ltimo comando da primeira lista for diferente de zero,
a segunda lista n�o � executada e a repeti��o
termina. Se nenhum comando da segunda lista for
executado, ent�o o comando
.b while
retorna zero como valor de retorno . O comando
.b until
pode ser utilizado ao inv�s de
.b while
para negar o teste de t�rmino de repeti��o.
.in 0
.sp


.sp 4

.b
5.6 - Blocos de Comandos
.r

.pp
Uma lista de comandos pode formar um bloco, com o objetivo
de ser executada sob as mesmas condi��es, por�m diferentes das dos
demais. Como exemplo destas condi��es podem ser citadas o redirecionamento
de entrada e sa�da, o ambiente, o tratamento de exce��es, etc...

.pp
Um bloco de comandos pode ser executado pela pr�pria "shell" corrente,
ou por uma "shell" "filha" criada especialmente para execut�-lo.
Uma lista de comandos entre par�nteses � executada por uma "shell" "filha",
enquanto uma terminada por ';' e entre chaves �
executada pela pr�pria "shell" corrente.
Modifica��es das condi��es de execu��o da "shell" realizadas por
comandos componentes de um
bloco de comandos executado pela "shell" corrente mant�m-se para
a execu��o dos pr�ximos comandos. J� estas modifica��es realizadas
por um bloco de comandos executados por uma "shell" filha s� s�o
v�lidas durante a a exist�ncia da "shell" filha, ou seja durante a
execu��o do bloco.


.sp 4

.b
5.7 - Tratamento de Exce��es
.r

.pp
A "shell" tem um mecanismo que permite especificar as a��es
a serem realizadas quando da ocorr�ncia de uma exce��o.
S�o consideradas exce��es a recep��o de um sinal (veja signal (sys))
e o fim de arquivo da entrada padr�o da "shell".

.pp
O comando interno "trap" posibilita a associa��o de uma linha
de comando para cada exce��o. As exce��es s�o especificadas pela sua 
constante inteira correspondente, por exemplo: a recep��o de um sinal
de alarme de rel�gio provoca a exce��o "SIGALRM". O fim de arquivo da
entrada padr�o da "shell" corrente corresponde a exce��o 0.
Mais de uma exce��o pode ser associada a uma mesma linha de comando.
� poss�vel especificar exce��es que devem ser ignoradas e exce��es
cujo tratamento deve ser restaurado ao estado inicial. Uma descri��o
detalhada da sintaxe de "trap" est� no cap�tulo 4.

.sp 6

.b
5.8 - Coment�rios
.r

.pp
O caractere '#' delimita o in�cio de um coment�rio. Todos os
caracteres posteriores at� o primeiro <nl> posterior s�o ignorados.
