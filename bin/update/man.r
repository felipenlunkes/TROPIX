.bp
.he 'UPDATE (cmd)'TROPIX: Manual de Refer�ncia'UPDATE (cmd)'
.fo 'Atualizado em 14.07.97'Vers�o 3.0.0'Pag. %'

.b NOME
.in 5
.wo "update -"
atualiza os sistemas de arquivos periodicamente
.br

.in
.sp
.b SINTAXE
.in 5
.(l
update [<n>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando "update" atualiza periodicamente o conte�do dos diversos
sistemas de arquivos em disco.
Isto � realizado atrav�s da escrita de todas as informa��es contidas no
sistema operacional que ainda est�o mais atuais na mem�ria do que no disco.
Entre estas informa��es est�o os superblocos modificados, os n�s-�ndices
modificados e os blocos de E/S ainda n�o escritos.

.sp
O argumento <n> indica a periodicidade (em segundos) das atualiza��es.
Se <n> n�o for dado, s�o feitas atualiza��es a cada 30 segundos.

.sp
O comando "update", ao ser chamado, inicia um processo que
n�o tem fim. Ele foi concebido para ser utilizado
apenas pelo administrador do sistema operacional.

.in
.sp
.b OBSERVA��O
.in 5
O par�metro <n> n�o deve ser muito grande, pois se ocorrer
uma falha no sistema ("crash") e a �ltima atualiza��o tiver
sido feita h� muito tempo, � prov�vel que o disco esteja
com muitos blocos desatualizados. Por outro lado, se <n> 
tiver um valor muito
baixo, o desempenho do sistema pode ser afetado.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sync
.br
.wo "(sys): "
sync
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
