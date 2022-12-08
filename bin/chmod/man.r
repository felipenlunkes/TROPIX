.bp 1
.he 'CHMOD (cmd)'TROPIX: Manual de Refer�ncia'CHMOD (cmd)'
.fo 'Atualizado em 08.05.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "chmod -"
modifica a permiss�o de acesso de arquivos

.in
.sp
.b SINTAXE
.in 5
.(l
chmod [-vN] <modo> [<arquivo> ...]
.)l

.in
.sp
.b DESCRI��O
.in 5
O modo de cada <arquivo> dado � alterado segundo o <modo> especificado,
que pode ser dado na forma absoluta ou simb�lica.
A filosofia de prote��o de acesso a arquivos pode ser vista em "intro" (sys).

.sp
As op��es do comando s�o:

.in +3
.ip -v
Lista os modos antigo e novo de cada <arquivo>.

.ip -N
Le os nomes dos arquivos da entrada padr�o.
Esta op��o � impl�cita se n�o forem dados <arquivo>s.

.ep
.in -3

.in
.sp
.b 'FORMA ABSOLUTA'
.in 5
A forma absoluta de um modo consiste de um n�mero inteiro,
representando o out�rio dos bites individuais de permiss�o
de acesso do arquivo, como descritos no arquivo <stat.h>. 
Em "chmod" (sys) temos uma descri��o mais detalhada de
cada bite.

.sp
O n�mero inteiro pode ser dado em decimal, hexadecimal ou octal
conforme as conven��es da linguagem "C" (veja "strtol" (libc)).

.in
.sp
.b 'FORMA SIMB�LICA'
.in 5
A forma simb�lico de um modo tem a forma:

.sp
.nf
		[<quem>] <op> [<permiss�o>]
.fi
.sp
O argumento <quem> � especificado atrav�s da combina��o das letras
"u" (para as permiss�es do dono), "g" (do grupo) e "o" (outros).
A letra "a" equivale a todas as letras ("ugo").
Se "quem" for omitido, � assumido "a".

.sp
O argumento <op> pode ser "+" para adicionar permiss�es ao modo do arquivo,
"-" para retirar permiss�es e "=" para atribuir permiss�es absolutamente
(todas as outras permiss�es ser�o negadas).

.sp
O argumento <permiss�o> � dado atrav�s da combina��o
das letras "r" (permiss�o de leitura), "w" (de escrita),
"x" (execu��o/pesquisa), "s" ("set user/group ID"),
"t" (mantenha o texto no swap) e "m" (mantenha o texto na mem�ria).
O argumento <quem> especifica a quem as
permiss�es se referem na modifica��o do modo atual. A omiss�o de
permiss�es � �til apenas em conjun��o com "=" para retirar todas as
permiss�es.

.sp
M�ltiplos modos simb�licos podem ser dados,
desde que estejam separados por v�rgulas.
Neste caso, as opera��es s�o efetuadas seq�encialmente
(onde uma opera��o eventualmente pode alterar uma a��o anterior).

.sp
A letra "s" significa "set user ID" em conjunto com "u",
e "set group ID" em conjunto com "g".

.sp
Somente o dono do arquivo (ou o superusu�rio) pode trocar o modo de um arquivo.
Somente o superusu�rio pode adicionar as permiss�es "t" e "m".

.in
.sp
.b OBSERVA��O
.in 5
Repare que usando a forma absoluta do modo, se o n�mero N�O come�ar
por 0, ele ser� interpretado como decimal, e N�O octal.
 
.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
ls
.br
.wo "(sys): "
intro, chmod, stat
.br
.wo "(libc):"
strtol
.br

.in
.sp
.b ARQUIVOS
.in 5
/usr/include/stat.h

.in
.sp
.b EXEMPLOS
.in 5
O comando
.sp
.nf
		chmod 0751 arquivo
.fi
.sp
altera o modo do arquivo para: permiss�o
para leitura, escrita e execu��o/pesquisa (0400 + 0200 + 0100) para o dono,
leitura e execu��o/pesquisa (0040 + 0010) para os usu�rios do mesmo grupo,
e somente permiss�o de execu��o para os demais usu�rios.

.sp 2
O comando
.sp
.nf
		chmod ug=r,u+w,a+x arquivo
.fi
.sp
� equivalente ao anterior.

.sp 2
O comando
.sp
.nf
		chmod =rwx,g+s arquivo
.fi
.sp
permite a todos ler, executar e executar/pesquisar o arquivo;
al�m disto, liga o bite de "set group ID".

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
