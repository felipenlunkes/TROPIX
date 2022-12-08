.bp
.he 'FTP (cmd)'TROPIX: Manual de Refer�ncia'FTP (cmd)'
.fo 'Atualizado em 03.03.01'Vers�o 4.0.0'Pag. %'

.b NOME
.in 5
.wo "ftp -"
programa de c�pia remota de arquivos da INTERNET
.br

.in
.sp
.b SINTAXE
.in 5
.(l
ftp [-vn] <n�_remoto>
.)l

.in
.sp
.b DESCRI��O
.in 5
O programa "ftp" � a interface do usu�rio para o protocolo padr�o de
c�pias de arquivos da INTERNET. O programa permite a c�pia de arquivos
de/para um computador remoto de uma r�de.

.sp
Inicialmente, "ftp" obt�m uma conex�o com o servidor "ftp" do
<n�_remoto> e em seguida executa a seq��ncia de "login",
pedindo a conta/senha do usu�rio no <n�_remoto> (veja a op��o "-n").
Finalmente, "ftp" passa o controle para o interpretador de comandos,
aguardando instru��es do usu�rio.
Para indicar que est� aguardando comandos, "ftp" imprime uma linha
contendo os caracteres "ftp> ".

.sp
As op��es do programa s�o:

.in +3
.ip -v
Verboso: imprime as estat�sticas sobre as transfer�ncias de dados,
al�m de outras informa��es.

.ip -n
N�o executa automaticamente a seq��ncia de "login", passando diretamente o
contr�le para o interpretador de comandos. Repare no entanto, que a maioria
dos comandos s� podem ser executados com um usu�rio em sess�o. Para entrar
em sess�o mais tarde, deve ser usado o comando "user".

.ep
.in -3

.sp
O nome do <n�_remoto> e/ou o nome do usu�rio podem ser pr�-definidos no
ambiente (veja "environ" (fmt)) atrav�s da vari�vel "FTP",
cujo valor deve ter a forma:

.sp
.(l
	node=<n�_remoto>,user=<nome_do_usu�rio>
.)l

.in
.sp
.b 'PAR�METROS DE TRANSFER�NCIA DE DADOS'
.in 5
O protocolo FTP define uma s�rie de par�metros que definem como a
transfer�ncia dos dados de um arquivo ser� realizada.

.sp
O tipo de representa��o dados pode ser ASCII, EBCDIC, IMAGEM ou LOCAL.
Esta implementa��o suporta apenas os tipos ASCII e IMAGEM.
O tipo ASCII � tamb�m chamado de ISO porque s�o conservados os 8 bits.

.sp
O contr�le de formato pode ser NON-PRINT, TELNET ou ASA.
Esta implementa��o suporta apenas o formato NON-PRINT.

.sp
A estrutura de dados pode ser FILE, RECORD ou PAGE.
Esta implementa��o suporta apenas a estrutura FILE.

.sp
O modo de transmiss�o de dados pode ser STREAM, BLOCK ou COMPRESSED.
Esta implementa��o suporta apenas o modo STREAM.

.sp
A conex�o de dados � normalmente aberta no modo "ativo", isto �, com
o servidor executando o "connect". Isto pode ser alterado atrav�s do comando
interno "passive" (veja abaixo).

.in
.sp
.b COMANDOS
.in 5
O programa "ftp" reconhece os seguintes comandos:

.in +3
.ip " 1." 4
? [-s] [<comando>]
.sp
Como "help", abaixo.

.ip " 2." 4
!<comando> [<argumento> ...]
.sp
Executa o <comando> com os respectivos <argumento>s no n� local.
Isto vale inclusive para o comando "cd".

.ip " 3." 4
ascii
.sp
Altera o tipo da representa��o de dados para ISO (ASCII).

.ip " 4." 4
bin
.sp
Altera o tipo da representa��o de dados para IMAGEM.

.ip " 5." 4
binary
.sp
Altera o tipo da representa��o de dados para IMAGEM.

.ip " 6." 4
bye
.sp
Encerra o programa. Um EOF (normalmente <^D>) tem o mesmo efeito.

.ip " 7." 4
cd [<diret�rio_remoto>]
.sp
Altera o diret�rio corrente do n� remoto para <diret�rio_remoto>.
Se o <diret�rio_remoto> n�o for dado, ser� usado o diret�rio "HOME"
do usu�rio remoto.

.ip " 8." 4
cdup
.sp
Altera o diret�rio corrente do n� remoto para o pai do diret�rio
corrente atual.

.ip " 9." 4
cmp <arquivo_local> [<arquivo_remoto>]
.sp
Compara um arquivo do n� local com um arquivo do n� remoto. Se o nome
do <arquivo_remoto> n�o for dado, ser� igual ao nome do <arquivo_local>.

.ip 10. 4
delete <arquivo_remoto>
.sp
Remove o <arquivo_remoto>.

.ip 11. 4
dir [<arquivo_remoto> [<arquivo_local]]
.sp
� equivalente ao comando "ls", abaixo.

