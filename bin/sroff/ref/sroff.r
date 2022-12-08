.bp
.tp
.sp 10
.nf
      *******   *******  *******   *******    *    *     *
         *      *     *  *     *   *     *    *     *   *
         *      *     *  *     *   *     *    *      * *
         *      *******  *     *   *******    *       *
         *      *  *     *     *   *          *      * *
         *      *   *    *     *   *          *     *   *
         *      *    *   *******   *          *    *     *
.fi
.sp 10
.ce
SROFF
.sp 2
.ce
Vers�o 4.7.0
.sp 4
.ce
Manual de Refer�ncia
.sp 12
.ce
Julho de 1997

.bp
.sp 10
.ce
CONTE�DO
.sp 5
.nf
	Cap. 1 - Introdu��o ..............................  2

	Cap. 2 - Defini��es Preliminares .................  3

	Cap. 3 - Controle de P�gina ....................... 6

	Cap. 4 - Controle de Linha ........................ 7

	Cap. 5 - Controle de Par�grafo .................... 9

	Cap. 6 - Controle de Blocos ...................... 10

	Cap. 7 - Controle do Tipo do Caractere ........... 12

	Cap. 8 - Formata��o de Tabelas ................... 13
.fi

.bp
.he 'Sistema TROPIX'Manual de Refer�ncia'SROFF'
.fo 'Escrito em 07.07.97'Vers�o 4.7.0'Pag. %'
.sp 5
.nf
     *********************************************************
     *							     *
     *			CAP�TULO 1			     *
     *							     *
     *	     		INTRODU��O			     *
     *							     *
     *********************************************************
.fi
.sp 4
.pp
O SROFF � um processador de texto n�o interativo
baseado num subconjunto das especifica��es do NROFF
do UNIX da AT&T. O SROFF � n�o interativo porque
o texto formatado n�o aparece imediatamente na tela
do terminal ap�s ser datilografado no teclado. O
texto de entrada � acompanhado de comandos para
o SROFF e gravado em um arquivo. O programa SROFF
l� este arquivo, interpreta os comandos e produz o
arquivo de sa�da com o texto formatado a partir
do texto de entrada.

.pp
O SROFF baseia-se num subconjunto das especifica��es
do NROFF e utiliza algumas caracter�sticas das macros
ME desenvolvidas na universidade de Berkeley, E.U.A..

.pp
Este manual apresenta os diversos comandos aceitos
pelo SROFF com as suas respectivas op��es.
Alguns exemplos s�o dados para facilitar o
entendimento dos comandos.

.bp
.sp 5
.nf
     *********************************************************
     *							     *
     *			CAP�TULO 2			     *
     *							     *
     *		   DEFINI��ES PRELIMINARES		     *
     *							     *
     *********************************************************
.fi
.sp 4

.ip "2.1 -" 6
Identifica��o dos comandos e seus par�metros.

.pp
Um comando para o SROFF � indentificado por um ponto (".")
na primeira coluna de uma linha de entrada. O comando
� indentificado por dois caracteres que seguem o ponto.
Os par�metros do comando seguem a indentifica��o do
comando separados por brancos.
.sp
.ce
Ex:  .ip  "T�TULO" 15
.sp

.ip "2.2 -" 6
Conven��es.

.pp
Diversos comandos alteram caracter�sticas b�sicas do SROFF
(tamanho da linha de texto, por exemplo). Caso este comando
n�o seja especificado, o valor entre colchetes ("[", "]") �
assumido.

.pp
Em rela��o ao espacejamento, usa-se a conven��o "v" para
um espacejamento vertical e "h" para um espacejamento 
horizontal.

.pp
O par�metro "n" que aparece em muitos comandos � num�rico
e pode ser especificado sem sinal ou com sinal "+" ou "-".
Se especificado sem sinal, representa o valor absoluto.
Com o sinal "+" ou "-", representa altera��es relativas
ao valor corrente. O valor assumido para "n", caso ele seja
omitido, � dado entre colchetes.

.pp
Quanto � disposi��o do texto formatado, imagina-se que
c�pias do texto em tamanho A4 ser�o tiradas usando-se apenas
uma das faces do papel. Vers�es futuras do SROFF permitir�o
formata��es mais sofisticadas.

