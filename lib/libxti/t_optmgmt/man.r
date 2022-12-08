.bp
.he 'T_OPTMGMT (xti)'TROPIX: Manual de Refer�ncia'T_OPTMGMT (xti)'
.fo 'Atualizado em 24.06.98'Vers�o 3.0.2'Pag. %'

.b NOME
.in 5
.wo "t_optmgmt -"
gerencia op��es de um "endpoint" de transporte
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_optmgmt (int fd, const T_OPTMGMT *req, T_OPTMGMT *ret);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_optmgmt" permite que o usu�rio recupere, verifique
ou negocie op��es espec�ficas do protocolo utilizado.

.sp
.(l
	    +-------------------+------------+------------+
	    |   Argumentos	| Na chamada | No retorno |
	    +-------------------+------------+------------+
	    | fd		|     x      |     /      |
	    |			|	     |		  |
	    | req->opt.maxlen	|     /      |     /      |
	    | req->opt.len	|     x      |     /      |
	    | req->opt.buf	|    x (x)   |     /      |
	    | req->flags	|     x      |     /      |
	    |			|	     |		  |
	    | ret->opt.maxlen	|     x      |     /      |
	    | ret->opt.len	|     /	     |     x      |
	    | ret->opt.buf	|     x      |    (x)     |
	    | ret->flags	|     /      |     x      |
	    +-------------------+------------+------------+
.)l

.sp
O argumento "fd" identifica o  "endpoint" de transporte,
que j� deve ter um endere�o associado (atrav�s de "t_bind").

.sp
Os argumentos "req" e "ret" devem apontar para estruturas "T_OPTMGMT",
que cont�m os seguintes membros:

.sp
.(l
     NETBUF     opt;
     long       flags;
.)l

.sp
O membro "opt" da estrutura "T_OPTMGMT" especifica as op��es
de protocolo e o membro "flags" � usado para especificar a
ac�o a tomar com estas op��es.

.sp
As op��es s�o representadas por uma estrutura "NETBUF" de forma
similar ao endere�o utilizado pela fun��o "t_bind".
O argumento "req" � utilizado para enviar as op��es ao sistema de
transporte e requisitar uma a��o espec�fica sobre estas op��es.
O campo "len" especifica o n�mero de bytes das op��es,
"buf" aponta para a �rea com as op��es e "maxlen" n�o tem significado
neste argumento.

.sp
O sistema de transporte pode retornar valores de op��es e "flags"
para o usu�rio atrav�s da estrutura "ret".
Em "ret", "maxlen" especifica o tamanho da �rea de op��es e "buf"
aponta para esta �rea. Ap�s o retorno, "len" cont�m o n�mero de
bytes de op��es retornados.

.sp
O campo "flags" do argumento "req" deve especificar uma das a��es abaixo:

.in +3
.ip T_NEGOTIATE 13
Esta a��o possibilita o usu�rio a negociar os valores das op��es
especificados em "req" com o sistema de transporte.
O sistema ir� avaliar as op��es requisitadas,
negociar seus valores e retornar os valores negociados em "ret".

.ip T_CHECK 13
Esta a��o possibilita o usu�rio a verificar se as op��es
especificadas em "req" s�o suportadas pelo sistema de transporte.
No retorno, o campo "flags" de "ret" conter� "T_SUCCESS" ou
"T_FAILURE" para indicar se as op��es s�o suportadas.
Estes "flags" s� tem significado para a a��o "T_CHECK".

.ip T_DEFAULT	13
Esta a��o permite que o usu�rio seja informado acerca das op��es
"default". O sistema de transporte armazena estes valores no
campo "opt" de "ret".
Em "req", o campo "len" de "opt" deve ser zero e o campo "buf"
pode conter um ponteiro NULO.

.in -3
.ep

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Nesta implementa��o, a fun��o "t_optmgmt" pode ser usada apenas para 
o protocolo TCP (isto �, no modo-com-conex�o), e "req->opt.buf" e
"ret->opt.buf" devem apontar para estruturas "TCP_OPTIONS"
(ver <xti.h>), das quais (nesta vers�o) apenas os membros
"max_seg_size", "max_wait", "max_silence" e "window_size" s�o relevantes.

.sp
O membro "max_seg_size" d� o tamanho m�ximo do segmento permitido;
o membro "max_wait" � o tempo m�ximo permitido para o estabelecimento
de uma conex�o (ap�s o qual a tentativa de conex�o � abortada
(n�o vale para o estado "T_INCON" (LISTEN)));
o membro "max_silence" � o tempo m�ximo permitido para uma conex�o
ficar sem receber/enviar segmentos
(ap�s o qual a conex�o � abortada);
o membro "window_size" d� o tamanho da janela de recep��o. Este valor
� tamb�m usado para o tamanho da �rea de entrada/sa�da para o
armazenamento do conte�do dos segmentos.

.sp
No momento da chamada a "t_optmgmt", o estado associado ao
"endpoint" deve ser "T_IDLE" (ver "t_getstate" (xti)).

.sp
No caso da a��o "T_CHECK", se "ret->opt.maxlen" indicar que "ret->opt.buf"
cont�m espa�o suficiente para uma estrutura "TCP_OPTIONS", ser�o
retornados os valores das op��es em uso no momento.

.sp
Repare que, para alterar apenas um (ou dois) dos membros, � necess�rio obter
inicialmente os valores em uso dos outros membros (atrav�s de uma
a��o "T_DEFAULT" ou "T_CHECK").

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso a fun��o devolve o valor 0.
Em caso contr�rio, devolve -1 e indica em "t_errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(xti): "
t_accept, t_alloc, t_connect, t_getinfo, t_listen,
.br
.wo '        t_open, t_rcvconnect, t_bind, t_getstate'
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
