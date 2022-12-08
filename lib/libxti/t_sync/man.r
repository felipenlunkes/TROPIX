.bp
.he 'T_SYNC (xti)'TROPIX: Manual de Refer�ncia'T_SYNC (xti)'
.fo 'Escrito em 09.08.92'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_sync -"
sincroniza a biblioteca do sistema de transporte
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_sync (int fd);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_sync" sincroniza as estruturas de dados da biblioteca
de transporte com as informa��es do sistema de transporte.

.sp
.(l
	    +--------------------+------------+------------+
	    |   Argumentos	 | Na chamada | No retorno |
	    +--------------------+------------+------------+
	    | fd		 |     x      |     /      |
	    +--------------------+------------+------------+
.)l

.sp
O argumento "fd" indica o "endpoint" local que est� utilizando
as estruturas de dados.

.sp
A fun��o "t_sync" pode converter um descritor de arquivos n�o
inicializado (obtido atrav�s de "open", "dup" ou como resultado
de "fork"/"exec") em um "endpoint" de transporte inicializado.
Esta fun��o tamb�m permite dois processos cooperantes a sincronizar
as suas intera��es com o sistema de transporte.

.sp
� importante lembrar que o sistema de transporte trata todos os
usu�rios de um "endpoint" de transporte como um usu�rio apenas.
Se v�rios processos est�o usando o mesmo "endpoint", eles devem
coordenar suas atividades para que o estado do "endpoint" n�o
seja violado. A fun��o "t_sync" retorna o estado corrente do
"endpoint" para o usu�rio, possibilitando-o a verificar este
estado antes de tomar outras a��es. Esta coordena��o s� �
v�lida entre processos cooperantes; � poss�vel que um processo
ou um evento mude o estado do "endpoint" ap�s "t_sync" ter sido
chamada.

.sp
Se o "endpoint" de transporte est� trocando de estado no momento em que
a "t_sync" foi chamada, a fun��o ir� falhar.

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Nesta implementa��o, esta fun��o n�o � necess�ria, e uma chamada
a "t_sync" n�o tem efeito.

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
.wo "(sys): "
dup, exec, fork, open
.br
.wo "(xti): "
t_intro
.br

.in
.sp
.(t
.b
REFER�NCIAS
.r
.in 5
"X/OPEN Portability Guide: Networking Services",
X/OPEN Company Ltd.,
Prentice Hall, New Jersey, 1st Edition, 1988.
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
