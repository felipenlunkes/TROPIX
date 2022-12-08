.bp
.he 'CDPLAY (cmd)'TROPIX: Manual de Refer�ncia'CDPLAY (cmd)'
.fo 'Atualizado em 19.3.00'Vers�o 3.2.3'Pag. %'

.b NOME
.in 5
.wo "cdplay -"
reproduz faixas de CDs
.br

.in
.sp
.b SINTAXE
.in 5
.(l
cdplay [-prt] [-s <inicial>] [-f <final>] [<dev>]
cdplay+
cdplay-
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "cdplay" permite reproduzir faixas de �udio em CDs.

.sp
As op��es do comando s�o:

.in +3
.ip -p
Suspende a reprodu��o. Se esta op��o for dada duas vezes ("cdplay -pp"),
a reprodu��o � definitivamente interrompida, sem possibilidade de continu�-la.

.ip -r
Reinicia a reprodu��o, do ponto onde foi suspensa.

.ip -t
Mostra o conte�do do CD (Table of Contents).

.ip -s
Come�a a reprodu��o na faixa <inicial>.

.ip -f
Encerra a reprodu��o na faixa <final>.

.ep
.in -3

.sp
Se invocado sem argumentos, o programa "cdplay" funciona da seguinte
maneira: havendo reprodu��o em andamento, todo o CD � reproduzido;
caso contr�rio, o programa informa qual faixa est� sendo reproduzida.
.sp
"cdplay+" avan�a a reprodu��o, se poss�vel, para a faixa seguinte.
Caso n�o haja reprodu��o em andamento, � equivalente a "cdplay".
.sp
"cdplay-" reinicia a reprodu��o, se poss�vel, na faixa anterior.
Caso n�o haja reprodu��o em andamento, � equivalente a "cdplay".
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
dosmp
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
