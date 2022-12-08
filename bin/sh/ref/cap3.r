.bp

.sp 5

.nf
     *********************************************************
     *							     *
     *			    CAP�TULO 3			     *
     *							     *
     *	         VARI�VEIS E OUTRAS SUBSTITUI��ES            *
     *							     *
     *********************************************************

.fi

.sp 4


.pp
Antes da execu��o dos comandos, seus argumentos s�o analisados
quanto � exist�ncia de vari�veis que devam ser substitu�das por
seus valores e, posteriormente, quanto � necessidade de expans�o
de nomes de arquivos.

.pp
Na an�lise de um comando a executar, a "shell" leva sempre em considera��o
o caractere "\" precedendo imediatamente um metacaractere. Este
procedimento anula o efeito especial do metacaractere.

.sp 4
.b
3.1 - Vari�veis
.r

.pp
A "shell" permite que sejam definidas vari�veis para posterior uso.
O nome de uma vari�vel � uma cadeia composta de caracteres alfanum�ricos,
podendo incluir tamb�m o caractere "_" (sublinhado).
O valor atribu�do a ela � qualquer cadeia de caracteres.


.pp
A atribui��o de uma cadeia a uma vari�vel � realizada
escrevendo-se o nome da vari�vel, sucedido pelo caractere "=" e da cadeia.
As vari�veis s�o declaradas na primeira atribui��o.
A vari�vel ser� substitu�da por seu valor,
quando esta for precedida pelo metacaractere "$".

.sp
Assim, dado

.sp
.in +5
$ DIR=a/b/c

.sp
$ mv pgm $DIR

.in -5
.sp
mover� o arquivo "pgm" do diret�rio corrente para o diret�rio "a/b/c".

.sp 2

.pp
Para a substitui��o, o nome da vari�vel a ser substitu�da � procurado a partir
do caractere "$" at� um caractere n�o alfanum�rico (exceto "_").
Se esse caractere for <sp> ou <ht>, significa o fim do nome.
Se esse caractere for qualquer outro n�o alfanum�rico, os caracteres a seguir
ser�o concatenados ao valor da vari�vel.

.sp
Assim, para

.sp
.in +5

$ A=a
$ AB=ab

.in -5
.sp

.nf
     $A          equivale a	a
     $AB         equivale a	ab
     $A.c        equivale a	a.c
     $AB.pgm     equivale a	ab.pgm
.fi


.pp
Os seguintes par�metros t�m seus valores automaticamente atribu�dos pela
"shell":
.in +5

.ip "#"
O n�mero de par�metros posicionais em decimal.

.ip "-"
Op��es de funcionamento fornecidas a "shell"  na evoca��o ou atrav�s do
comando "set".

.ip "?"
O valor decimal de t�rmino retornado pelo �ltimo comando executado sincronamente.

.ip "$"
A identifi�a��o do processo desta "shell".

.ip "!"
A identifica��o do processo do �ltimo comando em "background" evocado.

.ip ":"
O n�mero do pr�ximo comando a entrar no hist�rico.

.ip "@"
Os par�metros posicionais (veja adiante) � exce��o de $0.

.ip "*"
Uma cadeia com os par�metros posicionais � exce��o de $0.

.ip "\%"
Uma cadeia com o nome do n� (nome do computador na rede).

.ip "~"
O nome do diret�rio corrente.

.ip "&"
O caractere "#" se o usu�rio for um superusu�rio, e "$" em caso contr�rio.

.ep
.in -5


.pp
Algumas vari�veis t�m um sentido especial para a "shell" e s�o usadas por ela,
que j� as recebe definidas. (Ver Cap. 6). S�o elas:

.in +5
.ip HOME 7
diret�rio assumido por omiss�o como argumento para o comando interno "cd"

.ip PATH 7
diret�rios a serem pesquisados, em ordem, na procura do comando a executar

.ip PS1 7
"prompt" principal da "shell", fornecido quando 
est� apto a receber novo comando 

.ip PS2 7
"prompt" secund�rio da "shell", fornecido quando o comando
continuar� em outra linha

.ep
.in -5

.pp
A "shell" atribui valores iniciais para as vari�veis
"PATH", "PS1" e "PS2".
O valor da vari�vel "HOME" � atribu�do pelo comando "login".
O caractere '~', quando ocorre em caminhos, � equivalente a $HOME.

.sp 4
.b
3.2 - Expans�o de Nomes de Arquivos
.r

.pp
Muitos comandos aceitam argumentos que s�o nomes de arquivos.
A "shell" fornece um mecanismo para gera��o de uma lista,
em ordem lexicogr�fica, de nomes de arquivos que atendam a certo padr�o.
Para gerar os padr�es, existem os metacaracteres 
"*", "?", "[", "]" e "!", que significam:


.in +5
.ip * 8
qualquer cadeia de caracteres (exceto as iniciadas por ".")

