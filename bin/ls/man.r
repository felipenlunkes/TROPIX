.bp
.he 'LS (cmd)'TROPIX: Manual de Refer�ncia'LS (cmd)'
.fo 'Atualizado em 18.09.05'Vers�o 4.8.0'Pag. %'


.b NOME
.in 5
.wo "ls -"
lista caracter�sticas de arquivos e diret�rios
.br

.in
.sp
.b SINTAXE
.in 5
.(l
ls [-lL3ditaRN] [<nome> ...]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "ls" lista caracter�sticas de arquivos e conte�dos de diret�rios.
Para cada <nome> dado, se for um arquivo normal (n�o diret�rio),
"ls" fornece uma s�rie de caracter�sticas, e se for um diret�rio,
fornece as mesmas caracter�sticas para cada membro deste diret�rio.

.sp
Se n�o for dado nenhum <nome> (nem a op��o "-N"), � considerado o
diret�rio corrente.

.sp 2
O formato da listagem � controlado pelas op��es:

.in +3
.ip --
Simples: se n�o for dada nenhuma das 3 op��es abaixo, a listagem cont�m
apenas os nomes dos arquivos/diret�rios.

.ip -l
Longo: a listagem cont�m o tipo do arquivo, prote��o,
n�mero de elos f�sicos, o dono (UID), o grupo (GID), tamanho (bytes),
data da �ltima modifica��o e o seu nome.
Para arquivos especiais, � dado (ao inv�s do tamanho),
a identifica��o num�rica ("major" e "minor") do dispositivo.
Normalmente s�o impressos os nomes simb�licos do dono/grupo,
a n�o ser que eles n�o sejam encontrados nos arquivos correspondentes.

.ip -L
Muito longo: como o longo, mas com o modo completo (os 24 bites).

.ip -3
Tempos: a listagem cont�m o tipo do arquivo, data da cria��o,
data da �ltima modifica��o, data do �ltimo acesso e o seu nome.

.ep
.in -3

.sp 2
Temos ainda, as seguintes outras op��es:

.in +3
.ip -d
Se <nome> for um diret�rio, informa sobre o pr�prio diret�rio
(e n�o sobre o seu conte�do); � normalmente usado
em conjunto com "-l" para obter o estado de um diret�rio.

.ip -i
D� tamb�m o n�mero do n�-�ndice do arquivo.

.ip -t
Ordena os arquivos pela data da �ltima modifica��o, ao inv�s de
alfabeticamente pelo nome do arquivo, como � usual.

.ip -a
D� informa��es sobre todas as entradas; normalmente as informa��es
sobre as entradas "." e ".." s�o suprimidas.

.ip -R
Lista os conte�dos dos subdiret�rios encontrados recursivamente.
Deste modo, podemos obter caracter�sticas de todos os arquivos de uma �rvore.

.ip -N
L� os <nome>s dos arquivos da entrada padr�o.

.ep
.in -3

.sp 2
O tipo/modo/prote��o do arquivo dado pela op��o "-L" tem a forma:
.nf

		"R 7654321mtsg rwxrwxrwx"
.fi

.sp
onde o primeiro caractere indica o tipo de arquivo:

.sp
.in +3
.wo 'R  '
Arquivo regular
.br
.wo 'B  '
Dispositivo especial de blocos (estruturado)
.br
.wo 'C  '
Dispositivo especial de caracteres (n�o estruturado)
.br
.wo 'L  '
Elo simb�lico
.br
.wo 'D  '
Diret�rio
.br
.wo 'F  '
"Fifo"
.br
.wo '?  '
Arquivo de tipo inv�lido
.br
.in -3

.sp
Ap�s o tipo do arquivo, temos ent�o 11  caracteres relativos aos atributos
do arquivo. Se algum indicador estiver desligado, o caracter
assume o valor '-' ao inv�s do caracter indicado acima.
Os indicadores de nomes provis�rios "7" a "1" ainda n�o s�o usados
e est�o reservados para uso futuro. os 4 restantes s�o:

.in +3
.ip 'm  '
(S_IMETX)
Uma imagem do programa � guardada na mem�ria interna
ap�s a execu��o, mesmo que n�o haja mais usu�rios do programa.

.ip 't  '
(S_ISVTX)
Uma imagem do programa � guardada na �rea de SWAP (em disco)
ap�s a execu��o, mesmo que n�o haja mais usu�rios do programa.

.ip 's  '
(S_ISUID)
O UID efetivo do processo passa a ser igual ao
dono do arquivo quando o arquivo � executado como um programa
("set user ID"). 

.ip 'g  '
(S_ISGID)
O GID efetivo do processo passa a ser igual ao
grupo do arquivo quando o arquivo � executado como um programa
("set group ID"). 

.ep
.in -3

.sp
Para mais informa��es sobre os diversos atributos, veja "chmod" (sys).

.sp
Os �ltimos 9 caracteres referem-se ao modo de prote��o do arquivo,
dividido em 3 grupos de 3 caracteres.
O primeiro grupo de 3 caracteres d� a prote��o para o dono. Esta prote��o
cont�m a permiss�o para leitura (1. caractere), escrita (2. caractere)
e execu��o (arquivo regular)/pesquisa (diret�rio) (3. caractere) do arquivo,
de acordo com o seguinte c�digo:

.sp
.in +9
.wo 'r  '
permiss�o para leitura
.br
.wo 'w  '
permiss�o para escrita
.br
.wo 'x  '
permiss�o para execu��o/pesquisa
.br
.wo '-  '
sem a permiss�o correspondente
.in -9

.sp
Analogamente, os tr�s caracteres seguintes indicam a prote��o
relativa a usu�rios do mesmo grupo do arquivo, e os �ltimos tr�s
a prote��o relativa os demais usu�rios.

.sp
O tipo/prote��o do arquivo dado pela op��o "-l" tem a forma:
.nf

		"R rwxrwxrwx"

.fi
que � uma simplifica��o da forma acima, onde o grupo central � suprimido.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
chmod
.br
.wo "(sys): "
intro, chmod
.br
.wo "(libc):"
modetostr
.br

.in
.sp
.b ARQUIVOS
.in 5
 /etc/passwd
 /etc/group

.in
.sp
.b EXEMPLO
.r
.in 5
Uma execu��o do comando "ls -l ls" poder� imprimir:
.br
.nf

	R rwxr-x--x 1 <root> <sys>  5288  21:26:05 2005 18 set  ls

.fi
o que significa que "ls" � um arquivo regular,
com permiss�o para leitura, escrita e execu��o para o dono,
leitura e execu��o para os usu�rios do mesmo grupo
e de execu��o para os outros usu�rios.
O dono do arquivo � "root" e o seu grupo � "sys".
Vemos ainda, que o arquivo possui 5288 bytes, e a �ltima modifica��o
no arquivo foi feita �s 21 horas, 26 minutos e 5 segundos de 18 de setembro de 2005.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
