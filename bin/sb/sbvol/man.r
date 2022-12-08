.bp
.he 'SBVOL (cmd)'TROPIX: Manual de Refer�ncia'SBVOL (cmd)'
.fo 'Atualizado em 15.4.00'Vers�o 3.2.3'Pag. %'

.b NOME
.in 5
.wo "sbvol -"
controla o volume da placa de som SB-16
.br

.in
.sp
.b SINTAXE
.in 5
.(l
sbvol [-v] [-s <vol>]
sbvol+
sbvol-
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "sbvol" � um utilit�rio simples para controlar o volume mestre
da placa de som "Sound Blaster 16" ou sucessoras
("AWE-32", "AWE-64", ...).

.sp
Nesta vers�o, s�o controlados apenas os volumes mestres dos canais esquerdo
e direto simultaneamente.

.sp
Sem op��es, "sbvol" informa o volume atual (0 a 100 \%).

.sp
Na forma "sbvol+" aumenta o volume de aproximadamente 5 \%.

.sp
Na forma "sbvol-" diminui o volume de aproximadamente 5 \%.

.sp
As op��es do comando s�o:

.in +3
.ip "-v" 9
Verboso.

.ip "-s <vol>" 9
O volume passa a ser <vol> \%.

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
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
