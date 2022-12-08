.bp
.he 'T_GETINFO (xti)'TROPIX: Manual de Refer�ncia'T_GETINFO (xti)'
.fo 'Escrito em 04.03.96'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_getinfo -"
obt�m informa��es do servi�o de transporte
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>

int t_getinfo (int fd, T_INFO *info);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_getinfo" retorna as caracter�sticas correntes do protocolo
de transporte associado ao descritor de arquivo "fd". As informa��es
obtidas s�o as mesmas do que as obtidas atrav�s da fun��o "t_open".
A fun��o "t_getinfo" permite o usu�rio a obter estas informa��es
durante qualquer fase da comunica��o.

.sp
.(l
	    +----------------+------------+------------+
	    |   Argumentos   | Na chamada | No retorno |
	    +----------------+------------+------------+
	    | fd             |     x      |     /      |
	    |		     |		  |	       |
	    | info->addr     |     /      |     x      |
	    | info->options  |     /      |     x      |
	    | info->tsdu     |     /      |     x      |
	    | info->etsdu    |     /      |     x      |
	    | info->connect  |     /      |     x      |
	    | info->discon   |     /      |     x      |
	    | info->servtype |     /      |     x      |
	    +----------------+------------+------------+
.)l

.sp
O ponteiro "info" deve apontar para uma estrutura "T_INFO", cujos
seguintes membros s�o preenchidos pela fun��o "t_getinfo":

.sp
.(t
.(l
	long	addr;		/* Tamanho m�ximo do endere�o */
	long 	options;	/* Tamanho m�ximo das op��es */
	long	tsdu;		/* Tamanho m�ximo da mensagem */
				/* normal */
	long	etsdu;		/* Tamanho m�ximo da mensagem */
				/* urgente */
	long	connect;	/* Tamanho m�ximo de dados para */
				/* primitivas de conex�o */
	long	discon;		/* Tamanho m�ximo de dados para */
				/* primitivas de desconex�o */
	long	servtype;	/* Tipos de servi�o dispon�veis */
.)l
.)t

.sp 2
Os conte�dos destes membros t�m os seguintes significados:

.in +3
.ip addr 10
Um valor maior ou igual a zero indica o tamanho m�ximo do endere�o do
protocolo de transporte;
um valor igual -1 especifica que n�o h� limite para o tamanho do endere�o;
um valor igual a -2 especifica que o usu�rio n�o tem acesso aos endere�os.

.ip options 10
Um valor maior ou igual a zero indica o tamanho m�ximo das op��es
espec�ficas do protocolo utilizado;
um valor igual -1 especifica que n�o h� limite para o tamanho das op��es;
um valor igual a -2 especifica que o sistema de transporte
n�o suporta estas op��es.

.ip tsdu 10
Um valor maior que zero indica que o sistema de transporte suporta
o modo de enviar dados normais orientado a registro
(preservando as fronteiras entre as mensagens)
e o valor dado � o tamanho m�ximo do registro;
Um valor igual a -1 indica que n�o h� limite para o tamanho m�ximo do registro;
um valor igual a zero indica que o sistema de transporte suporta
apenas o modo de enviar dados normais orientado a uma seq��ncia de bytes
(sem preservar as fronteiras entre as mensagens);
um valor igual a -2 indica que o sistema de transporte
n�o realiza transfer�ncia de dados normais.

.ip etsdu 10
Como acima (tsdu), para dados urgentes.

.ip connect 10
Um valor maior ou igual a zero indica a quantidade m�xima de dados
que pode ser enviada durante a fase de estabelecimento da conex�o;
um valor igual -1 especifica que n�o h� limite para a quantidade destes dados;
um valor igual a -2 especifica que o sistema de transporte
n�o realiza transfer�ncia de dados durante a fase de estabelecimento
da conex�o.

.ip discon 10
Um valor maior ou igual a zero indica a quantidade m�xima de dados
que pode ser enviada durante a fase de desconex�o (fun��es "t_snddis" e
"t_rcvdis" apenas);
um valor igual -1 especifica que n�o h� limite para a quantidade destes dados;
um valor igual a -2 especifica que o sistema de transporte
n�o realiza transfer�ncia de dados durante a fase de desconex�o.

.ip servtype 10
Este campo especifica os modos de comunica��o dispon�veis no sistema
de transporte. S�o eles:

.in +10
.ip T_COTS	12
Modo-com-conex�o, mas sem desconex�o ordenada.

.ip T_COTS_ORD 12
Modo-com-conex�o e com desconex�o ordenada.

.ip T_CLTS	12
Modo-sem-conex�o.

.ep
.in -10

.ep
.in -3

.sp 2
Se um usu�rio deseja obter independ�ncia de protocolo, os tamanhos
descritos acima devem ser consultados para determinar o tamanho das
�reas que ir�o conter as informa��es.
Uma alternativa � a utiliza��o da fun��o "t_alloc" para alocar estas
�reas.
N�o � preciso lembrar que, se o usu�rio exceder algum dos tamanhos
permitidos, ocorrer� um erro.
Os valores dos diversos membros
descritos acima podem mudar como um resultado da negocia��o de op��es.

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
No modo-de-acesso-interno, o campo "servtype" recebe o valor 0.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso a fun��o preenche a estrutura e devolve o valor 0.
Em caso contr�rio, devolve -1 e indica em "t_errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(xti): "
t_intro, t_open, t_alloc
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
