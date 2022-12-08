.bp
.he 'CMP (cmd)'TROPIX: Manual de Refer�ncia'CMP (cmd)'
.fo 'Atualizado em 27.08.04'Vers�o 4.6.0'Pag. %'

.b NOME
.in 5
.wo "cmp -"
compara pares de arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
cmp [-lpqsx] <arquivo1> <arquivo2>
cmp [-lpqsx] <arquivo1> [<arquivo2> ...] <diret�rio>
cmp [-lpqsx] [-N] <diret�rio>
.)l

.lp
.in
.b DESCRI��O
.in 5
Em sua primeira forma, o comando "cmp" compara <arquivo1> com
<arquivo2>. Se <arquivo1> ou <arquivo2> for "-", o outro arquivo
ser� comparado com a entrada padr�o.

.sp
Na segunda forma, compara um ou mais <arquivo>s com
os respectivos <arquivo>s hom�nimos do <diret�rio> especificado.

.sp
A terceira forma � an�loga � segunda, com exce��o dos nomes
dos <arquivo>s, que s�o lidos da entrada padr�o, um por linha.

.sp
O comando "cmp" nada comenta sobre pares de <arquivo>s iguais.
Para <arquivo>s diferentes (se n�o for dada nenhuma op��o),
ele indica o n�mero da linha e da coluna do primeiro caractere diferente.

.sp
O comando "cmp" indica se um dos <arquivo>s � vazio, ou um
prefixo do outro.
 
.sp
O programa "cmp" obedece �s conven��es da fun��o "modecolor",
consultando a vari�vel MODECOLOR do ambiente para obter
as cores dos nomes dos arquivos e das mensagens
de erro (veja "modecolor" (libc)).

.sp
As op��es do comando s�o:

.in +3
.ip -l
Ao encontrar um caractere diferente entre os <arquivo>s,
lista as linhas correspondente de cada <arquivo>.
Isto s� � realizado se nenhum dos <arquivo>s for um m�dulo objeto.
Esta op��o � ignorada se for dada a op��o "-s".

.ip -p
Considera como iguais pares de <arquivo>s quando um deles for um
prefixo do outro (mas N�O se um deles for vazio).

.ip -q
Compara��o r�pida: apenas compara os tamanhos e os primeiros 4 KB bytes
dos pares de <arquivo>s. N�o pode ser usado juntamente com as op��es "-l" new "-p".

.ip -s
Funcionamento silencioso:
"cmp" nada comenta nem lista, apenas retorna os c�digos.

.ip -x
Compara os n�s-�ndices ao inv�s dos conte�dos dos <arquivo>s.

.sp
No caso de elos simb�licos,
compara os conte�dos dos pr�prios elos ao inv�s dos <arquivo>s
por eles referenciados.
.bc	/*************************************/
N�o dereferencia os elos simb�licos, isto �, 
.ec	/*************************************/

.sp
Quando esta op��o � usada na segunda ou terceira forma, e o <diret�rio>
tamb�m for um elo simb�lico, podem ser comparados <arquivo>s n�o desejados.

.ip -N
L� os nomes dos <arquivo>s da entrada padr�o 
(usado para a terceira forma).
Esta op��o � impl�cita se  for dado apenas o nome do <diret�rio>.

.ep
.in -3

.in
.sp
.(t
.b
VALOR DE RETORNO
.r
.in 5
Em sua primeira forma, o comando "cmp" retorna 0 para arquivos iguais,
1 para  arquivos diferentes e 2 para argumentos faltando ou inacess�veis.
Nas outras formas, o valor de retorno � o somat�rio dos valores
indicados para a primeira forma, para cada par de arquivos comparados.
.)t

.in
.sp
.b OBSERVA��ES
.in 5
O comando "cmp" N�O � indicado para comparar m�dulos objeto,
pois o cabe�alho destes m�dulos cont�m informa��es 
s�bre a data de gera��o, vers�o/modifica��o, ..., que podem
ocasionar uma indica��o (err�nea) de que os conte�dos
dos m�dulos s�o diferentes.
Para compara��o de m�dulos objeto deve-se utilizar "cmpobj" (cmd).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc): "
modecolor
.br
.wo "(cmd):  "
cmpobj, cmptree, comm
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
