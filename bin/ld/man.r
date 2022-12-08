.bp 1
.he 'LD (cmd)'TROPIX: Manual de Refer�ncia'LD (cmd)'
.fo 'Atualizado em 12.07.02'Vers�o 4.3.0'Pag. %'

.b NOME
.in 5
ld - "link-editor" de m�dulos objeto

.in
.sp
.b SINTAXE
.in 5
ld [-rbsmnvu.] [-o <obj>] [-e <ent>] [-T <tb>] [-D <db>]
.in 45
<mod> ... [-l<x> ...]

.in
.sp
.b DESCRI��O
.in 5
O comando "ld" re�ne diversos m�dulos objeto em apenas um,
efetuando reloca��es e resolvendo s�mbolos externos.

.sp
Dependendo das op��es, "ld" efetua uma das 4 seguintes fun��es:

.in +3
.ip "1. " 3
Gera um m�dulo execut�vel regular:
Neste caso, s�o dados v�rios m�dulos objeto <mod> ..., que
s�o reunidos, gerando um m�dulo objeto execut�vel.
Isto � obtido se N�O for dada nenhuma das op�es "-n", "-r" nem "-b".

.ip "2. " 3
Gera um m�dulo execut�vel reentrante:
Como acima, mas gerando m�dulo objeto execut�vel reentrante,
isto �, durante a execu��o, a sec�o TEXT e a se��es DATA+BSS ficar�o em
regi�es diferentes e o texto ser� protegido contra escritas. 
Isto � obtido com a op��o "-n".

.ip "3. " 3
Gera um m�dulo objeto N�O execut�vel, que pode ser usado como futuras
entradas para "ld".
Isto � obtido com a op��o "-r".

.ip "4. " 3
Gera uma biblioteca compartilhada.
Isto � obtido com a op��o "-b".

.ep
.in -3

.bc	/*************************************/
  ld [-rbsmnvu.] [-o <obj>] [-e <ent>] [-T <tb>] [-D <db>] <m> ... [-l<x> ...]

Op��es:	-r: Mantem a reloca��o, n�o define COMMON
	-b: Gera uma biblioteca compartilhada
	-s: Gera o m�dulo objeto sem tabela de s�mbolos
	-m: Gera um mapa de link-edi��o
	-n: Gera o m�dulo objeto reentrante
	-v: Verboso
	-u: Lista os s�mbolos n�o referenciados
	    Se for dado duas vezes, lista tamb�m os das bibliotecas
	-.: Usa os arquivos tempor�rios no diret�rio corrente
	-o: O nome do m�dulo gerado ser� <obj> ao inv�s de "a.out"
	-e: O nome do s�mbolo de entrada ser� <ent> ao inv�s de "start"
	-T: O endere�o do in�cio da se��o "text" ser� <tb>
	-D: O endere�o do in�cio da se��o "data" ser� <db>

Obs.:	<m> ... s�o m�dulos objeto
	<x> ... s�o abreviaturas para nomes de bibliotecas
.ec	/*************************************/

.bc	/*************************************/
.sp
No caso mais simples, s�o dados v�rios m�dulos objeto <mod> ..., que
s�o reunidos, produzindo um m�dulo objeto que pode ser executado, ou
se foi dada a op��o "-r", ser usado como a entrada de uma execu��o
subseq�ente de "ld".
.ec	/*************************************/

.sp
Normalmente, a sa�da de "ld" � posta no arquivo "a.out", que � um
m�dulo objeto execut�vel, se N�O ocorreu nenhum erro durante a execu��o
de "ld" e N�O foram dadas as op�es "-r" nem "-b".
(veja as op��es "-o", "-r", "-b").

.sp
Cada <mod> dado pode ser o nome de um m�dulo objeto
(veja o formato em  "a.out" (fmt)), o nome de uma biblioteca convencional
de m�dulos objeto (veja "mklib" (cmd) e "lib" (fmt)) ou ainda o nome de
uma biblioteca compartilhada.
Das bibliotecas s�o somente carregados os m�dulos necess�rios para
definir refer�ncias externas ainda n�o resolvidas.

.sp
Os nomes das bibliotecas podem ser dados na sua forma completa
(por ex. "/lib/lib<x>"), ou na sua forma abreviada -l<x>.
O nome -l<x> representa uma das bibliotecas "/lib/lib<x>", "/usr/lib/lib<x>"
ou "/usr/xwin/lib/lib<x>", pesquisadas nesta ordem.
Como exemplo, a biblioteca padr�o de fun��es da linguagem "C" ("libc")
encontra-se no diret�rio "/lib/libc" e pode ser representada abreviadamente
por "-lc", na chamada de "ld".

