.bp
.sp 5
.nf
     *********************************************************
     *                                                       *
     *                      CAP�TULO 2                       *
     *                                                       *
     *                      MODO VISUAL                      *
     *                                                       *
     *********************************************************
.fi
.sp 4
.pp
O "vi" no modo Visual utiliza o v�deo do terminal
como uma janela sobre o texto em edi��o
e o cursor como um apontador no texto, localizando as opera��es de edi��o.

.pp
Os comandos no modo Visual s�o compostos de alguns poucos
(geralmente um) caracteres normalmente n�o ecoados.
O efeito dos comandos � percebido instantaneamente pelo usu�rio
atrav�s do movimento do cursor e/ou da altera��o do texto na janela.
Os comandos, em sua maioria, podem ser precedidos de uma contagem.
Os comandos que requerem mais de um caractere
podem ser cancelados (se ainda n�o foram totalmente digitados)
teclando-se o caractere <esc>.

.sp 2
.b
2.1. Observa��o e Localiza��o no Texto
.r
.pp
A maioria dos comandos do editor "vi" em seu modo Visual
move a janela sobre o texto ou movimenta o cursor pelo texto.
De modo geral, estes comandos podem ser precedidos por uma contagem,
para indicar uma repeti��o no efeito destes comandos.

.sp
.b
2.1.1. Movendo a Janela sobre o Texto
.r

.pp
A por��o de texto mostrada a cada instante pela janela
� chamada de uma
.b p�gina.
� poss�vel mover a janela 
avan�ando ou retrocedendo p�ginas
ou, mais suavemente, deslocando a janela gradualmente.

.pp
Os comandos <^F> (move forward) e <^B> (move backward) movem a janela
em unidades de uma p�gina, respectivamente avan�ando ou retrocedendo.
Avan�ando ou retrocedendo a janela de uma p�gina,
o editor "vi" conserva duas linhas da p�gina mostrada anteriormente,
de modo a possibilitar a leitura cont�nua do texto.
Ap�s estes comandos o cursor se localiza
no in�cio da primeira palavra
na primeira linha da nova p�gina corrente.

.pp
Os comandos <^D> (sroll down) e <^U> (scroll up)
propiciam um modo mais confort�vel para percorrermos o texto.
Estes comandos respectivamente descem e sobem a janela sobre o texto,
"rolando" o v�deo e gradualmente expondo as linhas de texto adjacentes
� p�gina mostrada antes do comando.
Quando especificamos uma contagem, esta se refere ao n�mero de linhas 
em que a janela deve ser deslocada.
Quando n�o especificamos uma contagem,
a janela � deslocada de acordo com a �ltima contagem
fornecida a estes comandos ou,
se at� o momento n�o foram especificadas contagens para estes comandos,
de meia p�gina.
Os comandos <^E> e <^Y>, respectivamente sobem e descem a janela de uma linha.

.pp
Se o caractere apontado pelo cursor permanecer na janela
ap�s a execu��o dos comandos <^D>, <^U> <^E> ou <^Y>,
ele continuar� sendo apontado;
em caso contr�rio, o cursor apontar�
o in�cio da primeira palavra
na primeira linha na janela.

.pp
Exemplos:
a seq��ncia de comandos "5<^D><^U>"
move a janela abaixo cinco linhas e retorna � posi��o original,
o comando <^B> retrocede uma p�gina
e o comando "5<^F>" avan�a cinco p�ginas.

.sp
.b
2.1.2. Apontando uma Linha no Texto
.r

.pp
Os comandos "+" ou <cr> e "-" respectivamente avan�am e retrocedem uma linha.
O comando "H" (home) move o cursor para a primeira linha na janela.
O comando "M" (medium) move o cursor para uma linha
aproximadamente no meio da janela.
O comando "L" (last) move o cursor para a �ltima linha na janela.
O comando "G" (go) move o cursor para a linha especificada pela contagem;
na falta de uma contagem, "G" move o cursor para a �ltima linha do texto.
O comando <^G> informa a ordem da linha apontada
e o n�mero total de linhas no texto.

.sp
.b
2.1.3. Movendo o Cursor na P�gina Corrente
.r

.pp
As teclas "h", "j", "k" e "l" movem o cursor respectivamente 
para a esquerda, para baixo, para cima e para a direita.
Se h� setas no teclado do seu terminal,
elas provavelmente s�o reconhecidas pelo editor "vi"
e tamb�m podem ser usadas para mover o cursor.

