.bp

.sp 5

.nf
     *********************************************************
     *							     *
     *			    CAP�TULO 4			     *
     *							     *
     *	           COMANDOS INTERNOS E HIST�RICO	     *
     *							     *
     *********************************************************

.fi

.sp 4
.b
4.1 - Hist�rico
.r

.pp
Uma das facilidades mais interessantes oferecidas pela  "shell"
quando em uso interativo � a manuten��o de um hist�rico.
Seu prop�sito � guardar os �ltimos comandos fornecidos pelo usu�rio,
visando facilitar a edi��o e reexecu��o de comandos grandes
e de dif�cil digita��o, bem como manter controle do trabalho
realizado no terminal.

.pp
O hist�rico consiste numa lista cujo tamanho � dado pela vari�vel "HIST",
que inicialmente tem valor igual a 10, mas pode ser facilmente modificada
pelo usu�rio atrav�s de uma atribui��o.

.pp
Cada comando recebe um n�mero, atrav�s do qual pode ser posteriormente
refereciado.
O hist�rico pode ent�o ser consultado e seus comandos editados,
agrupados e reexecutados atrav�s dos comandos internos "h", "eh", "gh" e "xh",
respectivamente.

.sp 2
.b
4.2 - Comandos Internos
.r

.pp
Os comandos internos s�o executados pela "shell" sem a cria��o de um
subprocesso.
.in +5

.sp
.ip ":"
Este comando n�o faz nada. Produz um valor de retorno igual a zero.

.ip ". arquivo"
L� e executa os comandos em "arquivo" e retorna. Os caminhos de busca
especificados em "PATH" s�o utilizados para achar o diret�rio contendo
"arquivo".

.ip "cd [dir]"
Troca o diret�rio corrente para "dir". O valor da vari�vel "HOME"
� o argumento assumido por omiss�o.

.ip "eh [num]"
Permite a edi��o do comando "num" do hist�rico. Se "num" n�o for
especificado, � assumido o �ltimo comando do hist�rico.
Os comandos de edi��o s�o os do editor visual "ex" que fazem
sentido para uma linha. Os comandos do editor e a edi��o terminam
respectivamente por <esc> ou "q".

.ip "eval [arg ...]"
Os argumentos s�o lidos como entrada para a "shell"
e os comandos resultantes executados.

.ip "exec [arg ...]"
O comando especificado pelos argumentos � executado no lugar
desta "shell", sem que seja criado um subprocesso. Redirecionamentos
de entrada e sa�da podem aparecer, e se nenhum outro argumento
for dado, causa a modifica��o da entrada/sa�da da "shell".

.ip "exit [n]"
Provoca o t�rmino da "shell" com valor de retorno "n".
Se "n" for omitido, o valor de retorno do �ltimo comando executado
� utilizado.

.ip "export [nome ...]"
As vari�veis mencionadas s�o marcadas como export�veis, o que provoca
a inclus�o de uma cadeia definindo seu valor nos ambientes
dos programas executados posteriormente.
Se n�o for mencionado nenhum nome de vari�vel, a "shell" mostra as vari�veis
que s�o export�veis.

.ip "false  "
Produz um valor de retorno diferente de zero.

.ip "gh     "
O hist�rico �  mostrado na tela e o usu�rio poder� selecionar o
comando desejado atrav�s das setas. Escolhido o comando, tr�s op��es s�o
poss�veis: <enter> para executar o comando, <e> para editar o comando ou
<q> para desistir.

.ip "h      "
Apenas mostra o hist�rico com os �ltimos comandos executados.

.ip "login   "
Termina a sess�o corrente da "shell".

.ip "read [nome ...]"
Este comando � usado para ler valores de vari�veis.
Uma linha � lida da entrada padr�o e a primeira palavra
� atribu�da ao primeiro nome, a segunda palavra ao segundo nome,
e assim sucessivamente.
As palavras que sobrarem s�o todas atribu�das ao �ltimo nome.
Qualquer caractere pode ser quotado precedendo-o por barra invertida
('\'), inclusive <nl>. O valor de retorno � zero, a menos que
seja encontrado um fim de arquivo.

.ip "readonly [nome ...]"
As vari�veis cujos nomes s�o mencionados tornam-se inalter�veis,
n�o podendo ser afetadas por atribui��es posteriores.
Se nenhum argumento for dado, uma lista de todos as vari�veis neste estado
� mostrada.

.ip "rehash"
Por quest�o de efici�ncia, o "sh" mant�m internamente uma tabela HASH
contendo os nomes de todos os arquivos execut�veis encontrados nos diret�rios
especificados no conte�do da vari�vel PATH. Assim, se um destes diret�rios
for modificado atrav�s da inclus�o ou exclus�o de algum
execut�vel, o comando "rehash" deve ser utilizado, a fim de manter
atualizada a estrutura de dados interna do "sh".

.(t
.ip "set [--derv] [arg ...]"

.in +7

.ip "-d"
Permite que a execu��o se encerre com <control-D>.
.)t

.ip "-e"
Termina a execu��o imediatamente, se um comando n�o retornar zero.

.ip "-r"
Verifica a reescrita de arquivos no redirecionamento.

.ip "-v"
Lista cada linha de comandos lida do arquivo de entrada.

.ep

.in -7

.ip "shid"
Imprime a vers�o corrente da "shell".

.ip "shift [n]"
Os par�metros posicionais de $n+1 ... s�o renomeados de $1 ...
Se "n" n�o for dado, ele � assumido que � 1.

.ip "time arg ..."
Marca e mostra o tempo de execu��o do comando formado pelos argumentos
dados.

.ip "times "
Mostra os tempos de usu�rio e sistema acumulados para os processos
executados pela "shell".

.ip "trap [arg] [n] ..."
O comando "arg" ser� lido e executado quando a "shell".
receber o(s) sinal(is) cujos n�meros foram dados.
(Note que "arg" � varrido quando o comando
� dado e quando o sinal � recebido.) Os comandos dados s�o
executados na ordem dos n�meros dos sinais. Qualquer tentativa
de prepara��o para a recep��o de um sinal que estava sendo ignorado
na entrada da "shell" � ineficaz.
Se "arg" n�o for dado ent�o os "traps" dos n�meros dados
s�o restaurados aos seus valores originais. Se "arg" �
uma cadeia de caracteres nula, ent�o os sinais relacionados
s�o ignorados pela "shell" e pelos comandos que ela evocar.
Se for especificado o sinal zero, ent�o o comando relacionado
� executado ao fim da execu��o da shell, sen�o ao recebimento
de um sinal de n�mero "n", conforme especificado em "signal" (sys).
Se n�o forem dados argumentos "trap" mostra os comandos
associados a cada sinal.

.ip "true  "
N�o faz nada: apenas produz o valor de retorno igual a zero.

.ip "umask [nnn]"
A m�scara de cria��o de arquivos do usu�rio � modificada para "nnn"
(veja umask (sys)). Se "nnn" for omitido, o valor corrente de "umask"
� mostrado.

.ip "unset [nome ...]"
Para cada nome dado, remove a vari�vel correspondente.

.ip "wait [n]"
Espera pelo processo ass�ncrono (em "background") cuja identifica��o
seja "n" e mostra seu valor de retorno . Se "n" for omitido todos os
processos ass�ncronos correntemente ativos s�o esperados e o
valor de retorno ser� zero.

.ip "xh [num]"
Reexecuta o comando de n�mero dado do hist�rico. Assume por omiss�o
o �ltimo comando.

.ep
.in -5
