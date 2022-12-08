.bp
.he 'NM (cmd)'TROPIX: Manual de Refer�ncia'NM (cmd)'
.fo 'Atualizado em 08.05.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "nm -"
imprime a tabela de s�mbolos de m�dulos objeto
.br

.in
.sp
.b SINTAXE
.in 5
.(l
nm [-gutdbcarfonepN] [<m�dulo> ...]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "nm" imprime a tabela de s�mbolos de cada <m�dulo> objeto dado.
Se n�o for dado nenhum <m�dulo>, nem a op��o "-N" (ver abaixo), � impressa
a tabela de s�mbolos do m�dulo "a.out".

.sp
Cada <m�dulo> objeto pode ser reloc�vel ou absoluto, e � normalmente obtido
atrav�s do comando "as" ou "ld" (cmd).

.bc	/*************************************/
.sp
Cada s�mbolo vem precedido do seu valor (ou de brancos se for
indefinido), e de uma letra indicando
seu tipo, que pode ser: "U" (indefinido),
"A" (absoluto), "R" (registro do processador),
"C" ("common"), "T" ("text"),
"D" ("data", dados inicializados),
"B" ("bss", dados n�o inicializados) ou "F" (nome do m�dulo).
.ec	/*************************************/

.sp
Cada s�mbolo vem precedido do seu valor em hexadecimal (ou de brancos se for
indefinido), e de uma letra indicando um de seus 8 tipos poss�veis:

.in +8
.ip 'U'
indefinido;

.ip 'T'
se��o TEXT;

.ip 'D'
se��o DATA: dados inicializados;

.ip 'B'
se��o BSS: dados n�o inicializados;

.ip 'C'
se��o COMMON;

.ip 'A'
absoluto;

.ip 'R'
registro do processador;

.ip 'F'
nome de m�dulo.

.ep
.in -8

.sp
Se a s�mbolo for local, o tipo ser� dado pela respectiva letra min�scula.
Para cada um destes tipos de s�mbolos, existe uma op��o
correspondente (ver abaixo). Assim, temos a op��o "-t" para a se��o
TEXT (tipos 't' ou 'T'), op��o "-d" para a se��o DATA, e assim por diante.

.sp
Normalmente, "nm" imprime todos os s�mbolos, e a
sa�da � ordenada em ordem alfab�tica crescente pelo nome do s�mbolo.

.sp
Se n�o for dada nenhuma das 8 op��es referentes aos tipos ("-utdbcarf"),
s�o impressos todos os s�mbolos. Se for dada uma (ou mais) destas op��es
s�o impressos apenas os s�mbolos dos tipos correspondentes.

.sp
O formato da tabela de s�mbolo pode ser controlado pelas seguintes op��es:

.in +3
.ip -g 6
Imprime somente os s�mbolos globais.

.ip -u 6
Imprime os s�mbolos indefinidos.

.ip -t 6
Imprime os s�mbolos da se��o TEXT.

.ip -d 6
Imprime os s�mbolos da se��o DATA.

.ip -b 6
Imprime os s�mbolos da se��o BSS.

.ip -c 6 
Imprime os s�mbolos da se��o COMMON.

.ip -a 6 
Imprime os s�mbolos absolutos.

.ip -r 6 
Imprime os s�mbolos de registros.

.ip -f 6 
Imprime os nomes de m�dulos.

.ip -o 6
Inclue o nome do <m�dulo> em cada linha da sa�da.

.ip -n 6
Ordena numericamente pelo valor do s�mbolo
(e alfabeticamente pelo nome em caso de valores iguais).

.ip -e 6
Ordena na ordem inversa (decrescente).

.ip -p 6
N�o ordena; imprime a tabela na ordem original.

.ip -N 6
Os nomes dos <m�dulo>s s�o lidos da entrada padr�o.

.ep
.in -3

.sp
Se for pedida a ordena��o num�rica ascendente de apenas uma se��o
("text", "data" ou "bss"), ser� inclu�da uma coluna adicional, contendo
o tamanho (em decimal) de cada elemento da tabela de s�mbolos.

.sp
O tamanho do �ltimo s�mbolo � obtido atrav�s de c�lculos
utilizando os tamanhos das se��es (o que nem sempre fornece o
valor correto). 

.sp
Al�m disto, como a tabela de s�mbolos pode estar incompleta (por exemplo,
sem os s�mbolos locais), estes tamanhos podem n�o ser os reais.

.in
.sp
.b OBSERVA��O
.in 5
As tabelas de s�mbolos de m�dulos objeto de bibliotecas
podem ser obtidas dos seguintes modos:
.sp
.nf
		nm /lib/libc/stdio/*.o
	ou
		walk -p "*.o" /lib/libc/stdio | nm -N
.fi

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
mklib, ld, as
.br
.wo "(fmt): "
a.out
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
