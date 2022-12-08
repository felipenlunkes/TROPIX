.bp
.he 'LN (cmd)'TROPIX: Manual de Refer�ncia'LN (cmd)'
.fo 'Atualizado em 22.04.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "ln -"
cria elos (f�sicos ou simb�licos) para arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
ln [-sifv] <arquivo1> <arquivo2>
ln [-sifv] <arquivo1> [<arquivo2> ...] <diret�rio>
ln [-sifv] -N <diret�rio>
.)l

.in
.sp
.b DESCRI��O
.in 5
Um elo (f�sico ou simb�lico) � uma refer�ncia a um arquivo,
que lhe d� um nome (ou seja, um caminho). 
Um arquivo (juntamente com seu tamanho, informa��es sobre prote��o, ...)
pode ter v�rias refer�ncias (isto �, v�rios nomes).
N�o h� distin��o entre o arquivo referido por interm�dio de cada um
de seus nomes; qualquer mudan�a realizada no arquivo independe
do nome utilizado.

.sp
Um elo f�sico ("hard link") � uma entrada de um diret�rio contendo um nome.
Um arquivo pode ter v�rios elos f�sicos, todos tendo o mesmo estado,
isto �, n�o h� o elo f�sico "original".
Todos os elos f�sicos de um arquivo devem estar no mesmo sistema de arquivos.

.sp
Um elo simb�lico ("soft link") � um pequeno arquivo especial cujo conte�do
� o nome de um outro arquivo.
Um elo simb�lico pode referenciar um arquivo de um outro sistema de arquivos.

.sp
Em sua primeira forma, o comando "ln" cria a nova entrada de diret�rio 
<arquivo2> para <arquivo1>.

.sp
Na segunda forma, s�o criadas novas entradas para
<arquivo1>, <arquivo2> ..., no <diret�rio> especificado.

.sp
A terceira forma � an�loga � segunda, com exce��o dos nomes
dos <arquivo>s, que s�o lidos da entrada padr�o, um por linha.

.sp
As op��es do comando s�o:

.in +3
.ip -s
Cria um elo simb�lico (ao inv�s de f�sico).

.ip -i
Modo interativo:
� pedida a confirma��o do usu�rio para cada elo a criar. 

.ip -f
Se o arquivo destino j� existir, "ln" normalmente pede permiss�o
ao usu�rio para remov�-lo. Com esta op��o, o arquivo �
removido silenciosamente.

.ip -v
Lista os nomes dos elos que est�o sendo criados.

.ip -N
L� os nomes dos <arquivo>s da entrada padr�o 
(usado para a terceira forma).

.ep
.in -3

.in
.lp
.b
OBSERVA��ES
.r
.in 5
N�o � permitido criar elos f�sicos para diret�rios.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
rm, cp, mv
.br

.in
.sp 2
.b ESTADO
.in 5
Efetivo.
.in
