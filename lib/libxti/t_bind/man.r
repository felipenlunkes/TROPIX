.bp
.he 'T_BIND (xti)'TROPIX: Manual de Refer�ncia'T_BIND (xti)'
.fo 'Escrito em 04.03.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_bind -"
associa endere�o(s) de protocolo a um "endpoint"
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_bind (int fd, const T_BIND *req, T_BIND *ret);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_bind" associa endere�o(s) de protocolo ao "endpoint"
especificado por "fd", ativando este "endpoint".

.sp
.(l
	    +-------------------+------------+------------+
	    |   Argumentos	| Na chamada | No retorno |
	    +-------------------+------------+------------+
	    | fd		|     x      |     /      |
	    |			|	     |		  |
	    | req->addr.maxlen	|     /      |     /      |
	    | req->addr.len	|   x >= 0   |     /      |
	    | req->addr.buf	|    x (x)   |     /      |
	    | req->qlen		|   x >= 0   |     /      |
	    |			|	     |		  |
	    | ret->addr.maxlen	|     x      |     /      |
	    | ret->addr.len	|     /	     |     x      |
	    | ret->addr.buf	|     x      |    (x)     |
	    | ret->qlen		|     /      |   x >= 0   |
	    +-------------------+------------+------------+
.)l

.sp
Ap�s uma chamada com sucesso a "t_bind":
no modo-com-conex�o, o sistema de transporte pode come�ar a enfileirar
pedidos de conex�o recebidos para este "endpoint",
assim como utilizar este "endpoint" para enviar pedidos de conex�o;
nos modo-sem-conex�o e modo-de-acesso-interno o usu�rio pode
enviar e receber datagramas atrav�s deste "endpoint".

.sp
Os argumentos "req" e "ret" devem apontar para estruturas "T_BIND",
que cont�m os seguintes membros:

.sp
.(l
     NETBUF     addr;
     unsigned   qlen;
.)l

.sp
O membro "addr" da estrutura "T_BIND" especifica o(s) endere�o(s)
a ser(em) associado ao "endpoint", e o membro "qlen" � usado para indicar
o n�mero m�ximo permitido de pedidos de conex�o pendentes.

.sp
O argumento "req" � usado para requisitar que determinado(s)
endere�o(s) sejam associado(s) ao "endpoint".
O par�metro "len" especifica o n�mero de bytes do(s) endere�o(s)
e "buf" aponta para a �rea que cont�m o(s) endere�o(s)
(um vetor de  estruturas "INADDR", veja <xti.h>).
O par�metro "maxlen" n�o tem significado para o argumento "req".

.sp
No retorno, "ret" cont�m o(s) endere�o(s) efetivamente associado(s)
ao "endpoint" (o endere�o local pode ser diferente do requisitado em "req").
Em "ret", o usu�rio especifica "maxlen",
que � o tamanho m�ximo da �rea que ir� conter o(s) endere�o(s),
e "buf", que aponta para esta �rea.
No retorno, "len" especifica o n�mero de bytes do(s) endere�o(s)
colocado(s) em "buf". Se "maxlen" n�o for suficiente para
conter o(s) endere�o(s), ocorrer� um erro.

.sp
Se o endere�o local requisitado n�o est� dispon�vel,
ou se nenhum endere�o local foi especificado em "req"
(o campo "len" de "addr" em "req" � zero),
o sistema de transporte ir� gerar automaticamente
um endere�o, que ser� retornado no campo "addr" de "ret".
O usu�rio pode comparar os endere�os em "req" e "ret" para determinar
se o sistema de transporte utilizou o endere�o pedido, ou se gerou
um outro endere�o.

.sp
O par�metro "req" pode ser um ponteiro NULO, caso o usu�rio
n�o deseje especificar nenhum endere�o.
Neste caso, o valor de "qlen" � considerado zero e o
sistema de transporte fornecer� um endere�o local para o "endpoint".
Da mesma forma, "ret" pode ser um ponteiro NULO,
se o usu�rio n�o se interessa pelo endere�o local efetivamente
associado ao "endpoint" nem pelo valor negociado de "qlen".
� poss�vel inclusive chamar a fun��o "t_bind" com ambos os ponteiros NULOs.
Neste caso, o sistema de transporte gera um endere�o local para associar
ao "endpoint" e n�o retorna nenhuma informa��o para o usu�rio.

.sp
O membro "qlen" tem significado apenas no modo-com-conex�o.
Ele indica o n�mero m�ximo de pedidos de conex�o pendentes que o
sistema de transporte deve enfileirar para o "endpoint".
Um pedido de conex�o pendente � aquele pedido de conex�o
que j� foi notificado ao usu�rio, mas que ainda n�o foi aceito
ou rejeitado.
O valor de "qlen" s� deve ser maior que zero
no caso de "endpoints" que ser�o usados para receber pedidos de conex�o
(servidores).
O valor de  "qlen" ser� negociado pelo sistema de transporte,
podendo ser alterado caso o valor indicado pelo usu�rio exceda
o limite estabelecido pelo sistema.
No retorno, o membro "qlen" de "ret" conter� o valor negociado.

