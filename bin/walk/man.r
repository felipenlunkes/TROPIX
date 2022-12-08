.bp
.he 'WALK (cmd)'TROPIX: Manual de Refer�ncia'WALK (cmd)'
.fo 'Atualizado em 25.04.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "walk -"
caminha em �rvores do sistema de arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
walk [rdbclfamL.N] [<�rvore> ...]

Valores de <PAD>: [-s] [-p "<p>"] [-P "<P>"]
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "walk" caminha em cada <�rvore> dada do sistema de arquivos
e escreve os nomes completos dos arquivos selecionados (ver as op��es)
na sa�da padr�o, um por linha.

.sp
As op��es do comando s�o:

.in +3
.ip "--"
Sem nenhuma das op��es "-rdbclfa" (veja abaixo) seleciona todos os tipos 
de arquivos exceto diret�rios.

.ip "-r"
Seleciona arquivos regulares.

.ip "-d"
Seleciona diret�rios.

.ip "-b"
Seleciona arquivos especiais de bloco (estruturados).

.ip "-c"
Seleciona arquivos especiais de caracteres (n�o estruturados).

.ip "-l"
Seleciona elos simb�licos.

.ip "-f"
Seleciona FIFOs.

.ip "-a"
Seleciona todos os tipos de arquivos (equivalente a "-rdbcf").

.ip "-m"
Imprime um prefixo contendo o tipo do arquivo e o seu tamanho.

.ip "-L"
N�o seleciona nomes que correspondem a arquivos cujos conte�dos
j� foram selecionados anteriormente. 
Isto pode ocorrer quando um arquivo possui v�rios elos f�sicos.

.ip "-."
Seleciona tamb�m nomes de arquivos ocultos.
Normalmente, arquivos cujos nomes cont�m algum componente que
come�a com um ponto (exceto "..") n�o s�o selecionados
(como por exemplo "/usr/src/sys/.old/rot.c").
Esta op��o faz com que estes arquivos sejam tamb�m considerados.

.ip "-N"
L� os nomes das <�rvore>s da entrada padr�o.
Esta op��o � impl�cita se n�o forem dadas <�rvore>s.

.ip "-s"
Esta op��o � a abreviatura de
.sp
.nf
			-p "*[Mm]akefile *.[cshryv]"
.fi
.sp
e � �til para selecionar arquivos relacionados com a linguagem "C".
Padr�es adicionais podem ser dados com a op��o "-p" (veja abaixo).

.bc	/*************************************/
.ip -p
Padr�es de inclus�o:
tanto na entrada como na sa�da, podemos dar <padr�es>
(isto �, express�es regulares, como os
do "sh", formados com "*", "?", "!", "[...]") 
para a sele��o dos nomes dos arquivos desejados.
Repare que os <padr�es> s�o aplicados ao nome completo do arquivo,
de tal modo que podemos utilizar (por exemplo) um padr�o da forma "*/etc/*.c".
No momento podemos dar at� 20 <padr�es>, entre aspas, separados
por brancos ou tabula��es.
.ec	/*************************************/

.ip "-p"
Padr�es de inclus�o:
Seleciona apenas arquivos cujos nomes s�o aceitos por um dos <padr�es> dados.
Cada padr�o � uma express�o regular, como as do "sh" (cmd),
formada com "*", "?", "!", "[...]" (ver patmatch (libc)).
Os padr�es s�o aplicados ao nome completo do arquivo,
sem considerar o caractere "/" como especial.
Um caractere branco ou <ht> indica o final de um padr�o, de tal modo que
uma �nica op��o pode conter v�rios padr�es
(desde que venham entre aspas ou ap�strofes).
Ao total podemos ter at� 20 <padr�es>.

.ip -P
Padr�es de exclus�o:
Esta op��o � an�loga � op��o "-p", exceto que os padr�es s�o usados
para a exclus�o de arquivos (ao inv�s de inclus�o).
Todos os arquivos cujos nomes s�o
aceitos por estes padr�es n�o s�o selecionados, mesmo que tenham sido
aceitos pelos padr�es das op��es "-p" ou "-s".

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sh
.br
.wo "(libc):"
ftw, patmatch
.br

.(t
.in
.sp
.b EXEMPLO
.in 5
O comando
.sp
.nf
		walk -p "*env.c *man.r" /src/lib/libc
.fi

.sp
procura arquivos cujos nomes terminam em "env.c ou "man.r" na �rvore
cuja raiz � "/src/lib/libc" e produz (por exemplo)

.sp
.nf
		/src/lib/libc/etc/getenv/getenv.c
		/src/lib/libc/etc/putenv/putenv.c
		/src/lib/libc/etc/putenv/man.r
.fi
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.
