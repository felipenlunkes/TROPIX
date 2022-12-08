.bp
.he 'XDEFRAG (cmd)'TROPIX: Manual de Refer�ncia'XDEFRAG (cmd)'
.fo 'Atualizado em 03.11.03'Vers�o 4.5.0'Pag. %'

.b NOME
.in 5
.(l
xdefrag - melhora a aloca��o dos blocos de sistemas de arquivos
.)l

.in
.sp
.b SINTAXE
.in 5
.(l
xdefrag [-r] [-g <geo>] [-f <frente>] [-b <fundo>]
					[-d <video>] [-F <fonte>]
.)l

.in
.sp
.b DESCRI��O
.in 5
O comando gr�fico "xdefrag" tenta melhorar a aloca��o dos blocos
de sistemas de arquivos T1.

.sp
� medida em que um sistema de arquivos vai sendo usado
(isto �, arquivos v�o sendo criados e removidos),
h� uma tend�ncia natural de os blocos dos arquivos novos n�o serem
alocados contiguamente no disco. Isto acarreta um tempo maior no
acesso a estes arquivos, pois o bra�o do disco ter� de executar movimentos
maiores para ler/escrever cada um dos blocos do arquivo
(que estar�o espalhados pelo disco).

.sp
O comando "xdefrag" tenta realocar os blocos
dos sistemas de arquivos para que os blocos de dados e endere�os de um mesmo
arquivo fiquem cont�guos e sequenciais (isto �, "compactados").
.bc	/*************************************/
Repare que esta vers�o de "xdefrag" N�O realoca os blocos de n�s-�ndice.
.ec	/*************************************/

.sp
Ele oferece tres m�todos para a realoca��o dos blocos
(que podem ser selecionados no bot�o "op��es", veja abaixo):

.in +3
.ip 1. 3
Apenas os arquivos: � feita uma an�lise arquivo a arquivo, e somente s�o
realocados os blocos dos arquivos que n�o est�o compactados.
Este m�todo � o mais simples e r�pido, e normalmente � suficiente.
No entanto (possivelmente), ir� deixar regi�es com blocos n�o alocados
entre os arquivos (lacunas).
Al�m disto, n�o s�o realocados os blocos de n�s-�ndice.

.ip 2. 3
Arquivos e lacunas: Este m�todo � uma extens�o do m�todo anterior para
tentar eliminar (ou pelo menos reduzir) as lacunas.

Como acima, n�o s�o realocados os blocos de n�s-�ndice.

.ip 3. 3
Completo: A �rvore do sistema de arquivos � caminhada em profundidade,
realocando todos os diret�rios, arquivos e n�s-�ndices.
Este m�todo � o mais demorado, mas tem a vantagem
de eliminar inteiramente as lacunas.
.sp
Al�m disto, s�o feitos esfor�os para que
os n�s-�ndices fiquem pr�ximos dos diret�rios que os referenciam,
e os blocos dos arquivos pr�ximos aos seus respectivos n�s-�ndice.

.ep
.in -3

.in
.sp
.b 'DISPOSI��O DAS JANELAS'
.in 5
O programa "xdefrag" cont�m (de cima para baixo) as seguintes janelas:

.in +3
.ip 1. 3
Janela de bot�es: op��es (veja acima), analisa o sistema de arquivos, desfragmenta
o sistema de arquivos e encerra a execu��o do programa.

.ip 2. 3
Janela de dispositivos:
A primeira coluna cont�m um c�digo de cores, que significa:

.in +5
.ip Vermelho: 10
Sistema de arquivos N�O dispon�vel (n�o pronto, n�o � um sistema de arquivos T1):
N�O pode ser analisado nem compactado.

.bc	/*************************************/
Sistema de arquivos N�O dispon�vel (n�o pronto, n�o pode ser desmontado,
dispositivo permite apenas leituras,
n�o � um sistema de arquivos T1).
.ec	/*************************************/

