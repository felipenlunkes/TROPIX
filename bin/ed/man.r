.bp 1
.he 'ED (cmd)'TROPIX: Manual de Refer�ncia'ED (cmd)'
.fo 'Atualizado em 27.04.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
ed - editor de textos orientado por linhas

.in
.sp
.b SINTAXE
.in 5
ed [nome]

.in
.sp
.b DESCRI��O
.in 5
O programa "ed" � um editor de textos orientado por linhas.

.br
.sp
Se o par�metro "nome" estiver presente, "ed" l� o arquivo correspondente
simulando um comando "e" (edit), descrito abaixo.

.br
.sp
O editor "ed" opera em uma c�pia do arquivo em edi��o.
Quaisquer altera��es realizadas na c�pia
n�o afetar�o o arquivo at�
que um comando "w" (write) seja executado.
Chamaremos a c�pia do arquivo em edi��o de
.b
"buffer".
.r

.br
.sp
Os comandos de "ed" t�m uma estrutura simples e regular:
zero, um ou dois endere�os seguidos de um comando com apenas um caractere,
possivelmente acompanhado de argumentos e sufixos.
Os endere�os especificam as linhas no "buffer" atingidas pelo comando.
Na falta de endere�os s�o assumidos endere�os pr�-estabelecidos.

.br
.sp
.b Endere�amento:
.in 5
.sp
O endere�amento de linhas no "buffer"
baseia-se no conceito de linha corrente.
De modo geral a linha corrente � a �ltima linha afetada
por um comando; entretanto o efeito exato na linha corrente
� explicado na discuss�o dos comandos.
Endere�os podem ser construidos do seguinte modo:
.br

.in 10
.ip 1. 4
O caractere "." endere�a a linha corrente.

.ip 2. 4
O caractere "$" endere�a a �ltima linha no "buffer".

.ip 3. 4
Um n�mero decimal "n" endere�a a linha de ordem "n'�sima" no "buffer".

.ip 4. 4
A sequ�ncia "'m" endere�a a linha marcada com o nome "m",
que deve ser uma letra min�scula.
Linhas s�o marcadas com o comando "k" (mark), que ser� descrito adiante.

.ip 5. 4
Uma express�o regular entre barras ("/express�o/")
endere�a a linha encontrada buscando-se avante ap�s a linha corrente
ou ap�s o endere�o especificado at� ent�o
e parando na primeira linha que contem uma cadeia
que corresponda � express�o regular.
Se necess�rio a busca d� a volta, passando pelo fim do "buffer".

.ip 6. 4
Uma express�o regular entre interroga��es ("?express�o?")
endere�a a linha encontrada buscando-se retroativamente
antes da linha corrente
ou do endere�o especificado at� ent�o
e parando na primeira linha que contem uma cadeia
que corresponda � expressao regular.
Se necess�rio a busca d� a volta, passando pelo in�cio do "buffer".

.ip 7. 4
Um endere�o seguido de um "+" (sinal de soma)
ou de um "-" (sinal de subtra��o)
seguido de um n�mero decimal especifica um endere�o mais ou menos
o n�mero indicado de linhas.

.ip 8. 4
Se um endere�o come�a com "+" ou com  "-" a adi��o ou subtra��o
� tomada como em rela��o a linha corrente, isto �,
"-5" equivale � ".-5".

.ip 9. 4
Se um endere�o termina com "+" (ou "-"), ent�o um � somado (ou subtraido).
Como consequ�ncia desta regra e da regra 8,
o endere�o "-" se refere � linha anterior a linha corrente.
Mais ainda, "-" e "+" no final de um endere�o t�m efeito cumulativo,
assim "--" se refere a linha corrente menos dois.
.lp

.br
.in 5
.sp
.b 'Express�es Regulares:'

.br
.in 5
.sp
O editor "ed" suporta uma forma limitada de express�es regulares.
Uma express�o regular especifica um conjunto de cadeias de caracteres.
Dizemos que um membro deste conjunto de cadeias
corresponde � express�o regular.
Na defini��o de express�o regular a seguir a palavra "caractere"
significa qualquer caractere � exce��o de <nl>:

