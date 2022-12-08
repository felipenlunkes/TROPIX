.bp 1
.he 'ABORT (libc)'TROPIX: Manual de Refer�ncia'ABORT (libc)'
.fo 'Atualizado em 06.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "abort  -"
termina o processo anormalmente
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <stdlib.h>

void	abort (void);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "abort" termina o processo anormalmente
(enviando o sinal "SIGABRT")
a n�o ser que este sinal seja interceptado,
e a fun��o interceptadora n�o retorne.

.sp
As fun��es registradas s�o chamadas (veja "atexit" (libc))
e os arquivos abertos t�m os seus conte�dos atualizados antes do t�rmino
do processo.

.sp
Se o sinal n�o tiver sido programado para ser ignorado ou interceptado,
uma imagem do processo � gravada em disco ("core dump").

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
A fun��o "abort" n�o pode retornar.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.br
.wo "(sys):  "
exit, kill, signal
.br
.wo "(libc): "
atexit

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
