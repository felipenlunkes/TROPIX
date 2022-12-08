.bp
.he 'EDSCB (cmd)'TROPIX: Manual de Refer�ncia'EDSCB (cmd)'
.fo 'Atualizado em 21.10.03'Vers�o 4.5.0'Pag. %'

.b NOME
.in 5
.wo "edscb -"
imprime/edita o bloco de controle do n�cleo do TROPIX
.br

.in
.sp
.b SINTAXE
.in 5
.(l
edscb [-v] [<kernel> [<scbfile> ...] ]
.)l

.in
.sp
.b DESCRI��O
.in 5
O n�cleo do sistema operacional TROPIX cont�m um bloco de controle
(SCB) com diversos par�metros,
cujo objetivo � definir a configura��o do sistema.
Alterando um (ou mais) destes par�metros podemos modificar v�rios
aspectos do sistema operacional,
e deste modo atender a diversos desejos e necessidades.
Os par�metros do SCB s�o descritos em "scb" (fmt).

.sp
O comando "edscb" edita o bloco de controle do n�cleo do TROPIX, cuja
imagem est� no arquivo <kernel>. Se <kernel> n�o for dado, ser�
impresso o bloco de controle do n�cleo em execu��o.

.sp
Se o TROPIX foi instalado em arquivos do MS-DOS, o arquivo contendo
a imagem do n�cleo estar� no disquete BOOT (veja a observa��o, abaixo).

.sp
Se um ou mais arquivos de configura��o <scbfile> forem dados, eles
devem conter comandos de configura��o. Em caso contr�rio, os comandos
de configura��o s�o lidos da entrada padr�o (normalmente o teclado) -
veja o "modo interativo" e "modo n�o-interativo", abaixo.

.sp
Os novos valores dos par�metros somente entrar�o em vigor
ap�s uma nova carga do sistema operacional, e valer�o enquanto
n�o for utilizado novamente o comando "edscb".

.sp
Ap�s a carga, pode ser utilizado o comando "prscb" (cmd)
(que imprime os par�metros em uso efetivo no momento),
para verificar se as modifica��es realizadas atrav�s de "edscb"
foram as desejadas.

.sp
� tamb�m poss�vel alterar os par�metros de forma provis�ria,
durante a carga do sistema, respondendo afirmativamente a pergunta
"Deseja alterar par�metros?".
Estas alterac�es, no entanto, ser�o v�lidas apenas para aquela execu��o
do sistema operacional, j� que � apenas alterada a tabela na mem�ria
interna do computador, e n�o no arquivo imagem do sistema.
 
.sp
Repare que podemos ter v�rias imagens do n�cleo com diversas configura��es
(por exemplo, "/new.tropix", "/big.tropix", ...) e selecionar a configura��o
desejada durante o "boot", escolhendo um dos arquivos.

.sp
No momento (ainda) n�o podemos alterar din�micamente os par�metros. Sempre
necessitamos recarregar o sistema para ativar efetivamente um
SCB modificado.

.bc	/*************************************/
Esta tabela (chamada de SCB, ou seja "system control block") est� contida
na imagem do n�cleo do TROPIX em disco (normalmente o arquivo "/tropix"),
e � copiada para a mem�ria (de onde � consultada) durante o processo
de "boot" (ou seja, a carga do sistema operacional).
.ec	/*************************************/

.sp
As op��es do comando s�o:

.in +3
.ip -v
Verboso.

.ep
.in -3

.in
.sp
.(t
.b "MODO INTERATIVO"
.in 5
Se N�O for dado nenhum arquivo de configura��o <scbfile>, os comandos
de configura��o s�o lidos da entrada padr�o (normalmente teclado).
Neste caso, o comando utiliza o modo interativo, no qual "edscb" imprime uma
tela contendo alguns par�metros,
e em seguida aguarda um comando do usu�rio ap�s o "prompt"
"> ".
.)t

.sp
Como uma tela apenas n�o � suficiente para todos os par�metros, s�o usadas
3 telas: "A", "B" e "C".
Para consultar uma outra tela, basta teclar o nome da tela desejada.

.sp
Um comando da forma "<param>=<valor>" atribui o valor <valor> ao par�metro
<param>. O <valor> pode ser um n�mero decimal, hexadecimal ou octal (de acordo
com a sintaxe de "strtol" (libc)) com o sufixo opcional "k", "K", "m" ou "M" indicando
que o n�mero deve ser multiplicado por 1024 ou (1024 * 1024).

.bc	/*************************************/
Para alterar um par�metro, deve-se dar um comando da forma "<param>=<valor>".
.ec	/*************************************/


.sp
Para encerrar "edscb", com a possibilidade de atualizar o SCB da
imagem do n�cleo, temos os comandos "w" e "q" (ou basta teclar <^D>).
Repare que a imagem do n�cleo s� � atualizada ao final da execu��o
de "edscb", e somente se for respondida afirmativamente
a confirma��o de atualiza��o do arquivo <kernel>.

.in
.sp
.b "MODO N�O-INTERATIVO"
.in 5
Tamb�m � poss�vel ler os comandos de configura��o dos par�metros de um
(ou mais) arquivo(s) de configura��o <scbfile>.
Cada comando deve ser da forma "<param>=<valor>" (ver acima), e dados um por linha.
N�O � necess�rio incluir os comandos "w" ou "q" ao final.

.in
.sp
.b OBSERVA��O
.in 5
Se o TROPIX foi instalado em arquivos do MS-DOS, o arquivo contendo
a imagem do n�cleo estar� no disquete BOOT, e os par�metros do SCB
podem ser modificados do seguinte modo:

.sp
.nf
	mount -w /dev/fd0 /mnt
	edscb /mnt/tropix ... 
	umount /dev/fd0
.fi

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(libc): "
strtol
.br
.wo "(cmd):  "
prscb
.br
.wo "(ref):  "
install
.br
.wo "(fmt):  "
scb
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
