.bp
.he 'T_SNDUDATA (xti)'TROPIX: Manual de Refer�ncia'T_SNDUDATA (xti)'
.fo 'Escrito em 17.08.00'Vers�o 4.0.0'Pag. %'

.b NOME
.in 5
.wo "t_sndudata -"
envia um datagrama
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_sndudata (int fd, const T_UNITDATA *data);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_sndudata" � usada para enviar um datagrama para um outro
usu�rio no modo-sem-conex�o.

.sp
.(l
	    +--------------------+------------+------------+
	    |   Argumentos	 | Na chamada | No retorno |
	    +--------------------+------------+------------+
	    | fd		 |     x      |     /      |
	    |			 |	      |		   |
	    | data->addr.maxlen	 |     /      |     /      |
	    | data->addr.len	 |     x      |     /      |
	    | data->addr.buf	 |    x(x)    |     /      |
	    |			 |	      |		   |
	    | data->opt.maxlen	 |     /      |     /      |
	    | data->opt.len	 |     x      |     /      |
	    | data->opt.buf	 |    ?(?)    |     /      |
	    |			 |	      |		   |
	    | data->udata.maxlen |     /      |     /      |
	    | data->udata.len	 |     x      |     /      |
	    | data->udata.buf	 |    x(x)    |     /      |
	    +--------------------+------------+------------+
.)l

.sp
O argumento "fd" indica o "endpoint" local atrav�s do qual o datagrama
ser� enviado e "data" cont�m informa��es associadas ao datagrama
que ser� enviado.
O argumento "data" deve apontar para uma estrutura "T_UNITDATA"
que cont�m os seguintes membros:

.sp
.(l
     NETBUF     addr;
     NETBUF     opt;
     NETBUF     udata;
.)l

.sp
O membro "addr" especifica o endere�o de protocolo
(endere�o INTERNET e "port") do usu�rio destinat�rio,
"opt" identifica op��es espec�ficas do protocolo associadas ao pedido
e "udata" cont�m os dados a enviar.
O usu�rio pode preferir n�o dar op��es, atribuindo um valor NULO
a "opt.len"; neste caso o sistema de transporte usar� op��es
"default".

.sp
Normalmente, "t_sndudata" opera no modo s�ncrono e pode esperar caso
haja retri��es de controle de fluxo.
No entanto, se o indicador O_NONBLOCK foi ligado
(atrav�s de "t_open" ou "fcntl" (sys)),
"t_sndudata" executa no modo ass�ncrono, e se houver
retri��es de controle de fluxo
retorna imediatamente com -1 e atribui o valor [TFLOW]  a "t_errno".

.sp
A quantidade de dados especificados em "udata" n�o pode exceder
o valor do campo "tsdu" da estrutura "info"
retornada por "t_open" ou "t_getinfo".
Se "t_sndudata" � chamada antes que o usu�rio destinat�rio
tenha ativado o seu "endpoint" (veja "t_bind"),
o datagrama pode ser descartado.

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Esta implementa��o N�O suporta a associa��o de op��es
espec�ficas de protocolo com o datagrama;
portanto, na chamada "data->opt.len" deve ser NULO.

.sp
� tamb�m poss�vel especificar o endere�o IP
de fonte do datagrama (isto �, do pr�prio computador).
Isto � �til no caso de roteadores, no qual o computador possui v�rios
endere�os (um para cada interface).
Para dar este endere�o, basta fornecer "data->addr.len" com um tamanho
suficiente para 2 estruturas INADDR; ele dever� ser dado no segundo elemento do
vetor.

.sp
Al�m disto, a fun��o "t_sndudata" s� opera no modo
s�ncrono, isto �, ela sempre ir� esperar caso haja retri��es de
controle de fluxo.

.sp
No protocolo UDP, o "checksum" � opcional. Nesta vers�o do sistema,
no entanto, N�O � poss�vel enviar um datagrama sem "checksum".

.sp
Se o endere�o de protocolo n�o for dado ("data->addr.len" NULO),
ser� utilizado o endere�o dado no "t_bind" (xti).

.sp
Nesta implementa��o, tamb�m � poss�vel a utiliza��o da chamada ao
sistema "write" (sys) para enviar um datagrama.
A chamada

.sp
.(l
	  write (fd, buf, nbytes);
.)l

.sp
� equivalente a

.sp
.(l
	  data->addr.len  = 0;

	  data->udata.len = nbytes;
	  data->udata.buf = buf;

	  t_sndudata (fd, data);
.)l

.sp
onde o endere�o remoto utilizado ser� o endere�o dado no "t_bind" (xti).

.sp
O envio de um datagrama vazio (isto �, com "data->udata.len" NULO)
pode ser feito com "t_sndudata", mas n�o com "write".

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
.wo "(sys): "
fcntl, write
.br
.wo "(xti): "
t_alloc, t_open, t_bind, t_rcvuderr, t_rcvudata
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