.sp
A fun��o permite que mais de um "endpoint" de transporte esteja
associado ao mesmo endere�o local de protocolo, mas n�o � poss�vel
associar mais de um endere�o de protocolo a um "endpoint"
de transporte. Se um usu�rio associar mais de um "endpoint" de
transporte ao mesmo endere�o de protocolo, somente um dos 
"endpoints" pode ser usado para receber pedidos de conex�o.
Em outras palavras, somente um "t_bind" para um determinado
endere�o de protocolo pode especificar um valor de "qlen" maior
do que zero. Deste modo, o sistema de transporte pode determinar
qual "endpoint" deve receber um pedido de conex�o.

.sp
Se um usu�rio
tentar associar o mesmo endere�o local de protocolo a um segundo "endpoint"
com o valor de "qlen" maior do que zero, o sistema de transporte
ir� obter um outro endere�o para ser associado �quele "endpoint",
ou (se a gera��o autom�tica de endere�os n�o for suportada), ir�
atribuir [TADDRBUSY] a "t_errno" e retornar -1. Quando um usu�rio
aceita uma conex�o em um "endpoint" de transporte que est� sendo
usado como "endpoint" de recebimento de pedidos de conex�o, o endere�o de
protocolo estar� ocupado durante esta conex�o, at� que seja chamada uma
das fun��es "t_unbind" ou "t_close".

.sp
Nenhum outro "endpoint" de
transporte pode estar recebendo pedidos de conex�o no mesmo
endere�o local de protocolo enquanto aquele "endpoint" inicial de recebimento
de pedidos de conex�o est� ativo. Isto ir� impedir que mais de um
"endpoint" de transporte  associados ao mesmo endere�o de protocolo 
recebam pedidos de conex�o.

.bc	/*************************************/
a: "endpoint" de transporte 
b: endere�o de protocolo 
c: o sistema de transporte
d: "endpoint"
e: recebimento de pedidos de conex�o
.ec	/*************************************/

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Esta implementa��o suporta a gera��o autom�tica de endere�os locais
(modo-com-conex�o e modo-sem-conex�o apenas).
Esta gera��o s� � utilizada para a defini��o de "ports" locais,
e somente se o endere�o local n�o for dado ou for dado um valor NULO
para o "port".

.sp
No modo-com-conex�o:
O membro "addr" refere-se a duas estruturas "INADDR", do qual
a primeira estrutura cont�m o endere�o local e a segunda
cont�m o endere�o remoto. De acordo com o valor de "req->addr.len"
podem ser dadas as duas estruturas (2 * sizeof (INADDR)),
apenas uma, a do endere�o local (sizeof (INADDR))
ou nenhuma (0).
No endere�o local, apenas o membro "a_port" � relevante,
definindo o "port" local.
Definir o endere�o remoto somente � necess�rio para servidores
que ir�o realizar a conex�o no mesmo "port" local utilizado para
receber os pedidos de conex�o (mas outro "endpoint").

.sp
No modo-sem-conex�o: 
.bc	/*************************************/
O membro "addr" refere-se a apenas uma estrutura "INADDR", da qual
apenas o membro "a_port" � relevante, definindo o "port" local.
.ec	/*************************************/
O membro "addr" refere-se a duas estrutura "INADDR", do qual
a primeira estrutura cont�m o endere�o local e a segunda
cont�m o endere�o remoto. De acordo com o valor de "req->addr.len"
podem ser dadas as duas estruturas (2 * sizeof (INADDR)),
apenas uma, a do endere�o local (sizeof (INADDR))
ou nenhuma (0).
Do endere�o local apenas o membro "a_port" � relevante,
definindo o "port" local.
Atrav�s do endere�o remoto, podemos definir o endere�o destino
de datagramas enviadas atrav�s de um "write" ou de um "t_sndudata" (xti)
no qual o endere�o n�o � dado.

.sp
No modo-de-acesso-interno:
O membro "addr" refere-se a apenas uma estrutura "INADDR", da qual
o membro "a_addr" cont�m o endere�o remoto e o membro "a_proto"
cont�m o n�mero do protocolo.
Estes dados s�o utilizados do seguinte modo: em um "t_sndraw" (xti):
estes valores s�o usados caso o membro "addr" n�o seja dado; em um
"t_rcvraw" (xti): estes valores s�o usados para "filtrar" os datagramas
de entrada: se "a_addr" for n�o NULO, ser�o aceitos apenas os datagramas
cujos endere�os remotos forem iguais ao dado;
se "a_proto" for n�o NULO, ser�o aceitos apenas os datagramas de entrada,
cujos n�meros de protocolo forem iguais ao dado.

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
t_intro, t_open, t_close, t_optmgmt, t_unbind,
.br
.wo "        t_rcvraw, t_sndraw, t_sndudata"
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
