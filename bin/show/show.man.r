.bp
.he 'SHOW (cmd)'TROPIX: Manual de Refer�ncia'SHOW (cmd)'
.fo 'Atualizado em 04.12.02'Vers�o 4.4.0'Pag. %'

.b NOME
.in 5
.wo "show -"
mostra um arquivo em uma janela do video
.br

.in
.sp
.b SINTAXE
.in 5
.(l
show [-d] [<arquivo> ...]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "show" permite examinar de forma conveniente
um <arquivo> em uma janela do video. 
Se for dado mais de um nome de <arquivo>, "show" pede ao usu�rio
para escolher o nome desejado.
Se o nome do <arquivo> for omitido, ser� lida a entrada padr�o ("pipe").

.sp
O comando permite que o trecho vis�vel do <arquivo> na janela avance ou
retroceda, podendo-se examinar p�ginas posteriores ou reexaminar p�ginas
anteriores do <arquivo>.
Isto � especialmente �til para arquivos lidos da entrada padr�o.

.sp
Os comandos internos que permitem avan�ar/retroceder as p�ginas do
<arquivo> s�o dados abaixo. Eles s�o semelhantes aos comandos internos
do "vi" (cmd), e o o usu�rio habituado com o "vi" n�o ter� dificuldades
em utilizar o comando "show".

.sp
Normalmente, se o <arquivo> tiver linhas longas (maiores do que a janela)
elas ser�o truncadas. No entanto, se o tamanho da janela for aumentada,
as linhas ser�o reescritas completas (se o novo tamanho permitir).

.sp 2
As op��es do comando "show" s�o:

.in +3
.ip -d
Dobra:  as linhas longas s�o dobradas ao inv�s de truncadas.
Isto � uma opera��o definitiva; mesmo que o tamanho da janela seja aumentada, 
as linhas continuar�o dobradas. 

.ep
.in -3

.sp 2
Os comandos internos para avan�ar/retroceder a p�gina vis�vel do
<arquivo> na janela s�o os seguintes:

.in +3

.ip '[<n>] +' 13
.it '[<n>] <nl>' 13
.it '[<n>] <cr>' 13
Avan�a <n> linhas. Se <n> for omitido, avan�a uma linha.

.ip '[<n>] -' 13
Retrocede <n> linhas. Se <n> for omitido, retrocede uma linha.

.ip <^D> 13
.it '<Page Down>' 13
Avan�a meia janela.

.ip <^U> 13
.it '<Page Up>' 13
Retrocede meia janela.

.ip <Home> 13
Retrocede para o in�cio do diret�rio/carta.

.ip <End> 13
Avan�a para o final do diret�rio/carta.

.ip "[<n>] <^F>" 13
Avan�a <n> janelas. Se <n> for omitido, avan�a uma janela.

.(t
.ip "[<n>] <^B>" 13
Retrocede <n> janelas. Se <n> for omitido, retrocede uma janela.
.)t

.ip "[<n>] <^V>" 13
Avan�a <n> p�ginas (de 75 linhas cada). Se <n> for omitido, avan�a uma p�gina.

.ip "[<n>] <^Z>" 13
Retrocede <n> p�ginas. Se <n> for omitido, retrocede uma p�gina.

.ip <^R> 13
Reescreve a janela.

.ip 'f' 13
.it 'F' 13
.it <^G> 13
Escreve o nome do <arquivo> na �ltima linha da janela.

.ip '<sp>' 13
Tira a mensagem da �ltima linha da janela.

.ip "[<n>] g" 13
.it "[<n>] G" 13
Avan�a/retrocede para a janela que come�a na linha <n>.
Se <n> for omitido, avan�a para a �ltima janela do <arquivo>.

.ip "[<n>] p" 13
.it "[<n>] P" 13
Avan�a/retrocede para a p�gina <n>.
Se <n> for omitido, avan�a para a �ltima p�gina do <arquivo>.

.ip '/ <cadeia>' 13
Busca de cadeia: avan�a/retrocede para a primeira janela do <arquivo>
cuja primeira linha cont�m a <cadeia> dada.

.ip 'n' 13
Repete a busca de cadeia avan�ando: mostra a janela seguinte do <arquivo>
cuja primeira linha cont�m a <cadeia> dada.

.ip 'N' 13
Repete a busca de cadeia retrocedendo: mostra a janela anterior do <arquivo>
cuja primeira linha cont�m a <cadeia> dada.

.ip 'w <nome>' 13
.it 's <nome>' 13
Cria o arquivo <nome> com o conte�do do <arquivo> sendo examinado,
desde que o arquivo <nome> ainda n�o exista.
Isto � especialmente �til para arquivos lidos da entrada padr�o ("pipe").

.ip 'W <nome>' 13
.it 'S <nome>' 13
Escreve/reescreve o conte�do do <arquivo> sendo examinado no arquivo <nome>,
mesmo que o arquivo <nome> j� exista.

.ip '! <comando>' 13
Executa o <comando> atrav�s do "sh" (cmd).

.ip '?' 13
Mostra o manual do comando "show", para poder consultar esta lista
de comandos internos.

.ip <^C> 13
.it 'q' 13
.it 'Q' 13
Encerra a execu��o de "show".

.ep
.in -3

.in
.sp 2
.(t
.b OBSERVA��ES
.in 5
� feita uma an�lise simples dos caracteres do <arquivo>, e os caracteres
de controle (exceto <bs>, <cr> e <ht>) s�o convertidos nas
seq��ncias padronizadas "^X".
.)t

.bc	/*************************************/
.sp
Se o <arquivo> tiver linhas longas, e elas forem dobradas (isto �, n�o
for dada a op��o "-t"), o comando "show" perde a referencia aos n�meros
originais das linhas no <arquivo> dado.
Neste cado, os comandos "g" e "G" funcionam apenas com <n> igual a 1
ou com <n> omitido.
.ec	/*************************************/

.sp
Se o <arquivo> tiver linhas dobradas e/ou caracteres de controle,
o arquivo <nome> criado/reescrito
pelos comandos "w", "W", "s" e "S" n�o ser� id�ntico ao <arquivo> original.

.sp
Repare que os comandos internos "/", "n" e "N" procuram apenas
a cadeia como originalmente dada, n�o realizando uma busca de express�es
regulares, como o comando "vi" (cmd).

.sp
O comando "show" identifica se o arquivo em edi��o � do estilo UNIX
(linhas terminadas por <nl>) ou estilo DOS (linhas terminadas por <cr><nl>),
e processa corretamento os dois estilos.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
vi, ex, sh
.br

.in
.sp
.b EXEMPLO
.in 5
.nf
		grep INC *.c | show
.fi
.sp
mostra o arquivo de sa�da do comando "grep".

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
