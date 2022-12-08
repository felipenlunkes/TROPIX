.bp
.he 'T_PUSH (xti)'TROPIX: Manual de Refer�ncia'T_PUSH (xti)'
.fo 'Escrito em 04.08.92'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_push -"
transmite um segmento incompleto
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_push (int fd);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_push" transmite efetivamente um segmento que n�o tenha
sido completado no �ltimo "t_snd" relativo ao "endpoint" de
transporte "fd".

.sp
.(l
	    +--------------------+------------+------------+
	    |   Argumentos	 | Na chamada | No retorno |
	    +--------------------+------------+------------+
	    | fd		 |     x      |     /      |
	    +--------------------+------------+------------+
.)l

.sp
Por quest�es de efici�ncia, no modo-com-conex�o, os segmentos s� s�o
transmitidos quando completam o tamanho dado pelo membro "max_seg_size"
da estrutura "TCP_OPTIONS" (veja "t_optmgmt" (xti)).

.sp
Em certas situa��es, no entanto, � necess�rio transmitir o segmento
mesmo estando incompleto. Para isto, podemos utilizar o indicador
"T_PUSH" (veja "t_snd" (xti)) ou ent�o chamar a fun��o "t_push" ap�s o
"t_snd".

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Esta fun��o n�o faz parte da XTI, e portanto seu uso deve ser evitado
se for desejada portabilidade para outras implementa��es.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso a fun��o devolve 0.
Em caso contr�rio, devolve -1 e indica em "t_errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(xti): "
t_snd, t_optmgmt
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
