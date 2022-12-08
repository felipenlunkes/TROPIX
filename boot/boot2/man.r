.bp
.he 'FDISK (cmd)'TROPIX: Manual de Refer�ncia'FDISK (cmd)'
.fo 'Atualizado em 13.07.00'Vers�o 4.0.0'Pag. %'

.b NOME
.in 5
.wo "fdisk -"
editor de parti��es dos discos
.br

.in
.sp
.b SINTAXE
.in 5
.(l
-f	(invocado a partir do "boot2")
.)l

.in
.sp
.b DESCRI��O
.in 5
Assim como os outros sistemas operacionais, o TROPIX tamb�m possui o seu
editor de parti��es de discos, que (como � usual) � chamado de "fdisk".

.sp
No entanto, no TROPIX o "fdisk" est� incorporado ao "boot2" (ver "boot" (cmd)),
e s� pode ser executado durante a carga do sistema operacional
(e n�o com o sistema j� executando).
A id�ia � a de ressaltar o fato de que n�o � poss�vel alterar as
parti��es com o sistema em funcionamento.

.sp
Ao ser iniciado, "fdisk" imprime a tabela de parti��es do disco corrente,
que � o primeiro disco IDE ("hda"), ou se n�o houver discos IDE, o primeiro
disco SCSI ("sda").

.sp
Em seguida, "fdisk" aguarda um comando (indicado atrav�s do "prompt" "fdisk> ").
Cada comando inicia em geral um di�logo durante o qual s�o pedidos detalhes
para a sua execu��o.
Durante qualquer um destes di�logos, a resposta "n" cancela o comando.

.sp
Para uma explica��o sobre a "geometria" de um disco, veja a se��o
"GEOMETRIA dos DISCOS", abaixo.

.sp
Os blocos referenciados s�o sempre de 512 bytes.

.sp
Em "install" (ref) h� um exemplo de utiliza��o do "fdisk".

.sp
Repare que a tabela de parti��es residente no disco s� � efetivamente alterada
quando � dado o comando "w". Portanto voc� pode experimentar � vontade, criando,
alterando e removendo parti��es � vontade. Quando estiver finalmente
satisfeito com o resultado, use o comando "w" para gravar no disco a tabela editada.

.sp 2
Os comando de "fdisk" s�o os seguintes:

.in +3
.ip - 4
Imprime a tabela de parti��es do disco corrente:
Inicialmente escreve o nome do disco corrente, a sua geometria (BIOS) e o seu tamanho
(em blocos e MB).
.bc	/*************************************/
A geometria impressa � a que o "fdisk" sup�e ser a correta; em certos
(raros) casos, "fdisk" indica que n�o conseguiu obter a geometria; neste
caso � necess�rio usar o comando "e" (veja abaixo).
.ec	/*************************************/

.sp
Em seguida � impressa a tabela propriamente dita, com uma linha por parti��o.
A tabela cont�m as seguintes colunas:

.in +7
.ip 1. 3
O �ndice da parti��o. Este n�mero � utilizado apenas para referenciar uma
parti��o durante o uso do "fdisk"; n�o confundir com o n�mero da parti��o
(parti��es regulares/estendidas t�m n�meros de 1 a 4).

.ip 2. 3
O nome da parti��o. Durante o uso do TROPIX, cada parti��o � associada a
um dispositivo com o prefixo "/dev/" anteposto ao nome da parti��o.
Assim, por exemplo, a parti��o de nome "hda1" corresponder� ao dispositivo
"/dev/hda1".

.ip 3. 3
Um asterisco se a parti��o est� "ativa", isto �, se � poss�vel carregar
um sistema operacional desta parti��o. Durante o processo de "boot", o
est�gio inicial "boot0" s� considera parti��es "ativas".

.ip 4. 3
Um indicador de desalinhamento (somente se o alinhamente est� ligado, veja
o comando "u" abaixo):
"1" se o in�cio da parti��o estiver desalinhado,
"2" se o final estiver desalinhado e
"3" se ambos estiverem desalinhados.
Se ambos estiverem alinhados, a coluna aparece em branco.

.ip 5. 3
N�mero do bloco inicial da parti��o.

.ip 6. 3
N�mero do bloco final da parti��o.

.ip 7. 3
Tamanho da parti��o em blocos.

.ip 8. 3
Tamanho da parti��o em MB.

.ip 9. 3
Tipo da parti��o. � dado o c�digo num�rico e o tipo simb�lico
(se houver). Veja o comando "t".

.ep
.in -7

.ip p 4
Imprime a tabela de parti��es do disco corrente: este comando �
similar ao anterior, mas s�o tamb�m indicadas (por linhas de pontos)
as �reas vagas do disco (veja tamb�m o comando "s").

.ip c 4
Troca de dispositivo (disco) corrente.

