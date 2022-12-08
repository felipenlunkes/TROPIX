.bp 1
.he 'CPP (cmd)'TROPIX: Manual de Refer�ncia'CPP (cmd)'
.fo 'Atualizado em 24.08.01'Vers�o 4.1.0'Pag. %'

.b NOME
.in 5
cpp - pr�processador para fontes em "C"

.in
.sp
.b SINTAXE
.in 5
/lib/cpp [-PCTv] [-D <def> ...] [-U <id> ...] [-I <dir> ...]
.nf
					 <entrada> [<sa�da>]
.fi

.in
.sp
.b DESCRI��O
.in 5
O comando "cpp" � o pr�processador para programas fontes na linguagem
"C" do TROPIX.
Usualmente, ele � invocado automaticamente
atrav�s do comando "cc" (cmd), 
como o primeiro passo de uma compila��o.
O comando tamb�m pode ser utilizado separadamente, mas neste caso,
deve-se levar em conta o formato do arquivo de sa�da.

.sp
O argumento <entrada> � o nome do arquivo de onde o comando ir� obter
a entrada.
Se o segundo argumento <sa�da> for fornecido, ele ser� utilizado como
nome do arquivo de sa�da; em caso contr�rio, a sa�da ser� posta na sa�da padr�o.

.sp
Os diret�rios impl�citos de busca dos arquivos "#include" s�o:
"/usr/include", "/usr/xwin/include" e "/usr/xwin/include/X11" (veja a op��o "-I").

.sp
Nesta vers�o do sistema, foi removido o limite do tamanho dos identificadores,
isto �, os nomes das macros, vari�veis, ... podem ter tamanhos arbitr�rios.

.sp
As op��es do comando s�o:

.in +3
.ip -P 10
Normalmente, o pr�processador gera uma s�rie de informa��es de controle,
que s�o esperadas pelo compilador "C"
para acompanhar a origem de cada linha do programa fonte.
Com esta op��o, esta informa��o n�o � gerada.

.ip -C 10
Normalmente, o pr�processador suprime todos os coment�rios
(no estilo da linguagem "C") na sa�da.
Com esta op��o, os coment�rios s�o inclu�dos na sa�da.

.ip -T 10
Emite mais diagn�sticos.

.ip -v 10
Verboso. Ao final do pr�processamento, imprime uma tabela com
as macros definidas.

.ip '-D <def>' 10
Pr�define macros;
<def> � uma defini��o de macro do tipo "identificador" ou
"identificador=valor"
(no primeiro caso, a macro � definida com valor "1").

.sp
A op��o "-D" tem preced�ncia mais alta do que as defini��es de
macros atrav�s de "pragma getenv" (ver abaixo), isto �, se a mesma macro for
definida dos dois modos, a que prevalece � a dada pela op��o "-D".

.ip '-U <id>' 10
N�o permite macros com o nome <id>.
Mesmo que hajam defini��es da macro <id>
no decorrer do texto, elas s�o ignoradas.

.ip '-I <dir>' 10
Acrescenta <dir> � lista de diret�rios de busca de arquivos "#include"
cujos nomes n�o come�am por "/".

.sp
Arquivos "#include" cujos nomes est�o cercados por "" s�o 
procurados em primeiro lugar no diret�rio do arquivo que cont�m
a diretiva "#include", em seguida nos diret�rios dados pelas
op��es "-I" e finalmente nos diret�rios impl�citos (veja acima).

.sp
Para arquivos "#include" cujos nomes est�o cercados por <>, a
busca � an�loga, exceto que o diret�rio do arquivo que cont�m
a diretiva "#include" n�o � consultada.

.ep
.in -3

.sp 2
A diretiva "#pragma" reconhecida nesta vers�o de "cpp" � apenas o "getenv".
Atrav�s desta diretiva podemos definir vari�veis do ambiente como macros
(ver ("environ" (fmt)).
Ela pode ser usado em duas formas:
.sp
.nf
		#pragma getenv (<id1>, <id2>, ...)
.fi
.sp
em que s�o definidas as vari�veis <id1>, <id2>, ... e
.sp
.nf
		#pragma getenv
.fi
.sp
em que todas as vari�veis do ambiente s�o definidas como macros.

.sp
.in
.b
DIAGN�STICOS
.r
.in 5
As incorre��es s�o classificadas em "erros" e "advert�ncias".
Para cada incorre��o � impressa a linha, com um ponteiro
indicando o local prov�vel da incorre��o, seguida de uma
mensagem explicativa.
Para alguns tipos de incorre��es s�o impressos apenas o n�mero da linha
e nome do arquivo ao inv�s da linha propriamente dita. 

.sp
.in
.b
VEJA TAMB�M
.r
.nf
     (cmd): cc
     (fmt): environ
.fi

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
