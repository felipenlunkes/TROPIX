.bp
.he 'INTERNET (cmd)'TROPIX: Manual de Refer�ncia'INTERNET (cmd)'
.fo 'Atualizado em 27.08.99'Vers�o 3.2.2'Pag. %'

.b NOME
.in 5
.wo "internet -"
como preparar o TROPIX para acessar a INTERNET
.br

.in
.sp
.b DESCRI��O
.in 5
Ap�s a instala��o do TROPIX, a INTERNET j� deve estar ativa no modo interno.
Para verificar, use o comando "editscb -t" (cmd), e certifique-se
de que h� uma linha terminada com "<local>" (abaixo de "DISPOSITIVO").

.sp
Um outro modo de testar � executar o comando "ping" (cmd):

.sp
.nf
		ping meu_computador
.fi

.sp
O nome "meu_computador" � provis�rio; ele deve ser substitu�do por
um nome adequado no arquivo "/etc/itnetdev" (veja abaixo). 

.sp
O modo interno � necess�rio (entre outros) para o sistema gr�fico
X-Window.

.sp
A INTERNET (naturalmente) tamb�m pode (e deve) ser usada externamente atrav�s de
v�rios dispositivos de entrada/sa�da.
Abaixo damos os passos necess�rios para configurar a INTERNET:

.in +3
.ip 1. 3
Acertar as portas/IRQs dos dispositivos usados pela internet: linhas
seriais e/ou "ethernet". Veja "scb" (fmt) e "edscb" (cmd).
Certifique-se de que eles s�o reconhecidos durante a carga do TROPIX.

.ip 2. 3
Editar o arquivo "/etc/itnetserv".
Este arquivo (muito provavelmente) j� est� pronto, e n�o necessita de
modifica��es. Veja "itnetserv" (fmt).

.ip 3. 3
Editar o arquivo "/etc/itnetdev".
Veja "itnetdev" (fmt).

.ip 4. 3
Uma vez com estes dois arquivos prontos, podemos verificar se a INTERNET
j� pode ser iniciada corretamente, recarregando o sistema operacional.
Durante a passagem do modo "mono-usu�rio" para "multi-usu�rio", �
executado o programa

.sp
.nf
		/usr/lib/itnet/itnet_daemon 
.fi

.sp
atrav�s do arquivo "/etc/rc" (veja "rc" (fmt) e "itnet_daemon" (cmd)).
Observe se � impressa alguma mensagem de erro. Se houver alguma
mensagem, corrija o arquivo que ocasionou o erro, e reexecute o comando
acima (diretamente, N�O � necess�rio recarregar o sistema).

.sp
No caso de n�o ser impressa nenhuma mensagem de erro, provavelmente
os diversos processos da INTERNET foram iniciados corretamente.
Verifique atrav�s do comando "ps -x" (veja "ps" (cmd)) se este foi o caso
(devem estar presentes processos com os nomes "itnet_daemon",
"in_daemon", "out_daemon" e v�rios "serv_daemon").


.(t
.ip 5. 3
Fa�a um teste com

.sp
.nf
		ping meu_computador
.fi
.)t

.sp
e com

.sp
.nf
		rlogin meu_computador
.fi

.sp
onde "meu_computador" � o nome dado ao computador no in�cio do
arquivo "/etc/itnetdev".

.ip 6. 3
Para a utiliza��o de linha discada (protocolo PPP), veja "ppp" (cmd).

.ep
.in -3

.sp 2
Uma vez com a internet operacional,
o comando "editscb" pode ser usado para monitorar o seu funcionamento.
De particular import�ncia �
a op��o "-t", atrav�s da qual s�o impressas as tabelas
de endere�os IP conhecidos,
de roteamento e de endere�os "ethernet"
(veja "editscb" (cmd)).
Verificar se a tabela de roteamento est� correta.

.sp
Alguns dos servidores escrevem informa��es no arquivo "/var/adm/itnetlog"
(caso ele j� exista); para consultar este arquivo use "show" ou "tail" (cmd).

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd):"
edscb, ps, itnet_daemon, ppp, ping, rlogin, editscb,
.wo "				    show, tail"
.br
.wo "(fmt): "
scb, itnetserv, itnetdev, rc
.br

.in
.sp
.b ARQUIVOS
.in 5
/etc/itnetdev
 /etc/itnetserv
 /usr/lib/itnet/itnet_daemon 
 /etc/rc
 /var/adm/itnetlog

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