.pp
Todos os comandos descritos causam uma quebra na linhas corrente,
recome�ando a formata��o em uma nova linha. As exce��es s�o o
.b .wo
e
.b .ul
(veja Controle de Linha), e os comandos relativos ao tipo do caractere
(veja Controle do Tipo do Caracter).

.bp
.ip "2.3 -" 6
Padroniza��o vertical.

.pp
Os seguintes comandos especificam o espacejamento vertical
de uma p�gina de texto t�pica.
.sp
.in 5

.b .pl
n (page-length) [75v]
 Especifica o tamanho total da p�gina em linhas de texto
formatado.
.sp 2

.b .m1
n (margin 1) [4v]
 Especifica o espacejamento entre o topo da p�gina e o
header (se houver) ou a primeira linha de texto.
.sp 2

.b .m2
n (margin 2) [2v]
 Especifica o espacejamento entre o header e a 
primeira linha de texto.
Se n�o houver header, este espacejamento � ignorado.
.sp 2

.b .m3
n (margin 3) [2v]
 Especifica o espacejamento entre a �ltima linha 
de texto e o footer.
Se n�o houver footer, este espacejamento � ignorado.
.sp 2

.b .m4
n (margin 4) [1v]
 Especifica o espacejamento entre o footer (se houver)
ou a �ltima linha de texto e o final da p�gina.
.sp 2

.b .ls
n (line space) [1]
 Especifica o espacejamento entre duas linhas consecutivas no texto.
Se "n" � dois, produz-se um texto com espacejamento duplo.

.in
.sp
.ip "Obs: "
Os comandos 
.b ".pl, .m1, .m2, .m3"
e
.b .m4
quando usados no meio de uma p�gina, causam uma quebra na mesma.
.sp
Uma p�gina t�pica com header e footer ter�:

.ip 
.(l
4  linhas em branco
1  linha  de header
2  linhas em branco
55 linhas de texto
2  linhas em branco
1  linha  de footer
1  linha  em branco
.)l
.sp

.bp
.ip "2.4 -" 6
Padronizac�o horizontal.

.pp
Os comandos seguintes especificam o espacejamento
horizontal de uma linha t�pica.
.sp
.in 5

.b .ll
n (line length) [67h]
 Especifica o comprimento da linha de texto em caracteres.
.sp 2

.b .po
n (page offset) [0h]
 Especifica a margem a esquerda em n�mero de caracteres
a partir da qual devem come�ar todas as linhas do texto.
.sp 2

.b .in
n (indentation) [0h]
 Especifica o n�mero de caracteres a partir da margem esquerda
corrente que se deve deixar em branco quando uma nova linha
for impressa.
.in
.sp

.ip "Obs: "
Sem alterar os valores iniciais dos diversos par�metros,
o SROFF permite a impress�o de linhas que deixam 2,5cm
de margem a esquerda e 1,5cm de margem a direita em uma
p�gina de tamanho A4.
.sp

.ip "2.5 -" 6
Header e footer.

.pp
Especifica o que dever� ser impresso a esquerda, no centro
e a direita no alto da p�gina (header) e no p� da p�gina
(footer). Pode-se especificar tamb�m se s� se quer nas p�ginas
pares (".eh", ".ef") ou �mpares (".oh", ".of"). Ainda pode-se ter um
header (ou footer) para p�ginas pares, e outro para as �mpares.
.sp

.in 5
.b .he
'esquerda'centro'direita'
.sp
.b .eh
'esquerda'centro'direita'
.sp
.b .oh
'esquerda'centro'direita'
.sp
.b .fo
'esquerda'centro'direita'
.sp
.b .ef
'esquerda'centro'direita'
.sp
.b .of
'esquerda'centro'direita'
.sp
.in

.pp
Para que o header e/ou o footer sejam impressos em negrito,
basta que sejam definidos depois de um 
.b .b.
E para que sejam sublinhados basta que venham depois de um 
.b .ul.

.bp
.sp 5
.nf
     *********************************************************
     *							     *
     *			CAP�TULO 3			     *
     *							     *
     *		     CONTROLE DE P�GINA			     *
     *							     *
     *********************************************************
.fi
.sp 4
.in 5

.b .bp
n (begin page) [+1]
 Especifica o t�rmino da p�gina corrente e o in�cio
de uma nova. O par�metro "n" indica o valor do
n�mero para ser usado na nova p�gina.
.sp
.in

