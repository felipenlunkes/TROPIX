.bp
.he 'MV (cmd)'TROPIX: Manual de Refer�ncia'MV (cmd)'
.fo 'Atualizado em 02.05.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "mv -"
move (troca o nome de) arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
mv [-ifv] <arquivo1> <arquivo2>
mv [-ifv] <arquivo1> [<arquivo2> ...] <diret�rio>
mv [-ifv] [-N] <diret�rio>
.)l

.in
.sp
.b DESCRI��O
.in 5
Em sua primeira forma, o comando "mv" move
(troca o nome de) <arquivo1> para <arquivo2>.

.sp
Na segunda forma, um ou mais <arquivo>s s�o movidos para o
<diret�rio> especificado, com seus nomes originais.

.sp
A terceira forma � an�loga � segunda, com exce��o dos nomes
dos <arquivo>s, que s�o lidos da entrada padr�o, um por linha.

.sp
As op��es do comando s�o:

.in +3

.ip -i
Modo interativo:
� pedida a confirma��o do usu�rio para cada arquivo a mover.

.ip -f
Se o arquivo destino j� existir, "mv" normalmente pede permiss�o
ao usu�rio para remov�-lo. Com esta op��o, o arquivo �
removido silenciosamente.

.ip -v
Lista os nomes dos arquivos que est�o sendo movidos.

.ip -N
L� os nomes dos <arquivo>s da entrada padr�o 
(usado para a terceira forma).
Esta op��o � impl�cita se  for dado apenas o nome do <diret�rio>.

.ep
.in -3

.in
.sp
.b OBSERVA��ES
.in 5
O comando "mv" n�o move diret�rios. Para esta fun��o deve-se utilizar
"mvtree" (cmd).

.sp
Se durante uma mudan�a, o comando perceber que o arquivo destino ir�
residir em um outro sistema de arquivos, "mv" copia o conte�do do arquivo,
removendo o original.
Ao realizar esta c�pia, "mv" tenta preservar o estado do arquivo
(dono, grupo, modo, datas, etc ...), o que s� � inteiramente
poss�vel se o usu�rio for superusu�rio.

.sp
Al�m disto, no caso de c�pia, as rela��es dos elos f�sicos dos arquivos originais
(apenas com arquivos tamb�m n�o movidos) s�o perdidas.

.sp
A mudan�a de elos simb�licos para outros diret�rios pode produzir
refer�ncias inexistentes.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
cp, ln, mvtree
.br

.in
.sp
.(t
.b ESTADO
.in 5
Efetivo.
.)t

.in
