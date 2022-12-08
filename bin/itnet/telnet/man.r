.bp
.he 'TELNET (cmd)'TROPIX: Manual de Refer�ncia'TELNET (cmd)'
.fo 'Atualizado em 31.08.98'Vers�o 3.0.3'Pag. %'

.b NOME
.in 5
.wo "telnet -"
interface com um n� remoto usando o protocolo TELNET
.br

.in
.sp
.b SINTAXE
.in 5
.(l
telnet [-eliv] <n�_remoto> [<porta_remota>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "telnet" � a interface do usu�rio (cliente) para a
comunica��o com um n� remoto da r�de usando o protocolo TELNET.

.sp
Uma vez tendo completada a conex�o com o <n�_remoto>, "telnet"
l� caracteres do teclado, enviado-os para o <n�_remoto>
e l� caracteres recebidos do <n�_remoto>, escrevendo-os na tela do terminal.

.sp
Normalmente (isto �, sem as op��es "-e" e "-l"), "telnet" opera
no modo "caracter a caracter com eco remoto" (desde que o servidor
do <n�_remoto> concorde em ecoar os caracteres):
cada caractere teclado � imediatamente
enviado ao <n�_remoto> e o eco � realizado pelo servidor.
Este modo � o que permite o melhor contr�le
sobre o(s) processo(s) em execu��o no <n�_remoto>, mas � que mais
sobrecarrega a r�de de comunica��es.

.sp
Se a <porta_remota> for dada, usa esta porta ao inv�s da porta
padr�o do "telnet" (que � 23). Neste caso, automaticamente entra
no modo "linha a linha com eco local", e n�o processa as seq��ncias
de contr�le das op��es TELNET.

.sp
As op��es do comando s�o:

.in +3
.ip -e
Modo "caracter a caracter com eco local":
com esta op��o cada caractere teclado � imediatamente
enviado ao <n�_remoto>, mas o eco � realizado localmente por "telnet".
Este modo sobrecarrega menos a r�de (pois os ecos n�o a atravessam);
por outro lado, podem haver dificuldades na utiliza��o de editores de
textos tais como o "vi".

.ip -l
Modo "linha a linha com eco local":
com esta op��o, os caracteres s�o ecoados localmente por "telnet"
e somente s�o enviadas linhas completas para o <n�_remoto>.
Este modo � o que menos sobrecarrega a r�de
(pois os ecos n�o a atravessam e os caracteres s�o compactados em linhas);
por outro lado, podem haver dificuldades na utiliza��o de editores de
textos tais como o "vi" e com os caracteres de controle tais como
<^C>, etc ...

.ip -i
N�o converte o c�digo na recep��o: normalmente, � efetuada a convers�o
dos c�digos recebidos atrav�s da r�de para o c�digo apropriado do
terminal local (por exemplo ISO para ABICOMP). Com a op��o
"-i" esta convers�o n�o � efetuada; isto � �til quando o c�digo
recebido atrav�s de r�de j� � o adequado para o terminal.  

.ip -v
Verboso: Diversas informa��es s�o impressas, entre as quais as negocia��es
entre o cliente e o servidor.

.ep
.in -3

.sp
O programa "telnet" (cliente) pede ao servidor para que o
servidor ecoe (ou n�o) os caracteres (de acordo com as op��es dadas).

.in
.sp
.b OBSERVA��ES
.in 5
Tanto o cliente "telnet" como o servidor nunca enviam os caracteres
de controle "go ahead".

.sp
Somente parte do protocolo TELNET est� implementado. Por exemplo,
os caracteres de controle tais como "intr" (normalmente <^C>,
ver "stty" (cmd) ou "termio" (fmt)),
s�o enviados sem convers�es,
quando (pelo protocolo TELNET) deveriam ser convertidos nas
seq��ncias IAC ... (por exemplo, <^C> em IAC IP).

.sp
Das in�meras op��es TELNET, somente as op��es ECHO (1), SUPRESS GO AHEAD (3),
TERMINAL TYPE (24) e WINDOW SIZE (31) s�o reconhecidas e processadas.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
stty, rlogin
.br
.wo "(fmt): "
termio
.br

.in
.sp
.b
REFER�NCIAS
.r
.(l
Postel, J. & Reynolds J.:
"TELNET PROTOCOL SPECIFICATION, RFC 854",
Maio de 1983.
.)l

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
