.bp
.he 'SYNC (sys)'TROPIX: Manual de Refer�ncia'SYNC (sys)'
.fo 'Atualizado em 22.08.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "sync -"
atualiza o conte�do do disco
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <sys/syscall.h>

int	sync (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
A chamada ao sistema "sync" atualiza os conte�dos dos discos
escrevendo todas as informa��es contidas no sistema operacional
que ainda est�o mais atuais na mem�ria do que nos discos.
Isto inclui superblocos modificados, n�s-�ndices modificados
e blocos de E/S ainda n�o escritos.

.sp
Somente superusu�rios podem utilizar esta chamada,
que deve ser utilizada por programas que
examinam um sistema de arquivos, como por exemplo "fsck".
Sua utiliza��o � essencial antes de um "boot".

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso, a chamada ao sistema devolve zero.
Em caso contr�rio, devolve -1 e indica em "errno" a causa do erro.

.in
.sp
.b OBSERVA��O
.in 5
No TROPIX esta chamada ao sistema � s�ncrona, isto �,
ap�s o retorno com sucesso, as escritas no disco j� foram
completadas.

.in
.sp
.b ESTADO
.in 5
Efetivo.