.sp
.b
2.1.4. Movendo o Cursor na Linha Corrente
.r

.pp
Os seguintes comandos movem o cursor sobre a linha corrente:
<bs> para o caractere � esquerda do cursor,
<sp> para o caractere � direita do cursor,
<ht> para o caractere ocupando a pr�xima coluna de tabula��o,
"0" para o primeiro caractere,
"$" para o �ltimo caractere,
"w" e "W" (word) para o in�cio da pr�xima palavra,
"e" e "E" (end) para o pr�ximo fim de palavra,
"b" e "B" (begin) para o in�cio de palavra imediatamente anterior e
"^" para o in�cio da primeira palavra.

.pp
O editor "ex" distingue dois tipos de palavras:
para os comandos com letras mai�sculas
as palavras s�o seq��ncias de caracteres n�o incluindo
os separadores <sp> e <ht>;
para os comandos com letras min�sculas, seq��ncias alfanum�ricas
ou seq��ncias de sinais de pontua��o.
O alcance destes comandos n�o se limita � linha corrente.
Uma palavra � definida como uma seq��ncia de caracteres
diferentes de <sp> e <ht>.

.sp
.b
2.1.5. Busca de Express�es Regulares
.r

.pp
A busca de express�es regulares �
uma das formas mais pr�ticas de localizar um trecho espec�fico
dentro do texto em edi��o.
Durante a busca de uma express�o regular, o editor "vi" percorre o texto circularmente,
ou seja, o editor "vi" considera
que ao fim do texto segue-se o seu in�cio e vice-versa.

.pp
O comando "/" busca uma express�o regular fornecida na �ltima linha do v�deo
(como no modo Comandos descrito adiante)
avan�ando a partir do caractere apontado pelo cursor.
O comando "?" tamb�m requer uma express�o regular na �ltima linha do v�deo
e procura-a nas linhas anteriores do texto.
O comando "n" (next) repete o �ltimo comando "/" ou "?" executado.
O comando "N" repete a �ltimo comando "/" ou "?" revertendo o sentido da busca.

.pp
O comando "&" move o cursor para o caractere
seguinte � cadeia correspondente � express�o regular.

.sp
.b
2.1.6. Busca de Caracteres
.r
.pp
Os comandos "f" e "F" (find) buscam o caractere fornecido a seguir,
repectivamente para frente e para tr�s.
Os comandos "t" e "T" (up to) s�o an�logos aos comandos "f" e "F",
por�m n�o movem o cursor para o caractere procurado,
mas sim para o caractere que o antecedeu na busca.

.sp
.b
2.1.7. Marca��o de Linhas
.r
.pp
A marca��o de linhas permite que linhas sejam referenciadas por letras.
Um comando na forma "mx", onde "x" � uma letra min�scula,
associa � linha corrente a marca "x".
Uma linha marcada pode ser localizada por um comando na forma
"'x", onde "x" � a marca associada.
Um comando na forma "`x" localiza a posi��o exata da marca��o
(linha e ordem do caractere marcado).

.sp
.b
2.1.8. Verifica��o de Balanceamento
.r
.pp
O comando "%" busca o caractere correspondente ao balanceamento
do caractere corrente.
Os caracteres "[", "{" e "(" s�o balanceados respectivamente
pelos caracteres "]", "}" e ")" e vice-versa.

.sp 2
.b
2.2. Edi��o B�sica do Texto
.r
.pp
Esta se��o aborda todos os comandos do modo Visual
para altera��o do texto.

.sp
.(t
.b
2.2.1. Inser��o de Texto
.r

.pp
O editor "vi" disp�e de v�rios comandos
que permitem acrescentar caracteres teclados ao texto.
Estes comandos colocam o editor "vi" em seu modo Inser��o.
.)t

.pp
No modo Inser��o, o editor "vi" abre um espa�o apontado pelo cursor,
indicando onde o pr�ximo caractere ser� inserido.
O caractere <esc> encerra o modo Inser��o.
O estado do texto sob a janela � constantemente mantido atualizado no v�deo
durante o funcionamento do modo Inser��o
(para maiores detalhes, veja o Cap�tulo 4).

.pp
Existem quatro comandos b�sicos que iniciam o modo Inser��o.
Os comandos "i" (insert) e "a" (append) inserem texto
respectivamente � esquerda e � direita do caractere apontado pelo cursor.
Os comandos "o" e "O" (open) permitem a inser��o de texto
respectivamente abaixo e acima da linha apontada pelo cursor.