.ip "Obs: "
O n�mero da p�gina corrente � representado no texto por "\%".
Caso este caractere precise ser usado especifique "\\%".
.lp
.sp 2
.in 5

.b .pn
n (page number) [1]
 Especifica o n�mero da p�gina corrente.
.sp 2

.b .tp
(begin title page)
 Especifica o t�rmino da p�gina corrente e o in�cio de uma 
nova que n�o conter� header nem footer e n�o incrementar�
o n�mero da p�gina.

.bp
.sp 5
.nf
     *********************************************************
     *							     *
     *			CAP�TULO 4			     *
     *							     *
     *		     CONTROLE DE LINHA			     *
     *							     *
     *********************************************************
.fi
.sp 4
.in 5

.b .br
(break)
 Produz uma quebra na linha corrente, isto �, esta � impressa
sem haver ajustamento da margem direita. Uma linha de texto
de entrada come�ando com um caractere branco, faz o mesmo efeito.
.sp 2

.b .wo
(word) 'palavra'
 Imprime literalmente o conjunto de letras (incluindo brancos) passado
como par�metro entre
aspas duplas (") ou simples ('). Usado quando o n�mero de brancos
entre palavras n�o pode ser alterado.
.sp 2

.b .ce
(centered) [1]
 As "n" linhas seguintes de texto de entrada s�o centradas.
Linhas de comando, em branco, de listas, literais ou linhas de tabelas
n�o s�o consideradas. Caso seja usado 0 como par�metro, p�ra de centrar
antes das "n" linhas estabelecidas no comando
.b .ce
anterior.

.sp 2
.b .tl
'esquerda'centro'direita'
 O texto esquerda, centro, direita s�o escritos a esquerda,
no centro e a direita da linha como no header e footer.
Pode ser em negrito e/ou sublinhado da mesma forma que o header e o footer.
Bom para fazer �ndices.

.sp 2
.b .sp
n (space) [1]
 Especifica um "break" na linha corrente e um espacejamento
vertical de "n" linhas.
"n" deve ser positivo e diferente de 0.
.sp 2

.b .ul
n (underline) [1]
 Sublinha no texto formatado as pr�ximas "n" linhas do texto
de entrada.
.sp 2

.b .nf
(no fill)
 Come�a um trecho de texto sem ajustamento. As linhas do
texto de entrada s�o literalmente transferidas para
o texto formatado.
.sp 2

.b .li
(literal)
 O mesmo que ".nf".
.sp 2

.b .fi
(fill)
 Retornar ao modo de ajustamento normal.
.sp 2

.b .sh
"n" t�tulo x (section header)
 Faz a numera��o autom�tica dos cap�tulos. Nenhum par�metro apenas
zera a numera��o (nada � impresso). "n" indica o n�vel da numera��o
(para 1.2.2 o n�vel seria 3). "t�tulo" indica o que vai ser colocado
ao lado do n�mero (1.2.3 t�tulo).
Se "t�tulo" tiver <sp> ou <tb> deve vir entre '"' ou '''.
"x" � uma numera��o espec�fica. Deve ter o mesmo n�mero de
d�gitos que o n�vel indicado e os d�gitos devem vir separados
por <sp>. Caso n�o haja o par�metro "x", a numera��o colocada
� a seguinte � anterior. O n�vel pode variar de 1 a 3.
.sp
Exemplo:
.sp
.in +3
 .sh 1 tit1 gerar�
.sh 1 tit1
.sp

 .sh 2 tit1.1 gerar�
.sh 2 tit1.1
.sp

 .sh 1 tit2 gerar�
.sh 1 tit2
.sp

 .sh 3 tit2.1.1 gerar�
.sh 3 tit2.1.1
.in -3
.sp 2


.b .nr
n [5]
 Indenta todos os t�tulos de cap�tulos em um valor
proporcional a "n", ou seja cada t�tulo ser� indentado
em "n" vezes o n�vel dado no comando ".sh" menos um.
.in

.bp
.sp 5
.nf
     *********************************************************
     *							     *
     *			CAP�TULO 5			     *
     *							     *
     *		    CONTROLE DE PAR�GRAFO		     *
     *							     *
     *********************************************************
.fi
.sp 4
.in 5
.b .pp
(paragraph)
 Par�grafo padr�o. Produz uma quebra na linha corrente, pula
um espa�o vertical e indenta em cinco caracteres a pr�xima linha do texto
formatado a partir da margem esquerda.
.sp 2

.b .lp
(left paragraph)
 Id�ntico a ".pp" sem a indenta��o de cinco caracteres.
.sp 2

.b .ip
t�tulo "n" (indented paragraph)
 Produz uma quebra na linha corrente, pula um espa�o vertical,
coloca a palavra t�tulo na margem esquerda corrente e indenta
todas as linhas deste par�grafo. Se o t�tulo contiver brancos,
usar "t�tulo" ou 't�tulo'. A indenta��o produzida � a padr�o
de cinco caracteres. O par�metro "n" indica a altera��o deste
valor com validade para este par�grafo.
.sp 2

.b .ep
(end paragraph)
 Termina um par�grafo.

.bp
.sp 5
.nf
     *********************************************************
     *							     *
     *			CAP�TULO 6			     *
     *							     *
     *		     CONTROLE DE BLOCOS			     *
     *							     *
     *********************************************************
.fi
.sp 4

.in 5

.b .bc
 texto
 
.b .ec
 Usado para coment�rios. O texto ser� ignorado.
.sp 2

.b .(q
.wo "     (quote)"
 texto
 
.b .)q
 Usado para cita��es. Indenta o texto a esquerda e a direita
das margens correntes em cinco caracteres.
.sp 2

.b .(l
.wo "     (lista)"
 texto
 
.b .)l
 Usado para listas. Indenta o texto a esquerda em cinco caracteres
e transfere literalmente cada linha do texto de entrada para
o texto formatado.
.sp 2
.b .(b
f
.wo "   (block)"
 texto
 
.b .)b
 Usado para manter o texto em uma mesma p�gina. Se o par�metro "f"
n�o for especificado, o bloco � impresso na posi��o onde ele 
aparece no texto se couber na p�gina corrente. Se n�o couber,
ele � impresso no in�cio da p�gina seguinte e a p�gina corrente
� deixada com um espa�o em branco.
 Se o par�metro "f" for especificado, o bloco flutua dentro do texto.
Isto significa que o texto seguinte ao bloco continua a ser formatado
at� chegar � posi��o de impress�o do referido bloco. Esta posi��o
ser� o fim da p�gina, se o bloco couber nela, ou o come�o da pr�xima,
caso contr�rio.

.bp
.b .(t
.wo "     (text)"
 texto
 
.b .)t
 O mesmo que o bloco fixo, mantendo, entretanto, as condi��es
do sistema. Al�m disso, qualquer altera��o feita dentro do
bloco permanece ap�s o fim do mesmo.

.sp 2
.b .(f
.wo "     (footnote)"
 texto
 
.b .)f
 Usado para especificar uma nota de rodap�. O texto termina antes,
pula-se um espa�o vertical definido em ".ls" e o texto da nota de
rodap� � impresso. Caso o texto da nota n�o possa ser impresso
inteiramente na p�gina corrente, ele continuar� na p�gina seguinte.
Caso nem uma linha possa ser impressa na nota de rodap�, a
p�gina � terminada antes e a nota de rodap� � impressa na 
p�gina seguinte.

.in
.ip 'Obs. : ' 9
No caso de blocos (ou footnote) com tamanho acima do tamanho
da p�gina, estes ser�o divididos, e impressos em blocos menores, como
se fossem todos blocos fixos.
.lp

.bp
.sp 5
.nf
     *********************************************************
     *							     *
     *			CAP�TULO 7			     *
     *							     *
     *		CONTROLE DO TIPO DO CARACTERE		     *
     *							     *
     *********************************************************
.fi
.sp 4


.in 5
.b .r
(roman)
 Muda o tipo dos caracteres para romano.
� o tipo de caractere padr�o.
.sp 2
.b .i
(italic)
 Muda o tipo dos caracteres para it�lico.
.sp 2
.b .b
(bold)
 Muda o tipo dos caracteres para negrito.
.sp
.in
.ip "Obs: "
Se uma palavra � passada como par�metro com um dos tr�s
comandos acima, somente ela ter� seus caracteres alterados.
.lp


.bp
.sp 5
.nf
     *********************************************************
     *							     *
     *			CAP�TULO 8			     *
     *							     *
     *		   FORMATA��O DE TABELAS		     *
     *							     *
     *********************************************************
.fi
.sp 4

.ip "9.1 -" 6
Defini��o.

.in 5
.b .ts
 [op��es;]
 formatos.
 dados
.br
.b .t&
 formatos.
 dados
.br
.b .te
.in 0

.pp
Tabelas s�o formadas de campos que s�o independentemente centrados,
ajustados a esquerda, a direita ou pelo ponto decimal.
T�tulos podem ser colocados sobre uma coluna ou sobre um grupo de colunas.
.pp
Cada tabela em um texto � independente e deve conter informa��es
relativas � sua formata��o. Estas informa��es s�o especificadas na
se��o 'formatos' que vem entre as 'op��es' (informa��es relativas �
tabela como um todo) e os 'dados' (elementos que compor�o os campos
da tabela).
.pp
O comando '.t&' indica uma redefini��o dos formatos das linhas da tabela.
N�o � permitido alterar as 'op��es'. Deve ser considerado o fato
de que algumas condi��es estabelecidas ao longo da leitura dos dados
anteriores ao '.t&' n�o ser�o desprezados. S�o elas:
.in 5
.ip - 5
Largura m�nima de uma coluna.
.ip - 5
Largura m�nima dos campos esquerdo e direito, al�m da exist�ncia do
ponto decimal, para os campos num�ricos de cada coluna.
.ip - 5
O tamanho m�ximo dos campos pertencentes a uma subcoluna para
cada coluna.
.ip - 5
Colunas com indica��o para o mesmo tamanho.
.in 0

.pp
Os tamanhos indicados acima somente ser�o aumentados,
redu��es indicadas para os mesmos ser�o ignoradas.
Quanto �s colunas que devem ter o mesmo tamanho, elas
n�o perder�o esta condi��o, entretanto colunas que n�o possuiam
este atributo podem passar a possuir.

.ip "9.2 -" 6
Op��es.
.pp
As op��es alteram a formata��o da tabela como um todo.
Elas, se presentes, v�m seguindo o comando '.ts'.
S�o colocadas uma em cada linha e a �ltima deve ser terminada por ';'.
.pp
S�o elas:
.in 5
.ip - 5
center: centra a tabela (o default � ajustar a esquerda).
.ip - 5
expand: formata a tabela no tamanho da linha (o default � o m�nimo necess�rio).
.ip - 5
box: coloca a tabela em uma moldura.
.ip - 5
allbox: coloca todos os elementos da tabela em molduras.
.ip - 5
doublebox: coloca a tabela em uma moldura dupla.
.ip - 5
tab (c): 'c' indica o caractere separador dos dados (o default � <tb>).
.ip - 5
title n: a n-�sima linha de dados ser� usada como t�tulo
no in�cio de cada p�gina onde houver continua��o da tabela.
.in

.ip "9.3 -" 6
Formatos.
.pp
A se��o 'formatos' especifica exatamente a coloca��o dos elementos
na tabela. Cada linha desta se��o corresponde a uma linha da tabela.
Exceto a �ltima, que corresponde a todas as linhas seguintes
at� o pr�ximo '.t&' ou '.te'.
Cada linha cont�m uma letra chave para cada coluna.
O n�mero de letras chave na primeira linha de formatos
indicar� o n�mero de colunas da tabela. Nas seguintes,
formatos a mais ser�o ignorados e a menos ser�o subentendidos
como 'l'.
.pp
As letras chave s�o as seguintes:
.in 5
.ip "l - "
Indica campo alinhado a esquerda.
.ip "r - "
Indica campo alinhado a direita.
.ip "c - "
Indica campo centrado.
.ip "n - "
Indica campo num�rico, a ser alinhado com outros
campos num�ricos (na mesma coluna) pelo ponto decimal.
.ip "a - "
Indica uma subcoluna. Todos os campos correspondentes s�o alinhados
a esquerda de forma que o maior campo correspondente esteja centrado
na coluna.
.ip "s - "
Indica que o campo da coluna anterior se extende at� esta coluna
(n�o � permitido na primeira coluna).
.ip "^ - "
Indica campo em branco. Dados correspondentes a este formato
s�o ignorados.
.ip "'-' ou '=' - "
A coluna ser� totalmente preenchida pelo caractere '-' ou '=' respectivamente.
Dados correspondentes a esses formatos s�o ignorados.
.ip "| - "
Deve vir entre duas letras chave, indicando a� uma
(ou mais, dependendo do n�mero de barras) coluna vertical.
.in

.pp
Quando o formato "n" � especificado, o '.' mais a direita do dado
� usado como ponto decimal. Se n�o houver '.', o caractere mais a 
direita � considerado como unidade.
.pp
A �ltima linha de formatos deve vir seguida de um '.'.
.pp
Os seguintes atributos podem ser utilizados seguindo as letras chave,
visando mudar caracter�sticas das colunas:
.in 5
.ip "f - "
Deve vir seguido de 'b', 'r', ou 'i', para mudar o tipo do caractere
do campo correspondente para negrito, romano ou it�lico respectivamente.
O default � o tipo corrente.
O 'f' pode ser omitido, pois o sroff aceita como mesmo atributo
apenas o 'b', o 'r' ou o 'i'.
.ip "e - "
Indica colunas com mesmo tamanho. S�o ajustadas pelo maior tamanho.
.ip "w(n) - " 
O n�mero "n" (decimal) indica o tamanho m�nimo da coluna correspondente.
O default � o tamanho do maior campo desta coluna.
.ip "n - "
O n�mero "n" (decimal) indica a dist�ncia m�nima entre esta coluna
e a pr�xima. O default � 3. A op��o 'expand', expande a tabela
multiplicando as dist�ncias por uma constante de forma que
ocupe o m�ximo da linha.
.in 0

.ip "9.4 -" 6
Dados.
.pp
Os 'dados' da tabela v�m ap�s os formatos. Cada linha da tabela
vem em uma linha diferente, com os campos separados por <tb> ou
outro caractere definido pela op��o 'tab'.
.pp
Uma linha de dado pode conter:
.in 5
.ip "- "
Comando para o sroff.
.ip "- "
'-' ou '=': Indica uma linha inteira com o respectivo caractere.
.ip "- "
Campos separados por <tb>.
.in 0

.pp
Um campo pode ser:
.in 5
.ip "- "
'-' ou '=': Indica toda a coluna com o respectivo caractere. Para que
um deles seja o dado, usar "\&-" ou "\&=", ou colocar um <sp>
entre o caractere e o <tb>.
.ip "- "
'\a': todo o campo com o respectivo caractere.
.ip "- "
'\Rx': 'x' indica o caractere que ocupar� toda a extens�o do campo.
.ip "- "
'\^': indica campo em branco, todo ocupado por <sp>.
.ip "- "
's': 's' indica a cadeia de caracteres a ser colocada na tabela
de acordo com o formato correspondente.
.ip "- "
campo em branco (dois <tb> seguidos): indica campo em branco,
todo ocupado por <sp>.
.in 0

.pp
Deve ser levado em considera��o que comandos para o sroff indicados
dentro da tabela (na se��o de dados) ter�o seu efeito anterior
ou posterior � coloca��o da tabela no texto, uma vez que
a tabela (dados) � toda armazenada na mem�ria antes de ser montada
e colocada no texto. Enquanto os comandos do sroff s�o executados
imediatamente ap�s sua leitura.
.pp
Tabelas que estejam dentro de bloco n�o ter�o suas
"caixas" completadas nas extremidades das p�ginas.
Al�m disso o comando "title" n�o funciona para estas tabelas.

.ip "9.5 -" 6
Exemplos.

.(b
.nf

     .ts
     box
     tab (:);
     cb s s s s
     c  c c c c
     r2 | n2 | n2 | n2 | n.
     t�tulo
     =
     tit1:tit12:tit123:tit1234:tit12345
     -
     tit12:9.2:5.2:55:6.4
     tit123:4.34:666:7.65:5:43
     tit1234:6.43:-43:65.43:-34.65
     tit12345:23:5677:-7676:123.
     .te
.fi
.)b


.sp 2
.in 5
.ts
box
tab (:);
cb s s s s
c  c c c c
r2 | n2 | n2 | n2 | n.
t�tulo
=
tit1:tit12:tit123:tit1234:tit12345
-
tit12:9.2:5.2:55:6.4
tit123:4.34:666:7.65:5:43
tit1234:6.43:-43:65.43:-34.65
tit12345:23:5677:-7676:123.
.te
