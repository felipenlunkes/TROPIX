.bp
.he 'TERMINFO (fmt)'TROPIX: Manual de Refer�ncia'TERMINFO (fmt)'
.fo 'Atualizado em 04.01.91'Vers�o 2.3'Pag. %'

.b NOME
.in 5
terminfo

.in
.sp
.b DESCRI��O
.in 5
O banco de dados "terminfo"
cont�m as descri��es dos diversos tipos de terminais
presentes em uma instala��o.

Este banco de dados possibilita que
os programas constru�dos a partir da biblioteca "curses",
como por exemplo, o "vi" (editor de textos)
e o "wsdb" (depurador simb�lico),
funcionem em uma variedade de terminais sem que seja necess�rio
qualquer tipo de altera��o ou recompila��o.

.sp
Este texto apresenta a linguagem empregada para descrever um terminal.
O utilit�rio "tic"
converte a descri��o de um terminal desta linguagem para um formato interno,
que pode ser acessado mais rapidamente pela biblioteca "curses".

.sp
A descri��o de um terminal � uma seq�encia de campos
terminados por v�rgulas (",").
O primeiro campo de uma descri��o
cont�m os nomes pelos quais o terminal � conhecido.
Os campos seguintes s�o ocupados pelas caracter�sticas do terminal,
informando, por exemplo,
se o terminal apresenta determinados comportamentos,
como realizar certas opera��es no terminal
e as seq��ncias de caracteres enviadas por suas teclas especiais.

.sp
.b
Nomes do Terminal
.r
.sp
O primeiro campo inicia com os nomes (separados por "|")
pelos quais o terminal � conhecido
pela "curses";
um destes nomes deve ser atribu�do � vari�vel "TERM" no ambiente
(veja "environ" (fmt)).
Estes nomes n�o devem conter espa�os.
O �ltimo item no primeiro campo deve ser um nome longo
que identifique completamente o terminal;
este nome n�o � utilizado pela "curses"
e pode conter espa�os para melhorar a sua legibilidade.

.sp
.b
Capacidades do Terminal
.r
.sp
Os terminais s�o descritos em termos de capacidades
que podem ser dos tipos booleano, n�merico,
cadeia simples ou cadeia param�trica.

.sp
A presen�a do nome de uma capacidade booleana
indica que o terminal possui o correspondente recurso ou comportamento.
Por exemplo: o fato de um terminal ter margem autom�tica
(isto �, um avan�o para a primeira posi��o na linha seguinte
quando um fim de linha � alcan�ado)
� indicado pela presen�a de um campo contendo "am".

.sp
As capacidades num�ricas s�o expressadas
atrav�s de seu nome seguido do caractere "#"
e dos valores n�mericos associados.
Exemplo: se um terminal disp�e de oitenta colunas,
isto � indicado por um campo na forma "cols#80".

.sp
As capacidades do tipo cadeia s�o expressadas
atrav�s de seu nome seguido do caractere "="
e da cadeia delimitada pela v�rgula que separa os campos.
Exemplo: a descri��o de um terminal que limpa o seu v�deo
quando recebe a cadeia formada pelos caracteres
<esc>, "H", <esc> e "J"
cont�m um campo "clear=\EH\EJ".

.sp
O conjunto de campos de uma descri��o pode estar disperso
em v�rias linhas e todos os campos, exceto o primeiro,
podem ser livremente precedidos de espa�o
(caracteres <sp>, <ht> e <nl>).
Linhas iniciadas pelo caractere "#" s�o consideradas coment�rio e,
portanto, t�m efeito nulo.

.sp
Os valores para as capacidades num�ricas devem ser expressos em base decimal,
podendo ser precedidos de um sinal ("+" ou "-").
Os caracteres de controle podem ser expressos pela nota��o "^X",
ou "escapados" pelo caractere "\", de acordo com a seguinte codifica��o:

.sp
.ts
center
allbox;
c c c.
Seq��ncia	Alternativa	Significado
\E	\e	<esc>
\n	\l	<nl>
\r		<cr>
\t		<ht>
\b		<bs>
\f		<np>
\s		<sp>
\0		<nul>
 \^ 		^
\\		\
.te

.sp
.b
Cadeias Param�tricas
.r
.sp
O posicionamento do cursor e outras capacidades do tipo cadeia
que requerem par�metros s�o expressados atrav�s das cadeias param�tricas.
Estas cadeias utilizam uma nota��o similar � empregada
pela rotina "printf" para especificar o formato em que estes
par�metros s�o enviados.
Um exemplo:
o posicionamento do cursor � descrito pela capacidade "cup",
que utiliza dois par�metros: a linha e a coluna.
As linhas e colunas s�o sempre numeradas da esquerda para a direita
e de cima para baixo a partir de zero
e se referem ao v�deo efetivamente vis�vel ao usu�rio.