.ip n 4
Cria uma parti��o nova no disco.
� pedido o tipo da parti��o a criar (regular, estendida ou l�gica),
e em seguida inicia um di�logo pedindo caracter�sticas desejadas
da parti��o. As caracter�sticas s�o
influenciadas pelo alinhamento (veja o comando "u").

.ip d 4
Remove uma parti��o do disco.
Se for removida uma parti��o estendida, ser�o removidas todas as parti��es
l�gicas nela contida.

.ip m 4
Altera o tamanho de uma parti��o do disco.
Este comando mant�m o inic�o da parti��o, mas possibilita mudar
o seu final.
Os finais sugeridos/utilizados s�o
influenciados pelo alinhamento (veja o comando "u").

.ip a 4
Troca o estado (ativo/n�o ativo) da parti��o.

.ip l 4
Imprime os tipos/c�digos das parti��es.

.ip t 4
Troca o tipo da parti��o.

.ip s 4
Imprime as �reas vagas do disco.
Se o alinhamento estiver ligado, s� considera �reas de no m�nimo
um cilindro (veja a op��o "p").

.ip u 4
Liga/desliga o alinhamento (come�a ligado):

.sp
Normalmente (isto �, com o alinhamento ligado),
as parti��es regulares e estendidas alocadas por "fdisk"
come�am no in�cio de um cilindro
e terminam no final de um cilindro (isto �, s�o alinhadas em cilindros).

.sp
Exce��es s�o formadas pela primeira parti��o ocupada do disco, que come�a
no in�cio da segunda trilha do disco (para deixar espa�o para a pr�pria
tabela de parti��es do disco), e a �ltima parti��o ocupada, que (opcionalmente)
pode terminar no final do disco.
Este final do disco possivelmente n�o coincide com o final de um cilindro
(isto �, o tamanho do disco pode n�o ser exatamente m�ltiplo do
tamanho de um cilindro).

.sp
Normalmente, as parti��es l�gicas alocadas por "fdisk"
come�am no in�cio da segunda trilha
de um cilindro, e terminam no final de um cilindro.
Esta primeira trilha de uma parti��o l�gica � utilizada para conter um
"ponteiro" para a parti��o l�gica seguinte
(na realidade � utilizado apenas um setor desta trilha).

.sp
Com o alinhamento desligado, "fdisk" n�o realiza nenhum alinhamento,
possibilitando o usu�rio a escolher livremente o in�cio e final de
cada parti��o.

.sp
A utiliza��o do alinhamento como descrito acima, consiste no alocamento
"ortodoxo", que a maioria dos programas de edi��o de parti��es (de outros
sistemas operacionais) tamb�m adota.
A n�o utiliza��o deste esquema de alinhamento pode gerar ganhos
de espa�o (por exemplo quase uma trilha no in�cio de cada parti��o l�gica),
mas pode tamb�m causar problemas para certos sistemas operacionais.
O TROPIX n�o exige nenhum alinhamento das parti��es, mas
antes de criar parti��es desalinhadas para outros sistemas operacionais, 
certifique-se de que ele as suporta.

.bc	/*************************************/
.ip e 4
Altera a geometria do disco:
A geometria do disco consiste de 3 n�meros: o n�mero de trilhas por cilindro
(isto �, o n�mero de cabe�as), o n�mero de setores por trilha e o n�mero de
cilindros.
Estes n�meros s�o usados nas tabelas de parti��es, e s�o relevantes apenas
durante as etapas iniciais do "boot" (rodando no modo de 16 bits),
em que ainda s�o usadas as chamadas de entrada/sa�da da BIOS do PC
(INT 13).


.sp
Um disco IDE possui DUAS geometrias (que podem ser diferentes):
a "real" e a da BIOS. A "geometria real" � a que � usada para dar os comandos
de leitura/escrita nas portas dos controladores IDE. Como os discos
IDE modernos podem ter mais de 1023 cilindros, e a BIOS s� reservou 10 bits
para este campo, foi criado uma "geometria da BIOS" (fict�cia),
com a BIOS encarregando-se de realizar as convers�es
necess�rias. Esta geometria � normalmente chamada de LBA, e cont�m um n�mero
de cabe�as maiores (do que o real) para que o n�mero de cilindros fique abaixo de 1024.

.sp
Na realidade, os discos IDE modernos (assim como os SCSI) usam densidade vari�vel
(isto �, alocam mais setores por trilha na parte externa do que na parte interna), de
tal modo que a "geometria real" dos discos IDE pode tamb�m ser uma fantasia.

.sp
Os discos SCSI n�o possuem "geometria real", isto �, a geometria n�o � usada
nos comandos de leitura/escrita nas portas dos controladores SCSI
(os blocos dos discos SCSI s�o endere�ados linearmente pelo pr�prio n�mero do bloco).
Estes discos recebem geometrias "de fantasia" (normalmente
de 64 cabe�as/32 setores por trilha para discos at� de 1 GB,
e 255 cabe�as/63 setores por trilha para discos acima de 1 GB).
Isto � necess�rio para satisfazer as chamadas da BIOS.

