.bp
.he 'T_RCVRAW (xti)'TROPIX: Manual de Refer�ncia'T_RCVRAW (xti)'
.fo 'Escrito em 17.08.00'Vers�o 4.0.0'Pag. %'

.b NOME
.in 5
.wo "t_rcvraw -"
recebe um datagrama no modo-de-acesso-interno
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_rcvraw (int fd, T_UNITDATA *data, int *flags);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_rcvraw" � usada para receber um datagrama de um
n� da rede no modo-de-acesso-interno.

.sp
O modo-de-acesso-interno interage com o n�vel mais b�sico do
sistema de transporte, permitindo o envio/recep��o de datagramas com
protocolos definidos pelo usu�rio.
O objetivo deste modo � o de possibilitar o uso de protocolos
n�o convencionais e/ou experimentais. Somente o superusu�rio pode
usar este modo.

.sp
.(l
	    +--------------------+------------+------------+
	    |   Argumentos	 | Na chamada | No retorno |
	    +--------------------+------------+------------+
	    | fd		 |     x      |     /      |
	    |			 |	      |		   |
	    | data->addr.maxlen	 |     x      |     /      |
	    | data->addr.len	 |     /      |     x      |
	    | data->addr.buf	 |     x      |    (x)     |
	    |			 |	      |		   |
	    | data->opt.maxlen	 |     x      |     /      |
	    | data->opt.len	 |     /      |     x      |
	    | data->opt.buf	 |     x      |    (x)     |
	    |			 |	      |		   |
	    | data->udata.maxlen |     x      |     /      |
	    | data->udata.len	 |     /      |     x      |
	    | data->udata.buf	 |     x      |    (x)     |
	    |			 |	      |		   |
	    | flags		 |     x      |    (x)     |
	    +--------------------+------------+------------+
.)l

.sp
O argumento "fd" indica o "endpoint" local atrav�s do qual o datagrama
ser� recebido, "data" cont�m informa��es associadas ao datagrama
recebido e o argumento "flags" aponta para uma vari�vel onde ser�o
retornados indicadores opcionais.
O argumento "data" deve apontar para uma estrutura "T_UNITDATA"
que cont�m os seguintes membros:

.sp
.(l
     NETBUF     addr;
     NETBUF     opt;
     NETBUF     udata;
.)l

.sp
Os campos "maxlen" de "addr", "opt" e "udata" devem ser inicializados
antes da chamada � fun��o para indicar o tamanho m�ximo da �rea
de cada um deles.

.sp
No retorno, o membro "addr" especifica o endere�o de protocolo
(endere�o INTERNET) do n� da rede que enviou o datagrama
e o n�mero do protocolo do datagrama (em "a_proto"),
"opt" identifica op��es espec�ficas do protocolo associadas ao datagrama
e "udata" cont�m os dados recebidos.

.sp
Normalmente, "t_rcvraw" opera no modo s�ncrono e espera a chegada
de dados, caso n�o haja dados dispon�veis no momento da chamada.
No entanto, se o indicador O_NONBLOCK foi ligado
(atrav�s de "t_open" ou "fcntl" (sys)),
"t_rcvraw" executa no modo ass�ncrono, e se n�o houver dados dispon�veis
retorna imediatamente com -1 e atribui o valor [TNODATA]  a "t_errno".

.sp
A �rea definida no campo "udata" de "data" deve ser suficiente para
conter o datagrama recebido. Em caso contr�rio, ocorrer� o erro [TBUFOVFLW].

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Esta fun��o n�o faz parte da XTI, e portanto seu uso deve ser evitado
se for desejada portabilidade para outras implementa��es.

.sp
No retorno, o membro "addr" pode tamb�m fornecer o endere�o IP
de destino do datagrama (isto �, do pr�prio computador).
Isto � �til no caso de roteadores, no qual o computador possui v�rios
endere�os (um para cada interface).
Para obter este endere�o, basta fornecer "data->addr.maxlen" com um tamanho
suficiente para 2 estruturas INADDR; ele ser� fornecido no segundo elemento do
vetor.

.sp
Os dados recebidos em "data->udata" representam um datagrama
no protocolo definido pelo usu�rio (sobre o qual o sistema de transporte
nada conhece nem interpreta). � de inteira responsabilidade do
usu�rio gerenciar todos os campos deste datagrama,
inclusive o "checksum" (se houver).

.sp
Nesta vers�o, ainda n�o h� op��es nem indicadores opcionais dispon�veis;
portanto, no retorno "data->opt.len" e "flags" ser�o sempre NULOs.

.sp
Se forem dados o endere�o remoto e/ou o n�mero de protocolo em "t_bind" (xti),
estes valores s�o usados para "filtrar" os datagramas
de entrada: se "a_addr" for n�o NULO, ser�o aceitos apenas os datagramas
cujos endere�os remotos forem iguais ao dado;
se "a_proto" for n�o NULO, ser�o aceitos apenas os datagramas de entrada,
cujos n�meros de protocolo forem iguais ao dado.

.sp
Atrav�s da fun��o "t_getaddr" (xti) � poss�vel obter 
todos os endere�os/n�meros de protocolos associados ao "endpoint". 

.sp
Um modo de n�o ficar bloqueado em uma chamada a "t_rcvraw",
dispon�vel nesta implementa��o
(no modo s�ncrono) � a utiliza��o da fun��o "t_nread",
que fornece o n�mero de bytes de dados dispon�veis.

.sp
A chamada ao sistema "attention" (sys) pode ser usada para aguardar
a disponibilidade de dados para "t_rcvraw".

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
.(t
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
fcntl, attention
.br
.wo "(xti): "
t_alloc, t_open, t_bind, t_nread, t_getaddr
.br
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