.sp
.b
2.2.2. Operadores
.r

.pp
Operadores manipulam extens�es cont�guas de texto.
Os operadores devem ser seguidos de um comando para movimento do cursor
que especifica o escopo da opera��o.
Este comando para movimento do cursor � chamado
.b
objeto
.r
quando utilizado neste contexto.

.pp
As opera��es podem abranger linhas inteiras
ou uma parte do texto entre dois caracteres,
de acordo com o tipo do movimento correspondente ao objeto.
No caso de repeti��o do operador, a opera��o abrange
um n�mero de linhas inteiras dado pela contagem.

.pp
Os seguintes operadores est�o dispon�veis:
"d" (delete) para remo��o,
"c" (change) para substitui��o
(remo��o seguida de entrada no modo Inser��o)
e ">" e "<" para o deslocamento de linhas
respectivamente para a direita e para a esquerda
(atrav�s da inser��o e remo��o de caracteres <ht>).
O operador "y" (yank) para armazenamento independente
de partes do texto est� descrito adiante
(se��o 2.3. C�pia e Transfer�ncia de Blocos).

.pp
Exemplos:
o comando "d$" remove do caractere apontado pelo cursor
at� o final da linha corrente;
o comando "3cc" substitui a linha corrente
e mais duas abaixo por um texto inserido;
a seq��ncia "/ontem<esc>c&hoje<esc>"
busca a palavra "ontem" e a substitui pela palavra "hoje".

.sp
.b
2.2.3. Revers�o e Repeti��o dos Comandos de Edi��o
.r

.pp
O comando "u" (undo) reverte o �ltimo comando de edi��o.
Isto significa que sempre � poss�vel retornar o texto ao seu estado anterior.
O comando "u" tamb�m pode ser revertido.
A aplica��o repetida do comando "u"
faz com que o texto alterne entre dois estados (o atual e o anterior).

.pp
O comando "." (ponto) repete o �ltimo comando de edi��o.

.sp
.(t
.b
2.2.4. Substitui��o de um Caractere
.r

.pp
O comando "r" (replace) substitui o caractere apontado pelo cursor
pelo caractere teclado a seguir.
.)t

.sp 2
.b
2.3. C�pia e Transfer�ncia de Blocos de Texto
.r
.pp
Blocos de texto s�o grupos de linhas de texto cont�guas.
O editor "vi" disp�e de um conjunto de �reas de mem�ria
capazes de armazen�-los.
Estas �reas de mem�ria s�o chamadas 
.b buffers.
Existem 27 buffers no editor "vi";
26 s�o referenciados por uma letra min�scula
(buffers com nomes de "a" at� "z")
e um � acessado diretamente (buffer sem nome).

.pp
As opera��es b�sicas relativas aos buffers
s�o a c�pia de uma parte do texto para um buffer
e sua rec�proca - a c�pia do conte�do de um buffer para o texto.
O operador "y" (yank) copia o objeto especificado para um buffer.
Os comandos "p" e "P" (put) copiam o conte�do de um buffer
para respectivamente ap�s e antes o cursor.

.pp
O operador "y" e os comandos "p" e "P"
na forma mais simples trabalham com o buffer sem nome.
A especifica��o de um buffer antecede o comando
e � feita teclando aspas (") e a letra correspondente ao buffer desejado.

.pp
Os buffers n�o s�o preenchidos apenas pelo operador "y".
As partes do texto removidas pelo operador "d"
tamb�m s�o copiadas para os buffers.

.pp
Uma aplica��o interessante do buffer sem nome
� um modo bastante pr�tico
para a transfer�ncia de parte do texto,
realizando a seguinte s�rie de comandos:
remo��o da parte do texto desejada,
movimento do cursor
e c�pia do buffer sem nome para o texto em edi��o.

.pp
Exemplos:
o comando
.b
yw
.r
guarda uma palavra no buffer sem nome;
o comando
.b
"ay'x
.r
copia para o buffer "a" as linhas
desde a linha corrente at� a linha marcada como "x".

.sp 2
.b
2.4. Sin�nimos
.r

.pp
Existem alguns sin�nimos usando apenas um caractere
para os comandos ou seq��ncias de comandos utilizados
com maior frequ�ncia e que requerem dois ou mais caracteres
para serem executados.
A lista completa dos sin�nimos e seus respectivos significados
est� na tabela a seguir.

.sp
.(t
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
.te
.)t