.in 10
.br
.ip 1. 4
Qualquer caractere exceto um caractere especial corresponde a si pr�prio.
Caracteres especiais s�o o delimitador da express�o regular
e mais os caracteres "\", "[", "." e em alguns casos "^", "*" e "$".

.ip 2. 4
Um "\" (barra invertida) seguido de qualquer caractere corresponde
ao pr�prio caractere.

.ip 3. 4
Um "." (ponto) corresponde a qualquer caractere.

.ip 4. 4
Uma cadeia n�o vazia "s" entre colchetes "[s]" (ou "[^s]")
corresponde a qualquer caractere presente (ou ausente) "s".
Uma sub-cadeia "a-b" dentro de "s",
com "a" e "b" em ordem crescente ISO,
significa o conjunto de caracteres ISO entre "a" e "b", inclusive.
Os caracteres "]", "-" e "\" podem ser especificados precedendo-os com "\".

.ip 5. 4
Uma express�o regular da forma 1 at� 4 seguido de "*"
corresponde a zero ou mais ocorr�ncias da express�o regular.

.ip 6. 4
Uma express�o regular "x" da forma 1 at� 6, seguida
de uma express�o regular "y" da forma 1 at� 5
corresponde a uma ocorr�ncia de "x" seguida de uma ocorr�ncia de "y"
com a correspond�ncia para "x" sendo a mais longa
que permita a correspond�ncia para "y".

.ip 7. 4
Uma express�o regular da forma 1 at� 6 precedida por "^"
(ou seguida de "$"),
� restrita a correspond�ncias no in�cio (ou no fim)
de uma linha.

.ip 8. 4
Uma express�o regular da forma 1 at� 7 corresponde
� mais longa das correspond�ncias mais � esquerda da linha.

.ip 9. 4
Uma express�o regular vazia
equivale a c�pia da �ltima express�o regular procurada.
.lp
.in 5

Express�es regulares s�o usadas em endere�os para especificar linhas
e no comando "s" (substitute), descrito abaixo,
para especificar a por��o da linha que ser� substituida.
.br


.in 5
.br
.sp
.b 'Modo Entrada de Texto:'
.br

.in 5
.sp
Alguns comandos permitem a adi��o de texto novo no "buffer".
Enquanto "ed" est� recebendo texto,
dizemos que ele est� em modo de entrada de texto.
Neste modo, nenhum comando � reconhecido;
toda entrada � simplesmente acrescentada ao "buffer".
O modo de entrada de texto termina  quando entramos
uma linha contendo apenas "." (ponto).
Apos a execu��o destes comandos
a linha corrente ser� a �ltima linha no texto entrado
ou, se este for nulo, a linha endere�ada para o comando.
.br

.in 5
.br
.sp
.b Comandos:
.br

.in 5
.sp
Os comandos de "ed" podem requerer zero, um ou dois endere�os.
Quando s�o fornecidos endere�os a menos,
"ed" assume endere�os pr�-estabelecidos.
� um erro dar mais endere�os do que o comando espera.
.br

.sp
Se n�o for especificado nenhum comando
ap�s o endere�amento
o comando ser� "p" (print).
Uma linha em branco faz da linha seguinte � linha corrente
a nova linha corrente e a mostra.
.br

.sp
Endere�os s�o tipicamente separados por uma v�rgula (",").
Quando os endere�os s�o separados por um ponto e v�rgula (";"),
o segundo endere�o � calculado fazendo-se antes
o primeiro endere�o como linha corrente.
Esta caracter�stica pode ser usada para determinar 
a linha incial para buscas para frente e para tr�s ("/" e "?").
O segundo endere�o de toda sequ�ncia de dois endere�os
tem que corresponder a uma linha de ordem superior
a linha correspondente ao primeiro endere�o.
.br

.sp
Na lista a seguir de comandos do "ed",
os valores pr�-estabelecidos para os endere�os
s�o mostrados entre par�nteses.
.br
.sp
.(b
.in 5
(.) a
.br
<texto>
.br
 .
.br

.in 10
O comando 
"a" (append)
l� o texto dado
e o acrescenta ao "buffer" a partir da linha endere�ada.
.)b

.sp
.(b
.in 5
(.,.) c
.br
<texto>
.br
 .
.br

.in 10
O comando 
"c" (change)
remove as linhas endere�adas,
e ent�o recebe o texto entrado
que substitui estas linhas.
Se n�o houver texto entrado,
a nova linha corrente ser� a linha anterior �s linhas removidas.
.)b

.sp
.(b
.in 5
(., .) d[p]
.br
.in 10
O comando 
"d" (delete)
remove as linhas endere�adas do "buffer".
A linha originalmente ap�s a �ltima linha removida
se tornar�  a linha corrente;
se as linhas removidas estavam originalmente no final do "buffer",
a �ltima linha no "buffer" ser� a nova linha corrente.
Se o sufixo "p" estiver presente a nova linha corrente � mostrada.
.br
.)b

.sp
.(b
.in 5
e [arquivo]
.br

.in 10
O comando 
"e" (edit)
causa a remo��o de todas linhas no "buffer"
e a leitura de "arquivo" para o "buffer".
O n�mero de linhas e caracteres lidos � escrito.
O nome "arquivo" � lembrado para poder ser usado em sub-sequentes
comandos "r", "w" e "e" como nome de arquivo pr�-estabelecido.
.)b

.sp
.(b
.in 5

E [arquivo]
.br
.in 5
e! [arquivo]
.br
.in 10
Estes comandos s�o equivalentes ao comando "e",
exceto que nenhuma mensagem de erro � enviada
se o "buffer" j� foi alterado
desde sua �ltima atualiza��o no sistema de arquivos.
.br
.)b

.sp
.(b
.in 5

f [arquivo]
.br
.in 10
O comando 
"f" (filename)
informa o nome lembrado para o arquivo em edi��o.
Se "arquivo" � dado, o nome correntemente lembrado � trocado para "arquivo".
.br
.)b

.sp
.(b
.in 5

(1,$) g/express�o regular/ [comando]
.br
.in 10
O comando 
"g" (global)
marca todas as linhas endere�adas
onde h� uma ocorr�ncia de "express�o regular"
e para cada uma dessas linhas
a torna a linha corrente
e executa "comando"
Os comandos "a", "i", "c",
"g" e "v" n�o s�o permitidos.
.)b

.sp
.(b
.in 5
g [comando]
.br
.in 10
O comando 
"g" (global)
sem especifica��o de express�o regular
utiliza as linhas marcadas no �ltimo comando "g" ou "v".
.)b

.sp
.(b
.in 5
(.) i
.br
<texto>
.br
 .
.br

.in 10
O comando 
"i" (insert)
acrescenta  o texto antes da linha endere�ada.
Este comando difere do comando "a" apenas no local para coloca��o do texto.
.)b

.sp
.(b
.in 5
(., .+1) j
.br
.in 10
O comando
"j" (join)
transforma as linhas endere�adas
em uma �nica linha.
A linha resultante ser� a nova linha corrente.
.)b

.sp
.(b
.in 5
(.) k m
.br
.in 10
O comando 
"k" (mark)
marca a linha endere�ada com a letra min�scula "m".
O endere�amento "'m" se refere a esta linha.
.)b

.sp
.(b
.in 5
(., .) l
.br
.in 10
O comando 
"l" (list)
mostra as linhas endere�adas
de uma forma n�o amb�gua.
Os caracteres <bs> s�o indicados por "<"
e caracteres de tabula��o (<ht>) s�o indicados por ">".
Linhas muito longas s�o quebradas
em linhas de at� 72 colunas.
O final de cada linha � indicado com um "$".
.)b

.sp
.(b
.in 5
(., .) m endere�o
.br
.in 10
O comando 
"m" (move)
reposiciona as linhas endere�adas para ap�s a linha endere�ada
por "endere�o". A �ltima das linhas movidas se tornar� a linha
corrente.
.)b

.sp
.(b
.in 5
(., .) n
.br
.in 10
O comando 
"n" (number)
exibe as linhas endere�adas
com os n�meros das linhas e um <ht> � esquerda.
.)b

.sp
.(b
.in 5
(., .) p
.br
.in 10
O comando
"p" (print)
mostra as linhas endere�adas.
A �ltima linha mostrada ser� a nova linha corrente.
O comando "p" pode ser colocado na mesma linha que um comando
que n�o realize entrada ou saida.
.)b

.sp
.(b
.in 5
(., .) P
.br
.in 10
Este comando mostra uma p�gina com a linha endere�ada no centro.
A linha corrente permanece inalterada.
.)b

.sp
.(b
.in 5
q
.in 10
O comando 
"q" (quit)
faz com que "ed" termine.
O arquivo em edi��o n�o � automaticamente atualizado no disco.
.)b

.sp
.(b
.in 5
Q
.br
.in 5
q!
.in 10
Estes comandos s�o o mesmo que "q", exceto que
nenhuma mensagem de erro
ocorre se o "buffer" j� foi alterado  desde
a �ltima atualiza��o do arquivo.
.)b

.sp
.(b
.in 5
($) r [arquivo]
.br
.in 10
O comando 
"r" (read)
l�  "arquivo" para o "buffer"
ap�s a linha endere�ada.
Se "arquivo" estiver ausente,
o nome corrente � utilizado.
O nome "arquivo"  � lembrado se ainda n�o houver um nome de arquivo corrente.
Se a leitura for bem sucedida,
o n�mero de  linhas e caracteres lidos � mostrado.
A nova linha corrente ser� a �ltima linha lida do arquivo.
A �ltima linha lida do arquivo ser� a nova linha corrente.
.)b

.sp
.(b
.in 5
(., .) s[n]/express�o regular/substitui��o/ [p]
.br
.in 10
O comando 
"s" (substitute)
busca em cada linha endere�ada
ocorr�ncias de "express�o regular"
e substitue as de ordem "n" por "substitui��o".
Se a ordem "n" n�o for especificada,
todas as ocorr�ncias de "express�o regular" s�o substituidas.
� um erro a n�o ocorr�ncia de 'express�o regular'
em todas as linhas endere�adas.
.br
.sp
Qualquer caractere de pontuac�o pode ser usado em lugar de "/"
para delimitar a express�o regular e a substitui��o.
.br
.sp
O caracter "&" em 'substitui��o' � substituido
pela cadeia correspondente � express�o regular.
O significado especial de "&" pode ser anulado
precedendo-o por "\".
.br
.sp
O caractere <nl> precedido por "\"
divide a linha substituida em duas.
.br
.sp
A �ltima linha onde houve substitui��o ser� a nova linha corrente.
.)b

.sp
.(b
.in 5
(., .) t endere�o
.br
.in 10
Este comando age como o comando "m" (move),
exceto que uma c�pia das linhas endere�adas
� colocada ap�s "endere�o".
A �ltima linha copiada ser� a nova linha corrente.
.)b

.sp
.(b
.in 5
(1, $) v/express�o regular/ [comando]
.br
.in 10
Este comando � o mesmo que o comando "g", exceto que
"comando" � executado para cada linha n�o contendo
"express�o regular".
.)b

.sp
.(b
.in 5
(1, $) w[!] [arquivo]
.br
.in 10
O comando 
"w" (write)
escreve as linhas endere�adas
em "arquivo".
Se o arquivo n�o existe, � criado.
Este comando n�o ser� obedecido se "arquivo" for o nome correntemente lembrado
e n�o tenha havido altera��o no texto
desde sua �ltima atualiza��o no disco
ou se "arquivo" n�o for o nome correntemente lembrado
e j� existir um arquivo com seu nome.
O comando seguido de exclama��o s� n�o � executado
em caso de erro de escrita no disco.
A linha corrente permanece inalterada.
Se o comando � bem sucedido
o n�mero de linhas e caracteres escritos � mostrado.
.)b

.sp
.(b
.in 5
(1, $) W [arquivo]
.br
.in 10
Este comando � o mesmo que "w", exceto que as linhas endere�adas
s�o acrescentadas no final de "arquivo".
.)b

.sp
.(b
.in 5
($) =
.br
.in 10
O n�mero da linha endere�ada � mostrado.
A linha corrente permanece inalterada.
.)b

.sp
.(b
.in 5
! [Comando Shell]
.br
.in 10
O restante da linha ap�s o "!" � enviado a "sh"(cmd)
para ser interpretado como um comando.
.)b

.sp
.(b
.in 5
(.+1, .+1)
.br
.in 10
Um endere�amento apenas mostra as linhas endere�adas.
A �ltima linha mostrada ser� a nova linha corrente.
.)b

.in
.sp
.b OBSERVA��O
.in 5
A vers�o inicial n�o disp�e do comando "undo".

.sp
Quando "ed" l� um arquivo, todos os caracteres nulos s�o descartados
e � acrescentado um <nl> ao final do arquivo,
se ele estiver ausente.

.sp
As linhas muito longas quando lidas de um arquivo
ou tecladas no modo de entrada de texto
s�o divididas em linhas de at� 255 caracteres.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
vi, 
sh
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
