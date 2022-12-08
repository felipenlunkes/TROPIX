.bp
.he 'UNIQ (cmd)'TROPIX: Manual de Refer�ncia'UNIQ (cmd)'
.fo 'Atualizado em 13.07.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
.wo "uniq -"
indica linhas repetidas de um arquivo
.br

.in
.sp
.b SINTAXE
.in 5
.(l
uniq [-nudc] [-f <f>] [-b <b>] [<entrada> [<sa�da>]]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "uniq" l� o arquivo de <entrada> comparando linhas adjacentes.
No modo normal (sem op��es), "uniq" escreve o arquivo na <sa�da>,
mantendo apenas um exemplar de cada linha repetida.

.sp
Note que as linhas repetidas devem estar adjacentes para serem encontradas
(veja "sort" (cmd)).

.sp
Se <sa�da> n�o for dado, "uniq" escreve na sa�da padr�o.
Se <entrada> n�o for dado ou for "-", "uniq" l� da entrada padr�o.



.sp
As op��es do comando s�o:

.in +3
.ip -n
Mant�m apenas um exemplar de cada linha repetida (modo normal por omiss�o).

.ip -u
Escreve na <sa�da> apenas as linhas n�o repetidas.

.ip -d
Escreve na <sa�da> apenas um exemplar somente das linhas repetidas.

.ip -c
Escreve cada linha precedida de uma contagem de freq��ncia.

.ip -f
Na compara��o, ignora os <f> campos iniciais, juntamente com os brancos
(<sp> ou <ht>) que os delimitam. Um campo � definido como uma cadeia
de caracteres n�o-brancos delimitada por brancos.

.ip -b
Na compara��o, ignora os <b> caracteres iniciais.
Se for dada tamb�m a op��o "-f", os caracteres s�o pulados ap�s os campos.

.ep
.in -3

.in
.sp
.b OBSERVA��O
.in 5
Repare que sa�da do modo normal � a uni�o das sa�das dos modos
das op��es "-u" e "-d".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sort, comm
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
