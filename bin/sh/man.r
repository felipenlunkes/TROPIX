.bp
.he 'SH (cmd)'TROPIX: Manual de Refer�ncia'SH (cmd)'
.fo 'Atualizado em 24.03.04'Vers�o 4.5.0'Pag. %'

.b NOME
.in 5
sh - interpretador de comandos program�vel
.br

.in
.sp
.b SINTAXE
.in 5
sh [-c <comando>] [-derv] [<arg> ...]

.in
.sp
.b DESCRI��O
.in 5
O utilit�rio "sh" � um interpretador de comandos program�vel que
executa comandos lidos de um terminal ou arquivo.
Os comandos devem ser dados em uma linguagem pr�pria, que � descrita abaixo.

.sp
As op��es s�o:

.in +3 
.ip "-c" 5
Executa o <comando> dado como argumento e encerra.

.ip "-d" 5
Aceita tamb�m <^D> para terminar o "sh". Normalmente, para
terminar a execu��o, devem ser usados os comandos internos
"exit", "login" ou "logout".

.ip "-e" 5
Termina a execu��o do "sh" imediatamente, se um comando retornar n�o-zero.

.ip "-r" 5
Verifica a reescrita de arquivos no redirecionamento.

.ip "-v" 5
Lista cada linha de comandos lida do arquivo de entrada.

.ep
.in -3 

.in
.sp 2
.b "DESCRI��O DA LINGUAGEM"
.in 5

.in
.sp
.in 2
.b Defini��es
.in 5
.sp
Um "branco" � um <sp> ou um <ht>. Uma "palavra" � uma seq��ncia de
caracteres que n�o incluem brancos.
Um "nome" � uma seq��ncia de letras, d�gitos, ou "sublinhado"s ("_")
iniciada por uma letra ou "sublinhado".
Um "par�metro" � um nome, um d�gito,
ou um dos caracteres "*", "@", "#", "?", "-", "$", "!", ":" e "\%".

.in
.sp
.in 2
.b Comandos
.in 5
.sp
Um "comando-simples" � uma seq��ncia de palavras separadas por brancos.
A primeira palavra especifica o nome do comando a ser executado.
Salvo exce��es (que ser�o vistas abaixo), as palavras restantes s�o
passadas como argumentos ao comando invocado.
O nome do comando � passado como argumento de n�mero 0 (veja "exec" (sys)).

.sp
Se um comando-simples terminar normalmente, o seu "valor de retorno"
� dado pelo argumento fornecido � chamada "exit" (sys).
Caso contr�rio, o seu "valor de retorno" � dado por 0x80 + c�digo de retorno
(veja "wait" e "signal" (sys) para uma lista dos c�digos de retorno).

.sp
Uma "linha de canais" ("pipeline") � uma seq��ncia de dois ou mais comandos
separados por "|".
Um "pipeline" � constru�do conectando-se a sa�da padr�o de cada comando
(com a exce��o do �ltimo), � entrada padr�o do comando seguinte
atrav�s da chamada ao sistema "pipe" (sys).

Cada comando � executado como um processo independente;
"sh" espera pelo t�rmino do �ltimo comando.
O valor de retorno de um "pipeline" � o valor de retorno do �ltimo comando.

.sp
Uma "lista de pipelines" (ou simplesmente uma "lista")
� uma seq��ncia de um ou mais "pipeline"s separados por ";", "&", "&&" ou "||"
e, opcionalmente, terminado por ";" ou "&".

Destes quatro s�mbolos, ";" e "&" t�m a mesma preced�ncia,
que � menor do que as preced�ncias de "&&" e "||".
Os s�mbolos "&&" e "||" tamb�m t�m a mesma preced�ncia.

.sp
Um ponto e v�rgula (";") causa a execu��o seq�encial do "pipeline"
precedente; um "e comercial" ("&") provoca uma execu��o ass�ncrona do
"pipeline" precedente (isto �, "sh" n�o espera pelo t�rmino daquele "pipeline").

.sp
O s�mbolo "&&" ("||") faz com que a lista que o
segue seja executada apenas se o "pipeline" anterior tiver
um valor de retorno igual a zero (diferente de zero).
Um n�mero arbitr�rio de <nl> pode aparecer em
uma lista, ao inv�s de ponto e v�rgulas, para delimitar comandos.

.sp
Um "comando" � uma lista, um "comando-interno" ou
um dos comandos-de-programa��o descritos adiante
(veja "comandos internos" e "comandos de programa��o", abaixo).
A menos que seja estabelecido de outro modo, o valor de retorno de
um comando � aquele do �ltimo comando-simples executado.

