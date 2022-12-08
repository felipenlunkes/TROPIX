.bp
.he 'FDFORMAT (cmd)'TROPIX: Manual de Refer�ncia'FDFORMAT (cmd)'
.fo 'Atualizado em 13.05.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "fdformat -"
formata disquetes
.br

.in
.sp
.b SINTAXE
.in 5
.(l
fdformat [-fvt] [-s <tamanho>] [-e <entre>] [-01] [<dispositivo>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O utilit�rio "fdformat" formata o disquete <dispositivo>.
Este <dispositivo> deve ser dado na forma "n�o estruturada"
(de caracteres), "/dev/rfd0" ou "/dev/rfd1".

.sp
Na presente vers�o, "fdformat" processa os sequintes formatos:

.bc	/*************************************/
   |    3�"   |  1722   |     82    |     21     |  3444  |
.ec	/*************************************/

.sp
.(l
   +----------+---------+-----------+------------+--------+
   | Diametro | Tamanho | Cilindros |   Setores  | Blocos |
   |          |  (KB)   |           | por trilha |        |
   +----------+---------+-----------+------------+--------+
   |    3�"   |  1440   |     80    |     18     |  2880  |
   |    3�"   |   720   |     80    |      9     |  1440  |
   |          |         |           |            |        |
   |    5�"   |  1200   |     80    |     15     |  2400  |
   |    5�"   |   360   |     40    |      9     |   720  |
   +----------+---------+-----------+------------+--------+
.)l

.sp
Um par�metro importante a ser considerado na formata��o de disquetes
� o fator de entrela�amento, que define a posi��o de cada setor
dentro da trilha.
Com o fator de entrela�amento 1, isto �, com a numera��o seq�encial
dos setores na forma

.sp
.nf
		1 2 3 4 5 6 7 8 9
.fi
.sp
possivelmente a leitura/escrita do disquete ser� lenta.
Isto ocorre porque entre a leitura/escrita de dois setores seguidos (5 e 6,
por exemplo) n�o h� uma "pausa" necess�ria para a prepara��o da
leitura/escrita seguinte.
Isto significa que quando for iniciada a opera��o para acessar o setor 6,
a cabe�a de leitura/escrita ter� acabado de passar por ele, for�ando
uma rota��o extra do disquete.

.sp
Por outro lado, com o fator de entrela�amento 2 teremos a disposi��o
da forma

.sp
.nf
		1 6 2 7 3 8 4 9 5
.fi
.sp
com a qual (por exemplo, ap�s a leitura do setor 7),
temos o tempo durante a cabe�a est� em cima do setor 3
para preparar a leitura/escrita do setor 8.
Desta maneira evitamos a rota��o sup�rflua e aumentamos a velocidade
do dispositivo. 

.sp
Os valores por omiss�o do fator de entrela�amento
� 2 para o tamanho de 1200 KB, e 1 para os demais.
.bc	/*************************************/
s�o 2 para os tamanhos de 1722 e 1200 KB, e 1 para os demais.
.ec	/*************************************/

.sp
.(t
As op��es do comando s�o:

.in +3
.ip -f
Normalmente, o comando pede uma confirma��o do usu�rio antes de
efetivamente iniciar a formata��o (que ir� destruir o conte�do
antigo do disquete).
Com a op��o "-f", esta confirma��o n�o � pedida.
.)t

.ip -v
Verboso: com esta op��o, s�o dados as seguintes informa��es sobre
a formata��o: n�mero de setores por trilha, n�mero de cilindros,
n�mero total de setores e o entrela�amento usado.

.ip -t
Apenas identifica��o: com esta op��o, o comando ao inv�s de formatar o
disquete, apenas tenta descobrir se o disquete j� est� formatado,
e (se sim) com qual formata��o.

.ip -s
Tamanho do conte�do do disquete: o <tamanho> dado deve ser um dos
tamanhos em KB da tabela acima. Se esta op��o n�o for dada, �
assumido o tamanho "1440".
.bc	/*************************************/
assumido o tamanho "1722".
.ec	/*************************************/

.sp
Podem tamb�m ser usados os seguintes
.bc	/*************************************/
sin�nimos: "1.72" para "1722", "1.44" para "1440", "1.2" para "1200",
.ec	/*************************************/
sin�nimos: "1.44" para "1440", "1.2" para "1200",
".72", "0.72" para 720 e ".36", "0.36" para 360.

.ip -e
Usa o fator de entrela�amento <entre> ao inv�s do valor por omiss�o
(comentado acima).

.ip -0
Uma abrevia��o para o <dispositivo> "/dev/rfd0".

.ip -1
Uma abrevia��o para o <dispositivo> "/dev/rfd1".

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
gar, dosmp
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
