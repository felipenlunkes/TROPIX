.bp
.he 'TEST (cmd)'TROPIX: Manual de Refer�ncia'TEST (cmd)'
.fo 'Atualizado em 24.04.02'Vers�o 4.2.0'Pag. %'

.b NOME
.in 5
.wo "test -"
testa propriedades de arquivos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
test [-o] [-{rwxfdcblpugkms} <arquivo>] ... [-t <fd>] ...
.)l

.in
.sp
.b DESCRI��O
.in 5
O utilit�rio "test" testa diversas propriedades de arquivos,
com a finalidade principal de fornecer um c�digo de retorno
para o comando de programa��o "if" do "sh" (cmd).
 
.sp
Se a express�o (composta do e-�rio ou ou-t�rio das diversas
propriedades testadas) for verdadeira, "test" retorna "0"
(o que � interpretado como verdadeiro pelo "if" do "sh");
no caso contr�rio retorna "1" (o que � interpretado como falso).

.sp
As diversas permiss�es de acesso a arquivos s�o testadas utilizando-se
os UID/GID efetivos (ver "intro" (sys)). Se n�o for dado nenhum
teste de arquivo, o retorno de "test" � falso.

.sp
Se o <arquivo> for um elo simb�lico, a propriedade ser� testada
no alvo referenciado, exceto na op��o "-l" (ver abaixo).

.sp
As op��es do comando s�o:

.in +5
.ip -o 14
Normalmente, � realizado o e-�rio dos diversos testes dos arquivos.
Com esta op��o, � feito um ou-t�rio.
Se usada, esta op��o deve ser a primeira.

.ip '-r <arquivo>' 14
Verdadeiro se o <arquivo> existe, e puder ser lido.

.ip '-w <arquivo>' 14
Verdadeiro se o <arquivo> existe, e puder ser escrito.

.ip '-x <arquivo>' 14
Verdadeiro se o <arquivo> existe, e puder ser executado.

.ip '-f <arquivo>' 14
Verdadeiro se o <arquivo> existe, e for regular.

.ip '-d <arquivo>' 14
Verdadeiro se o <arquivo> existe, e for um diret�rio.

.ip '-c <arquivo>' 14
Verdadeiro se o <arquivo> existe, e for especial de caracteres
(n�o-estruturado).

.ip '-b <arquivo>' 14
Verdadeiro se o <arquivo> existe, e for especial de blocos
(estruturado).

.ip '-l <arquivo>' 14
Verdadeiro se o <arquivo> existe, e for um elo simb�lico.

.ip '-p <arquivo>' 14
Verdadeiro se o <arquivo> existe, e for um FIFO.

.ip '-u <arquivo>' 14
Verdadeiro se o <arquivo> existe, e o bite "set-user-ID" estiver ligado.

.ip '-g <arquivo>' 14
Verdadeiro se o <arquivo> existe, e o bite "set-group-ID" estiver ligado.

.ip '-k <arquivo>' 14
Verdadeiro se o <arquivo> existe, e o bite para guardar
o texto no "swap" estiver ligado.

.ip '-m <arquivo>' 14
Verdadeiro se o <arquivo> existe, e o bite para guardar
o texto na mem�ria estiver ligado.

.ip '-s <arquivo>' 14
Verdadeiro se o <arquivo> existe, e o seu tamanho for maior do que zero.

.ip '-t <fd>' 14
Verdadeiro se o arquivo cujo descritor for <fd> estiver aberto e for um terminal.

.ep
.in -5

.in
.sp
.b OBSERVA��O
.in 5
O teste "-x" apenas consulta os bites correspondentes do modo do arquivo,
n�o garantindo que o referido arquivo possa realmente ser executado.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
sh
.br
.wo "(sys): "
intro
.br

.in
.sp
.b EXEMPLOS
.in 5
O comando
.sp
.nf
		test -f alpha -d dir
.fi

.sp
retorna verdadeiro se "alpha" for um arquivo regular E "dir" um diret�rio. 

.sp
Por outro lado, o comando
.sp
.nf
		test -o -f alpha -d dir
.fi

.sp
retorna verdadeiro se "alpha" for um arquivo regular OU "dir" um diret�rio. 

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
