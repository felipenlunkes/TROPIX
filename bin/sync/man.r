.bp 1
.he 'SYNC (cmd)'TROPIX: Manual de Refer�ncia'SYNC (cmd)'
.fo 'Atualizado em 12.07.97'Vers�o 3.0.1'Pag. %'

.b NOME
.in 5
sync - atualiza o conte�do dos discos

.in
.sp
.b SINTAXE
.in 5
sync

.in
.sp
.b DESCRI��O
.in 5
O comando
"sync" atualiza o conte�do do disco
escrevendo todas as informa��es contidas no sistema operacional
que ainda est�o mais atuais na mem�ria do que no disco.
Isto inclui superblocos modificados, n�s-�ndices modificados
e blocos de E/S ainda n�o escritos.
.sp
Somente o superusu�rio pode utilizar este comando, 
e sua utiliza��o � essencial
antes de um "boot".

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
 (cmd): update
 (sys): sync

.in
.sp
.b ESTADO
.in 5
Efetivo.
.in
