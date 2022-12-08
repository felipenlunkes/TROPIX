.bp
.he 'T_GETSTATE (xti)'TROPIX: Manual de Refer�ncia'T_GETSTATE (xti)'
.fo 'Escrito em 14.05.92'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_getstate -"
obt�m o estado atual de um "endpoint"
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_getstate (int fd);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_getstate" retorna o estado corrente do sistema de transporte
associado ao "endpoint" especificado por "fd".

.sp
.(l
	    +--------------------+------------+------------+
	    |   Argumentos	 | Na chamada | No retorno |
	    +--------------------+------------+------------+
	    | fd		 |     x      |     /      |
	    +--------------------+------------+------------+
.)l

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de erro, a fun��o devolve -1 e indica em "t_errno" a causa do erro.
Em caso de sucesso devolve um dos estados correntes da tabela abaixo:

.sp
.(t
.(l
	+---------------+-------------------------------+
	|    Estado	|	   Descri��o		|
	+---------------+-------------------------------+
	| T_UNINIT	| N�o inicializado - estado	|
	|		| inicial e final da interface	|
	+---------------+-------------------------------+
	| T_UNBND	| Inicializado, mas sem endere�o|
	+---------------+-------------------------------+
	| T_IDLE	| Inicializado e com endere�o,	|
	|		| mas sem conex�o		|
	+---------------+-------------------------------+
	| T_OUTCON	| Aguardando resposta de um	|
	|		| pedido de conex�o (cliente)	|
	+---------------+-------------------------------+
	| T_INCON	| Aguardando um	pedido de	|
	|		| conex�o (servidor)		|
	+---------------+-------------------------------+
	| T_DATAXFER	| Transferindo dados		|
	+---------------+-------------------------------+
	| T_OUTREL	| Aguardando resposta de um	|
	|		| pedido de desconex�o ordenada	|
	+---------------+-------------------------------+
	| T_INREL	| Aguardando um	pedido de	|
	|		| desconex�o ordenada		|
	+---------------+-------------------------------+
.)l
.)t

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(xti): "
t_open
.br

.in
.sp
.b
REFER�NCIAS
.r
.in 5
"X/OPEN Portability Guide: Networking Services",
X/OPEN Company Ltd.,
Prentice Hall, New Jersey, 1st Edition, 1988.

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
