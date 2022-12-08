.bp
.he 'DOSMP (cmd)'TROPIX: Manual de Refer�ncia'DOSMP (cmd)'
.fo 'Atualizado em 19.10.05'Vers�o 4.8.0'Pag. %'

.b NOME
.in 5
.wo "dosmp -"
processa um sistema de arquivos no formato MS-DOS
.br

.in
.sp
.b SINTAXE
.in 5
.(l
dosmp [-crv] [-0123] [<dispositivo>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "dosmp" � uma interface para o processamento de sistemas
de arquivos no formato MS-DOS. Ele permite uma s�rie de opera��es
tais como listagens, c�pias e compara��es de arquivos de/para o
sistema TROPIX.

.sp
O nome do <dispositivo> contendo o sistema de arquivos DOS pode ser dado
juntamente com o nome do programa, ou pode ser dado posteriormente
atrav�s do comando "mount" (ver abaixo). Caso o <dispositivo> ainda
n�o contenha um sistema de arquivos DOS, pode ser utilizada a op��o
"-c" (ver abaixo) para criar um sistema DOS, ou pode ser utilizado
posteriormente o comando "mkfs".

.sp
Nesta vers�o, "dosmp" s� est�
aceitando <dispositivo>s especiais estruturados (isto �, de blocos),
e arquivos regulares (isto �, uma imagem de um sistema de arquivos
DOS contida em um arquivo regular).
S�o aceitas FATs de 12, 16 e 32 bits.

.sp
Se for dado um diret�rio, "dosmp" sup�e que seja um ponto de montagem
e procura o  <dispositivo> correspondente na tabela "fstab" (veja "fstab" (fmt)).

.sp
Ap�s a an�lise do <dispositivo> (possivelmente) dado, "dosmp" passa
o controle para o interpretador de comandos, aguardando instru��es
do usu�rio. Para indicar que est� aguardando comandos, "dosmp" imprime
uma linha contendo os caracteres
.sp
.nf
		"dosmp [n]> "
.fi
.sp
onde "n" � o n�mero
do comando no hist�rico (ver os comandos "h", "eh" e "xh" abaixo). 
Caso o sistema de arquivos contenha o nome de um volume no diret�rio
raiz (por exemplo, "cartas"), a linha impressa ser�
.sp
.nf
		"dosmp (cartas) [n]>".
.fi
.sp

.sp
As op��es do comando s�o:

.in +3
.ip --
(Caso normal, sem as op��es "-c" e "-r"): Se for dado um <dispositivo>,
"dosmp" assume que cont�m um sistema de arquivos DOS, e monta-o somente
para leituras (o que pode ser alterado posteriormente atrav�s do comando "rw").
Se N�O for dado um <dispositivo>, "dosmp" aguarda comandos do usu�rio.

.ip -c
Se for dado um <dispositivo>, "dosmp" nele cria um sistema de arquivos
DOS. Em caso contr�rio, aguarda comandos do usu�rio.

.ip -r
Modo garantido contra modifica��es dos sistemas de arquivos:
como o caso normal acima, s� que n�o � aceito o comando "rw", nem
qualquer outro que modifique o sistema de arquivos DOS.

.ip -v
Verboso.

.ip -0
O <dispositivo> usado � "/dev/fd0".

.ip -1
O <dispositivo> usado � "/dev/fd1".

.ip -2
O <dispositivo> usado � "/dev/zip0".

.ip -3
O <dispositivo> usado � "/dev/zip1".

.ep
.in -3

.(t
.in
.sp
.b 'MODO DE REPRESENTA��O DE DADOS'
.in 5
O formato de armazenamento de arquivos de texto em sistemas DOS �
ligeiramente diferente do que no TROPIX. As separa��es de linhas,
por exemplo, s�o feitas atrav�s de dois caracteres, <cr><nl> (ao
inv�s apenas de <nl>), e o final do arquivo pode conter o caratere <^Z>.
.)t

.sp
Para controlar a convers�o (ou n�o) entre os formatos, temos
o modo de representa��o de dados corrente, que pode ser ISO (ASCII) ou
BIN�RIO. O modo ISO sup�e que estejamos processando textos, e portanto
todos os conte�dos dos arquivos regulares lidos/escritos de/para
o sistema DOS s�o convertidos conforme a descri��o acima.
O modo BIN�RIO sup�e que estejamos processando dados bin�rios, e portanto
os conte�dos n�o s�o convertidos.
Os conte�dos de diret�rios nunca s�o convertidos.

.sp
O comando "status" informa o modo corrente,
o comando "iso" altera o modo para ISO e
o comando "bin" altera o modo para BIN�RIO.
Durante a descri��o de cada comando (abaixo), � mencionado se o modo de
representa��o de dados corrente � relevante para o seu funcionamento.

.sp
O programa "dosmp" inicia no modo ISO.

.in
.sp
.b 'NOMES DE ARQUIVOS'
.in 5
O comando "lfn" do programa "dosmp" permite escolher o modo de convers�o
dos nomes do sistema TROPIX para o DOS. Com o modo "off", os nomes
s�o convertidos para o formato antigo (tradicional) do DOS, que permite
apenas 11 caracteres ma�usculos, 8 na base e 3 na extens�o.

.sp
Com o modo "on", os nomes s�o convertidos para o formato novo ("Long
File Names" (LFN), do Windows 95/98), que permite at� 255 caracteres.

.sp
Independente do modo, "dosmp" sempre le integralmente os LFNs encontrados.
O comando "ls" (veja abaixo) imprime os nomes completos, enquanto que
o comando "lc" (veja abaixo) os trunca a 35 caracteres.

.sp
O programa "dosmp" inicia no modo "on".
O comando "status" informa o modo corrente (veja o comando "lfn", abaixo).

.bc	/*************************************/
.in
.sp
.b 'NOMES DE ARQUIVOS'
.in 5
A sintaxe dos nomes de arquivos tamb�m s�o diferentes entre os sistemas
DOS e TROPIX. Enquanto que no TROPIX, os nomes podem ter at� 14 caracteres
mai�sculos ou min�sculos, no DOS os nomes podem ter apenas 11 caracteres
ma�usculos, 8 na base e 3 na extens�o.

.sp
Na cria��o ou c�pia de arquivos, o usu�rio � alertado quando o nome
dado (ou obtido do TROPIX) n�o � adequado para o DOS. Neste caso,
o pr�prio "dosmp" sugere um truncamento adequado, e consulta o usu�rio
se ele aceita a sugest�o.
No caso da sugest�o ser aceita, "dosmp" tenta conservar os caracteres
truncados em uma �rea n�o utilizada dos diret�rios DOS
(apenas para facilitar o usu�rio do pr�prio "dosmp"). 
Em caso contr�rio, "dosmp" pede um nome substituto para o usu�rio,
mas neste caso, os (poss�veis) caracteres truncados n�o s�o conservados.

.sp
As sugest�es de truncamento s�o feitas sempre no final da base/extens�o,
como mostram os seguintes exemplos:
.nf

		abcdefghijkl		=>  ABCDEFGH
		abc.uvwxyz		=>  ABC		UVW
		abcdefghijkl.uvwxyz	=>  ABCDEFGH	UVW
		.abc.uvw		=>  ABC		UVW
		abc.def.uvw		=>  ABC		DEF
.fi

.sp
Utilizando o comando "lc" (ver abaixo) podemos ver os nomes dos
arquivos com os caracteres truncados (possivelmente) restaurados,
e usando "lc -d", podemos ver os nomes dos arquivos como ser�o
"vistos" pelos sistemas DOS. 

.sp
O que infelizmente n�o � conservado, � a informa��o de quais os caracteres
s�o originalmente mai�sculos no TROPIX. Todos caracteres s�o armazenados
em ma�usculo no sistema DOS, e convertidos para min�sculos quando
"dosmp" se referencia a eles.
Portanto (por exemplo), o nome "Makefile" ser� armazenado como
"MAKEFILE" no sistema de arquivos DOS, e convertido de volta para "makefile"
quando "dosmp" se referir a ele.
Por este motivo, nestes casos, � prefer�vel usar os comandos de compara��o
que obtenham os nomes do sistema TROPIX, tais como "cmpput" e "cmpputtree"
(ao inv�s de "cmp" e "cmpgettree").
.ec	/*************************************/

.in
.sp
.b 'EXPANS�O DOS META-CARACTERES DOS ARGUMENTOS'
.in 5
De acordo com o comando, os meta-caracteres "?*[]!" dos seus argumentos
n�o s�o expandidos,
s�o expandidos no sistema de arquivos DOS ou
s�o expandidos no sistema de arquivos TROPIX.

.sp
Normalmente, quando os argumentos n�o se referirem a arquivos ou
se referirem a arquivos que ainda v�o ser criados, eles
n�o s�o expandidos (tal como nos comandos "mount" e "mkdir");
quando os argumentos se referirem a arquivos DOS, eles s�o expandidos
no sistema DOS (tal como nos comandos "mv" e "get"); e
quando os argumentos se referirem a arquivos TROPIX, eles s�o expandidos
no sistema TROPIX (tal como nos comandos "put" e "puttree").

.sp
Repare que na expans�o no sistema DOS, os arquivos com o atributo "h"
(ver "chmod", abaixo) n�o s�o considerados.
Durante a descri��o de cada comando, o usu�rio � alertado se por acaso
a expans�o n�o segue o bom senso descrito acima.

.in
.sp
.b 'DIRET�RIO CORRENTE'
.in 5
Ao utilizar o comando "dosmp", temos em cada momento, dois diret�rios
correntes: o do DOS e o do TROPIX. Eles podem ser alterados respectivamente
pelos comandos "cd" e "!cd".

.sp
O modo mais c�modo de usar o "dosmp" � o de trabalhar entre diret�rios
correntes. Isto � uma decorr�ncia do fato de que alguns dos comandos mais
importantes ("get" e "put", entre outros) sempre se referirem a arquivos no
diret�rio corrente do sistema de arquivos destino.

Por exemplo, no comando "get alpha/beta/gamma.c" � copiado o arquivo
"alpha/beta/gamma.c" do sistema DOS no arquivo "gamma.c" do diret�rio
corrente do sistema TROPIX.

.sp
Se durante a descri��o de um comando, nada for mencionado,
s�o utilizados os nomes completos dos arquivos
(isto �, todos os componentes do caminho).
Em caso contr�rio, � indicado em qual sistema � usado o diret�rio
corrente.

.in
.sp
.(t
.b COMANDOS
.in 5
O programa "dosmp" reconhece os seguintes comandos:

.bc	/*************************************/
.in +3
.ec	/*************************************/
.ip " 1." 4
?
.sp
Como "help", abaixo.

.ip " 2." 4
!<comando> [<argumento> ...]
.sp
Executa o <comando> com os respectivos <argumento>s no sistema TROPIX.
Isto vale inclusive para o comando "cd".
.)t

.ip " 3." 4
arena [-v]
.sp
Imprime e verifica a consist�ncia da arena de "malloc" (libc).
Este comando � indicado para a depura��o e/ou manuten��o do programa,
e n�o para o uso normal.

.(t
.ip " 4." 4
ascii
.sp
Altera o modo de representa��o de dados para ISO (ASCII).
.)t

.ip " 5." 4
bin
.sp
Altera o modo de representa��o de dados para BIN�RIO.

.ip " 6." 4
bye
.sp
Encerra o programa. Um EOF (normalmente <^D>) tem o mesmo efeito.

.ip " 7." 4
cat <arquivo>
.sp
Imprime um arquivo DOS na sa�da padr�o.
O conte�do do arquivo � convertido,
conforme o modo de representa��o de dados.

.ip " 8." 4
cd <novo_diret�rio>
.sp
Altera o diret�rio corrente DOS para <novo_diret�rio>.

.ip " 9." 4
chd <novo_diret�rio>
.sp
Como "cd", acima.

.ip "10." 4
chm [-v] <modo> <arquivo> ...
.sp
Como "chmod", abaixo.

.ip "11." 4
chmod [-v] <modo> <arquivo> ...
.sp
Altera atributos de arquivos DOS.
Podem ser alterados os atributos "m" (arquivo modificado),
"s" (arquivo do sistema DOS), "h" (arquivos ocultos),
"r" (arquivo com prote��o de escrita), al�m dos atributos
"1" e "2" (reservados).
O <modo> pode ser dado como uma constante inteira decimal,
octal ou hexadecimal (conforme a sintaxe da linguagem "C")
ou ainda simbolicamente com a sintaxe
.sp
.nf
			[u] <op> <atributo>
.fi
.sp
onde <op> pode ser "=", "+" ou "-" e <atributo> deve ser uma das
letras descritas acima. V�rios modos podem ser dados, separados
por virgulas, como no exemplo
.sp
.nf
			chmod u-h,+r alpha beta
.fi
.sp
Se for dada a op��o "-v", s�o listados os modos antigo e novo de
cada <arquivo>. A sintaxe do <modo> deste comando � baseada em
"chmod" (cmd), onde podem ser vistos mais detalhes.

.ip "12." 4
chsize [-s <n>]
.sp
O objetivo do comando "chsize" � o de liberar <n> MB ainda n�o
alocados do final do sistema de arquivos DOS, para a
cria��o de uma nova parti��o
(por exemplo, para um sistema de arquivos de um outro sistema operacional).
Antes de usar este comando, � recomend�vel desfragmentar
o sistema de arquivos atrav�s do comando DEFRAG ou SPEED DISK
(dos NORTON UTILITIES).
Talvez seja �til tamb�m usar o comando "compac" (veja abaixo).

.sp
Sem op��es, o comando informa o tamanho atual da parti��o,
o tamanho atual do sistema de arquivos DOS
e o espa�o livre dispon�vel no final do sistema de
arquivos (em MB).

.sp
Com a op��o "-s <n>", al�m dos dados acima, s�o propostos novos tamanhos
para a parti��o DOS, o sistema de arquivos DOS e a nova parti��o
a ser criada. Este �ltimo valor pode n�o ser exatamente igual ao
valor dado <n>, por arredondamentos decorrentes do tamanho do cilindro
do disco.

.sp
Se a proposta for aceita, o superbloco original do sistema de arquivos
� gravado no arquivo "dos_sb" (no diret�rio corrente do TROPIX),
e o sistema de arquivos tem o seu tamanho
reduzido para o valor da proposta.
Anote o novo tamanho da parti��o DOS e o tamanho da nova parti��o
a ser criada (em MB e blocos).

.sp
Se tudo correr de acordo com as expectativas (isto �, o DOS reconhecer
corretamente o novo tamanho do sistema de arquivos DOS), utilize o
"fdisk" (dispon�vel no "boot2") para alterar o tamanho 
da parti��o DOS e criar a nova parti��o (de acordo com os tamanhos anotados).

.sp
Se houver problemas com o novo sistema de arquivos DOS
(de tamanho reduzido), o tamanho original pode ser restaurado atrav�s do
comando

.sp
.nf
		dd if=dos_sb of=/dev/dos_c
.fi
.sp
onde "/dev/dos_c" deve ser substitu�do pelo dispositivo correspondente
� parti��o DOS.

.ip "13." 4
clri <arquivo> ...
.sp
Remove entradas de diret�rio DOS (modo de p�nico).
Em casos de emerg�ncia, remove <arquivos>, que por alguma raz�o,
o comando "rm" (ver abaixo) n�o consegue remover. Ap�s o uso, deve
ser usado o comando "fsck" (ver abaixo) para restaurar a consist�ncia
do sistema de arquivos DOS.
Este comando n�o � indicado para o uso normal.

.(t
.ip "14." 4
cmp <arquivo> ...
.sp
Compara pares de arquivos correspondentes entre os sistemas DOS e TROPIX.
O comando "cmp" nada comenta sobre arquivos iguais.
Para arquivos diferentes, indica o n�mero do primeiro caractere
diferente, ou se um dos arquivos � prefixo do outro.
Se N�O forem iguais, informa qual das vers�es � a mais recente.
.)t
.sp
Se algum nome de <arquivo> for um caminho com v�rios componentes,
o nome completo ser� usado apenas para referenciar o arquivo DOS;
no TROPIX ser� utilizado o diret�rio corrente.
Os conte�dos dos arquivos DOS s�o convertidos,
conforme o modo de representa��o de dados.
Os meta-caracteres "?*[]!" s�o expandidos no sistema DOS.

.ip "15." 4
cmpget <arquivo> ...
.sp
Como "cmp", acima.

.ip "16." 4
cmpgettree [-ui.s] [-p "<p>"] [-P "<P>"] <�rvore>
.sp
O comando "cmpgettree" caminha a <�rvore> DOS comparando cada
arquivo com o arquivo correspondente da <�rvore> TROPIX.
Se for encontrada alguma diferen�a entre as �rvores, ela � indicada,
e de acordo com a op��o "-u" a �rvore TROPIX pode
ser atualizada.
.sp
Para maiores detalhes sobre as op��es "-ui.spP" consulte "cmptree" (cmd).
Normalmente n�o s�o selecionados arquivos com o atributo "h"
(ver "chmod" acima). A op��o "-." seleciona tamb�m estes arquivos.
.sp
O comando "cmpgettree" nada comenta sobre pares de arquivos iguais.
Para arquivos diferentes, indica o n�mero do primeiro caractere
diferente, ou se um dos arquivos � prefixo do outro.
Se N�O forem iguais, informa qual das vers�es � a mais recente.
.sp
O nome completo da <�rvore> � usado tanto para referenciar o
sistema TROPIX como o DOS.
Os conte�dos dos arquivos DOS s�o convertidos,
conforme o modo de representa��o de dados.
Os meta-caracteres "?*[]!" s�o expandidos no sistema DOS.

.ip "17." 4
cmpput <arquivo> ...
.sp
Como "cmp", acima, s� que
se algum nome de <arquivo> for um caminho com v�rios componentes,
o nome completo ser� usado apenas para referenciar o arquivo TROPIX;
no DOS ser� utilizado o diret�rio corrente. Al�m disto,
os meta-caracteres "?*[]!" s�o expandidos no sistema TROPIX.

.(t
.ip "18." 4
cmpputtree [-ui.s] [-p "<p>"] [-P "<P>"] <�rvore>
.sp
O comando "cmpputtree" caminha a <�rvore> TROPIX comparando cada
arquivo com o arquivo correspondente da <�rvore> DOS.
Se for encontrada alguma diferen�a entre as �rvores, ela � indicada,
e de acordo com a op��o "-u" a �rvore DOS pode
ser atualizada.
.)t
.sp
Para maiores detalhes sobre as op��es "-ui.spP" consulte "cmptree" (cmd).
.sp
O comando "cmpputtree" nada comenta sobre pares de arquivos iguais.
Para arquivos diferentes, indica o n�mero do primeiro caractere
diferente, ou se um dos arquivos � prefixo do outro.
Se N�O forem iguais, informa qual das vers�es � a mais recente.
.sp
O nome completo da <�rvore> � usado tanto para referenciar o
sistema TROPIX como o DOS.
Os conte�dos dos arquivos DOS s�o convertidos,
conforme o modo de representa��o de dados.
Os meta-caracteres "?*[]!" s�o expandidos no sistema TROPIX.

.ip "19." 4
compac [-v]
.sp
Compacta o sistema de arquivos. Este comando � um desfragmentador
especial para retirar do final do sistema de arquivos aqueles
arquivos que cont�m "cluster"s os quais os desfragmentadores
tais como o DEFRAG ou SPEED DISK (dos NORTON UTILITIES)
consideram que "n�o devem ser movidos".
Isto � �til para um posterior uso do comando "chsize" (veja acima).

.sp
Lembre-se no entanto, ao usar o comando "compac", de que ele n�o tem
consci�ncia das poss�veis conseq��ncias ocasionadas por
estas mudan�as no funcionamento do DOS/Windows.

.bc	/*************************************/
.ps
O comando "compac"
deve (naturalmente) ser usado somente ap�s o sistema de
arquivos tiver sido desfragmentado por um desfragmentador
do Windows, e ele ter decidido n�o mover alguns "cluster"s
no final do sistema de arquivos.
Mesmo assim, deve ser usado apenas quando 
.ec	/*************************************/

.sp
Este comando � interativo; a cada ciclo ele imprime o grau de
compacticidade e o espa�o livre ao final do sistema de arquivos
(100 \% de compacticidade significa que todos os "cluster"s ocupados
est�o cont�guos no in�cio do sistema de arquivos).

.sp
Em seguida � impresso o nome do arquivo que cont�m o �ltimo
"cluster" ocupado do sistema de arquivos, e o usu�rio � consultado
se deseja mover o arquivo para o in�cio do sistema.

.sp
Se a resposta for afirmativa, o arquivo � movido,
e o ciclo se repete. Deste modo podemos mover arquivos at� que haja
um certo espa�o livre desejado ao final do sistema para um
"chsize" posterior.

.ip "20." 4
del [-ifv] <arquivo> ...
.sp
Como "rm", abaixo.

.(t
.ip "21." 4
df
.sp
Imprime o espa�o total e livre do sistema de arquivos em KB.
Informa tamb�m o nome do dispositivo, se est� protegido contra
escritas ("RO") e a identifica��o contida no super-bloco do sistemas
de arquivos.
.)t

.(t
.ip "22." 4
diff <arquivo>
.sp
Compara diferencialmente arquivos entre os sistemas TROPIX e DOS.
Este comando copia o arquivo DOS para uma arquivo tempor�rio,
compara as vers�es atrav�s de "diff" (cmd) e mostra as diferen�as
com "show" (cmd).
A ordem das diferen�as indicadas � TROPIX, DOS.
.)t
.sp
Se o nome do <arquivo> for um caminho com v�rios componentes,
o nome completo ser� usado apenas para referenciar o arquivo TROPIX;
no DOS ser� utilizado o diret�rio corrente.
O conte�do do arquivo DOS � convertido,
conforme o modo de representa��o de dados.
Os meta-caracteres "?*[]!" s�o expandidos no sistema DOS.

.ip "23." 4
du [-sa] [<�rvore> ...]
.sp
Informa sobre o espa�o usado (em KB) por todos os arquivos e diret�rios 
contidos em cada <�rvore> dada do sistema de arquivos.
.sp
Se for dada a op��o "-s", imprime somente o total de cada <�rvore>.
Se for dada a op��o "-a", imprime uma linha para cada arquivo.
Os meta-caracteres "?*[]!" s�o expandidos no sistema DOS.

.(t
.ip "24." 4
dir [-d] [<diret�rio> ...]
.sp
Como "lc", abaixo.
.)t

.ip "25." 4
dump <arquivo>
.sp
Como "xd", abaixo.

.ip "26." 4
echo [-d] <argumento> ...
.sp
Ecoa os <argumento>s (expandidos no sistema DOS).
Isto � �til para saber como os argumentos ir�o ser expandidos,
antes de utilizar um comando cujos argumentos s�o expandidos no DOS.
.sp
Se for dada a op��o "-d", os argumentos ser�o impressos em um formato
vetorial (ao inv�s de linear).

.ip "27." 4
echoget [-d] <argumento> ...
.sp
Como "echo", acima.

.ip "28." 4
echoput [-d] <argumento> ...
.sp
Como "echo", acima, s� que
os meta-caracteres "?*[]!" s�o expandidos no sistema TROPIX.

.ip "29." 4
eh [<n>]
.sp
Edita (e opcionalmente executa) o comando de n�mero <n> do hist�rico.
Se <n> for omitido, edita o �ltimo comando presente no hist�rico.
A edi��o � realizada pela fun��o "edit" (libc).
Ap�s a edi��o, o usu�rio � consultado se deseja realmente executar
o comando editado.

.(t
.ip "30." 4
era [-ifv] <arquivo> ...
.sp
Como "rm", abaixo.
.)t

.ip "31." 4
exit
.sp
Encerra o programa. Um EOF (normalmente <^D>) tem o mesmo efeito.

.ip "32." 4
fsck [-f]
.sp
Verifica a consist�ncia do sistema de arquivos. Se o sistema de arquivos
estiver montado com permiss�o de escrita, o usu�rio � consultado
se deseja consertar alguns erros mais simples.
Se for dada a op��o "-f", "fsck" conserta sem consultar o usu�rio.

.sp
De modo normal, no entanto, recomendamos efetuar o conserto
do sistema de arquivos MS-DOS atrav�s do pr�prio MS-DOS.

.(t
.ip "33." 4
get [-ifv] <arquivo> ...
.sp
Copia arquivos DOS para o diret�rio corrente do sistema TROPIX.
Para detalhes sobre as op��es "-ifv", use "get -H".
.)t
.sp
Se algum nome de <arquivo> for um caminho com v�rios componentes,
o nome completo ser� usado apenas para referenciar o arquivo DOS.
Os conte�dos dos arquivos DOS s�o convertidos,
conforme o modo de representa��o de dados.

.ip "34." 4
gettree [-ifv.s] [-p "<p>"] [-P "<P>"] <�rvore>
.sp
Copia �rvores DOS para o sistema TROPIX.
Para maiores detalhes sobre as op��es "-ifv.spP" consulte "cptree" (cmd).
Normalmente n�o s�o selecionados arquivos com o atributo "h"
(ver "chmod" acima). A op��o "-." seleciona tamb�m estes arquivos.
.sp
O nome completo da <�rvore> � usado tanto para referenciar o
sistema TROPIX como o DOS.
Os conte�dos dos arquivos DOS s�o convertidos,
conforme o modo de representa��o de dados.

.ip "35." 4
h
.sp
Imprime os comandos do hist�rico. Nesta vers�o, o hist�rico armazena
os �ltimos 20 comandos executados.

.ip "36." 4
help
.sp
Imprime uma lista de todos os comandos dispon�veis. Em certos
casos, recomenda o uso de alguns comandos.
Para obter um resumo de um <comando>, use "<comando> -H".

.ip "37." 4
image
.sp
Altera o modo de representa��o de dados para BIN�RIO.

.ip "38." 4
iso
.sp
Altera o modo de representa��o de dados para ISO (ASCII).

.(t
.ip "39." 4
lc [<diret�rio> ...]
.sp
Imprime o conte�do dos <diret�rio>s dados.
Se n�o for dado nenhum <diret�rio> ser� considerado o diret�rio corrente.
.)t

.sp
Se o ambiente contiver a vari�vel MODECOLOR, os diversos tipos
de arquivos ser�o impressos com cores distintas (veja "modecolor" (libc)).

.(t
.ip "40." 4
lfn [off|8.3] [on|255|w95|W95]
.sp
Indica o modo de cria��o dos nomes DOS. Com o argumento "off" ou "8.3",
os nomes ser�o criados no estilo "antigo" ou "ortodoxo", isto �, da �poca
pr�-windows-95, com nome de at� 8 caracteres e uma extens�o de at� 3
caracteres.
.)t
.sp
Com o argumento "on", "255", "w95" ou "W95",
os nomes ser�o criados no estilo "novo", isto �, da �poca
windows-95/98, com nomes de at� 255 caracteres.

.(t
.ip "41." 4
ls [-al] <arquivo> ...
.sp
Imprime caracter�sticas dos <arquivo>s dados.
Se um <aquivo> for um diret�rio, imprime caracter�sticas de todos
arquivos do diret�rio.
Se n�o for dado nenhum <arquivo> ser� considerado o diret�rio corrente.
.)t
.sp
Com a op��o "-a" s�o listados tamb�m as entradas "." e ".." dos diret�rios.
Sem a op��o "-l" s�o listados apenas os nomes dos arquivos;
com esta op��o s�o listados tamb�m o tipo do arquivo, os seus atributos,
o seu tamanho e sua data. Se o arquivo tiver o atributo "h"
(ver "chmod" acima), o seu nome vir� entre parenteses.

.sp
Se o ambiente contiver a vari�vel MODECOLOR, os diversos tipos
de arquivos ser�o impressos com cores distintas (veja "modecolor" (libc)).

.ip "42." 4
md <diret�rio> ...
.sp
Como "mkdir", abaixo.

.ip "43." 4
mkd <diret�rio> ...
.sp
Como "mkdir", abaixo.

.ip "44." 4
mkdir <diret�rio> ...
.sp
Cria diret�rios DOS.
O diret�rio pai de cada <diret�rio> a ser criado j� deve existir.

.ip "45." 4
mkfile <arquivo> <MB sz>
.sp
Cria o <arquivo> DOS de tamanho <MB sz>.
O espa�o em disco necess�rio � alocado em uma �rea cont�gua.
Se o sistema de arquivos n�o possuir <MB sz> cont�guos,
� emitida uma mensagem de erro, e o arquivo n�o � criado.
O conte�do do arquivo N�O � inicializado (ou em outras palavras,
permanecem os valores j� existentes nos blocos do disco).

.sp
O objetivo usual deste comando � cria��o dos arquivos necess�rios
para a instala��o do TROPIX em arquivos de uma parti��o DOS.

.ip "46." 4
mkfs [-v] [-sfc ...] [-01] [-c <b>] [<dispositivo>]
.sp
Cria um sistema de arquivos DOS.
Para detalhes sobre as op��es do comando, use "mkfs -H".
.sp
Se n�o for dado o nome do <dispositivo>, ser� usado o corrente.

.bc	/*************************************/
.sp
Repare que com a cria��o de sistemas de arquivos com par�metros n�o
convencionais h� o risco de desentendimentos (fatais)
com o sistema operacional MS-DOS j� que ele (aparentemente)
n�o examina o superbloco dos sistemas de arquivos.
.sp
Embora que o programa "dosmp" possa ser usado para criar sistemas de
arquivos nos discos r�gidos, isto deve ser feito com muito cuidado,
pela mesma raz�o do par�grafo anterior.
.ec	/*************************************/

.ip "47." 4
mkv <nome_do_volume>
.sp
Cria um nome de volume de sistema de arquivos DOS. Repare que o
<nome_do_volume> deve vir normalmente na raiz do sistema de arquivos.

.ip "48." 4
mount [-01] [<dispositivo>]
.sp
Monta o <dispositivo> com um sistema de arquivos DOS.
Para detalhes sobre as op��es do comando, use "mount -H".
.sp
Se o nome do <dispositivo> n�o for dado, ser� usado o dispositivo corrente.
Neste caso, o meio (por exemplo, um disquete) pode ser trocado,
para ser montado um novo sistema de arquivos.

.ip "49." 4
mv [-ifv] <arquivo1> <arquivo2>
.br
mv [-ifv] <arquivo1> [<arquivo2> ...] <diret�rio>
.sp
Move (troca o nome) de arquivos (regulares ou volumes) DOS.
Para detalhes sobre as op��es do comando, use "mv -H".
.sp
Em sua primeira forma, o comando "mv" move
(troca o nome de) <arquivo1> para <arquivo2>.
Na segunda forma, um ou mais <arquivo>s s�o movidos para o
<diret�rio> especificado, com seus nomes originais.

.ip "50." 4
mvtree <diret�rio1> <diret�rio2>
.sp
Move (troca o nome) de diret�rios DOS.
Se o <diret�rio2> ainda n�o existe, o novo nome de <diret�rio1>
ser� <diret�rio2>. Em caso contr�rio, ser� <diret�rio2>/<nome1>, onde
<nome1> � o �ltimo componente do caminho de <diret�rio1>.

.ip "51." 4
param
.sp
Imprime os par�metros do sistema de arquivos DOS montado.

.ip "52." 4
path
.sp
Como "pwd", abaixo.

.(t
.ip "53." 4
put [-ifv] <arquivo> ...
.sp
Copia arquivos TROPIX para o diret�rio corrente do sistema DOS.
Para detalhes sobre as op��es "-ifv", use "get -H".
.)t
.sp
Se algum nome de <arquivo> for um caminho com v�rios componentes,
o nome completo ser� usado apenas para referenciar o arquivo TROPIX.
Os conte�dos dos arquivos DOS s�o convertidos,
conforme o modo de representa��o de dados.

.ip "54." 4
puttree [-ifv.s] [-p "<p>"] [-P "<P>"] <�rvore>
.sp
Copia �rvores TROPIX para o sistema DOS.
Para maiores detalhes sobre as op��es "-ifv.spP" consulte "cptree" (cmd).
.sp
O nome completo da <�rvore> � usado tanto para referenciar o
sistema TROPIX como o DOS.
Os conte�dos dos arquivos DOS s�o convertidos,
conforme o modo de representa��o de dados.

.ip "55." 4
pwd
.sp
Imprime o diret�rio corrente DOS.

.ip "56." 4
quit (ou simplesmente "q")
.sp
Encerra o programa. Um EOF (normalmente <^D>) tem o mesmo efeito.

.ip "57." 4
rd <diret�rio> ...
.sp
Como "rmdir", abaixo.

.ip "58." 4
ren [-ifv] <arquivo1> <arquivo2>
.br
ren [-ifv] <arquivo1> [<arquivo2> ...] <diret�rio>
.sp
Como "mv", acima.

.ip "59." 4
rm [-ifv] <arquivo> ...
.sp
Remove arquivos DOS (regulares ou volumes).
Para detalhes sobre as op��es "-ifv", use "rm -H".

.(t
.ip "60." 4
rmd <diret�rio> ...
.sp
Como "rmdir", abaixo.
.)t

.ip "61." 4
rmdir <diret�rio> ...
.sp
Remove diret�rios DOS.

.(t
.ip "62." 4
rmtree [-fv] <�rvore>
.sp
Remove uma �rvore DOS.
Para detalhes sobre as op��es "-fv", use "rmtree -H".
.)t

.ip "63." 4
rmv [-ifv] <arquivo> ...
.sp
Como "rm", acima.

.ip "64." 4
ro
.sp
Permite apenas leituras no sistema de arquivos DOS.

.ip "65." 4
rv [-ifv] <arquivo> ...
.sp
Como "rm", acima.

.(t
.ip "66." 4
rw
.sp
Permite leituras e escritas no sistema de arquivos DOS.
Este comando n�o � aceito se foi dada a op��o "-r" para "dosmp".
.)t

.(t
.ip "67." 4
set
.sp
Como "status", abaixo.
.)t

.ip "68." 4
seta
.sp
Altera o modo de representa��o de dados para ISO (ASCII).

.ip "69." 4
setb
.sp
Altera o modo de representa��o de dados para BIN�RIO.

.(t
.ip "70." 4
show <arquivo>
.sp
Mostra um arquivo na tela do terminal.
Este comando copia o arquivo DOS para uma arquivo tempor�rio,
e mostra-o atrav�s de "show" (cmd).
.)t
.sp
O conte�do do arquivo DOS � convertido,
conforme o modo de representa��o de dados.

.(t
.ip "71." 4
stat
.sp
Como "status", abaixo.
.)t

.ip "72." 4
status
.sp
Informa o estado do sistema de arquivos e o modo de representa��o
de dados corrente.

.ip "73." 4
sys [-v] [-d <dir>]
.sp
Grava os arquivos "IO.SYS", "DRVSPACE.BIN", "MSDOS.SYS" e "COMMAND.COM"
na raiz do sistema de arquivos DOS para torn�-lo carreg�vel.

.sp
Estes arquivos s�o procurados no diret�rio <dir> (normalmente ".").

.(t
.ip "74." 4
tdat <arquivo> ...
.sp
Como "touch", abaixo.
.)t

.ip "75." 4
touch <arquivo> ...
.sp
Atribui a data atual a cada <arquivo> DOS dado.

.ip "76." 4
tree [-l] [<�rvore> ...]
.sp
Como "walk", abaixo.

.ip "77." 4
type <arquivo>
.sp
Como "cat", acima.

.(t
.ip "78." 4
umount
.sp
O sistema de arquivos � desmontado, e "dosmp" aguarda que outro
seja montado (atrav�s de "mount", acima) ou que seja criado um (atrav�s
de "mkfs", acima).
.)t

.(t
.ip "79." 4
walk [-l] [<�rvore> ...]
.sp
Percorre �rvores DOS listando os nomes dos arquivos.
Se n�o for dada nenhuma <�rvore>, � percorrido o diret�rio corrente.
.)t
.sp
Normalmente, � dado o tipo do arquivo, seu tamanho e nome.
Se for dada a op��o "-l" s�o dados tamb�m o n�mero do primeiro
"cluster" do arquivo e outras informa��es.

.sp
Se o ambiente contiver a vari�vel MODECOLOR, os diversos tipos
de arquivos ser�o impressos com cores distintas (veja "modecolor" (libc)).

.ip "80." 4
waste
.sp
Analisa o sistema de arquivos e imprime o espa�o total (em KB)
desperdi�ados nos finais dos "cluster"s alocados aos arquivos.

.ip "81." 4
xd <arquivo>
.sp
"Dump" em hexadecimal e ISO do <arquivo>,
que pode ser regular ou um diret�rio.
.sp
Se o <arquivo> for regular, o seu conte�do � convertido,
conforme o modo de representa��o de dados.

.ip "82." 4
xh [<n>]
.sp
Excuta o comando de n�mero <n> do hist�rico.
Se <n> for omitido, executa o �ltimo comando presente no hist�rico.

.ep
.bc	/*************************************/
.in -3
.ec	/*************************************/

.in
.sp
.b OBSERVA��O
.in 5
Como o sistema de arquivos DOS n�o tem o conceito de elo f�sico nem simb�lico,
os comandos de c�pia n�o testam a exist�ncia de elos no sistema TROPIX.
Isto significa (por exemplo) que se durante uma opera��o de c�pia
para o DOS, dois nomes de arquivos se referirem a um mesmo arquivo TROPIX,
ele ser� copiado duas vezes, uma vez com cada nome.

.in
.sp
.b AGRACECIMENTO
.in 5
O autor agradece a Norival Ribeiro Figueira cujo programa "pldos" (cmd)
foi meticulosamente estudado, e serviu de inspira��o para o "dosmp".

.in
.sp
.(t
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc): "
edit, modecolor
.br
.wo "(cmd):  "
pldos, chmod, cptree, cmptree, diff, show
.br
.wo "(fmt):  "
ambiente, fstab
.br
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
