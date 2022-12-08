.bp
.he 'MAIL (cmd)'TROPIX: Manual de Modifica��es'MAIL (cmd)'
.fo 'Atualizado em 22.01.07'Vers�o 4.9.0'Pag. %'

.b NOME
.in 5
.wo "mail -"
recebe ou envia cartas do correio eletr�nico
.br

.in
.sp 2
.ip "03.12.97  3.0.0" 20
VERS�O CORRENTE
.sp

.ip "07.02.98  3.0.1" 20
Acrescentados os comandos de busca de cadeias e c�pia/movimenta��o
de cartas.

.ip "23.02.98  3.0.2" 20
Agora inicialmente, s� le as informa��es das cartas da �ltima p�gina.
Vai lendo as informa��es das cartas restantes � medida que precisa.
Consertado o pequeno detalhe da cadeia de busca (acrescentado o
"ungetc").

.ip "30.07.98  3.0.3" 20
J� podemos remover, copiar e salvar cartas sem precisar de voltar para o hist�rico.

.ip "26.08.98  3.0.4" 20
Modifica��es: no servidor, aceitar brancos ap�s FROM e RCPT; no cliente, n�o
se atrapalhar quando removeu todas as cartas.

.ip "20.10.98  3.1.0" 20
Foi incorporada a decodifica��o do tempo recebido nas cartas; agora sendo
usado para gerar o nome do arquivo.

.sp
Inclu�do "domain" em ".mailrc".

.ip "30.11.98  3.1.1" 20
Tirado o "quit" quando vem uma desconex�o;
dobrando as linhas das cartas recebidas (cliente).

.ip "07.02.99  3.1.6" 20
Corrigido o ".forward".

.ip "23.08.99  3.2.2" 20
Estava esquecendo de fechar arquivos em "mail_s".

.ip "10.05.00  3.2.3" 20
"send_mail" agora est� ignorando o SIGHUP.
"mail" agora cont�m o comando "r" para responder a uma carta.

.ip "11.10.00  4.0.0" 20
"mail" foi totalmente revisto, agora j� com MIME recursivo (partes dentro
de partes), comandos "r" e "f".

.ip "12.12.00" 20
Consertado o detalhe de uma parte ser uma carta inteira (rfc822).

.ip "20.12.00" 20
Agora, o servidor permite mais de um "MAIL TO:".

.ip "07.03.01" 20
Agora, o servidor permite tamb�m outros nomes de computadores, desde que
o dom�nio esteja correto.

.ip "28.03.01" 20
Consertado um pequeno detalhe em "src/show_direc.c", para o caso da remo��o
da �ltima carta.

.ip "04.04.01" 20
O servidor agora est� verificando se h� espa�o suficiente para o recebimento de cartas.

.ip "11.07.01" 20
Agora, o servidor est� verificando se o ".forward" � recursivo.

.ip "11.08.01" 20
Usando "readdir".

.ip "12.08.01" 20
Introduzida a op��o "-u".

.ip "30.09.01" 20
Corrigido o "mime_2".

.ip "12.07.02  4.3.0" 20
Agora partindo as linhas entre as palavras.

.ip "01.01.03  4.4.0" 20
Usando o arquivo de �ndices "status".

.ip "29.01.03" 20
Agora, mostrando textos codificados em base 64.

.ip "15.04.03" 20
Resolvido o problema do "\r" repetido.

.ip "04.01.07  4.9.0" 20
Resolvidos os problemas do nome do arquivo anexado comprido e dos
caracteres acima de 127 (base 64).

.ip "22.01.07" 20
Colocando as letras em min�sculo do destinat�rio.