.ip 12. 4
exit
.sp
� equivalente ao comando "quit", abaixo.

.(t
.ip 13. 4
get <arquivo_remoto> [<arquivo_local>]
.sp
Copia um arquivo do n� remoto para o n� local. Se o nome do
<arquivo_local> n�o for dado, ser� igual ao nome do <arquivo_remoto>.
Se o nome do <arquivo_local> for "-", o conte�do do <arquivo_remoto>
ser� impresso na sa�da padr�o.
.)t

.ip 14. 4
help [-s] [<comando>]
.sp
Imprime uma descri��o do significado do <comando>. Se o nome do <comando>
n�o for dado, imprime uma lista dos comandos dispon�veis. Se for dada a
op��o "-s" ser�o fornecidas as mesmas informa��es, mas obtidas do
servidor.

.ip 15. 4
image
.sp
Altera o tipo da representa��o de dados para IMAGEM.

.ip 16. 4
iso
.sp
Altera o tipo da representa��o de dados para ISO (ASCII).

.ip 17. 4
lc [<diret�rio_remoto>]
.sp
Imprime o conte�do (no estilo de "lc") do <diret�rio_remoto>.
Se este n�o for dado, ser� considerado o diret�rio corrente remoto.
Este comando n�o � padr�o do protocolo FTP, e n�o pode ser usado com
outros servidores.

.ip 18. 4
ls [<arquivo_remoto> [<arquivo_local]]
.sp
Imprime informa��es (no estilo de "ls -l") do <arquivo_remoto>.
O <arquivo_remoto> pode tamb�m ser um diret�rio, caso em que ser�o
impressas informa��es sobre o conte�do do diret�rio remoto.
Se o <arquivo_remoto> n�o for dado (ou for igual a "."), ser� considerado
o diret�rio corrente remoto.
Se o <arquivo_local> for dado, as informa��es s�o postas neste arquivo;
em caso contr�rio s�o impressas na sa�da padr�o.


.ip 19. 4
mget [-f] [<diret�rio>]
.sp
Copia os arquivos regulares contidos no <diret�rio> do n� remoto
para o n� local.
Os arquivos locais ser�o colocados no <diret�rio> (de mesmo nome) local,
que j� dever� existir.
Se o nome do <diret�rio> n�o for dado, ser� considerado o diret�rio corrente
(remoto e local).
Se a op��o "-f" n�o for dada, ser� pedida a confirma��o da c�pia de cada
arquivo.

.(t
.ip 20. 4
mkdir <diret�rio_remoto>
.sp
Cria o <diret�rio_remoto>.
.)t

.ip 21. 4
mput [-f] [<diret�rio>]
.sp
Copia os arquivos regulares contidos no <diret�rio> do n� local
para o n� remoto.
Os arquivos locais ser�o colocados no <diret�rio> (de mesmo nome) remoto,
que j� dever� existir.
Se o nome do <diret�rio> n�o for dado, ser� considerado o diret�rio corrente
(local e remoto ).
Se a op��o "-f" n�o for dada, ser� pedida a confirma��o da c�pia de cada
arquivo.

.ip 22. 4
mv <nome_antigo> <nome_novo>
.sp
Muda o nome do arquivo remoto <nome_antigo> para <nome_novo>.

.ip 23. 4
nlst [<diret�rio_remoto>]
.sp
Imprime os nomes dos arquivos regulares contidos no <diret�rio_remoto>.
Se o <diret�rio_remoto> n�o for dado, ser� considerado
o diret�rio corrente remoto.
Este comando � �til para verificar quais os arquivos que um comando "mget"
ir� copiar.

.ip 24. 4
noop
.sp
N�o realiza nenhuma opera��o.
Este comando � �til para verificar se a conex�o ainda est�
ativa e estimar o tempo de resposta do servidor.

.ip 25. 4
passive
.sp
Alterna entre os modos "ativo" e "passivo" da abertura da conex�o
de dados. No modo "ativo", � o servidor que realiza o "connect",
enquanto que no modo "passivo" � o cliente.

.ip 26. 4
port [-sn] [<n�mero_do_port>]
.sp
Pelo protocolo FTP, a conex�o de dados deve usar normalmente o "port"
de n�mero 20, podendo ser mudado atrav�s de um comando "PORT".
Al�m disto, uma vez mudado este n�mero,
este novo "port" dever� ser utilizado pelo servidor em todas as opera��es
seguintes (at� a recep��o de um novo comando "PORT").

.sp
No entanto, h� servidores FTP que n�o seguem estas conven��es.
A fun��o do comando "port" � o de permitir o uso destes servidores.

.sp
Se for dada a op��o "-s", ser� executado um comando "PORT" para cada
opera��o que utiliza a conex�o de dados.
Por outro lado, se for dada a op��o "-n", ser� executado um comando
"PORT" apenas se o n�mero do "port" for diferente do utilizado
na opera��o anterior.

