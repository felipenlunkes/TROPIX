.bp 1
.he 'SIGTOSTR (libc)'TROPIX: Manual de Refer�ncia'SIGTOSTR (libc)'
.fo 'Atualizado em 26.06.95'Vers�o 3.0'Pag. %'

.b NOME
.in 5
sigtostr - obt�m a descri��o de um sinal

.in
.sp
.b SINTAXE
.(l
#include <signal.h>

const char	*sigtostr (int signum)
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "sigtostr" devolve um ponteiro
para uma cadeia com o nome e a descri��o do sinal "signum".

.sp
Os primeiros 8 caracteres cont�m o nome do sinal,
enquanto que os caracteres  restantes descrevem o sinal.
A cadeia N�O cont�m um <nl> no final.

.in
.sp
.b DIAGN�STICOS
.in 5
Se "signum" contiver um n�mero de sinal inv�lido, "sigtostr" devolver�
"Sinal  desconhecido".

.sp
Se "signum" contiver 0, "sigtostr" devolver�
"SIGNULL: Sinal NULO".

.in
.sp
.b
VEJA TAMB�M
.r
.nf
     (cmd): kill
     (sys): signal
.fi

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