.sp
� preciso salientar que nos PC modernos, cada disco possui DUAS geometrias
(que podem ser diferentes): a REAL e a da BIOS.
A geometria real � a que � usada para dar os comandos nas portas dos
controladores IDE

.sp
Apenas os discos IDE possuem uma geo

.sp
No passado, estes n�meros correspondiam � geometria real do disco, que realmente
tinha estes n�meros de cabe�as, setores, cilindros, etc ..., e durante um comando
de entrada/sa�da os n�meros s�o usados.
Nos discos IDE modernos (em geral usando um esquema LBA), assim como nos
discos SCSI, estes 3 n�meros s�o apenas "fantasias" para satisfazer o modo
de chamar as fun��es de entrada/sa�da da BIOS.

.sp
O "boot2" do TROPIX quase sempre consegue obter a geometria correta do disco,
a partir de uma tabela de parti��o j� existente, ou da tabela contida na
mem�ria CMOS do PC (que � atribu�da/alterada atrav�s do "setup" do PC).
No caso de discos SCSI (se for necess�rio), s�o usados os valores
(fict�cios) descritos acima.

.sp
Naturalmente, a geometria utilizada pelo "fdisk" deve ser id�ntica �
geometria usada pela BIOS do PC.
H� somente um caso em que o TROPIX n�o consegue obter a geometria correta:
no caso de um disco IDE rec�m-instalado (isto �, ainda sem tabela de parti��es),
conectado ao segundo controlador IDE. Neste caso � necess�rio utilizar o
comando "e" para escolher entre as v�rias propostas de geometria, ou ainda,
se for necess�rio, dar manualmente os valores corretos da geometria.
.ec	/*************************************/

.ip w 4
Reescreve (atualiza) a tabela de parti��es no disco.

.ip q 4
Termina a execu��o do editor de parti��es, retornando ao "boot2".
Mesmo que tabelas de parti��es tenham sido alteradas,
� poss�vel continuar com o processo de carga do TROPIX
(ele ir� receber as tabelas atualizadas).
N�O � necess�rio dar novo "boot".

.ep
.in -3

.in
.sp
.b "GEOMETRIA dos DISCOS"
.in 5
A geometria do disco consiste de 3 n�meros: o n�mero de trilhas por cilindro
(isto �, o n�mero de cabe�as), o n�mero de setores por trilha e o n�mero de
cilindros.
Estes n�meros s�o usados nas tabelas de parti��es, e s�o relevantes apenas
durante as etapas iniciais do "boot" (rodando no modo de 16 bits),
em que ainda s�o usadas as chamadas de entrada/sa�da da BIOS do PC
(INT 13).

.sp
Originalmente, as opera��es de leitura/escrita atrav�s da INT 13 eram feitas
atrav�s da tripla (cabe�a, setor, cilindro).
A geometria definida para a INT 13 limitava o n�mero de
cabe�as a 255, o n�mero de setores por trilha a 63 e o n�mero de cilindros
a 1024. Com isto, havia um limite de (aproximadamente) 8 GB, ap�s o qual n�o
se conseguia acessar os discos.

.sp
Em meados de 1995 foram criadas "extens�es" para 
a INT 13, atrav�s das quais � dado o n�mero linear do bloco do disco (de 64 bits),
ao inv�s da tripla (cabe�a, setor, cilindro). Com isto, acabou-se
com o limite de 8 GB, al�m da "geometria" do disco ficar irrelevante.

.sp
Se o seu computador possuir estas extens�es, voc� poder� dar "boot" em
parti��es acima do limite de 8 GB. Para verificar se � o caso, use o comando
"prdisktb" (cmd), ou ent�o verifique em "boot0", durante a carga do sistema.
Al�m disto, atrav�s de "edboot" (cmd), voc� poder� verificar se est� instalado
o "boot1" adequado.

.sp
Normalmente, o TROPIX consegue obter a geometria dos discos atrav�s
de consulta � pr�pria BIOS. Quando isto n�o � poss�vel, ele tenta
calcular a geometria atrav�s de parti��es j� existentes na tabela
de parti��es. Se n�o conseguir � impressa uma mensagem de erro, e neste
caso N�O � prudente usar o "fdisk".

.in
.sp
.(t
.b
VEJA TAMB�M
.r
.in 5
.wo "(cmd): "
boot, prdisktb, edboot
.br
.wo "(ref): "
install
.br
.)t

.in
.sp
.b ARQUIVOS
.in 5
/boot

.in
.sp
.b ESTADO
.in 5
Efetivo.

.in