.sp
Se for dado um <n�mero_do_port> diferente de zero, este ser� utilizado
a partir das opera��es seguintes. Se ele for igual a zero, ser� obtido
um n�mero de "port" tempor�rio do sistema operacional, e que ser�
utilizado a partir das opera��es seguintes.
Se o  n�mero de "port" dado n�o puder ser usado, tamb�m ser� obtido
um n�mero de "port" tempor�rio do sistema operacional.
Se o <n�mero_do_port> n�o for dado, continuar� a ser usado o "port"
anteriormente utilizado.

.sp
Inicialmente, "ftp" utiliza o "port" 20 (padr�o) para a conex�o de dados e
executa um comando "PORT" para cada opera��o que usa a conex�o de dados.

.ip 27. 4
put <arquivo_local> [<arquivo_remoto>]
.sp
Copia um arquivo do n� local para o n� remoto. Se o nome do
<arquivo_remoto> n�o for dado, ser� igual ao nome do <arquivo_local>.

.ip 28. 4
pwd
.sp
Imprime o nome do diret�rio corrente remoto.

.ip 29. 4
quit
.sp
Encerra o programa. Um EOF (normalmente "^D") tem o mesmo efeito.

.ip 30. 4
quote <nome> [<argumento_1> [<argumento_2>] ]
.sp
Envia para o servidor um comando consistindo do <nome> e
possivelmente um ou dois <argumento>s (exatamente como dado(s)).
� esperada uma (e apenas uma) resposta do servidor.
A chegada de outras respostas pode ser verificada atrav�s do comando
"reset".

.sp
O comando "quote" � �til para a utiliza��o de comandos dispon�veis
em um outro servidor, que no entanto esta implementa��o "ftp" n�o suporta.
Uma outra possibilidade � o uso de comandos que ainda
ir�o ser definidos futuramente no protocolo FTP
(e que estar�o dispon�veis em um futuro servidor).

.sp
Repare que com "quote" s� podemos utilizar comandos que n�o utilizam a
conex�o de dados.

.ip 31. 4
rename <nome_antigo> <nome_novo>
.sp
Muda o nome do arquivo remoto <nome_antigo> para <nome_novo>.

.ip 32. 4
reset
.sp
L� uma resposta do servidor (se dispon�vel).
Isto � �til para que o cliente e o servidor fiquem novamente em
fase, caso o servidor (violando o protocolo) emita resposta(s)
a mais.

.ip 33. 4
rm <arquivo_remoto>
.sp
Remove o <arquivo_remoto>.

.ip 34. 4
rmdir <diret�rio_remoto>
.sp
Remove o <diret�rio_remoto>.

.ip 35. 4
status
.sp
Fornece informa��es sobre o cliente e o servidor.

.ip 36. 4
system
.sp
Obt�m o tipo de sistema operacional do servidor.

.ip 37. 4
type [ascii|a|image|i|binary|bin|b]
.sp
Altera o tipo da representa��o de dados.
Os nomes v�lidos s�o "ascii" e "a" para o tipo ISO (ASCII) e
"image", "i", "binary" e "bin" para o tipo IMAGEM.
Se n�o for dado nenhum nome, ser� impresso o tipo corrente.

.ip 38. 4
user [<nome_do_usu�rio>]
.sp
Inicia a seq��ncia de "login". Se o <nome_do_usu�rio> n�o for
dado, ele � pedido, assim como a senha e conta (caso necess�rios).
A n�o ser que seja dada a op��o "-n" (do programa), esta seq��ncia
� iniciada automaticamente quando "ftp" � executado.

.in -3
.ep

.in
.sp
.b "INTERRUP��O DE COMANDOS E DE C�PIA DE ARQUIVOS"
.in 5
Esta implementa��o do protocolo FTP ainda n�o possibilita a interrup��o
de uma c�pia de arquivos em andamento. Se for usada a tecla de interrup��o
(normalmente <^C>), ser� impressa uma mensagem indicando isto, mas a
c�pia prosseguir� at� o final.

.sp
O �nico uso significativo da tecla de interrup��o � nos
comandos "mget" e "mput", que ser�o interrompidos ao final da
c�pia do arquivo em andamento.

.in
.sp
.b "COMANDOS ACEITOS/N�O ACEITOS PELO SERVIDOR"
.in 5
O servidor reconhece e processa os seguintes comandos:

.sp
.(l
	USER	PASS,	PASV,	ACCT,	CWD,	CDUP,	QUIT,
	PORT,	TYPE,	STRU,	MODE,	RETR,	STOR,	RNFR,
	RNTO,	DELE,	RMD,	MKD,	PWD,	LIST,	LC,
	NLST,	SYST,	STAT,	HELP,	NOOP
.)l

.sp
.(t
O servidor reconhece, mas n�o processa os seguintes comandos:

.sp
.(l
	SMNT,	REIN,	STOU,	APPE,	ALLO,	REST,
	ABOR,	SITE
.)l
.)t

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
tcmpto
.br
.wo "(fmt): "
environ
.br

.in
.sp
.b
REFER�NCIAS
.r
.(l
Postel, J. & Reynolds J.:
"FILE TRANSFER PROTOCOL (FTP), RFC 959",
Outubro de 1985.
.)l

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
