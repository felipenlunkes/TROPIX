.bp
.he 'T_RCVUDATA (xti)'TROPIX: Manual de Refer�ncia'T_RCVUDATA (xti)'
.fo 'Escrito em 17.08.00'Vers�o 4.0.0'Pag. %'

.b NOME
.in 5
.wo "t_rcvudata -"
recebe um datagrama
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_rcvudata (int fd, T_UNITDATA *data, int *flags);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_rcvudata" � usada para receber um datagrama de um outro
usu�rio no modo-sem-conex�o.

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
recebido. O argumento "flags" aponta para uma vari�vel onde ser�o
retornados indicadores opcionais, como descritos abaixo. Se "flags"
for um ponteiro NULO, n�o ser�o retornados os indicadores.

.sp
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
No retorno, "addr" especifica o endere�o de protocolo
(endere�o INTERNET e "port") do usu�rio que enviou o datagrama,
"opt" identifica op��es espec�ficas do protocolo associadas ao datagrama
e "udata" cont�m os dados recebidos.

.sp
Normalmente, "t_rcvudata" opera no modo s�ncrono e espera a chegada
de dados, caso n�o haja dados dispon�veis no momento da chamada.
No entanto, se o indicador O_NONBLOCK foi ligado
(atrav�s de "t_open" ou "fcntl" (sys)),
"t_rcvudata" executa no modo ass�ncrono, e se n�o houver dados dispon�veis
retorna imediatamente com -1 e atribui o valor [TNODATA]  a "t_errno".

.sp
Se a �rea definida no campo "udata" de "data" n�o � suficiente para
conter o datagrama recebido, a �rea ser� preenchida e o indicador
"T_MORE" ser� ligado em "flags" no retorno.
Neste caso, "t_rcvudata" deve ser chamada novamente para obter
os dados restantes.

.bc	/*************************************/
Nestas chamadas subsequentes, "t_rcvudata" retornar� ZERO no
tamanho do endere�o e das op��es at� que o datagrama seja obtido
inteiramente.
.ec	/*************************************/

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Esta implementa��o N�O suporta a associa��o de op��es
espec�ficas de protocolo com o datagrama;
portanto, no retorno "data->opt.len" ser� sempre NULO.

.sp
No retorno, o membro "addr" pode tamb�m fornecer o endere�o IP
de destino do datagrama (isto �, do pr�prio computador).
Isto � �til no caso de roteadores, no qual o computador possui v�rios
endere�os (um para cada interface).
Para obter este endere�o, basta fornecer "data->addr.maxlen" com um tamanho
suficiente para 2 estruturas INADDR; ele ser� fornecido no segundo elemento do
vetor.

.sp
No protocolo UDP, o "checksum" � opcional. Nesta vers�o do sistema,
no entanto, N�O � poss�vel enviar um datagrama sem "checksum".
Por outro lado, � poss�vel receber datagramas sem "checksum",
oriundos de outros sistemas operacionais.
Se o datagrama recebido N�O contiver "checksum", ser� retornado
o indicador "T_NO_CHECKSUM" ligado em "flags".

.sp
Um modo de n�o ficar bloqueado em uma chamada a "t_rcvudata",
dispon�vel nesta implementa��o
(no modo s�ncrono) � a utiliza��o da fun��o "t_nread",
que fornece o n�mero de bytes de dados dispon�veis.

.sp
A chamada ao sistema "attention" (sys) pode ser usada para aguardar
a disponibilidade de dados para "t_rcvudata".

.sp
Nesta implementa��o, tamb�m � poss�vel a utiliza��o da chamada ao
sistema "read" (sys) para receber um datagrama.
A chamada

.sp
.(l
	  read (fd, buf, nbytes);
.)l

.sp
� equivalente a

.sp
.(l
	  data->addr.maxlen  = 0;

	  data->udata.maxlen = nbytes;
	  data->udata.buf    = buf;

	  t_rcvudata (fd, data, (int *)NULL);
.)l

.sp
onde o endere�o remoto contido no datagrama n�o � fornecido.
Isto no entanto, pode ser obtido atrav�s de "t_getaddr" (xti).

.bc	/*************************************/
.sp
O tamanho do endere�o � retornado corretamente em todas as chamadas.
.ec	/*************************************/

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
fcntl, read, attention
.br
.wo "(xti): "
t_alloc, t_open, t_rcvuderr, t_sndudata, t_nread,
.br
.wo "        t_getaddr"
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
