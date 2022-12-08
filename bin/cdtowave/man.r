.bp
.he 'CDTOWAVE (cmd)'TROPIX: Manual de Refer�ncia'CDTOWAVE (cmd)'
.fo 'Atualizado em 03.04.00'Vers�o 3.2.3'Pag. %'

.b NOME
.in 5
.wo "cdtowave -"
extrai faixas de CDs de audio
.br

.in
.sp
.b SINTAXE
.in 5
.(l
cdtowave [-vt] [-s <inicial>] [-f <final>] [-o <arq>] [<dev>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "cdtowave" permite extrair faixas de �udio em CDs,
gerando a sa�da em formato WAVE.

.sp
As op��es do comando s�o:

.in +3
.ip -e
Ejeta o CD.

.ip -s
Come�a a extra��o a partir da faixa <inicial>. O default � 1.

.ip -f
Encerra a extra��o na faixa <final>. O default � a faixa inicial.

.ip -o
Gera o arquivo <arq> com o resultado da extra��o. Se omitida, � 
assumida a sa�da padr�o.

.ip -t
Mostra o conte�do do CD (TOC).

.ip -v
Diz, a cada passo, quantos blocos faltam para completar a extra��o.

.ep
.in -3

.sp
Se invocado sem argumentos, o programa "cdtowave" extrai a
primeira faixa do CD.
.sp
Se <dev> for omitido, � assumido "/dev/cdrom".

.in
.sp
.b OBSERVA��O
.in 5

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
cdplay
.r
.in 5
.wo "(cmd): "
sbwave
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
