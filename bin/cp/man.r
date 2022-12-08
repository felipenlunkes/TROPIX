.bp
.he 'CP (cmd)'TROPIX: Manual de Refer�ncia'CP (cmd)'
.fo 'Atualizado em 01.05.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "cp -"
copia arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
cp [-ifvmx] <arquivo1> <arquivo2>
cp [-ifvmx] <arquivo1> [<arquivo2> ...] <diret�rio>
cp [-ifvmx] [-N] <diret�rio>
.)l

.in
.sp
.b DESCRI��O
.in 5
Em sua primeira forma, o comando "cp" copia <arquivo1> para <arquivo2>.

.sp
Na segunda forma, um ou mais <arquivo>s s�o copiados para o
<diret�rio> especificado, com seus nomes originais.

.sp
A terceira forma � an�loga � segunda, com exce��o dos nomes
dos <arquivo>s, que s�o lidos da entrada padr�o, um por linha.

.sp
As op��es do comando s�o:

.in +3

.ip -i
Modo interativo:
� pedida a confirma��o do usu�rio para cada <arquivo> a copiar.

.ip -f
Se o <arquivo> destino j� existir, "cp" normalmente pede permiss�o
ao usu�rio para remov�-lo. Com esta op��o, o <arquivo> �
removido silenciosamente.

.ip -v
Lista os nomes dos <arquivo>s que est�o sendo copiados.

.ip -m
Copia o estado do <arquivo>:
normalmente, o dono e o grupo do <arquivo> destino s�o conservados
se �ste j� existe, e s�o usados os do usu�rio do comando em caso contr�rio. 
Com a op��o "-m", s�o utilizados o dono, grupo, prote��o e datas do <arquivo>
fonte no <arquivo> destino. Isto s� � inteiramente poss�vel se o
usu�rio do comando for superusu�rio. 

.ip -x
Copia os n�s-�ndices ao inv�s dos conte�dos dos <arquivo>s.

.sp
Se o <arquivo> fonte for um elo simb�lico, copia o pr�prio elo simb�lico
ao inv�s do conte�do do <arquivo>.

.ip -N
L� os nomes dos <arquivo>s da entrada padr�o 
(usado para a terceira forma).
Esta op��o � impl�cita se  for dado apenas o nome do <diret�rio>.

.ep
.in -3

.in
.sp
.b OBSERVA��O
.in 5
O comando "cp" n�o copia �rvores. Para esta fun��o deve-se utilizar
"cptree" (cmd).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
cat, pr, cp, mv, ln, cptree
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