.sp
Uma cadeia param�trica permite especificar algumas opera��es aritm�ticas
a serem realizadas sobre os par�metros antes de envi�-los ao terminal.
Para isto existe um mecanismo para armazenamento dos par�metros
em uma pilha e a realiza��o de opera��es aritm�ticas
em Nota��o Reversa Polonesa.
No caso mais simples, uma seq��ncia empilha um par�metro
e o envia no formato especificado.
Uma opera��o aritm�tica � feita empilhando seus dois operandos
e indicando a opera��o.
S�o usados os seguintes c�digos:
.in +3

.ip "\%p[1-9]" 10
empilha o par�metro especificado.

.ip "\%'x'" 10
empilha o caractere "x".

.ip "\%{n}" 10
empilha o n�mero "n"
(em decimal, podendo ser precedido por um sinal "+" ou "-").

.ip "\%c" 10
desempilha e envie em formato caractere (um octeto).

.ip "\%d" 10
desempilha e envie em formato decimal.

.ip "\%o" 10
desempilha e envie em formato octal.

.ip "\%x" 10
desempilha e envie em formato hexadecimal com letras min�sculas.

.ip "\%X" 10
desempilha e envie em formato hexadecimal com letras mai�sculas.

.ip "\%+" 10
Desempilha dois valores da pilha, soma-os e empilha o resultado.

.ip "\%*" 10
Desempilha dois valores da pilha, multiplica-os e empilha o resultado.

.ip "\%-" 10
Desempilha dois valores da pilha, subtrai o primeiro do segundo
e empilha o resultado.

.ip "\%/" 10
Desempilha dois valores da pilha, divide o segundo pelo primeiro
e empilha o resultado.

.ip "\%m" 10
Desempilha dois valores da pilha, divide o segundo pelo primeiro
e empilha o resto da divis�o.

.ip "\%i" 10
Incrementa os dois primeiros par�metros ("%p1" e "%p2").

.ep
.in -3
.sp
Exemplos:
.sp
Uma seq��ncia de comando para o endere�amento do cursor
consistindo dos caracteres <esc> e "=" e mais dois caracteres
indicando respectivamente a linha e a coluna,
cujos valores s�o somados ao caractere <sp>,
� indicada da seguinte forma:
.in +5
.sp
cup=\E=\%'\s'\%p1\%+\%c%'\s'\%p2\%+\%c,
.in -5

.in
.sp
.b "VARI�VEIS EM USO"
.in 5
A rela��o abaixo cont�m as capacidades correntemente consultadas
pela "curses".
O tipo das capacidades � indicado entre par�nteses,
sendo "(b)" para capacidades booleanas,
"(n)" para capacidades num�ricas,
"(c)" para cadeias e
"(p)" para cadeias param�tricas.

.sp
Dimens�es
.in +3
.ip "cols (n)" 12
N�mero de colunas no v�deo.

.ip "lines (n)" 12
N�mero de linhas no v�deo.
.ep
.in -3

.sp
Movimento relativo do cursor (*)

.(f
(*) Estes movimentos nunca s�o usados a partir de posi��es que
deslocariam o cursor para fora do v�deo.
.)f

.in +3
.ip "home (c)" 12
Move para o canto superior esquerdo do v�deo (linha 0 e coluna 0).
.ip "cub1 (c)" 12
Move o cursor para a coluna imediatamente � esquerda na linha corrente.
.ip "cud1 (c)" 12
Move o cursor para a linha imediatamente abaixo na coluna corrente.
.ip "cuf1 (c)" 12
Move o cursor para a coluna imediatamente � direita na linha corrente.
.ip "cuu1 (c)" 12
Move o cursor para a linha imediatamente acima na coluna corrente.
.ip "cr (c)" 12
Move o cursor para a primeira coluna da linha corrente.
.ip "ht (c)" 12
Move para a pr�xima coluna de tabula��o (m�ltipla de 8).
.ep
.in -3

.sp
Movimento direto do cursor
.in +3
.ip "smcup (c)" 12
Cadeia para preparar o terminal para movimento direto do cursor.
.ip "rmcup (c)" 12
Cadeia para anular o efeito da cadeia "smcup".
.ip "cup (p)" 12
Movimento do cursor.
Par�metros: linha e coluna (contados a partir de 0).
.ep
.in -3

.sp
Atributos
.in +3
.ip "blink (c)" 12
Caracteres piscantes.
.ip "bold (c)" 12
Caracteres refor�ados.
.ip "rev (c)" 12
Caracteres em v�deo reverso.
.ip "smso (c)" 12
Inicia caracteres em evid�ncia.
.ip "rmso (c)" 12
Termina caracteres em evid�ncia.
.ip "smul (c)" 12
Inicia caracteres sublinhados.
.ip "rmul (c)" 12
Termina caracteres sublinhados.
.ip "uc (c)" 12
Sublinhe o pr�ximo caractere.
.ip "sgr0 (c)" 12
Termina qualquer campo.
.ip "xmc (c)" 12
N�mero de posi��es ocupadas pelo in�cio ou t�rmino de um campo de atributos.
.ip "ms (c)" 12
Seguro mover o cursor enquanto escrevendo caracteres com atributos.
.ep
.in -3