.ip ? 8
qualquer caractere simples (exceto ".")

.ip [...] 8
qualquer caractere no intervalo [...]

.ip ! 8
qualquer caractere diferente do que segue "!"

.ep
.in -5

.sp
Por exemplo:

.sp
.in +5
$ ls -l *.c

.in -5
.sp
lista, em ordem alfab�tica, informa��es sobre todos os nomes de arquivos,
do diret�rio corrente que terminam com o sufixo ".c"

.sp
.in +5

$ ls /cmd/*/teste

.in -5
.sp
lista todos os arquivos de nome "teste" de qualquer subdiret�rio de "/cmd"

.sp
.in +5

$ ls /a/?

.in -5
.sp
lista todos os arquivos do diret�rio "/a", cujos nomes t�m um s� caractere

.sp
.in +5
$ ls [a-d]*

.in -5
.sp
lista todos os arquivos come�ados com as letras "a", "b", "c" e "d"


.sp 4
.b
3.3 - Metacaracteres como Caracteres Comuns
.r

.pp
Os seguintes caracteres t�m um significado especial para a
"shell" e causam o fim de uma palavra a menos que estejam quotados:
.sp
.in +5
.b
;  &  (  )  |  ^  <  >  <nl>  <sp>  <ht>
.r
.in -5

.pp
Um caractere pode ser quotado (i.e. faz�-lo siginificar ele mesmo)
precedendo-o por uma barra invertida ou inserindo-o entre um par de
marcas de quota��o ('' ou ""). Durante o processamento, a "shell"
pode quotar alguns caracteres para evitar que eles tenham um
significado especial. Barras invertidas usadas para quotar um
caractere s�o removidas da palavra antes que o comando seja
executado. O par "\<nl>" � removido antes da substitui��o de
comandos e par�metros.

.pp
Todos os caracteres entre um par de acentos agudos, exceto
um acento agudo, s�o quotados pela "shell".
Barra invertida
n�o tem um significado especial dentro de um par de acentos
agudos. Um acento agudo pode ser quotado dentro de um par de
aspas (por exemplo "'").

.pp
Dentro de um par de aspas (""), ocorre a substitui��o de
par�metros e comandos, mas sobre o resultado a
"shell" n�o faz interpreta��o de brancos, nem gera��o de nomes de arquivos.
Se "$*" est� entre um par de aspas ("$*"), os par�metros
posicionais s�o substitu�dos e formam uma �nica palavra,
considerada como quotada, com um espa�o entre cada par de
par�metros ("$1 $2 $3 ...").
Uma barra invertida ('\') retira
o significado especial dos caracteres '\', ''', '"' e '$'.
O par "\<nl>" � removido antes da substitu���o de par�metros
e comandos.
A barra invertida s� tem o significado especial em vigor
quando precede os caracteres anteriores.

.pp
Assim, a sa�da de

.sp
.in +5
$ echo \?
.in -5
.sp
ser� o caractere "?"

.sp
e a de
.sp
.in +5
$ echo xx'||||'xx
.in -5
.sp
ser�
.sp
.in +5
xx||||xx
.in -5
.sp 2

.sp 4
.b
3.4 - Substitui��o de Comandos
.r

.pp
A sa�da padr�o de um comando que aparece entre um par de acentos graves (``)
pode ser usada como parte, uma, ou mais palavras. Assim, o comando

.sp
.in +5
$ grep -l driver `walk -s .`
.in -5
.sp
faz com que a lista de arquivos produzida pelo comando "walk" seja
utilizada pelo comando "grep".

.sp
Um comando �til para a utiliza��o com os acentos graves � o "from",
como no exemplo abaixo:

.sp
.nf
	for i in `from 1 to 10`
	do
		echo $i
	done
.fi

.sp
em que o comando "echo" � executado 10 vezes, com os valores consecutivos
de "1" a "10" para a vari�vel "i".

.pp
N�o � realizada qualquer interpreta��o dos caracteres da cadeia
lida, exceto para a remo��o de barras invertidas ('\'), usadas para
desabilitar o significado especial de caracteres.
Uma barra invertida ('\') pode ser usada para desabilitar o significado
especial de um acento grave ou outra barra invertida ('\') e
� removida antes que a cadeia de caracteres seja lida.

.pp
Se uma barra invertida ('\') � usada para anular o significado especial
de um <nl>, tanto a barra invertida quanto o <nl> ser�o
removidos.
Em adi��o, barras invertidas usadas para anular o significado do
cifr�o ('$') s�o removidos. J� que n�o � realizada uma
interpreta��o na cadeia de caracteres do comando antes que ele
seja lido, a inser��o de uma barra invertida antes de um cifr�o
n�o tem efeito. Barras invertidas que precedam caracteres
outros que '\', '`', '"', <nl> e '$' s�o mantidos intactos quando
a cadeia de caracteres do comando � lida.