.sp
.in 2
.b
Comandos-de-Programa��o
.r
.in 5

.sp
for <nome> [in <palavra> ...] do <lista> done
.br

.in +8
.sp
Este comando executa a <lista> para cada <palavra> dada.
Em cada execu��o, <nome> recebe o valor da <palavra> seguinte.

.bc	/*************************************/
atribuindo <nome> com o valor da respectiva <palavra>. 
.ec	/*************************************/

Se a parte "in <palavra> ..." for omitida, a <lista> ser� executada
para cada "par�metro posicional" definido
(veja "substitui��o de par�metros", abaixo).

.in -8
.sp
.(l
case <palavra> in
    [<padr�o> [|<padr�o>] ...) <lista> ;;] ...
esac
.)l
.in +8
.br

.sp
O comando "case" executa a <lista> associada ao primeiro <padr�o> que
seja aceito (tenha correspond�ncia) com a <palavra> dada.
A forma dos <padr�es> � a mesma que � usada para a gera��o de nomes de arquivos
(veja "gera��o de nomes de arquivos"),
exceto que uma barra ("/'), um ponto (".") inicial,
ou um ponto imediatamente ap�s
uma barra n�o precisam ser aceitos explicitamente.

.in -8
.sp
.(l
if <lista> then <lista>
    [ elif <lista> then <lista> ] ...
    [ else <lista> ]
fi
.)l
.br

.in +8
A <lista> ap�s o "if" � executada,
e caso tenha um valor de retorno igual a zero,
� executada a <lista> ap�s o "then".
Em caso contr�rio, a <lista> ap�s o "elif" (se dada) � executada,
e caso tenha um valor de retorno igual a zero,
� executada a <lista> ap�s o "then" seguinte.
Falhando todos os "elif"s, � executada a <lista>
ap�s o "else" (se dada).
Caso n�o seja executada nenhuma <lista> de "else" ou "then",
o comando termina com um valor de retorno diferente de zero.

.in -8
.sp
.(t
while <lista> do <lista> done
.sp
until <lista> do <lista> done
.br

.sp
.in +8
O comando "while" executa repetidamente a primeira e a segunda <lista>.
Se o valor de retorno do �ltimo comando da primeira <lista> for
diferente de zero, a segunda <lista> n�o � executada e a malha termina.
Se nenhum comando da segunda <lista> for executado, o comando
"while" termina com o valor de retorno igual a zero.
A palavra chave "until" pode ser utilizado ao inv�s de "while"
para negar o teste de t�rmino de repeti��o.
.)t
.in -8

.sp
( <lista> )
.sp
.in +8
Cria um processo filho "sh" para executar a <lista>. 
.in -8

.sp
{ <lista>; }
.in +8
.sp
Executa a <lista> neste "sh".
.in -8

.sp
As seguintes palavras s�o sempre consideradas reservadas:
.sp
.(l
    if then else elif fi case esac for while until do done { }
.)l

.sp
Se, em algum momento, for necess�rio utiliz�-las de outro
modo, elas devem ser inclu�das entre aspas ou ap�strofos.

.in
.sp
.in 2
.b Coment�rios
.in 5
.sp
Todos os caracteres ap�s o "#" at� o primeiro <nl> posterior s�o ignorados.

.in
.sp
.in 2
.b
Substitui��o de Comandos
.r
.in 5
.sp
O comando "sh" l� comandos de uma cadeia de caracteres entre dois acentos
graves (`...`), executa estes comandos, e a sua sa�da padr�o
pode ser usada como parte integral ou parcial de uma palavra.
Os caracteres <nl> da sa�da padr�o s�o removidos.

.sp
Um comando �til para a utiliza��o com os acentos graves � o "from",
como no exemplo abaixo:

.sp
.nf
	for i in `from 1 to 10`
	do
		echo $i
	done
.fi

.sp
em que o comando "echo" � executado 10 vezes, com os valores consecutivos
de "1" a "10" para a vari�vel "i".

.sp
N�o � realizada qualquer interpreta��o dos caracteres da cadeia
lida, exceto para a remo��o de barras invertidas ("\"), usadas para
desabilitar o significado especial de caracteres. Uma barra invertida ("\")
pode ser usada para desabilitar o significado especial de um acento
grave ou outra barra invertida ("\") e � removida antes que a cadeia
de caracteres seja lida.
Se a substitui��o de comandos encontra-se entre um par de aspas
.wo '(" ... ` ... ` ... "),'
ent�o uma barra invertida usada para desabilitar o significado especial
de uma aspas ser� removida; em outros casos ela ser� mantida intacta.


.bc	/*************************************/
A desabilita��o do significado especial de
acentos graves permite o aninhamento de substitui��es de comandos.
.ec	/*************************************/


.sp
Se uma barra invertida ("\") � usada para anular o significado especial
de um <nl>, tanto a barra invertida quanto o <nl> ser�o
removidos (veja a se��o posterior sobre "mecanismos de quota��o").
Al�m disto, barras invertidas usadas para anular o significado do
sinal de dollar ("$") s�o removidos. J� que n�o � realizada nenhuma
interpreta��o na cadeia de caracteres do comando antes que ele
seja lido, a inser��o de uma barra invertida antes de um sinal de
dollar n�o tem efeito. Barras invertidas que precedam caracteres
outros que "\", "`", '"', <nl> e "$" s�o mantidos intactos quando
� lida a cadeia de caracteres do comando.

.in
.sp
.in 2
.b
Substitui��o de Par�metros
.r
.in 5
.sp
O caractere '$' � usado para introduzir par�metros substitu�veis.
Temos dois tipos de par�metros: posicionais e de palavras-chaves.
Se um par�metro � um d�gito, ele � um par�metro posicional.
Podemos atribuir valores aos par�metros posicionais com o comando
"set".
Atribuimos valores a par�metros de palavras-chaves (tamb�m chamadas
de vari�veis) escrevendo:

.sp
.in +5
    <nome>=<valor> [<nome>=<valor> ...]
.in -5

.sp
A expans�o de nomes n�o � realizada em <valor>.
.bc	/*************************************/
N�O podemos ter uma fun��o e uma vari�vel com o mesmo nome.
.ec	/*************************************/

.ip "${<par�metro>}" 16
O valor, se algum, do <par�metro> � substitu�do.
As chaves s� s�o necess�rias se o nome do <par�metro>
for seguido por uma letra, d�gito, ou "sublinhado" ('_'),
que n�o deve ser interpretado como parte do nome.

.ep

.sp
Os seguintes par�metros t�m seus valores automaticamente
atribu�dos pelo comando "sh":

.in +3
.ip "#" 3
O n�mero de par�metros posicionais (em decimal).

.ip "-" 3
Op��es dadas ao comando "sh" ou dadas atrav�s do comando "set".

.ip "?" 3
O valor de retorno em decimal retornado pelo �ltimo comando
executado sincronamente.

.ip "$" 3
A identifi�a��o do processo (PID) deste "sh".

.ip "!" 3
A identifi�a��o do processo (PID) do �ltimo comando em "background" executado.

.ip ":" 3
O n�mero do pr�ximo comando a entrar no hist�rico (veja "hist�rico", abaixo).

.ip "@" 3
Os par�metros posicionais (veja adiante) � exce��o de $0.

.ip "*" 3
Uma cadeia com os par�metros posicionais � exce��o de $0.

.ip "\%" 3
Uma cadeia com o nome do n� (nome do pr�prio computador na rede).

.ip "~" 3
O nome do diret�rio corrente.

.ip "&" 3
O caractere "#" se o usu�rio for um superusu�rio, e "$" em caso contr�rio.

.in -3
.ep

.sp
.(t
Os seguintes par�metros s�o utilizados pelo comando "sh":

.in +3
.ip "HOME" 6
O diret�rio "home", o argumento assumido por omiss�o para o comando "cd".
O caractere '~' � equivalente a $HOME, quando ocorre em caminhos.
.)t

.ip "PATH" 6
Os caminhos de busca para os comandos (veja execu��o abaixo).

.ip "PS1" 6
A cadeia de caracteres com o "prompt", normalmente "$ ".

.ip "PS2" 6
A cadeia de caracteres com o "prompt" secund�rio, normalmente "> ".

.bc	/*************************************/
.ip "IFS" 6
Separadores de campos utilizados pelo comando "sh",
normalmente  <sp>, <ht> e <nl>.
.ec	/*************************************/

.in -3
.ep

.sp
A 
O comando "sh" atribui os valores iniciais para as vari�veis
"PATH", "PS1" e "PS2".
O valor inicial de "HOME" � atribu�do pelo comando "login".

.in
.sp
.in 2
.(t
.b
Interpreta��o de brancos
.r
.in 5
.sp

Ap�s a substitui��o de par�metros e de comandos, o resultado da substitui��o
� examinado � procura de caracteres separadores de campos
e separado em argumentos distintos
onde estes s�o encontrados.
Argumentos explicitamente nulos ("" ou '') s�o mantidos.
Argumentos nulos impl�citos (aqueles decorrentes de par�metros sem valor)
s�o removidos.
.)t

.in
.sp
.in 2
.b
Redirecionamento de Entrada e Sa�da
.r
.in 5
.sp
As entradas e sa�das de um comando podem ser redirecionadas
usando uma nota��o especial interpretada pelo comando "sh".
As constru��es apresentadas a seguir
podem aparecer em qualquer lugar de um comando-simples,
e n�o s�o passados como argumentos ao comando invocado.
Note que a substitui��o de comandos e par�metros � realizada
antes que <nome> ou <d�gito> seja usado.

.in +3
.ip "< <nome>" 12
Usa o arquivo <nome> como a entrada padr�o
(relativo ao descritor de arquivos 0).

.ip "> <nome>" 12
Usa o arquivo <nome> como a sa�da padr�o
(relativo ao descritor de arquivos 1).
Se o arquivo n�o existe ele � criado; em caso contr�rio � truncado.

.ip ">> <nome>" 12
Usa o arquivo <nome> como sa�da padr�o.
Se o arquivo j� existe a sa�da � adicionada ao seu final;
em caso contr�rio o arquivo � criado.

.ip "<< <nome>" 12
Ap�s a substitui��o de par�metros e de comandos ser realizada em <nome>,
a entrada do comando "sh" � lida at� a primeira linha que corresponda
literalmente ao <nome> resultante, ou at� um fim de arquivo.

.ip "< &<d�gito>" 12
Usa o arquivo associado ao descritor de arquivos dado pelo <d�gito>
como a entrada padr�o.

.ip "> &<d�gito>" 12
Usa o arquivo associado ao descritor de arquivos dado pelo <d�gito>
como a sa�da padr�o.

.ip "<&-" 12
Fecha a entrada padr�o.

.ip ">&-" 12
Fecha a sa�da padr�o.

.in -3
.ep

.sp
Se qualquer uma das cadeias acima for precedida por um d�gito,
o descritor de arquivos que ser� associado ao arquivo � aquele
dado pelo d�gito (ao inv�s dos valores 0 ou 1 assumidos por omiss�o).
Por exemplo:

.sp
.in +8
 ... 2>&1
.in -8

.sp
associa o descritor de arquivos 2 ao arquivo correntemente associado
com o descritor de arquivos 1.

.sp
A ordem em que s�o dadas as redire��es � significante;
o comando "sh" avalia as redire��es da esquerda para direita.
Por exemplo:

.sp
.in +8
 ... 1> <arquivo> 2>&1
.in -8
.sp

em primeiro lugar associa o descritor de arquivos 1 ao <arquivo>;
em seguida associa o descritor de arquivos 2 ao arquivo associado
ao descritor de arquivos 1 (isto � <arquivo>).

.sp
Se a ordem de redire��es fosse a reversa, o descritor de arquivos 2
seria associado ao terminal/v�deo (assumindo que o descritor de arquivos
1 o tinha sido) e em seguida, o descritor de arquivos 1 seria associado
ao <arquivo>.

.sp
Usando a terminologia introduzida na primeira p�gina, em "comandos",
se um comando � composto de v�rios comandos-simples, as redire��es
s�o avaliadas para o comando como um todo, antes que sejam avaliadas
para cada comando-simples.
Em outras palavras, o comando "sh" avalia os redirecionamentos
para a lista inteira, em seguida para cada "pipeline" dentro da lista e
finalmente para cada lista dentro de cada comando.

.sp
Se um comando � seguido por "&", a entrada padr�o para o
comando ser� o arquivo vazio "/dev/null".
Em caso contr�rio, o ambiente para a execu��o de um comando
cont�m os descritores de arquivos do comando "sh"
que o invocou, segundo as modifica��es dadas pelas
especifica��es de entrada e sa�da.

.in
.sp
.in 2
.b
Gera��o de Nomes de Arquivos
.r
.in 5
.sp
Antes que um comando seja executado, cada palavra do comando �
examinada � procura dos caracteres "*", "?", "!" e "[".
Se algum destes caracteres estiver presente, a palavra � considerada
um padr�o.
A palavra � substitu�da pela lista ordenada alfabeticamente
de nomes de arquivos que correspondem ao padr�o dado. Se n�o for
encontrado nomes de arquivos que correspondam ao padr�o, o comando
"sh" indica o erro. O caractere "." no in�cio de um nome de arquivo
ou imediatamente ap�s uma barra ("/"), assim como o caractere barra
devem corresponder explicitamente ao padr�o.

.in +3
.ip ? 8
Corresponde a (um) caractere qualquer.

.ip * 8
Corresponde a zero ou mais caracteres quaisquer.

.ip !c 8
Corresponde a qualquer caractere diferente de "c".

.ip [...] 8
Corresponde a um caractere igual a um dos caracteres entre os colchetes.
Podemos tamb�m ter constru��es do tipo "x-y"
entre os colchetes,
que representa todos os caracteres de "x" a "y" (inclusive). 

.ip ![....] 8
Corresponde a um caractere que deve ser diferente de todos os caracteres
entre os colchetes. Assim como acima, "x-y" representa todos os
caracteres de "x" a "y".

.ip \c 8
Corresponde ao caractere "c". Esta constru��o � �til para desfazer
o efeito especial dos meta-caracteres.

.in +3
.ep

.bc	/*************************************/
.sp
.in +5

.ip "*" 8
Corresponde a qualquer cadeia de caracteres, inclusive a cadeia nula.

.ip "?" 8
Corresponde a qualquer (�nico) caractere.

.ip "[...]" 8
Corresponde a qualquer um dos caracteres entre os colchetes.
Um par de caracteres separados por "-" corresponde a qualquer
caractere lexicamente entre o par (incluindo o primeiro o �ltimo).
Se o primeiro caractere ap�s o abre colchete for um "!" qualquer caractere
n�o especificado entre os colchetes � correspondido.

.ip "!" 8
Corresponde a qualquer caractere a exce��o do caractere especificado
ap�s.
.ep
.in -5
.ec	/*************************************/

.in
.sp
.in 2
.b
Mecanismos de Quota��o
.r
.in 5

.sp
Os seguinte caracteres t�m um significado especial para o comando "sh"
e causam o fim de uma palavra a menos que estejam quotados:
.sp
.in +5
.b
;  &  (  )  |  <  >  <nl>  <sp>  <ht>
.r
.in -5

.sp
Um caractere pode ser "quotado"
(isto �, fazer com que perca o seu significado especial)
precedendo-o por uma barra invertida ("\") ou inserindo-o entre um par de
marcas de quota��o ('' ou "").
Durante o processamento, o comando "sh" pode quotar alguns caracteres
para evitar que eles tenham um significado especial.
Barras invertidas usadas para quotar um caractere s�o removidas
da palavra antes que o comando seja executado.
O par "\<nl>" � removido antes da substitui��o de comandos e par�metros.

.sp
Todos os caracteres entre um par de acentos agudos (''), exceto
um acento agudo, s�o quotados pelo comando "sh".
Uma barra invertida n�o tem um significado especial dentro de um
par de acentos agudos.
Um acento agudo pode ser quotado dentro de um par de
aspas (por exemplo "'").

.sp
Dentro de um par de aspas (""), � realizada a substitui��o de
par�metros e comandos, mas sobre o resultado o comando "sh"
n�o faz interpreta��o de brancos, nem gera��o de nomes de arquivos.
Se "$*" est� entre um par de aspas ("$*"), os par�metros
posicionais s�o substitu�dos e formam uma �nica palavra,
considerada como quotada, com um espa�o entre cada par de
par�metros ("$1 $2 $3 ...").
No entanto, se "$@" estiver entre um par de aspas ("$@"),
os par�metros posicionais s�o
substitu�dos e quotados separados por espa�os
("$1" "$2" "$3" ...).
Uma barra invertida ("\") retira
o significado especial dos caracteres "\", "'", '"' e "$".
O par "\<nl>" � removido antes da substitu���o de par�metros
e comandos.
Se a barra invertida precede caracteres diferentes de "\", "'", '"' e "$",
ela pr�pria � quotada pelo comando "sh".

.in
.sp
.in 2
.(t
.b '"Prompt"'
.in 5

.sp
Quando usado interativamente, o comando "sh" mostra o "prompt" dado
pelo valor da vari�vel "PS1", antes de ler o comando.
Se a qualquer tempo um <nl> for teclado e for
necess�ria mais entrada para completar o comando, o "prompt"
secund�rio (isto �, o valor de "PS2") � exibido.
.)t

.in
.sp
.in 2
.b Ambiente
.in 5

.sp
O ambiente (veja environ (fmt)) � uma lista de pares (<nome>, <valor>)
que � passada a um programa executado, do mesmo modo que a lista de
argumentos.
O comando "sh" interage com o ambiente de v�rios modos.
Na sua invoca��o, o comando "sh" examina o ambiente,
e cria uma vari�vel para cada <nome> encontrado,
associando-a ao <valor> respectivo.
Se o usu�rio modificar o <valor> de qualquer dessas vari�veis ou
criar novas vari�veis, nenhuma destas afeta o ambiente a menos
que o comando "export" seja utilizado para direcionar a vari�vel
do comando "sh" para o ambiente (veja tamb�m "set -a").
Uma vari�vel pode ser removida do ambiente atrav�s do comando "unset".
O ambiente recebido por qualquer comando executado � ent�o composto dos
pares (<nome>, <valor>) n�o modificados, originalmente herdado pelo
comando "sh", menos os pares removidos pelo comando "unset",
mais quaisquer modifica��es ou adi��es,
realizadas atrav�s do comando "export".

.bc	/*************************************/
.sp
O ambiente para qualquer comando-simples pode ser acrescido
prefixando por uma ou mais atribui��es a vari�veis. Logo:
.sp
.in +5
$ TERM=450 cmd
.wo "                         e"
.br
$ (export TERM; TERM=450; cmd)
.in -5
.sp
s�o equivalentes no que concerne a excecu��o de "cmd".

.sp
Se a op��o "-k" est� ativa, todas as vari�veis s�o colocadas no
ambiente dos comandos, mesmo que elas ocorram ap�s o nome do comando.
Por exemplo:
.sp
.in +5
$ echo a=b c
.br
$ set -k
.br
$ echo a=b c
.sp
mostra "a=b c" e ent�o "c".
.ec	/*************************************/

.in
.sp
.in 2
.b Sinais
.in 5

.sp
Os sinais SIGINT e SIGQUIT (veja "signal" (sys))
para um comando executado s�o ignorados
se o comando for seguido de um "&";
os demais sinais t�m seus valores herdados pela
comando "sh" do seu pai, com a exce��o do sinal SIGBUS
(veja o comando "trap" abaixo).

.in
.sp
.in 2
.b Execu��o
.in 5

.sp
Para cada comando executado, s�o efetuadas as substitui��es dadas acima.
Se o nome do comando corresponde a um dos comandos-internos
dados abaixo, ele � executado no processo do pr�prio comando "sh"
(ao inv�s de criar um comando "sh" filho).

.bc	/*************************************/
Se o nome do comando n�o corresponde ao nome de um comando-interno nem
o nome de uma fun��o definida, um novo processo � criado
e uma tentativa � efetuada para executar o comando via exec (sys).
.ec	/*************************************/

.sp
A vari�vel "PATH" do comando "sh" define os caminhos
dos diret�rios onde os comandos ser�o procurados.
Os nomes dos diversos diret�rios devem vir separados por dois-pontos (":").
O "PATH" padr�o � ".:/bin:/usr/bin:/etc" (especificando o diret�rio
corrente ".", "/bin", "/usr/bin" e "/etc", nesta ordem).

.sp
Se o nome do comando come�ar por "/", trata-se de um nome absoluto,
e a vari�vel "PATH" n�o � utilizada.
Em caso contr�rio, cada diret�rio dado em "PATH" � examinado � procura
de um arquivo execut�vel com o nome do comando.
Se o arquivo tem permiss�o de execu��o,
mas n�o � um arquivo com o formato "a.out"
(veja o arquivo "/usr/include/a.out.h"),
assume-se que seja um arquivo contendo comandos para o "sh",
ou seja, um procedimento de comando "sh".
Neste caso, um "sh" filho � criado para process�-lo.
Um comando entre par�nteses tamb�m � executado por um comando "sh" filho.

.sp
Por quest�o de efici�ncia, o "sh" mant�m internamente uma tabela HASH
contendo os nomes de todos os arquivos execut�veis encontrados nos diret�rios
especificados no conte�do da vari�vel PATH. Assim, se um destes diret�rios
for modificado atrav�s da inclus�o ou exclus�o de algum
execut�vel, o comando "rehash" deve ser utilizado, a fim de manter
atualizada a estrutura de dados interna do "sh".

.in
.sp
.in 2
.b
Hist�rico
.r
.in 5
.br
O comando "sh" armazena em um "hist�rico", um certo n�mero
dos �ltimos comandos executados.
Com isto, � poss�vel re-executar comandos executados anteriormente,
inclusive com altera��es.
Os comandos internos que gerenciam o h�st�rico s�o "h", "eh" e "xh"
(veja abaixo).
O n�mero de comandos armazenados no hist�rico � dado pela vari�vel
"HIST".

.in
.sp
.in 2
.b
Comandos Internos
.r
.in 5
.br

.sp
Os comandos internos s�o executados pela "shell" sem a cria��o de um
subprocesso.
O redirecionamento de entrada/sa�da tamb�m � permitido para os
comandos-internos.

.sp
.in +3
.ip ":"
.sp
Sem efeito; este comando nada faz.
Produz um valor de retorno igual a zero.

.ip ". <arquivo>"
.sp
L� e executa os comandos do <arquivo> e retorna.
Os caminhos de busca especificados em "PATH" s�o utilizados
para achar o diret�rio contendo <arquivo>.

.ip "cd [<dir>]"
.sp
Troca o diret�rio corrente para "<dir>".
Se <dir> n�o for dado, troca o diret�rio corrente para o valor
da vari�vel "HOME".

.ip "eh [<num> ...]"
.sp
Permite a edi��o do comando <num> do hist�rico.
Se forem dados mais de um <num>, permite a jun��o, edi��o e execu��o
de v�rios comandos do hist�rico.
Se <num> n�o for especificado, edita o �ltimo comando do hist�rico.
Os comandos de edi��o s�o os do editor visual "ex" (cmd) que fazem
sentido para a edi��o de uma �nica linha.
Os comandos do editor e a edi��o terminam respectivamente por <esc> ou "q".

.ip "eval [<arg> ...]"
.sp
Os argumentos s�o lidos como entrada para o comando "sh"
e os comandos resultantes executados.

.ip "exec [<arg> ...]"
.sp
O comando especificado pelos <arg>s � executado no lugar
deste comando "sh", sem que seja criado um novo processo.
Podem ser dados redirecionamentos de entrada e sa�da,
e se nenhum outro <arg> for dado,
causa a modifica��o da entrada/sa�da do comando "sh".

.ip "exit [<n>]"
.sp
Termina a execu��o do presente comando "sh",
com o valor de retorno <n>.
Se <n> for omitido, o valor de retorno � o do �ltimo comando executado.
De acordo com a op��o "-d", um fim de arquivo (normalmente <^D>) tamb�m
pode terminar o "sh" (veja o comando-interno "set").

.ip "export [<nome> ...]"
.sp
Os <nome>s dados s�o marcados para a exporta��o autom�tica para
o ambiente dos comandos executados posteriormente.
Se n�o forem dados argumentos, s�o listados os <nome>s das vari�veis
que s�o export�veis.

.ip "false"
.sp
Produz um valor de retorno diferente de zero
(para ser usado em conjunto com os comandos-de-programa��o).

.ip "gh"
.sp
O hist�rico �  mostrado na tela e o usu�rio poder� selecionar o
comando desejado atrav�s das setas. Escolhido o comando, tr�s op��es s�o
poss�veis: <enter> para executar o comando, "e" para editar o comando ou
"q" para desistir.

.ip "h"
.sp
Mostra o hist�rico com os �ltimos $HIST comandos executados.

.ip "login"
.sp
Termina a sess�o corrente do comando "sh" (veja o comando-interno "exit").

.(t
.ip "read [<nome> ...]"
.sp
Uma linha � lida da entrada padr�o e, usando os separadores
de campo internos (<sp> ou <ht>), para
delimitar as fronteiras entre as palavras, a primeira palavra
� atribu�da ao primeiro <nome>, a segunda palavra ao segundo <nome>,
e assim sucessivamente.
As palavras que sobrarem s�o todas atribu�das ao �ltimo <nome>.
Qualquer caractere pode ser quotado precedendo-o por barra invertida
("\"), inclusive <nl>. O valor de retorno � zero, a menos que
seja encontrado um fim de arquivo.
.)t

.ip "readonly [<nome> ...]"
.sp
Os <nome>s dados s�o considerados como vari�veis apenas para a leitura,
e os seus valores n�o podem ser alterados por atribui��es posteriores.
Se nenhum argumento for dado, � impressa uma lista de
todas as vari�veis "readonly".

.ip "set [-derv] [<arg> ...]"

.sp
Altera alguns indicadores do "sh":

.in +7
.ip "-d" 4
Aceita tamb�m <^D> para terminar o "sh". Normalmente, para
terminar a execu��o do presente "sh", deve-se usar os comandos-internos
"exit", "login" ou "logout.

.ip "-e" 4
Termina a execu��o do "sh" imediatamente, se um comando retornar n�o-zero.

.ip "-r" 4
Verifica a reescrita de arquivos no redirecionamento.

.ip "-v" 4
Lista cada linha de comandos lida do arquivo de entrada.

.ep
.sp
Com "+" ao inv�s de "-", os indicadores s�o desligados.
Este indicadores tamb�m podem serem usados na invoca��o do "sh".
O estado atual destes indicadores pode ser consultada atrav�s de "$-".
Os <arg>s dados s�o valores atribu�dos aos par�metros posicionais
"$0", "$1", ... Se n�o forem dados argumentos, s�o impressos os
valores de todos os nomes.

.in -7

.ip "shid"
.sp
Imprime a vers�o do comando "sh".

.(t
.ip "shift [<n>]"
.sp
Os par�metros posicionais $<n+1> ... recebem os novos nomes $1 ...
Se <n> n�o for dado, assume-se o valor 1.
.)t

.ip "time <arg> ..."
.sp
Marca e mostra o tempo de execu��o do comando formado pelos <arg>s
dados.

.ip "times"
.sp
Mostra os tempos de usu�rio e sistema acumulados para os processos
executados pelo comando "sh".

.ip "trap [<arg>] [<n> ...]"
.sp
O comando <arg> � lido e executado quando o comando "sh"
receber o(s) sinal(is) de n�mero(s) <n> ...
(note que <arg> � examinado quando o comando
� dado e quando o sinal � recebido).
Os comandos dados s�o executados na ordem dos n�meros dos sinais.
Qualquer tentativa para interceptar a recep��o de um sinal
que estava sendo ignorado na invoca��o do comando "sh" � ineficaz.
Se <arg> n�o for dado, ent�o os "traps" dos n�meros dados
s�o restaurados aos seus valores originais.
Se <arg> � uma cadeia de caracteres nula, ent�o os sinais relacionados
s�o ignorados pelo comando "sh" e pelos comandos que ele invocar.
Se <n> for zero, ent�o o comando especificado
� executado ao fim da execu��o do comando "sh".
Se n�o forem dados <arg>s, "trap" lista os comandos associados a cada sinal
(veja "signal" (sys)).

.ip "true"
.sp
Produz o valor de retorno igual a zero
(deve ser usado em conjunto com os comandos-de-programa��o).

.ip "umask [<nnn>]"
.sp
A m�scara de cria��o de arquivos do usu�rio � modificada para <nnn>
(veja umask (sys)). Se <nnn> for omitido, � impresso o valor corrente.
Todos os valores <nnn> s�o dados em octal.

.(t
.ip "unset [<nome> ...]"
.sp
Para cada <nome> dado, remove a vari�vel correspondente.
As vari�veis "PATH", "PS1" e "PS2" n�o podem ser removidas.
.)t

.(t
.ip "xh [<num>]"
.sp
Reexecuta o comando de n�mero <num> do hist�rico.
Assume por omiss�o o �ltimo comando.
.)t

.ip "wait [<n>]"
.sp
Espera pelo processo ass�ncrono (em "background") cuja identifica��o
(PID) � <n>, e imprime seu valor de retorno.
Se <n> for omitido, todos os processos ass�ncronos correntemente
ativos s�o esperados e o valor de retorno ser� zero.

.in -3
.ep

.in
.sp
.in 2
.b
Invoca��o
.r
.in 5
Se um comando "sh" � invocado atrav�s de "exec" (sys)
e o primeiro caractere do argumento zero � "-",
ent�o inicialmente o comando "sh"
l� comandos do arquivo "/etc/.profile" e de "$HOME/.profile
(caso estes arquivos existam).
A partir deste ponto, o comando "sh" l� comandos como descrito anteriormente,
que � tamb�m o caso quando o comando "sh" � invocado como "/bin/sh".
Ao t�rmino da execu��o do comando "sh", ele
executa os comandos de "$HOME/.logout" se o primeiro caractere
do argumento zero for "-".

.bc	/*************************************/
.sp
As op��es a seguir s�o interpretadas pelo
comando "sh" apenas na sua invoca��o.
Note que, a menos que a op��o "-c" seja dada, assume-se
que o primeiro argumento � o nome de um arquivo
contendo comandos, e os demais argumentos passados como par�metros
posicionais daquele arquivo de comandos.

.in +3
.ip "-c <linha>"
S�o lidos e executados comandos da cadeia <linha>.

.in -3
.ep

.sp
As op��es restantes s�o descritas na parte referente
ao comando-interno "set".
.ec	/*************************************/

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Erros detetados pelo comando "sh" (como erros de sintaxe),
acarretam um valor de retorno diferente de zero do "sh".
Se o comando "sh" est� sendo utilizada n�o interativamente,
a execu��o do arquivo passado ao comando "sh" � abandonada.
Em caso contr�rio, a comando "sh" devolve o valor de retorno
do �ltimo comando executado (veja tamb�m o comando "exit" acima).

.in
.sp
.(t
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
echo, intro, login, pwd, test, ex
.br
.wo "(sys): "
dup, exec, fork, pipe, signal, umask, exit
.br
.wo "(libc):"
edit
.br
.wo "(fmt): "
environ
.br
.)t

.in
.sp
.(t
.b ARQUIVOS
.in 5
/etc/.profile
 $HOME/.profile
 $HOME/.logout
 /tmp/sh*
 /dev/null
 /usr/include/a.out.h
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo

.in
