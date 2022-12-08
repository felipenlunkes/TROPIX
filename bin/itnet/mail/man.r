.bp
.he 'MAIL (cmd)'TROPIX: Manual de Refer�ncia'MAIL (cmd)'
.fo 'Atualizado em 12.08.01'Vers�o 4.0.0'Pag. %'

.b NOME
.in 5
.wo "mail -"
le ou envia cartas do correio eletr�nico
.br

.in
.sp
.b SINTAXE
.in 5
.(l
mail [-ve] [-f <arquivo>] <destinat�rio> ...

mail [-rsu] [-d <caixa postal>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "mail" le cartas recebidas atrav�s do sistema de correio eletr�nico,
ou envia cartas para um ou mais <destinat�rio>s.

.sp
Se forem dados <destinat�rio>s, "mail" ir� enviar uma carta;
em caso contr�rio ir� abrir o �ndice de cartas recebidas.

.sp
As op��es do programa s�o:

.in +3
.ip -v
Durante o processo de envio de cartas (ver abaixo), imprime o di�logo com os servidores 
contatados (atrav�s do protocolo SMTP).

.ip -e
Se for dado um <arquivo> contendo o texto a ser enviado, executa o programa "vi" para edit�-lo
(veja a op��o "-f", abaixo).

.ip -f
O conte�do da carta � dado no <arquivo>, ao inv�s de ser teclado. As op��es
"-e" e "-f" s�o normalmente usadas pelos comandos internos "r" e "f"
(veja abaixo).

.ip -r
N�o modifica a caixa postal. Isto significa que n�o � permitido remover cartas, e o estado das
cartas (lida/n�o lida) na caixa postal n�o � atualizado.

.ip -s
Substitui a data da carta no �ndice de cartas pelo seu tamanho.

.ip -u
Mostra apenas cartas n�o lidas.

.ip -d
Abre a <caixa postal> dada, ao inv�s da caixa postal do usu�rio
(normalmente "/usr/spool/mail/$USER").

.ep
.in -3

.in
.sp
.b "LEITURA DE CARTAS RECEBIDAS"
.in 5
Sem op��es nem argumentos, "mail" imprime a primeira p�gina do �ndice
das cartas presentes na "caixa postal" do usu�rio (veja a op��o "-d", acima).

.sp
O formato do �ndice cont�m as seguintes colunas:

.in +3
.ip 1. 3
A letra "U" indica que a carta � nova (ou seja, ainda n�o lida), e
a letra "R" indica que a carta � antiga (ou seja, j� lida).

.ip 2. 3
O n�mero da carta.

.ip 3. 3
O remetente da carta (exceto quando o remetente � o pr�prio
usu�rio; neste caso d� o destinat�rio).

.ip 4. 3
A data/hora de recebimento da carta (veja a op��o "-s", acima).

.ip 5. 3
O assunto da carta.
 
.ep
.in -3

.sp
Para ler uma carta, basta usar as teclas "-" e/ou "+" para mover o cursor, e
teclar <enter> quando o cursor estiver apontando para a carta desejada.

.sp
Os comandos internos para avan�ar/retroceder a p�gina vis�vel do
�ndice de cartas na tela e outras fun��es s�o dados abaixo
(na se��o "comandos internos").

.in
.sp
.b "ENVIO DE CARTAS"
.in 5
Dando um mais <destinat�rio>s, "mail" envia a carta para os <destinat�rio>s dados
(outros <destinat�rio>s adicionais podem ser dados posteriormente atrav�s de "cc").

.sp
Ap�s certificar-se de que a sintaxe dos v�rios <destinat�rio>s est� correta, "mail"
imprime a linha "Assunto:", e espera que seja digitado o assunto da carta
(que pode ter apenas uma linha).

.sp
.(t
Em seguida, deve ser digitado o conte�do da carta. Durante este processo, podem ser dados
os seguinte comandos (sempre no in�cio da linha):

.in +3
.ip ~v 13
Invoca o editor de textos "vi" (cmd) para editar o texto j� digitado.
Isto � especialmente �til para efetuar corre��es no texto
(o "assunto" no entanto, N�O pode ser mais modificado).
A edi��o termina com "w" e "q".
.)t

.ip "~r <arquivo>" 13
Insere o conte�do do <arquivo> no texto sendo digitado.

.ep
.in -3

.sp
Para encerrar o texto a ser enviado, deve-se teclar "." (ou <^D>) sozinho em uma linha.

.sp
A seguir, "mail" imprime a linha "Anexos: ", e espera que sejam digitados um (ou mais)
nomes de arquivos que devem ser anexados � carta
(separados por v�rgulas, brancos ou <ht>, mas em apenas uma linha.

.sp
Em seguida, "mail" imprime a linha "Cc: ", e espera que sejam digitados um (ou mais)
destinat�rios adicionais (separados por v�rgulas, brancos ou <ht>, mas em apenas uma linha.

.sp
Finalmente, "mail" tenta enviar a carta para os diversos destinat�rios.
Se houver algum insucesso, uma c�pia da carta � adicionada ao final do arquivo "dead.letter"
do diret�rio "HOME" do usu�rio.

.sp
Na presente vers�o, "mail" tenta enviar a carta apenas UMA vez, isto �, N�O tentando
enviar outras vezes posteriormente.

.in
.sp
.b "COMANDOS INTERNOS"
.in 5
Durante a leitura das cartas recebidas, temos 3 tipos de tela:

.in +3
.ip a. 3
O �ndice de cartas:
� a lista de todas as cartas recebidas, conforme o formato dado acima
em "leitura de cartas recebidas".

.ip b. 3
O �ndice de partes:
Se uma certa carta conter "partes" (conforme a sintaxe MIME),
� dada uma lista das partes da carta.

.ip c. 3
O texto de uma carta: 
Se uma carta consistir apenas de um texto simples, ou ent�o uma das partes
for leg�vel, ela � apresentada na tela.

.ep
.in -3

.sp
Os comandos internos para efetuar diversas fun��es durante a leitura de
cartas recebidas s�o as seguintes:

.in +3

.ip 'u' 14
.it 'o' 14
.it '<nl>' 14
.it '<cr>' 14
.it '<enter>' 14
.it '<page down>' 14
Desce de n�vel:
Se estiver no �ndice de cartas, mostra a carta apontada pelo cursor;
se estiver em um �ndice de partes, mostra a parte apontada pelo cursor (se for um texto ou
outro �ndice de partes),
ou o grava em um arquivo (em caso contr�rio).

.ip 'i' 14
.it '<page up>' 14
Sobe de n�vel:
Retorna ao �ndice de cartas ou ao �ndice de partes superior.

.ip '+' 14
.it '=' 14
.it 'j' 14
.it <^E> 14
.it '<arrow down>' 14
Avan�a uma linha.

.ip '-' 14
.it '_' 14
.it 'k' 14
.it <^Y> 14
.it '<arrow up>' 14
Retrocede uma linha.

.ip 'l' 14
.it '<arrow right>' 14
Avan�a para o irm�o seguinte de mesmo n�vel:
Se estiver no texto de uma parte, avan�a para a parte seguinte da mesma carta;
Se estiver no texto de uma carta, avan�a para a carta seguinte.

.ip 'h' 14
.it '<arrow left>' 14
Retrocede para o irm�o anterior de mesmo n�vel:
Se estiver no texto de uma parte, retrocede para a parte anterior da mesma carta;
Se estiver no texto de uma carta, retrocede para a carta anterior.

.(t
.ip <^D> 14
Avan�a meia p�gina.
.)t

.ip <^U> 14
Retrocede meia p�gina.

.ip "<^F>" 14
Avan�a uma p�gina.

.ip "<^B>" 14
Retrocede uma p�gina.

.ip "[<n>] g" 14
.it "[<n>] G" 14
Se estiver em uma carta, avan�a/retrocede para a linha <n>;
se estiver no �ndice de cartas, avan�a/retrocede para a carta de n�mero <n>;
se estiver em um �ndice de partes, avan�a/retrocede para a parte de n�mero <n>;
Se <n> for omitido, avan�a para a �ltima parte/linha do �ndice/carta.

.ip <home> 14
Retrocede para o in�cio do �ndice/carta.

.ip <end> 14
Avan�a para o final do �ndice/carta.

.ip <^R> 14
Reescreve a tela.

.ip '/<cadeia>' 14
Busca de cadeia: procura a primeira ocorr�ncia da
<cadeia> na carta/�ndice de cartas.

.ip 'n' 14
Repete a busca de cadeia avan�ando:
procura a ocorr�ncia seguinte da
<cadeia> na carta/�ndice de cartas.

.ip 'N' 14
Repete a busca de cadeia retrocedendo:
procura a ocorr�ncia anterior da
<cadeia> na carta/�ndice de cartas.

.ip 's <arquivo>' 14
Se estiver no texto de uma carta/parte, copia-a para o final do <arquivo> dado.
A carta na caixa postal n�o � modificada.

.ip 'r' 14
Responde a carta.
Se estiver no texto de uma carta/parte,
o utilit�rio "mail" � invocado com o <destinat�rio> desta carta.
O texto � inclu�do na carta a enviar, e ele � dado para ser editado atrav�s
de "vi" (cmd).

.ip 'f <dest>' 14
Envia a carta para o outro destinat�rio <dest>.

.ip 'd' 14
Remove a carta presente.
Ela s� � removida ap�s uma confirma��o do usu�rio.

.ip '! <comando>' 14
Executa o <comando> atrav�s do "sh" (cmd).

.ip <^C> 14
.it 'q' 14
.it 'Q' 14
Encerra a execu��o de "mail".

.ep
.in -3

.in
.sp
.b 'ARQUIVO ".mailrc"'
.in 5
O arquivo ".mailrc" do diret�rio "HOME" do usu�rio permite a defini��o
de nomes simb�licos para <destinat�rio>s.

.sp
Deste modo, se o arquivo ".mailrc" contiver a linha

.sp
.nf
	alias	paulo	paulosq@cateto.com.br paulo@infor.org.br
.fi

.sp
usar o comando

.sp
.nf
	mail paulo
.fi

.sp
� equivalente a usar

.sp
.nf
	mail paulosq@cateto.com.br paulo@infor.org.br
.fi

.sp
Os diversos campos devem vir separados por <sp> ou <ht>.

.sp
A linha de "alias" pode possuir linhas de continua��o da seguinte forma:

.sp
.nf
	alias	paulo	paulosq@cateto.com.br	\
			paulo@infor.org.br
.fi

.sp
Al�m disto, atrav�s das linhas "set from_with_host" ou "unset from_with_host"
podemos definir se desejamos (ou n�o) incluir o nome do computador no endere�o
do remetente. Normalmente o nome do computador N�O � inclu�do.

.sp
A forma "unset from_with_host" � util caso o arquivo "/etc/mailrc" (veja abaixo)
contenha a linha "set from_with_host", mas n�o desejamos incluir o nome do computador.

.in
.sp
.b 'ARQUIVO "/etc/mailrc"'
.in 5
O arquivo "/etc/mailrc" permite as mesmas defini��es do arquivo ".mailrc" descrito
acima, mas estas defini��es ser�o globais e v�lidas para todos os usu�rios do sistema. 

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
vi, show
.br

.in
.sp
.(t
.b
REFER�NCIAS
.r
.in 5
Postel, J: "Simple Mail Transfer Protocol", RFC 821, Agosto de 1982.
.)t
.sp
Crooker, D: "Standard for the Format of ARPA Internet Text Messages", RFC 822, Agosto de 1982.

.in
.sp
.(t
.b ARQUIVOS
.in 5
/usr/spool/mail/$USER
 $HOME/.mailrc
 /etc/mailrc
 $HOME/.deadletter
.)t

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
