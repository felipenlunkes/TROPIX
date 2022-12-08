.bp
.he 'EDOBJ (cmd)'TROPIX: Manual de Refer�ncia'EDOBJ (cmd)'
.fo 'Atualizado em 15.01.99'Vers�o 3.1.0'Pag. %'

.b NOME
.in 5
.wo "edobj -"
editor de m�dulos objeto
.br

.in
.sp
.b SINTAXE
.in 5
.(l
edobj [-f] -p "<busca>[:<substitui��o>]" <mod>
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "edobj" realiza opera��es simples de busca e substitui��o
de cadeias em um m�dulo objeto <mod>. O comando pode tamb�m ser utilizado
para realizar estas opera��es em arquivos de texto, mas para isto
outros editores, tais como "subst", "vi" ou "ed" (cmd)
s�o provavelmente mais adequados.

.sp
Cada execu��o de "edobj" realiza a busca de apenas uma cadeia de <busca>
em um m�dulo objeto <mod>. Para efetuar buscas/substitui��es de v�rias
cadeias diferentes ou em v�rios m�dulos objeto, s�o necess�rias v�rias
execu��es de "edobj".

.sp
A busca/substitui��o � definida por uma op��o "-p", que sempre deve ser dada
(ver abaixo).
� importante notar que as cadeias de busca N�O s�o express�es
tais como as utilizadas no comando "grep" (cmd), mas apenas
cadeias de caracteres que ser�o procuradas (ap�s processadas as seq��ncias
de escape) no arquivo dado.

.sp
Cada vez que a cadeia de <busca> � encontrada no arquivo, � impressa uma
linha com a regi�o da cadeia em hexadecimal e em ISO (ASCII), seguida por
uma linha contendo uma indica��o da cadeia encontrada.
Se foi dada tamb�m a cadeia de <substitui��o>, � impressa mais
uma linha mostrando a linha modificada, e finalmente o usu�rio � consultado
para confirmar se modifica��o deve ser feita no arquivo.  

.sp
As op��es do comando s�o:

.in +3
.ip -p
Par de cadeias de <busca> e <substitui��o>.
A op��o "-p" define a opera��o a ser feita no m�dulo objeto.
Se a op��o for da forma "-p <busca>" (isto �, sem o delimitador ":"
e sem a cadeia de <substitui��o>), s�o listadas todas as linhas
que cont�m a cadeia <busca> (opera��o de busca). 

.sp
Se a op��o for da forma completa "-p <busca>:<substitui��o>",
s�o modificadas todas as linhas que cont�m a cadeia <busca>,
substituindo-a por <substitui��o> (opera��o de substitui��o).
Neste caso, as duas cadeias devem ter o mesmo tamanho.

.sp
Nas duas cadeias, s�o permitidas todas as seq��ncias de escape
da linguagem "C", ou seja, os caracteres especiais (tais como
"\n", "\t", ...), caracteres octais ("\123", ...) e hexadecimais
("\x45", ...).

.ip -f
Normalmente, o usu�rio � consultado para confirmar a substitui��o.
Com esta op��o, a substitui��o � realizada sem consultar o usu�rio.

.ep
.in -3

.in
.sp
.b OBSERVA��ES
.in 5
Tome cuidado com um poss�vel conflito do sh" (cmd) com a utiliza��o do
caractere de escape "\".
Se forem utilizadas seq��ncias de escape, o mais seguro � colocar as
cadeias de <busca> e <substitui��o> entre ap�strofes,
como por exemplo '1234\n:5678\r'.

.sp
Repare que se o caractere delimitador ":" fizer parte de uma das cadeias,
ele deve ser escapado, como por exemplo '1\:23:5678'.

.sp
Para realizar substitui��es de instru��es de m�quina deve-se utilizar
as seq��ncias de escape com caracteres dados em octal ou hexadecimal.
Em vers�es futuras, possivelmente "edobj" ter� uma sintaxe mais
pr�pria para dar seq��ncias longas de d�gitos octais/hexadecimais.

.sp
Em vers�es futuras, possivelmente "edobj" ser� capaz de realizar
buscas/substitui��es de v�rias cadeias e/ou em v�rios m�dulos objeto.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
subst, vi, ed, grep
.br

.in
.sp
.b EXEMPLOS
.in 5
.nf
		edobj -p 'INCS\:\n' alpha.o
.fi
.sp
Mostra todas as regi�es onde o m�dulo "alpha.o" cont�m a cadeia
de caracteres "INCS:\n".

.sp 2
.nf
		edobj -f -p '\x20\x39:\x10\x39' teste/beta.o
.fi
.sp
Substitui (sem consultar o usu�rio) todas as ocorr�ncias da seq��ncia
"0x2039" (um "movl" do processador MC-68010) em
"0x1039" (um "movb") do m�dulo "teste/beta.o".

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
