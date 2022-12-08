
.bp
.sp 4
.nf
     *********************************************************
     *                                                       *
     *                      CAP�TULO  3                      *
     *                                                       *
     *                     MODO COMANDOS                     *
     *                                                       *
     *********************************************************
.fi
.sp 4
.pp
Tanto o modo Visual como o modo Comandos s�o suficientes
para a realiza��o da maioria das opera��es de edi��o normalmente necess�rias,
entretanto em determinados contextos pode ser mais vantajoso
trabalhar em um ou no outro modo.
O modo Visual � mais adequado quando � necess�ria uma melhor visualiza��o
do texto e para a realiza��o de corre��es localizadas.
O modo Comandos � mais pr�tico
quando as opera��es de edi��o podem ser mais facilmente localizadas
linha a linha ou abrangem um n�mero inteiro de linhas.
Este cap�tulo detalha a funcionalidade do modo Comandos.

.pp
Os comandos do modo Comandos podem requerer zero, um ou dois endere�os.
Quando s�o fornecidos endere�os a menos,
o "vi" assume endere�os pr�-estabelecidos.
� um erro dar mais endere�os do que o comando espera.
.br

.pp
Se n�o for especificado nenhum comando
ap�s o endere�amento
o comando ser� "p" (print) (explicado mais adiante).
Uma linha em branco faz da linha seguinte � linha corrente
a nova linha corrente e a mostra.

.pp
Endere�os s�o tipicamente separados por uma v�rgula (",").
Quando os endere�os s�o separados por um ponto e v�rgula (";"),
o segundo endere�o � calculado fazendo-se antes
o primeiro endere�o como linha corrente.
Esta caracter�stica pode ser usada para determinar 
a linha incial para buscas para frente e para tr�s ("/" e "?").
O segundo endere�o de toda seq��ncia de dois endere�os
tem que corresponder a uma linha de ordem superior
a linha correspondente ao primeiro endere�o.

.pp
As se��es a seguir descrevem a especifica��o de endere�os
e todos os comandos dispon�veis.

.sp 2
.b
3.1. Endere�amento
.r

.pp
O endere�amento de linhas no texto em edi��o
baseia-se no conceito de linha corrente.
De modo geral a linha corrente � a �ltima linha afetada por um comando;
entretanto a escolha exata da nova linha corrente
ap�s a execu��o de cada comando
� explicada na discuss�o dos comandos.
Endere�os podem ser constru�dos do seguinte modo:

.in +3
.ip 1. 4
O caractere "." endere�a a linha corrente.

.ip 2. 4
O caractere "$" endere�a a �ltima linha no texto em edi��o.

.ip 3. 4
Um n�mero decimal "n" endere�a a linha de ordem "n'�sima" no texto em edi��o.

.(t
.ip 4. 4
A seq��ncia "'m" endere�a a linha marcada com o nome "m",
que deve ser uma letra min�scula.
No modo Visual linhas s�o marcadas atrav�s do comando "m",
no modo Comandos atrav�s do comando "k" (mark).
.)t

.(t
.ip 5. 4
Uma express�o regular entre barras ("/express�o/")
endere�a a linha encontrada buscando-se avante ap�s a linha corrente
ou ap�s o endere�o especificado at� ent�o
e parando na primeira linha que cont�m uma cadeia
que corresponda � express�o regular.
Se necess�rio, a busca d� a volta, passando pelo fim do texto em edi��o.
.)t

.(t
.ip 6. 4
Uma express�o regular entre interroga��es ("?express�o?")
endere�a a linha encontrada buscando-se retroativamente
antes da linha corrente
ou do endere�o especificado at� ent�o
e parando na primeira linha que cont�m uma cadeia
que corresponda � express�o regular.
Se necess�rio, a busca d� a volta, passando pelo in�cio do texto em edi��o.
.)t

.(t
.ip 7. 4
Um endere�o seguido de um "+" (sinal de soma)
ou de um "-" (sinal de subtra��o)
seguido de um n�mero decimal especifica um endere�o
somado ou subtra�do
do n�mero indicado de linhas.
.)t

.(t
.ip 8. 4
Se um endere�o come�a com "+" ou com  "-" a adi��o ou subtra��o
� tomada como em rela��o a linha corrente, isto �,
"-5" equivale � ".-5".
.)t

.(t
.ip 9. 4
Se um endere�o termina com "+" (ou "-"), ent�o um � somado (ou subtra�do).
Como conseq��ncia desta regra e da regra 8,
o endere�o "-" se refere � linha anterior a linha corrente.
Mais ainda, "-" e "+" no final de um endere�o t�m efeito cumulativo,
assim "--" se refere a linha corrente menos dois.
.)t
.ep
.in -3

.sp 2
.b
3.2. Comandos
.r
.pp
Est�o listados a seguir todos os comandos do modo Comandos.
Os valores pr�-estabelecidos para os endere�os
indicando a abrang�ncia dos comandos
s�o mostrados entre par�nteses � esquerda dos comandos.
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
e o acrescenta ao texto em edi��o a partir da linha endere�ada.
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
remove as linhas endere�adas do texto em edi��o.
A linha originalmente ap�s a �ltima linha removida
se tornar�  a linha corrente;
se as linhas removidas estavam originalmente no final do texto em edi��o,
a �ltima linha no texto em edi��o ser� a nova linha corrente.
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
causa a remo��o de todas linhas no texto em edi��o
e a leitura de "arquivo" para o texto em edi��o.
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
se o texto em edi��o j� foi alterado
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
(1, $) g!/express�o regular/ [comando]
.br
.in 10
Este comando � o mesmo que o comando "g", exceto que
"comando" � executado para cada linha n�o contendo
"express�o regular".
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
utiliza as linhas marcadas no �ltimo comando "g".
.)b

.sp
.(b
.in 5
(.) i
 <texto>
 .

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
faz com que "vi" termine.
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
ocorre se o texto em edi��o j� foi alterado  desde
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
l�  "arquivo" para o texto em edi��o
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
todas as ocorr�ncias de "express�o regular" s�o substitu�das.
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
divide a linha substitu�da em duas.
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
v
.in 10
O comando "v" (visual) retorna o editor ao modo Visual.
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
s�o acrescenatadas no final de "arquivo".
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

.in 0
