.bp
.he 'HPPRINT (cmd)'TROPIX: Manual de Refer�ncia'HPPRINT (cmd)'
.fo 'Atualizado em 30.12.04'Vers�o 4.7.0'Pag. %'

.b NOME
.in 5
.wo "hpprint -"
ferramenta de impress�o para as impressoras HP
.br

.in
.sp
.b SINTAXE
.in 5
.(l
hpprint [-qvcN] [-P <dev>] [-p <papel>] [-l <nl>]
                [-t <tab>] [-o <nc>] [-CM] [<arquivo> ...]
.)l

.in
.sp
.b DESCRI��O
.in 5
O utilit�rio "hpprint" destina-se a facilitar a impress�o de textos
nas impressoras HP (e outras marcas) que utilizam a linguagem de controle "PCL".

.sp
Por omiss�o, "hpprint" imprime os textos com qualidade de rascunho, 75 linhas
por p�gina, 8 caracteres por tabula��o e sem margem � esquerda.

.sp
As op��es do comando s�o:

.in +3
.ip -q 11
Impress�o de boa qualidade (ao inv�s de rascunho).

.ip -v 11
Verboso (imprime estat�sticas na sa�da padr�o).

.ip -c 11
Utiliza caracteres comprimidos.

.ip -N 11
Obt�m os nomes dos arquivos a imprimir da entrada padr�o.

.ip "-P <dev>" 11
Imprime no dispositivo <dev> ao inv�s de "/dev/lp".

.ip "-p <papel>" 11
O papel sendo usado � "A4" ou "CARTA" (por omiss�o "A4").

.ip "-l <nl>" 11
Utiliza <nl> linhas/p�gina (ao inv�s de 75).

.ip "-l <tab>" 11
Utiliza <tab> como tamanho do tabulador ao inv�s de 8).

.ip "-o <nc>" 11
Utiliza um margem esquerda de <nc> colunas.

.ip "-C" 11
Impress�o de programas em "C" (equivalente �s op��es "-c -l 75 -o 16").

.ip "-M" 11
Impress�o de manuais (equivalente �s op��es "-c -l 75 -o 16").

.ep
.in -3

.in
.sp
.b OBSERVA��O
.in 5
Lembre-se de que "hpprint" N�O escreve cabe�alhos nem numera as
p�ginas; para isto use o comando "pr" (cmd).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
pr
.br

.in
.sp
.(t
.b EXEMPLO
.in 7
Pagina e imprime um programa em "C":
.)t

.sp
.(l
		pr alpha.c | hpprint -C
.)l

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
