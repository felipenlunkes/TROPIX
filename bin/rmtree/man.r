.bp
.he 'RMTREE (cmd)'TROPIX: Manual de Refer�ncia'RMTREE (cmd)'
.fo 'Atualizado em 26.04.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "rmtree -"
remove �rvores
.br

.in
.sp
.b SINTAXE
.in 5
.(l
rmtree [-vfs] [-p "<padr�es>"] <�rvore> ...
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "rmtree" caminha cada uma das <�rvore>s dadas e remove
seletivamente cada arquivo encontrado, de acordo com as op��es e/ou
confirma��o do usu�rio.

.sp
As op��es do comando s�o:

.in +3
.ip --
Se n�o for dada a opc�o "-f", "rmtree" funciona interativamente:
� pedida a confirma��o do usu�rio para cada diret�rio a percorrer e
para cada arquivo/diret�rio a remover.
Se for negada a confirma��o para percorrer certo diret�rio,
ser� pulada toda a sub-�rvore definida por este diret�rio.

.ip -v
No caso de uso n�o interativo, esta op��o pode ser usada
para imprimir os nomes do arquivos/diret�rios sendo removidos.

.ip -f
Normalmente o comando � interativo. Com esta op��o ele deixa de ser interativo,
percorrendo os diret�rios e removendo os arquivos/diret�rios
sem consultar o usu�rio.

.sp
Um outro m�todo de evitar as consultas � a de responder com letras
ma�usculas: com a resposta "S" ou "Y" todas as perguntas seguintes
ser�o automaticamente respondidas afirmativamente, e (analogamente)
com a resposta "N" ser�o respondidadas negativamente
(veja "askyesno" (libc)).

.ip "-s"
Esta op��o � a abreviatura de
.sp
.nf
			-p "*[Mm]akefile *.[cshryv]"
.fi
.sp
e � �til para selecionar arquivos relacionados com a linguagem "C".
Padr�es adicionais podem ser dados com a op��o "-p" (veja abaixo).

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
.b OBSERVA��O
.in 5
Como � desej�vel, o comando s� remove um diret�rio se todos os arquivos
nele contidos forem tambem removidos.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
rm, rmdir
.br
.wo "(libc): "
askyesno
.br

.in
.sp
.(t
.b EXEMPLOS
.in 5
O comando
.ce
rmtree -f /alpha/beta
.sp
ir� remover completamente a �rvore "/alpha/beta", enquanto que
.sp
.ce
rmtree -f -p "*.o" /alpha/beta
.sp
ir� remover todos os m�dulos objeto nela contidos, e mais os diret�rios
que eventualmente ficaram vazios com a remo��o dos m�dulos objeto. 
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
