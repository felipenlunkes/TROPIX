.bp 1
.he 'GREP (cmd)'TROPIX: Manual de Refer�ncia'GREP (cmd)'
.fo 'Atualizado em 08.05.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
grep - procura padr�es em arquivos
.sp

.in
.sp
.b SINTAXE
.in 5
grep [-clnsmrN] <padr�o>[|<padr�o> ...] [<arquivo> ...]

.in
.sp
.b DESCRI��O
.in 5
O comando "grep" l� um ou mais <arquivo>s, procurando por linhas que contenham
pelo menos um dos <padr�es> dados.
Normalmente, cada linha selecionada � copiada para a sa�da padr�o ("stdout").

.sp
Os nomes dos arquivos podem ser dados como argumentos,
podem ser lidos de um arquivo de nomes (ver a op��o "-N"),
ou por omiss�o, o arquivo pode ser a entrada padr�o ("stdin").


.sp
Os padr�es utilizados pelo comando "grep" s�o express�es regulares com
a mesma sintaxe das fun��es "regcmp" e "regex" (libc).

Podem ser dados v�rios padr�es, separados pelo caractere "|".
Para que um padr�o possa conter este caractere sem que seja confundido
com o separador de padr�es, basta preced�-lo por "\".

.sp
As op��es de funcionamento do "grep" s�o:

.in 8
.ip "-c" 5
Lista apenas o n�mero total de linhas selecionadas
(n�o copia as linhas selecionadas para a sa�da padr�o).

.ip "-l" 5
Lista apenas os nomes dos arquivos (uma �nica vez)
que cont�m linhas selecionadas
(n�o copia as linhas selecionadas para a sa�da padr�o).

.ip "-n" 5
Na listagem das linhas selecionadas, inclui al�m do nome do arquivo,
tamb�m o n�mero da linha no respectivo arquivo.

.ip "-s" 5
N�o lista nada; retorne apenas o estado (ver o valor de ret�rno).

.ip "-m" 5
Procura os padr�es sem fazer distin��o entre letras ma�usculas e min�sculas.

.ip "-r" 5
Inverte o sentido da busca, isto �, selecione linhas que N�O
contenham nenhum dos padr�es.

.ip "-N" 5
L� os nomes dos arquivos da entrada padr�o, ao inv�s de obt�-los
como argumentos.
Esta op��o � �til para utiliza��o com o comando "walk" (cmd).
Se n�o for dada esta op��o,
nem arquivos como argumentos,
o conte�do do arquivo ser� lido da entrada padr�o.

.ep
.in 5
.sp 2
Deve-se tomar cuidado com a utiliza��o dos caracteres
"$", "*", "[", "]", "|", e "\" nos padr�es,
j� que eles tamb�m t�m significado especial
para o interpretador de comandos "sh" (cmd).
O mais seguro � colocar o argumento com os padr�es entre aspas.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Retorna 0 se foi selecionada pelo menos uma linha, retorna 1 se
n�o foi selecionada nenhuma linha, e retorna 2 se houveram erros
de sintaxe ou arquivos inacess�veis.

.in
.sp
.b OBSERVA��O
.in 5
O tamanho das linhas � limitado a 1024 caracteres. Linhas maiores
s�o divididas em duas (ou mais).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sh, walk
.br
.wo "(libc):"
regcmp, regex
.br


.in
.sp
.b EXEMPLOS
.in 11
.sp
grep comando /etc/passwd
.sp
.br
.in 5
lista as linhas do arquivo "/etc/passwd" que cont�m
a cadeia "comando" da seguinte forma:
.sp
.(b
.nf
	/etc/passwd:  data::comando data:10:0:0:0::/:/bin/data
	/etc/passwd:  who::comando who:10:0:0:0::/:/bin/who
.fi
.)b

.sp 3
.in 11
grep -v "^a" *
.sp
.in 5
percorre todos os arquivos do diret�rio,
listando as linhas que n�o come�am com o caractere "a".

.sp 3
.in 11
walk -p "*.h" /usr/include | grep -N short
.sp
.br
.in 5
lista as linhas que cont�m "short" de todos os arquivos
de inclus�o da �rvore cuja raiz � "/usr/include".
.sp

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
