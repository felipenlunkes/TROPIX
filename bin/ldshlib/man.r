.bp
.he 'LDSHLIB (cmd)'TROPIX: Manual de Refer�ncia'LDSHLIB (cmd)'
.fo 'Atualizado em 21.06.02'Vers�o 4.3.0'Pag. %'

.b NOME
.in 5
.wo "ldshlib -"
carrega/descarrega uma biblioteca compartilhada
.br

.bc	/*************************************/
ldshlib - carrega/descarrega uma biblioteca compartilhada

Vers�o: 3.2.3, de 14.03.00

Sintaxe:
	ldshlib [-sv] [-u <�ndice>] [<biblioteca>]

Op��es:	-u: Descarrega a biblioteca com o <�ndice> dado
	-s: N�o imprime mensagem de erro caso a biblioteca j� esteja carregada
	-v: Verboso

Obs.:	A biblioteca pode ser dada na forma abreviada "-l..."
.ec	/*************************************/

.in
.sp
.b SINTAXE
.in 5
.(l
ldshlib [-sv] [-u <�ndice>] [<biblioteca>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "ldshlib" gerencia a carga e descarga das bibliotecas compartilhadas.

.sp
Antes que possam ser usadas, as bibliotecas compartilhadas necessitam de ser
carregadas. Como o pr�prio comando "init" (cmd) usado durante o processo de inicializa��o
do sistema j� usa a biblioteca compartilhada "/lib/libt.o", o pr�prio n�cleo
carrega esta biblioteca. Todas as demais biblioteca compartilhadas t�m de ser carregadas
atrav�s do comando "ldshlib".

.sp
Sem op��es nem argumentos, o comando "ldshlib" imprime um mapa das bibliotecas carregadas,
com os seguintes campos:

.in +3
.ip I: 7
�ndice da biblioteca.

.ip NOME: 7
Nome da biblioteca.

.ip DATA: 7
Data da gera��o da biblioteca.

.ip DEP: 7
M�scara de depend�ncias das outras bibliotecas.

.ip HSEQ: 7
Ordem em que os s�mbolos da biblioteca foram introduzidos na tabela HASH.

.ip TEXT: 7
Tamanho da �rea de TEXT da biblioteca.

.ip DATA: 7
Tamanho da �rea de DATA da biblioteca.

.ip BSS: 7
Tamanho da �rea de BSS da biblioteca.

.ip SYMTB: 7
Tamanho da tabela de s�mbolos da biblioteca.

.ip NSYM: 7
N�mero de s�mbolos na tabela de s�mbolos da biblioteca.

.ip NTENT: 7
N�mero de tentativas (m�dia) para encontrar um s�mbolo da biblioteca na tabela HASH.

.ep
.in -3

.sp 2
Se for dado o nome de uma <biblioteca>, ela ser� carregada.
O nome da <biblioteca> pode ser dado em sua forma completa (por exemplo "/usr/xwin/lib/libx.o"),
ou abreviada ("-lx.o"), conforme as conven��es dadas em "ld" (cmd).

.sp
As op��es do comando s�o:

.in +3
.ip -u
Descarrega a biblioteca com o <�ndice> dado. Este �ndice pode ser obtido atrav�s do mapa
das bibliotecas carregadas.

.ip -s
N�o imprime uma mensagem de erro caso a biblioteca j� esteja carregada.

.ip -v
Subsitui, no mapa das bibliotecas carregadas, os dois �ltimos campos (NSYM e NTENT)
pelos endere�os virtuais das �reas de TEXT e DATA.

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
init, ld, mkshlib
.br

.in
.sp
.b ARQUIVOS
.in 5
/lib/libt.o
 /usr/xwin/lib/libx.o
 /usr/xwin/lib/liby.o

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