.sp
Caracteres semigr�ficos:
.in +3
.ip "enacs (c)" 12
Habilita a utiliza��o de caracteres semigr�ficos.
.ip "smacs (c)" 12
Inicia modo semigr�fico.
.ip "rmacs (c)" 12
Termina modo semigr�fico.
.ip "ac (c)" 12
O pr�ximo caractere � semigr�fico.
.ip "acsc (c)" 12
Mapeamento dos caracteres semigr�ficos aos caracteres comuns.
Esta cadeia � formada de pares de caracteres,
em que o primeiro especifica um caractere semigr�fico
e o segundo especifica qual caractere o representa quando
o terminal est� em modo semigr�fico.
A tabela a seguir relaciona os caracteres semigr�ficos
com os caracteres que os especificam.
A terminologia utilizada corresponde ao terminal VT100 da DEC.

.sp
.(b
.ts
center
allbox;
c c.
Caracteres Semigr�ficos	Especifica��o
Seta apontando para a direita	+
Seta apontando para a esquerda	, (v�rgula)
Seta apontando para baixo	. (ponto)
Seta apontando para cima	- (menos)
bloco quadrado cheio	0
lanterna	I
diamante	' (ap�strofo)
checker board (stipple)	a
s�mbolo de grau	f
mais/menos	g
board of squares	h
canto inferior direito	j
canto superior direito	k
canto superior esquerdo	l
canto inferior esquerdo	m
mais	n
scan line 1	o
linha horizontal	q
linha vertical	x
scan line 9	s
t� esquerdo	t
t� direito	u
t� para baixo	v
t� para cima	w
bala	~
.te
.)b


.ep
.in -3

.(t
.sp
Inicializa��o
.in +3
.ip "is1 (c)" 12
Cadeia enviada quando os programas que utilizam a "curses" iniciam.
.ip "is2 (c)" 12
Cadeia enviada a cada vez os programas entram em modo "curses".
.ep
.in -3
.)t

.sp
Deslocamentos
.in +3
.ip "ind (c)" 12
Rolamento do v�deo no sentido convencional.
.ip "ri (c)" 12
Rolamento do v�deo no sentido anticonvencional.
.ip "il1 (c)" 12
Insere uma linha.
.ip "dl1 (c)" 12
Remove a linha corrente.
.ip "csr (p)" 12
Defini��o da regi�o para rolamento.
Par�metros: linhas superior e inferior.
.ep
.in -3

.sp
Teclas especiais
.in +3
.ip "khome (c)" 12
Tecla indicando o canto superior esquerdo do v�deo.
.ip "kcub1 (c)" 12
Seta para a esquerda.
.ip "kcuf1 (c)" 12
Seta para a direita.
.ip "kcuu1 (c)" 12
Seta para cima.
.ip "kcud1 (c)" 12
Seta para baixo.
.ip "kf[1-9] (c)" 12
Teclas de fun��es, normalmente indicadas no teclado como
F1, F2, ..., F9.
.ep
.in -3

.sp
Controle de Star/Stop
.in +3
.ip "xon (b)" 12
Este terminal utiliza controle start/stop de transmiss�o.
.ip "xonc (c)" 12
Caractere XON (rein�cio da transmiss�o).
.ip "xoffc (c)" 12
Caractere XOFF (suspens�o da transmiss�o).
.ep
.in -3

.sp
Altera��es no cursor
.in +3
.ip "civis (c)" 12
Torna o cursor invis�vel.

.ip "cnorm (c)" 12
Torna o cursor vis�vel.
.ep
.in -3

.sp
Outras Capacidades
.in +3
.ip "am (b)" 12
Margem autom�tica.
Indica que ap�s a �ltima coluna
o cursor avan�a para a primeira coluna da pr�xima linha.

.ip "xt (b)" 12
Caracteres de tabula��o destrutivos.
Isto �, eles escrevem espa�os
da posi��o atual at� a pr�xima coluna de tabula��o.

.ip "bel (c)" 12
Sinal sonoro.
.ip "clear (c)" 12
Limpa o v�deo.

.ep
.in -3

.in
.sp
.b OBSERVA��ES
.in 5
Na vers�o atual n�o est�o implementados "paddings".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd):   "
tac, tic
.br
.wo "(libc):  "
printf
.br
.wo "(curses):"
curses, incurses, newterm
.br

.in
.sp
.b ARQUIVOS
.in 5
.ip /usr/lib/terminfo/* 22
arquivos onde est�o armazenadas as descri��es.
.ep

.in
.sp
.b EXEMPLOS
.in 5
Apresentamos abaixo uma descri��o simplificada
do terminal TV3000-BR fabricado pela Sisco Computadores S.A.

.sp
.nf
       tv3000br|Sisco TV3000,
               lines#24, cols#80, am,
               cuf1=^L, cub1=\b, cud1=\l, cuu1=^K,
               home=^^, ht=\t, cr=\r,
               cup=\E=\%'\s'\%p1\%+\%c%'\s'\%p2\%+\%c,
               bel=^G, clear=^Z,
               rev=\EH, dim=\EG, blink=\EF,
               smul=\EI, rmul=\EP,
               sgr0=\EK,
.fi

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
