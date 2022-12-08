.bp
.he 'SROFF (cmd)'TROPIX: Manual de Modifica��es'SROFF (cmd)'
.fo 'Atualizado em 28.12.04'Vers�o 4.7.0'Pag. %'

.b NOME
.in 5
.wo "sroff -"
formatador de textos
.br

.in
.sp 2

.ip "11.05.86  1.0.0" 20
VERS�O CORRENTE
.sp

.ip "02.02.87  1.1.0" 20
???

.ip "17.08.88  2.0.0" 20
VERS�O CORRENTE
.sp

.ip "08.11.88  2.0.1" 20
Foram acrescentados os comandos ".bc" e ".ec" que
delimitam um bloco de coment�rios.
Assim, linhas entre um ".bc" e um ".ec" ser�o ignoradas.

.ip "14.05.89  2.2.0" 20
Foi feita pequena altera��o nos comandos ".bc" e ".ec"
para n�o examinar os restos das linhas ap�s os comandos.
Alterado "/src/procarq".

.ip "04.08.89  2.2.1" 20
Foi alterado para aceitar "headers" pares e �mpares
e "footers" pares e �mpares.

.ip "29.08.89  2.2.1" 20
Foi alterado para que, se houver mudan�a de p�gina
no meio de uma tabela que seja "allbox",
sejam usadas duas linhas divis�rias,
uma ap�s a �ltima linha da tabela na p�gina que est� no fim,
e outra antes da primeira linha da tabela na p�gina que continua.
Al�m disso, o n�mero de linhas por p�gina passou
a ser no m�nimo 10.

.ip "04.09.89  2.2.1" 20
Foi acrescentado o comando "title" �s op��es das tabelas.
O argumento deste comando indica a linha de dados
que deve ser usada como t�tulo no in�cio de cada
p�gina em que a tabela continua.

.ip "05.10.89  2.2.1" 20
Foi colocada uma mensagem de erro para o caso
em que o comando "title" � usado em uma tabela
que se encontra dentro de um bloco.
Neste caso o comando "title" n�o funciona.

.ip "25.10.89  2.2.1" 20
Foi acrescentada a op��o "-l" que possibilita
a impress�o de textos formatados pelo sroff
na impressora laser.

.ip "08.11.89  2.3.1" 20
Foi alterado para imprimir caracteres sublinhados
na impressora laser.

.ip "21.11.89  2.3.1" 20
Foi alterado para n�o trocar de p�gina quando
o header ou o footer forem trocados.
A troca de p�gina s� ocorre no momento da cria��o
do primeiro header ou do primeiro footer. 

.ip "23.11.89  2.3.1" 20
Foi alterado para imprimir 6 ou 8 linhas por polegadas
na impressora laser. Para isso foi criado o comando ".ln".

.ip "01.12.89  2.3.1" 20
Foi definido que os par�metros para
a laser ser�o enviados antes da primeira margem.
Sendo assim, ap�s o inicio da entrada do texto,
n�o � conveniente a altera��o do tamanho da p�gina (comando ".pl")
e do n�mero de linhas por p�gina (comando ".ln").

.ip "31.01.90  2.3.2" 20
Foi criado o comando ".it" que � semelhante ao ".ip",
s� que n�o pula linha.

.ip "08.02.90  2.3.2" 20
Foram feitas novas altera��es para a utiliza��o
da impressora laser.

.ip "05.03.90  2.3.2" 20
Foi consertado o problema que havia na utiliza��o
do comando ".sp" dentro de um bloco.

.ip "11.04.90  2.3.2" 20
O comando ".ts" foi alterado, passando a gerar uma quebra da linha corrente. 
Al�m disso, o formato "s" na primeira coluna de uma linha
de formatos e a n�o finaliza��o de um comando de bloco
passaram a ser detectados.

.ip "16.04.90  2.3.2" 20
Foi consertado um erro que havia na coloca��o de tabelas
dentro de blocos.

.ip "07.07.97  3.0.0" 20
Adaptado para o PC

.ip "28.12.04  4.6.7" 20
Alterado o tamanho da pagina para 75 linhas.
