.bp
.he 'T_RCVUDERR (xti)'TROPIX: Manual de Refer�ncia'T_RCVUDERR (xti)'
.fo 'Escrito em 09.08.92'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_rcvuderr -"
recebe uma indica��o de erro de datagrama
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_rcvuderr (int fd, T_UDERROR *uderr);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_rcvuderr" � usada no modo-sem-conex�o para receber
informa��es referentes a um erro ocorrido (anteriormente) durante
o envio de um datagrama.
A fun��o deve ser chamada apenas ap�s a ocorr�ncia do evento
"T_UDERR".
Ela informa o usu�rio do sistema de transporte que o envio de
um datagrama com um endere�o e op��es de protocolo espec�ficos
produziu um erro. 

.sp
.(l
	    +--------------------+------------+------------+
	    |   Argumentos	 | Na chamada | No retorno |
	    +--------------------+------------+------------+
	    | fd		 |     x      |     /      |
	    |			 |	      |		   |
	    | uderr->addr.maxlen |     x      |     /      |
	    | uderr->addr.len	 |     /      |     x      |
	    | uderr->addr.buf	 |     x      |    (x)     |
	    |			 |	      |		   |
	    | uderr->opt.maxlen	 |     x      |     /      |
	    | uderr->opt.len	 |     /      |     x      |
	    | uderr->opt.buf	 |     x      |    (x)     |
	    |			 |	      |		   |
	    | uderr->error	 |     /      |     x      |
	    +--------------------+------------+------------+
.)l

.sp
O argumento "fd" indica o "endpoint" local atrav�s do qual a indica��o
de erro ser� recebida e "uderr" deve apontar para uma estrutura "T_UDERROR"
que cont�m os seguintes membros:

.sp
.(l
     NETBUF     addr;
     NETBUF     opt;
     long       error;
.)l

.sp
Os campos "maxlen" de "addr" e "opt" devem ser inicializados
antes da chamada � fun��o para indicar o tamanho m�ximo da �rea
de cada um deles.

.sp
No retorno, "addr" especifica o endere�o de protocolo
(endere�o INTERNET e "port") do datagrama com erro, a estrutura
"opt" identifica op��es espec�ficas do protocolo associadas ao datagrama
e "error" especifica um c�digo de erro dependente do protocolo.

.sp
Se o usu�rio n�o se importa em identificar o datagrama que causou o
erro, "uderr" pode ser um ponteiro NULO. Neste caso, "t_rcvuderr"
simplesmente ir� remover a indica��o de erro sem fornecer nenhuma
informa��o ao usu�rio.

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Nesta implementa��o, esta fun��o n�o � suportada; todos os erros
referentes ao envio de um datagrama s�o reportados imediatamente
no retorno de "t_sndudata" (portanto o evento "T_UDERR" nunca ocorre).

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
t_rcvudata, t_sndudata
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
