.bp
.he 'T_OPEN (xti)'TROPIX: Manual de Refer�ncia'T_OPEN (xti)'
.fo 'Escrito em 06.01.93'Vers�o 3.0'Pag. %'

.b NOME
.in 5
.wo "t_open -"
cria um "endpoint" de transporte
.br

.in
.sp
.b SINTAXE
.in 5
.(l
#include <xti.h>
#include <fcntl.h>

int t_open (const char *name, int oflag, T_INFO *info);
.)l

.in
.sp
.b DESCRI��O
.in 5
A fun��o "t_open" deve ser chamada como primeira etapa na inicializa��o
de um "endpoint" de transporte.
Um "endpoint" � uma estrutura interna do sistema de comunica��es
na qual est�o as informa��es necess�rias para uma comunica��o 
em andamento.
.sp

.(l
	    +----------------+------------+------------+
	    |   Argumentos   | Na chamada | No retorno |
	    +----------------+------------+------------+
	    | name           |     x      |     /      |
	    |		     |		  |	       |
	    | oflag          |     x      |     /      |
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
O argumento "name" indica o nome do dispositivo associado
ao protocolo do n�vel de transporte a ser utilizado na comunica��o
(veja abaixo).

.sp
O argumento "oflag" deve ser constru�do a partir do indicador O_RDWR,
associado ou n�o, com O_NDELAY (ou O_NONBLOCK) - veja "open" (sys).

.sp
Em caso de sucesso, "t_open" retorna um descritor de arquivos
que identifica o "endpoint" (usualmente mencionado como "fd").
Este descritor deve ser usado em todas as chamadas subseq�entes
a fun��es para se referir a este "endpoint".

.sp
Se "info" for um ponteiro n�o NULO, "t_open" tamb�m preenche os diversos
membros da estrutura "T_INFO", contendo v�rias caracter�sticas
"default" do protocolo de transporte (veja "t_getinfo" (xti)). 

.in
.sp
.b 'DETALHES DE IMPLEMENTA��O'
.in 5
Nesta implementa��o, que utiliza os protocolos INTERNET, os nomes
dos dispositivos devem ser "/dev/itntcp" para o protocolo TCP
(modo-com-conex�o), "/dev/itnudp" para o protocolo UDP
(modo-sem-conex�o) e "/dev/itnraw" para o protocolo definido pelo usu�rio
(modo-de-acesso-interno). Este �ltimo s� pode ser usado pelo superusu�rio.

.in
.sp
.b
VALOR DE RETORNO
.r
.in 5
Em caso de sucesso a fun��o devolve um descritor de arquivos v�lido.
Em caso contr�rio, devolve -1 e indica em "t_errno" a causa do erro.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(sys): "
open
.br
.wo "(xti): "
t_getinfo
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