.sp
As bibliotecas compartilhadas seguem as mesmas conven��es de nomes, por
exemplo "-lt.o" representa "/lib/libt.o".

.sp
Normalmente, o ponto de entrada do m�dulo objeto final
(ou seja, o endere�o inicial de execu��o do programa)
� o s�mbolo "start" (que deve ser global e pertencer � se��o TEXT)
ou se este n�o existir, o endere�o de in�cio da se��o TEXT
(veja a op��o "-e").

.sp
As op��es do comando s�o:

.in +3
.bc	/*************************************/
.ip -a
Normalmente, a tabela de s�mbolos do m�dulo objeto final cont�m apenas
os s�mbolos globais. Com esta op��o, s�o conservados todos os s�mbolos.
.ec	/*************************************/

.ip -r
Mant�m a reloca��o no m�dulo objeto final e n�o define a �rea de COMMON.
O comando n�o emite diagn�sticos sobre s�mbolos ainda n�o definidos,
e o m�dulo objeto de sa�da n�o � execut�vel. 

.sp
O objetivo da op��o � o de realizar uma "link-edi��o" parcial de alguns m�dulos,
gerando um m�dulo objeto intermedi�rio que pode ser usado como
a entrada de uma execu��o subseq�ente de "ld".

.ip -b
Gera uma biblioteca compartilhada.
Esta fun��o � semelhante � op��o "-r", mas define a �rea de COMMON.

.ip -s
Gera o m�dulo objeto final sem a tabela de s�mbolos.
Somente permitido para m�dulos objeto execut�veis.
.bc	/*************************************/
Gera o m�dulo objeto final sem a tabela de s�mbolos nem as
informa��es de depura��o.
.ec	/*************************************/

.ip -m
Gera um mapa de "link-edi��o", contendo os endere�os e tamanhos das
tr�s se��es (TEXT, DATA e BSS) de cada um dos m�dulos carregados.

.ip -n
Gera um m�dulo objeto execut�vel reentrante.

.ip -v
Com esta op��o, s�o dadas informa��es sobre os m�dulos carregados.

.ip -u
Lista os s�mbolos n�o referenciados.
Se for dado apenas uma vez, ser�o listados os s�mbolos n�o
referenciados apenas dos m�dulos dados explicitamente.
Se for dado duas vezes (na forma "-uu") ser�o listados
todos os s�mbolos n�o referenciados, incluindo os das bibliotecas.

.ip -.
Aloca os arquivos tempor�rios no diret�rio corrente.
Isto pode ser �til se o tamanho do dispositivo de "/tmp" for pequeno.

.ip -o
Normalmente, o nome do m�dulo objeto final � "a.out".
Com esta op��o, o nome do m�dulo passa a ser <obj>.

.ip -e
O ponto de entrada do m�dulo objeto final ser� o s�mbolo <ent>,
ao inv�s do s�mbolo "start", ou o endere�o de in�cio da se��o TEXT.
O s�mbolo <ent> deve ser global e pertencer � se��o TEXT.

.ip -T
O endere�o inicial de carga da se��o TEXT do m�dulo-objeto final ser� <tb>.
Se esta op��o for omitida, este endere�o ser� 4 MB.
Se o endere�o dado come�ar por "0x" ou "0X" ele ser� considerado dado em
hexadecimal; se come�ar por "0", em octal;
em caso contr�rio em decimal.

.ip -D
O endere�o inicial de carga da se��o DATA do m�dulo-objeto final ser� <db>.
Se esta op��o for omitida, este endere�o ser� cont�guo ao fim da se��o TEXT,
no caso de programas normais (0407) ou 512 MB
no caso de programas reentrantes (0410).
Se o endere�o dado come�ar por "0x" ou "0X" ele ser� considerado dado em
hexadecimal; se come�ar por "0", em octal;
em caso contr�rio em decimal.

.in +3
.ep

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
mklib, mkshlib
.bc	/*************************************/
mklib, wsdb
.ec	/*************************************/
.br
.wo "(fmt): "
a.out, lib
.br

.in
.sp
.(t
.b ARQUIVOS
.in 5
 /usr/include/a.out.h
.bc	/*************************************/
 /usr/include/lib.h
.ec	/*************************************/
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
