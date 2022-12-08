.bp
.he 'STRIP (cmd)'TROPIX: Manual de Refer�ncia'STRIP (cmd)'
.fo 'Atualizado em 06.06.02'Vers�o 4.3.0'Pag. %'

.b NOME
.in 5
.wo "strip -"
remove as tabelas de s�mbolos e depura��o de m�dulos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
strip [-wN] [<m�dulo> ...] 
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "strip" remove a tabela de s�mbolos, a informa��o de reloca��o,
a tabela de linhas e a tabela de depura��o dos <m�dulo>s-objeto dados.
O objetivo desta remo��o � a redu��o do espa�o usado pelo <m�dulo> em disco.

.sp
Uma vez removidas estas informa��es de um m�dulo execut�vel,
n�o podemos mais depur�-lo atrav�s de "wsdb" (cmd),
nem consultar a sua tabela de s�mbolos atrav�s de "nm" (cmd)
(veja a op��o "-w").

.sp
No caso de uma biblioteca compartilhada, s�o removidas as tabelas de s�mbolos
e de m�dulos. Ap�s esta remo��o, n�o � mais poss�vel usar a biblioteca para
"link-edi��es" (ver "ld" (cmd)), nem para a gera��o de vers�es mais novas
da biblioteca  (ver "mkshlib" (cmd)).

.sp
Se n�o for dado nenhum <m�dulo> (nem a op��o "-N"),
ser� considerado o m�dulo "a.out".

.sp
O efeito de "strip" � o mesmo da op��o "-s" de "cc" ou "ld" (cmd).

.sp
As op��es do comando s�o:

.in +3
.ip -w
Remove apenas as tabelas de linhas e de depura��o.
A tabela de s�mbolos e as informa��es de reloca��o s�o mantidas,
o que significa que continuaremos podendo consultar a sua tabela de
s�mbolos atrav�s de "nm".

.ip -N
L� os nomes dos m�dulos de "stdin".

.ep
.in -3

.in
.sp
.b OBSERVA��O
.in 5
Um programa compilado com a op��o "-w" de "cc" (cmd) para conter
as tabelas de depura��o, seguido da remo��o destas tabelas atrav�s
de "strip" n�o ser� id�ntico ao programa compilado sem a op��o "-w".
Isto ocorre, porque o compilador "C" realiza outras modifica��es al�m
de gerar a tabela (como por exemplo, n�o considerar a declara��o "register").

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
cc, ld, wsdb, nm, mkshlib
.br
.wo "(fmt): "
a.out
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
