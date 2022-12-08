.bp
.he 'MODIF (cmd)'TROPIX: Manual de Refer�ncia'MODIF (cmd)'
.fo 'Atualizado em 04.12.02'Vers�o 4.4.0'Pag. %'

.b NOME
.in 5
.wo "modif -"
mostra um manual de modifica��es na janela do v�deo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
modif [-cslwnxD] [<manual de modifica��es>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "modif" permite ler/reler de forma conveniente
um <manual de modifica��es> na janela do v�deo.

.sp
O <manual de modifica��es> pedido pode ser o de refer�ncia de um comando,
de uma chamada ao sistema, de uma fun��o da biblioteca padr�o
ou de uma fun��o da biblioteca "curses".
Atrav�s da op��o "-D" (ver abaixo) podemos obter um �ndice dos
manuais de modifica��es dispon�veis em cada se��o.

.sp
A busca do <manual de modifica��es> � realizada na ordem indicada acima;
como em alguns casos se��es distintas possuem manuais hom�nimos,
podemos indicar qual a se��o desejada atrav�s de uma op��o. 

.sp
O comando permite que a p�gina vis�vel do <manual de modifica��es> na janela
avance ou retroceda, e podemos ler p�ginas posteriores ou reler p�ginas
anteriores do <manual de modifica��es>.

.sp
Os comandos internos que permitem avan�ar/retroceder as p�ginas do
<arquivo> s�o dados abaixo. Eles s�o semelhantes aos comandos internos
do "vi" (cmd), e o o usu�rio habituado com o "vi" n�o ter� dificuldades
em utilizar o comando "modif".

.sp 2
As op��es do comando s�o:

.in +3
.ip -c
Se��o "cmd": o <manual de modifica��es> desejado � o de refer�ncia
de um comando.

.ip -s
Se��o "sys": o <manual de modifica��es> desejado � o de uma chamada ao sistema.

.ip -l
Se��o "libc": o <manual de modifica��es> desejado � o de uma fun��o
da biblioteca padr�o da linguagem "C".

.ip -w
Se��o "curses": o <manual de modifica��es> desejado � o de uma fun��o
da biblioteca "curses".

.ip -n
Se��o "network": o <manual de modifica��es> desejado � o de uma fun��o
da biblioteca de redes (padr�o XTI).

.ip -x
Se��o "X-Window": o <manual de modifica��es> desejado � o de uma fun��o
ou de um comando do sistema "X-Window".

.ip -D
Ao inv�s de um manual de modifica��es, mostra na janela o �ndice dos manuais
de modifica��es dispon�veis  em uma das se��es (que deve ser escolhida
atrav�s de uma das op��es acima ("-c" por omiss�o)).

.ep
.in -3

.sp 2
.(t
Os comandos internos para avan�ar/retroceder a p�gina vis�vel do
<manual de modifica��es> na janela s�o os seguintes:

.in +3

.ip '[<n>] +' 13
.it '[<n>] <nl>' 13
.it '[<n>] <cr>' 13
Avan�a <n> linhas. Se <n> for omitido, avan�a uma linha.
.)t

.ip '[<n>] -' 13
Retrocede <n> linhas. Se <n> for omitido, retrocede uma linha.

.ip <^D> 13
.it '<Page Down>' 13
Avan�a meia janela (11 linhas).

.ip <^U> 13
.it '<Page Up>' 13
Retrocede meia janela.

.ip <Home> 13
Retrocede para o in�cio do diret�rio/carta.

.ip <End> 13
Avan�a para o final do diret�rio/carta.

.ip "[<n>] <^F>" 13
Avan�a <n> janelas (de 21 linhas cada). Se <n> for omitido, avan�a uma janela.

.ip "[<n>] <^B>" 13
Retrocede <n> janelas. Se <n> for omitido, retrocede uma janela.

.ip "[<n>] <^V>" 13
Avan�a <n> p�ginas (de 75 linhas cada). Se <n> for omitido, avan�a uma p�gina.

.ip "[<n>] <^Z>" 13
Retrocede <n> p�ginas. Se <n> for omitido, retrocede uma p�gina.

.ip <^R> 13
Reescreve a janela.

.ip 'f' 13
.it 'F' 13
.it <^G> 13
Escreve o nome do <manual de modifica��es> na �ltima linha da janela.

.ip '<sp>' 13
Tira a mensagem da �ltima linha da janela.

.ip "[<n>] g" 13
.it "[<n>] G" 13
Avan�a/retrocede para a janela que come�a na linha <n>.
Se <n> for omitido, avan�a para a �ltima janela do <manual de modifica��es>.

.ip "[<n>] p" 13
.it "[<n>] P" 13
Avan�a/retrocede para a p�gina <n>.
Se <n> for omitido, avan�a para a �ltima p�gina do <manual de modifica��es>.

.ip '/ <cadeia>' 13
Busca de cadeia: avan�a/retrocede para a primeira janela do <manual de
modifica��es> cuja primeira linha cont�m a <cadeia> dada.

.ip 'n' 13
Repete a busca de cadeia avan�ando: mostra a janela seguinte do
<manual de modifica��es> cuja primeira linha cont�m a <cadeia> dada.

.ip 'N' 13
Repete a busca de cadeia retrocedendo: mostra a janela anterior do
<manual de modifica��es> cuja primeira linha cont�m a <cadeia> dada.

.ip 'w <nome>' 13
.it 's <nome>' 13
Cria o arquivo <nome> com o conte�do do <manual> sendo lido,
desde que o arquivo <nome> ainda n�o exista.

.ip 'W <nome>' 13
.it 'S <nome>' 13
Escreve/reescreve o conte�do do <manual> sendo examinado no arquivo <nome>,
mesmo que o arquivo <nome> j� exista.

.ip '! <comando>' 13
Executa o <comando> atrav�s do "sh" (cmd).

.ip <^C> 13
.it 'q' 13
.it 'Q' 13
Encerra a execu��o de "man".

.ep
.in -3

.in
.sp 2
.b OBSERVA��O
.in 5
Repare que os comandos internos "/", "n" e "N" procuram apenas
a cadeia como originalmente dada, n�o realizando uma busca de express�es
regulares, como o comando "vi" (cmd).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
vi, ex, sh, show
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
