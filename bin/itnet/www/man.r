.bp
.he 'WWW (cmd)'TROPIX: Manual de Refer�ncia'WWW (cmd)'
.fo 'Atualizado em 07.05.00'Vers�o 3.2.3'Pag. %'

.b NOME
.in 5
Servidor e cliente HTTP
.sp
.wo "www_s -"
servidor
.br
.wo "www   -"
pequeno cliente para testes
.br

.in
.sp
.b SINTAXE
.in 5
.(l
/usr/lib/itnet/www_s

www [-pgv] [-r <intervalo>] [-n <n�_remoto>] [<p�gina>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O servidor "www_s" aceita pedidos de servi�os conforme o protocolo HTTP.
No momento est� processando apenas o comando "GET", mas j� com possibilidade
da retomada de uma transmiss�o do ponto em que foi interrompida.

.sp
Para utilizar este servidor, deve-se criar uma conta "www"
(veja "edusr" (cmd)), onde o diret�rio � usado como a raiz da �rvore
contendo todos os arquivos que podem ser pedidos atrav�s do protocolo;
estes arquivos deve pertencer (naturalmente) � conta "www".

.sp
Ao receber o pedido de um arquivo, "www_s" acrescenta o prefixo dado pelo
diret�rio acima; se este nome for o de um diret�rio, � acrescentado o
sufixo "index.html". N�O s�o permitidos nomes contendo "..".

.sp
Certifique-se de que h� a linha referente a este servidor no arquivo
"/etc/itnetserv" (veja "itnetserv" (fmt)).

.sp 3
O cliente "www" para testes acessa o <n�_remoto>, e tenta obter a
<p�gina> dada.

.sp
Se o <n�_remoto> n�o for dado, "www" procura uma
cadeia da forma "TNET=node=<n�_remoto>" no ambiente (veja "tnet" (cmd)).

.sp
Se a <p�gina> n�o for dada, usa o valor "index.html".

.sp
As op��es do comando s�o:

.in +3
.ip --
Normalmente, "www" escreve na tela as linhas HTTP recebidas, e o n�mero
de linhas da <p�gina>.

.ip -p
Imprime a <p�gina> recebida na tela.

.ip -g
Salva a <p�gina> recebida no diret�rio corrente.

.ip -v
Verboso.

.ip -r
D� o <intervalo> no formato come�o-final (comforme o protocolo HTTP 1/1).

.ip -r
Fornece o <n�_remoto> (ao inv�s de usar o do TNET do ambiente).

.ep
.in -3

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
edusr, tnet
.br
.wo "(fmt): "
itnetserv
.br

.in
.sp
.b ARQUIVOS
.in 5
/etc/itnetserv

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