.ip Amarelo: 10
Sistema de arquivos montado, dispositivo permite apenas leituras:
pode ser analisado mas N�O compactado.

.ip Preto: 10
Sistema de arquivos dispon�vel para ser analisado e compactado.

.ip Verde: 10
Sistema de arquivos escolhido para a an�lise e (possivelmente) a compacta��o.

.in -5
.ep

.in +3
.bc	/*************************************/
.sp
Cada vez que o bot�o de um dispositivo � clicado, o seu estado � reavaliado
(por exemplo, se ele foi montado/desmontado, ou se passou a permitir a escrita).
.ec	/*************************************/

.sp
As colunas seguintes cont�m as seguintes infoma��es: nome do dispositivo
(sem "/dev"), nome contido no sistema de arquivos, tamanho do sistema de
arquivos, e estado do dispositivo.
.in -3

.ip 3. 3
Janela de informa��es sobre o sistema de arquivos escolhido:
cont�m estat�sticas sobre quantos arquivos/blocos ser�o atualizados.

.ip 4. 3
Janela de aloca��o dos blocos antes da compacta��o:
barras vermelhas indicam regi�es mal alocadas (que ser�o movidas),
barras azuis indicam regi�es que j� est�o compactadas e
barras pretas indicam regi�es n�o alocadas.

.ip 5. 3
Janela de aloca��o dos blocos durante/depois da compacta��o:
como acima.

.ip 6. 3
Barra de progresso: as barras verdes indicam a fra��o j� processada.

.ep
.in -3

.in
.sp
.b 'MODO de USO'
.in 5
Antes de usar o utilit�rio "xdefrag", devemos verificar a integridade dos sistemas
de arquivos que desejamos desfragmentar (atrav�s de "fsck" (cmd)).

.sp
Em seguida, podemos seguir os seguintes passos:

.in +3
.ip 1. 3
Selecionar o dispositivo contendo o sistema de arquivos
a desfragmentar. Isto � realizado clicando o dispositivo desejado na janela de dispositivos.
Cada vez que o bot�o de um dispositivo � clicado, o seu estado � reavaliado
(por exemplo, se ele foi montado/desmontado, ou se passou a permitir a escrita).

.ip 2. 3
Escolher o m�todo desejado
(Apenas os arquivos, Arquivos e lacunas ou completo), veja acima.

.ip 3. 3
Clicar em "an�lise", quando obteremos uma no��o gr�fica do estado
do sistema de arquivos e tamb�m uma estat�stica de quantos arquivos/blocos ser�o
movidos/modificados.

.ip 4. 3
Clicar em "desfragmenta" (se for permitido no caso),
e poderemos acompanhar o progresso da compacta��o na janela inferior.

.ep
.in -3

.in
.sp
.b 'OP��ES DO COMANDO'
.in 5
.in +3
.ip -r
N�o modifica o sistema de arquivos. Realiza todas as opera��es, mas n�o escreve
os blocos do dispositivo (para testes).

.ip -g
Fornece a geometria inicial (em pixeis), no formato <largura>x<altura>.

.ip -f
Use a cor de <frente> dada.

.ip -b
Use a cor de <fundo> dada.

.ip -d
Conecte-se ao <v�deo> dado.

.ip -F
Use a <fonte> dada.

.ep
.in -3

.in
.sp
.b OBSERVA��ES
.in 5
� fundamental verificar a integridade do sistema de arquivos (atrav�s de "fsck" (cmd))
antes da desfragmenta��o. O uso de "xdefrag" em um sistema de arquivos com erros
poder� causar-lhe danos imprevis�veis.

.sp
A utiliza��o do comando "xdefrag" � uma opera��o potencialmente
perigosa, pois em caso de interrup��o da energia el�trica,
provavelmente todo o conte�do do sistema de arquivos ser� perdido.

.in
.sp
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
mkfs, fsck
.br

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
