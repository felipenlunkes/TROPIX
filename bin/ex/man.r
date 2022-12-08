.bp 1
.he 'EX (cmd)'TROPIX: Manual de Refer�ncia'EX (cmd)'
.fo 'Atualizado em 18.05.97'Vers�o 3.0.2'Pag. %'

.b NOME
.in 5
ex - editor visual de textos

.in
.sp
.b SINTAXE
.in 5
ex [-v] [<nome>]
.br

.in
.sp
.b DESCRI��O
.in 5
O comando "ex" � um editor de texto que pode utilizar toda
a tela do terminal para mostrar o arquivo em edi��o.
.sp
Op��es:
.in 8
.ip -v 8
Funcionamento verboso. Quando esta op��o est� ativa,
todos os comandos no modo Visual s�o ecoados.
.ep
.in 5

.sp
Argumentos:
.in 8
.ip <nome> 8
Nome do arquivo a ser editado.
Se este nome n�o corresponde a um arquivo j� existente,
o "ex" inicia a edi��o de um arquivo novo com o nome dado.
Se nenhum nome � fornecido, o "ex" inicia a edi��o 
de um arquivo novo, cujo nome poder� ser indicado
mais tarde atrav�s dos comandos "f" (file), "r" (read) ou "w" (write),
dispon�veis no modo Comandos.
.ep
.in 5

.sp
O editor "ex" tem dois modos principais de opera��o:
o modo 
.b Visual
(pelo qual ele inicia)
e o modo
.b Comandos.
Em cada modo existem comandos para a mudan�a de modo
ou para a execu��o de um comando no outro modo.

.in 5
.sp
.b 'Modo Visual:'
.sp
.in 5
No modo Visual o editor "ex" utiliza o v�deo do terminal
como uma janela para a visualiza��o do texto em edi��o
e o cursor como um apontador, indicando onde ser�o realizadas
as opera��es de edi��o.

.sp
Os comandos no modo Visual s�o compostos de alguns poucos
(geralmente um) caracteres normalmente n�o ecoados.
O efeito dos comandos � percebido instantaneamente pelo usu�rio
atrav�s do movimento do cursor e/ou da altera��o do texto na janela.
Os comandos, em sua maioria, podem ser precedidos de uma contagem,
indicando a repeti��o de seu efeito.
Os comandos que requerem mais de um caractere
podem ser cancelados (se ainda n�o foram totalmente digitados)
teclando-se o caractere <esc>.

.sp
As tabelas a seguir cont�m os comandos do modo Visual,
divididos em grupos com funcionalidade semelhante.

.(t
.sp
Os comandos a seguir reposicionam a janela sobre o texto em edi��o,
permitindo uma completa visualiza��o do mesmo.
.sp
.ts
center
allbox;
c s
c l.
Movendo a Janela
Comando	Fun��o
<^F>	avan�a uma janela de texto
<^B>	retrocede uma janela de texto
<^D>	avan�a suavemente meia janela
<^U>	retrocede suavemente meia janela
<^E>	avan�a uma linha
<^Y>	retrocede uma linha
G	mostra a linha dada a sua ordem
<^G>	informa a ordem da linha corrente
.te
.)t

.(t
.sp
Os comandos a seguir reposicionam o cursor,
passeando com o cursor pelo texto nas quatro dire��es b�sicas.
.sp
.ts
center
allbox;
c s
c l.
Movendo o Cursor nas Dire��es B�sicas
Comando	Fun��o
h	retrocede um caractere
j	avan�a uma linha na coluna corrente
k	retrocede uma linha na coluna corrente
l	avan�a um caractere
.te
.)t

.(t
.sp
Os comandos a seguir reposicionam o cursor,
passeando com o cursor por linhas pr�ximas a linha corrente.
.sp
.ts
center
allbox;
c s
c l.
Movendo o Cursor para Linhas Pr�ximas
Comando	Fun��o
 - 	retrocede uma linha
+	avan�a uma linha
H	primeira linha na janela
M	linha central na janela
L	�ltima linha na janela
.te
.)t

.(t
.sp
Os comandos a seguir reposicionam o cursor,
passeando com o cursor pela linha corrente.
.sp
.ts
center
allbox;
c s
c l.
Movendo o Cursor na Linha Corrente
Comando	Fun��o
0	primeiro caractere
^	in�cio (primeiro caractere n�o branco)
<bs>	retrocede um caractere
<sp>	avan�a um caractere
<ht>	pr�xima coluna de tabula��o
$	�ltimo caractere
.te
.)t

