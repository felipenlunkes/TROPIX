.bp
.he 'RM (cmd)'TROPIX: Manual de Refer�ncia'RM (cmd)'
.fo 'Atualizado em 02.05.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "rm -"
remove arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
rm [-fivN] [<arquivo> ...]
.)l

.in
.sp
.b DESCRI��O
.in 5
Para cada nome de <arquivo> dado, o comando "rm" remove a entrada
do seu respectivo diret�rio (elo f�sico).
No entando, o arquivo s� � efetivamente removido se este elo f�sico era o �ltimo.
.bc	/*************************************/
Se este elo a entrada referente a este nome era a �ltima (ou a �nica) do arquivo,
ent�o este arquivo � removido.
.ec	/*************************************/
Se n�o era o caso, o arquivo � conservado,
mas n�o pode mais ser acessado pelo nome removido.

.sp
Se o nome do <arquivo> for o de um elo simb�lico, este elo simb�lico � removido,
e n�o o arquivo referenciado.

.sp
A remo��o de um arquivo requer permiss�o de
escrita em seu diret�rio, mas n�o s�o necess�rias
permiss�es de leitura nem de escrita no pr�prio arquivo.

.sp
Para maior seguran�a, o comando "rm" � normalmente interativo,
isto �, ele pede a confirma��o do usu�rio para cada remo��o.
Al�m disto, o usu�rio � normalmente informado caso o arquivo n�o possua
permiss�o de escrita (veja a op��o "-f", abaixo). 

.sp
As op��es do comando s�o:

.in +3

.ip -i
Pede confirma��o do usu�rio para a remo��o de cada arquivo
(modo normal).

.ip -f
Remove o arquivo sem pedir confirma��o do usu�rio,
mesmo que o arquivo n�o possua permiss�o de escrita. 

.sp
Um outro m�todo de evitar as consultas � a de responder com letras
ma�usculas: com a resposta "S" ou "Y" todas as perguntas seguintes
ser�o automaticamente respondidas afirmativamente, e (analogamente)
com a resposta "N" ser�o respondidadas negativamente
(veja "askyesno" (libc)).

.ip -v
Lista os nomes dos <arquivo>s sendo removidos.
Isto � �til em conjunto com as op��es "-f" e "-N".

.ip -N
L� os nomes dos arquivos da entrada padr�o.
Esta op��o � impl�cita se n�o forem dados <arquivo>s.

.ep
.in -3

.in
.sp
.b OBSERVA��O
.in 5
O comando "rm" N�O remove diret�rios nem �rvores. 
Para estas fun��es deve-se utilizar respectivamente "rmdir" e "rmtree" (cmd).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
rmdir, rmtree
.br
.wo "(sys): "
unlink
.br
.wo "(libc):"
askyesno
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
