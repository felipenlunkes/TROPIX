.bp
.he 'UNTEXT (cmd)'TROPIX: Manual de Refer�ncia'UNTEXT (cmd)'
.fo 'Atualizado em 14.07.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
.wo "untext -"
libera os recursos de programas reentrantes
.br

.in
.sp
.b SINTAXE
.in 5
.(l
untext <texto> ...
.)l

.in
.sp
.b DESCRI��O
.in 5
Um programa reentrante ("texto") ocupa uma s�rie de recursos do sistema
operacional, e em particular,
regi�es da mem�ria interna e da �rea de "swap" em disco.

.sp
Se um programa reentrante tiver o indicador "m" ligado (ver "chmod" (cmd)),
a mem�ria interna continua ocupada, mesmo quando o programa
n�o tiver mais nenhum usu�rio.

.sp
� aconselhavel liberar os recursos ocupados por programas reentrantes,
quando se sabe que eles n�o ser�o utilizados durante algum tempo.

.sp
Para liberar os recursos de um programa <texto>, "untext" realiza
uma busca nos v�rios diret�rios da vari�vel do ambiente "PATH"
(ver "environ" (fmt)).
A busca termina quando � encontrado um arquivo com o nome dado, ou
a lista de diret�rios termina.

.in
.sp
.b OBSERVA��ES
.in 5
Se o nome do arquivo dado contiver um "/",
este nome � considerado o nome definitivo, e a busca n�o � realizada.

.sp
Se o ambinte n�o contiver a vari�vel "PATH", ser� utilizado 
o valor ".:/bin:/usr/bin".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
cc, ld, chmod (op��es "-m", "-t"), textmap
.br
.wo "(sys): "
untext
.br
.wo "(fmt): "
environ
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.