.(t
.sp
O editor "ex" distingue dois tipos de palavras:
para os comandos com letras mai�sculas
as palavras s�o sequ�ncias de caracteres n�o incluindo
os separadores <sp> e <ht>;
para os comandos com letras min�sculas, sequ�ncias alfanum�ricas
ou sequ�ncias de sinais de pontua��o.
O alcance destes comandos n�o se limita � linha corrente.
.sp
.ts
center
allbox;
c s
c l.
Movendo o Cursor por Palavras
Comandos	Fun��o
w  W	avan�a uma palavra
e  E	avan�a at� o final de uma palavra
b  B	retrocede ao inicio de uma palavra
.te
.)t

.(t
.sp
Os comandos a seguir movem o cursor para a primeira ocorr�ncia
do caractere especificado.
.sp
.ts
center
allbox;
c s
c l.
Busca de Caracteres
Comando	Fun��o
f<ch>	avan�a at� o caractere <ch> (inclusive)
F<ch>	retrocede at� o caractere <ch> (inclusive)
t<ch>	avan�a at� o caractere <ch> (exclusive)
T<ch>	retrocede at� o caractere <ch> (exclusive)
;	repete a �ltima busca de caractere
,	repete no sentido inverso
.te
.)t

.(t
.sp
Os comandos a seguir permitem que algumas linhas do texto
sejam referenciadas por letras min�sculas.
.sp
.ts
center
allbox;
c s
c l.
Marca��o de Linhas
Comando	Fun��o
m<letra>	marca a posi��o corrente como <letra>
'<letra>	move para a linha marcada como <letra>
`<letra>	move para a posi��o marcada como <letra>
''	retorna � posi��o corrente conseq�ente
-	ao �ltimo movimento relativo
.te
.)t

.(t
.sp
O editor "ex" � capaz de buscar express�es regulares no texto.
As express�es regulares aceitas est�o descritas resumidamente
adiante (se��o Express�es Regulares);
uma descri��o completa
pode ser encontrada no guia ("ex" (ref)).
.sp
.ts
center
allbox;
c s
c l.
Busca de Express�es Regulares
Comando	Fun��o
/<express�o><nl>	busca avan�ando
?<express�o><nl>	busca retrocedendo
n	repete a �ltima busca com "/" ou "?"
N	repete no sentido inverso
&	avan�a at� o primeiro caractere ap�s
-	a �ltima express�o regular encontrada
.te
.)t

.sp
Os comandos para a movimenta��o do cursor
podem ser utilizados para especificar a abrang�ncia
das opera��es de edi��o
(geralmente da regi�o apontada pelo cursor
at� a regi�o para onde o cursor iria).
Quando utilizados neste contexto, estes comandos s�o chamados de
.b
objetos.
.r

.(t
.sp
O "ex" disp�e de v�rios buffers, onde podem ser armazenadas partes do texto.
Os comandos para remo��o de texto e manipula��o de buffers
normalmente se referem a um buffer sem nome;
os outros buffers s�o nomeados por uma letra min�scula.
.sp
.ts
center
allbox;
c s
c l.
Manipula��o de Buffers
Comando	Fun��o
["<buf>]y<objeto>	operador para armazenamento
["<buf>]p	copia buffer ap�s o cursor
["<buf>]P	copia buffer antes do cursor
.te
.)t

.(t
.sp
Atrav�s dos operadores de edi��o podemos remover, substituir
e deslocar partes do texto.
.sp
.ts
center
allbox;
c s
c l.
Operadores de Edi��o
Comando	Fun��o
["<buf>]d<objeto>	remo��o
c<objeto>	substitui��o (remo��o e inser��o)
><objeto>	deslocamento para a direita
<<objeto>	deslocamento para a esquerda
.te
.)t

.(t
.sp
Atrav�s dos comandos para inser��o de texto
introduzimos o texto teclado no terminal
no texto em edi��o.
.sp
.ts
center
allbox;
c s
c l.
Inser��o de Texto
Comando	Fun��o
i	insere antes do cursor
a	insere ap�s o cursor
o	insere em uma nova linha abaixo
O	insere em uma nova linha acima
<eol>	termina inser��o de texto
.te
.)t

.(t
.sp
Todos os comandos de edi��o podem ser repetidos no mesmo ou em outro contexto
ou ter seu efeito anulado.
.sp
.ts
center
allbox;
c s
c l.
Repeti��o e Retroa��o dos Comandos de Edi��o
Comando	Fun��o
 . (ponto) 	repete o �ltimo comando de edi��o
u	desfaz a �ltima altera��o no texto
.te
.)t

.(t
.sp
Algumas opera��es mais utilizadas e que normalmente demandam
mais de um caractere para a sua especifica��o podem
ser especificados por comandos sin�nimos,
que consistem de apenas um caractere.
.sp
.ts
center
allbox;
c s s
c c l.
Alguns Sin�nimos �teis
Sin�nimo	Comandos	Fun��o
x	d<sp>	apaga o caractere sob o cursor
X	d<bs>	apaga o caractere anterior
s	c<sp>	substitui o caractere corrente
I	^i	insere no in�cio da linha
A	$a	insere ao final da linha corrente
C	c$	substitui at� o final da linha
D	d$	remove at� o final da linha
Y	yy	armazena a linha corrente
S	cc	substitui a linha corrente
<^N>	j	move para baixo
<nl>	j	move para baixo
<^P>	k	move para cima
<cr>	+	avan�a para a pr�xima linha
.te
.)t

.(t
.sp
A tabela a seguir cont�m alguns comandos de fun��es diversas,
que ainda n�o foram mencionados.
.sp
.ts
center
allbox;
c s
c l.
Outros Comandos
Comando	Fun��o
J	agrupamento de linhas
<^R> <^L>	reescreve a janela
!	envia um comando para a shell
rx	substitui o caractere corrente por "x"
%	busca o caractere par: () [] {}
.te
.)t

.in 5
.sp
.(t
.b 'Modo Inser��o'
.r
.sp
Durante a inser��o de texto (que pode ser ativada a partir do modo Visual)
os comandos do modo Visual n�o s�o v�lidos
e alguns caracteres especiais podem ser usados para editar
linha a linha o texto teclado,
permitindo a corre��o de erros de digita��o.
Os caracteres que comandam a edi��o da entrada s�o listados
a seguir com os nomes pelos quais eles podem ser alterados
atrav�s do comando "stty" e as suas respectivas fun��es.
.sp
.ts
center
allbox;
l l.
Caractere	Fun��o
<erase>	remove o �ltimo caractere inserido
<aerase>	alternativa a <erase>
<word>	remove a �ltima palavra inserida
<kill>	remove todo o texto inserido nesta linha
<retype>	reescreve a janela
<eol>	termina a inser��o
<eof>	alternativa a <eol>
<^V>	anula a fun��o especial do pr�x. caractere
.te
.)t

.in 5
.sp
.(t
.b 'Express�es Regulares'
.r
.sp
O editor "ex" reconhece um subconjunto de express�es regulares.
Uma express�o regular � especificada como uma cadeia de caracteres,
em que, com a exece��o de alguns caracteres especiais,
um caractere normalmente corresponde a ele mesmo.
Os caracteres especiais s�o ".", "[", "]", "\" e,
em alguns casos, "^", "$" , "*" e "+".
A tabela a seguir resume a funcionalidade dos caracteres especiais.
.)t

.sp
.(t
.ts
center
allbox;
c l.
Carac. Especial	Significado
^	in�cio de uma linha
$	final de uma linha
 . (ponto) 	qualquer caractere
[s]	um caractere presente na cadeia "s"
[^s]	um caractere ausente da cadeia "s"
x*	repeti��o de "x" (zero ou mais vezes)
x+	repeti��o de "x" (uma ou mais vezes)
\x	caractere "x"
.te
.)t

.in 5
.sp
.(t
.b 'Modo Comandos'
.r
.sp
.in 5
Os comandos do editor "ed" est�o dispon�veis no modo Comandos.
Entrada para o modo Comandos a partir do modo Visual: "Q".
Sa�da do modo Comandos e retorno para o modo Visual: "v".
.)t

.in
.sp
.b OBSERVA��ES
.in 5
O editor "ex" identifica o tipo de terminal onde ele est�
sendo executado atrav�s da vari�vel TERM, presente no ambiente.
Portanto antes de usar o "ex" � importante garantir
que o nome de seu terminal j� foi corretamente atribu�do a vari�vel TERM
e que esta vari�vel seja export�vel.

.sp
A recep��o dos sinais "SIGINT" e "SIGQUIT"
normalmente interrompe as opera��es do "ex".
A recep��o do sinal "SIGTERM" faz com que o texto em edi��o seja salvo
em um arquivo denominado "VI.SAVE" sob o diret�rio corrente
e que o "ex" termine a sua execu��o.

.sp
O comando "ex" identifica se o arquivo em edi��o � do estilo UNIX
(linhas terminadas por <nl>) ou estilo DOS (linhas terminadas por <cr><nl>),
e processa corretamento os dois estilos.

.in
.sp
.(t
.b "VEJA TAMB�M"
.r
.in 5
(cmd): ed, sh
.)t
.br
(ref): ex

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
